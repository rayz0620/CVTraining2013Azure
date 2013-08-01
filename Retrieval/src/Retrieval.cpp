#include "Retrieval.h"
#include "IO.h"
#include "SCC.h"

using namespace SCC;
using namespace IOUtils;
using namespace boost;

Retrival::Retrival( double g1 /*= 0.1*/, double g2 /*= 0*/, double b /*= 1e-5*/ )
	:gamma1(g1), gamma2(g2), beta(b)
{
	parallelScoreNum = 1;
}


double Retrival::Gamma1() const
{
	return gamma1;
}

void Retrival::Gamma1( double val )
{
	gamma1 = val;
}

double Retrival::Gamma2() const
{
	return gamma2;
}

void Retrival::Gamma2( double val )
{
	gamma2 = val;
}

double Retrival::Beta() const
{
	return beta;
}

void Retrival::Beta( double val )
{
	beta = val;
}

RetrievalDatabase* Retrival::RDb() const
{
	return rdb;
}

void Retrival::RDb( RetrievalDatabase* val )
{
	rdb = val;

}

double Retrival::TestSingle( const RetrievalDatabaseItem& query  )
{
	double currentPrecision = 0.0;
	int scope = 0;
	auto neighbour = semantic_neighbours(query.feature, f, W, sigma, beta, gamma1, gamma2);
	Mat cb = neighbour.at(0);
	Mat sou = neighbour.at(2);

	vector<RetrievalItem> result;

	if (parallelScoreNum > 1)
		result = parallelRetrieve(sou, cb, *rdb);
	else
		result = retrieve(sou, cb, *rdb);

	for (int i = 0; i < RETRIVAL_COUNT; i++)
	{
		if (query.label[0] == result[i].label[0] && query.id != result[i].id)
			scope++;
	}
	currentPrecision = (double)scope / RETRIVAL_COUNT;
	printf("%s: Precision: %lf\n", query.id.c_str(), currentPrecision);
	return currentPrecision;
}

double Retrival::TestAll( const RetrievalDatabase& database )
{
	double precision = 0.0;

	for (auto query : database)
	{
		precision += TestSingle(query.second);
	}
	precision /= database.size();
	return precision;
}

void Retrival::loadDefaultConfig()
{
	
}

vector<RetrievalItem> Retrival::retrieve( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabase& database )
{
	vector<RetrievalItem> retrievalList;
	retrievalList.reserve(database.size());

	int count = 0;
	for(auto db_it = database.begin(); db_it != database.end(); db_it++, count++)
	{
		RetrievalItem item;
		item.id = db_it->first;
		item.label = db_it->second.label;
		item.score = retrievalScore(queryFea, db_it->second.feature, codebook);
		retrievalList.push_back(item);
		if (!isParallel && count % 50 == 0)
			printf(".");
	}
	sort(retrievalList.begin(), retrievalList.end());
	return retrievalList;
}


vector<RetrievalItem> Retrival::parallelRetrieve( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabase& database )
{
	vector<RetrievalItem> retrievalList;
	retrievalList.reserve(database.size());
	boost::threadpool::pool threaP(parallelScoreNum);

	Mat cbM = codebook.getMat();
	Mat qfM = queryFea.getMat();

	for(auto db_it = database.begin(); db_it != database.end(); db_it++)
	{
		auto thread = boost::bind(&Retrival::parallelRetrieveScoreThread, this, queryFea, codebook, db_it->second, &retrievalList);
		threaP.schedule(thread);
		threaP.wait(parallelScoreNum + 1);
	}
	threaP.wait(0);
	sort(retrievalList.begin(), retrievalList.end());
	return retrievalList;
}


void Retrival::parallelRetrieveScoreThread( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabaseItem db_it, vector<RetrievalItem> *retrievalList )
{
	RetrievalItem item;
	item.id = db_it.id;
	item.label = db_it.label;
	item.score = retrievalScore(queryFea, db_it.feature, codebook);

	retrieval_list_mutex.lock();
	retrievalList->push_back(item);
	retrieval_list_mutex.unlock();
}

void Retrival::parallelRetrieveThread( RetrievalDatabaseItem query, double* ret_precision )
{
	double result = TestSingle(query);
	retrieval_precision_mutex.lock();

	*ret_precision += result;

	retrieval_precision_mutex.unlock();
}



double Retrival::TestGiven( const string& id )
{
	auto sub = rdb->operator[](id);
	return TestSingle(sub);
}

double Retrival::TestN( const RetrievalDatabase& query , int n /*= 1*/, int begin /*= 0*/ )
{
	double precision = 0.0;
	auto it = query.begin();
	for (int count = 0; count < begin; count++)
		it++;
	int count = 0;
	for (; count < n && it != query.end(); count++, it++)
	{
		precision += TestSingle(it->second);
	}
	precision /= count;
	return precision;
}

double Retrival::ParrallelTestAll( const RetrievalDatabase& queries )
{
	isParallel = true;
	double precision = 0.0;
	auto db_it = queries.begin();
	boost::threadpool::pool threadp(parallelQueryNum);

	for (;db_it != queries.end(); db_it++)
	{
		threadp.schedule(boost::bind<void>(&Retrival::parallelRetrieveThread, this, db_it->second, &precision));
		threadp.wait(parallelQueryNum * 2 + 1);
	}
	threadp.wait(0);
	return precision / queries.size();
}


double Retrival::ParrallelTestN( const RetrievalDatabase& queries, int n /*= 1*/, int begin /*= 0*/ )
{
	isParallel = true;
	double precision = 0.0;
	auto db_it = queries.begin();
	boost::threadpool::pool threadp(parallelQueryNum);

	for (int i = 0; i < begin; i++)
		db_it++;

	int count = 0;

	printf("Testing %d queries parallely\n", n);

	for (;count < n && db_it != queries.end(); count++, db_it++)
	{
		threadp.schedule(boost::bind<void>(&Retrival::parallelRetrieveThread, this, db_it->second, &precision));
		threadp.wait(parallelQueryNum * 2 + 1);
	}
	threadp.wait(0);
	return precision / count;
}

bool Retrival::IsParallel() const
{
	return isParallel;
}

void Retrival::IsParallel( bool val )
{
	isParallel = val;
}

void Retrival::loadConfigFile( const string& filename )
{
	FileStorage file(filename, FileStorage::READ);
	string auxDBPath, mainDBPath;
	if (file.isOpened())
	{
		file["beta"] >> beta;
		file["gamma1"] >> gamma1;
		file["gamma2"] >> gamma2;
		file["parallelQueryNum"] >> parallelQueryNum;
		file["parallelScoreNum"] >> parallelScoreNum;
	}
}

void Retrival::saveConfigFile( const string& filename )
{
	FileStorage file(filename, FileStorage::WRITE);
	if (file.isOpened())
	{
		file << "beta" << beta;
		file << "gamma1" << gamma1;
		file << "gamma2" << gamma2;
		file << "parallelQueryNum" << parallelQueryNum;
		file << "parallelScoreNum" << parallelScoreNum;
	}
}

SemanticDatabase * Retrival::Sdb() const
{
	return sdb;
}

void Retrival::Sdb( SemanticDatabase * val )
{
	sdb = val;
	initializeSemantic();
}

void Retrival::initializeSemantic()
{
	W = sdb->getRelationMatrix();
	f = sdb->getFeatureMatrix();
	sigma = Mat::eye(W.size(), W.type());
}

void Retrival::setParallel( int q, int s )
{
	parallelQueryNum = q;
	parallelScoreNum = s;
}
