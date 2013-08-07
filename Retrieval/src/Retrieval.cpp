#include "Retrieval.h"
#include "IO.h"
#include "SCC.h"

using namespace SCC;
using namespace IOUtils;
using namespace boost;

Retrieval::Retrieval( double g1 /*= 0.1*/, double g2 /*= 0*/, double b /*= 1e-5*/ )
	:gamma1(g1), gamma2(g2), beta(b)
{
	parallelScoreNum = 1;
}

Retrieval::Retrieval(const Retrieval& other)
{
	gamma1 = other.gamma1;
	gamma2 = other.gamma2;
	beta = other.beta;
	rdb = other.rdb;
	sdb = other.sdb;
}

double Retrieval::Gamma1() const
{
	return gamma1;
}

void Retrieval::Gamma1( double val )
{
	gamma1 = val;
}

double Retrieval::Gamma2() const
{
	return gamma2;
}

void Retrieval::Gamma2( double val )
{
	gamma2 = val;
}

double Retrieval::Beta() const
{
	return beta;
}

void Retrieval::Beta( double val )
{
	beta = val;
}

RetrievalDatabase* Retrieval::RDb() const
{
	return rdb;
}

void Retrieval::RDb( RetrievalDatabase* val )
{
	rdb = val;
}

vector<string> Retrieval::processQuery(Mat queryFea, int topNum)
{
	auto neighbour = semantic_neighbours(queryFea, f, W, sigma, beta, gamma1, gamma2);
	Mat cb = neighbour.at(0);
	Mat sou = neighbour.at(2);
	printf("%d Semantic neighbour retrieved\n", cb.cols);
	vector<RetrievalItem> result;
	vector<string> topNId(topNum);
	if (parallelScoreNum > 1)
		result = parallelRetrieve(sou, cb, *rdb);
	else
		result = retrieve(sou, cb, *rdb);
 
	for (int i = 0; i < topNum && i < result.size(); i++)
	{
		topNId[i] = result[i].id;
	}
	return topNId;
}

double Retrieval::TestSingle( const RetrievalDatabaseItem& query  )
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

double Retrieval::TestAll( const RetrievalDatabase& database )
{
	double precision = 0.0;

	for (auto query : database)
	{
		precision += TestSingle(query.second);
	}
	precision /= database.size();
	return precision;
}

void Retrieval::loadDefaultConfig()
{
	
}

vector<RetrievalItem> Retrieval::retrieve( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabase& database )
{
	vector<RetrievalItem> retrievalList;
	retrievalList.reserve(database.size());

	int count = 0;
	for(auto db_it = database.begin(); db_it != database.end(); db_it++, count++)
	{
		RetrievalItem item;
		item.id = db_it->second.id;
		item.label = db_it->second.label;
		item.score = retrievalScore(queryFea, db_it->second.feature, codebook);
		retrievalList.push_back(item);
		if (!isParallel && count % 50 == 0)
			printf(".");
	}
	sort(retrievalList.begin(), retrievalList.end());
	return retrievalList;
}


vector<RetrievalItem> Retrieval::parallelRetrieve( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabase& database )
{
	vector<RetrievalItem> retrievalList;
	retrievalList.reserve(database.size());
	boost::threadpool::pool threaP(parallelScoreNum);

	Mat cbM = codebook.getMat();
	Mat qfM = queryFea.getMat();

	for(auto db_it = database.begin(); db_it != database.end(); db_it++)
	{
		auto thread = boost::bind(&Retrieval::parallelRetrieveScoreThread, this, queryFea, codebook, db_it->second, &retrievalList);
		threaP.schedule(thread);
		threaP.wait(parallelScoreNum + 1);
	}
	threaP.wait(0);
	sort(retrievalList.begin(), retrievalList.end());
	return retrievalList;
}


void Retrieval::parallelRetrieveScoreThread( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabaseItem db_it, vector<RetrievalItem> *retrievalList )
{
	RetrievalItem item;
	item.id = db_it.id;
	item.label = db_it.label;
	item.score = retrievalScore(queryFea, db_it.feature, codebook);

	retrieval_list_mutex.lock();
	retrievalList->push_back(item);
	retrieval_list_mutex.unlock();
}

void Retrieval::parallelRetrieveThread( RetrievalDatabaseItem query, double* ret_precision )
{
	double result = TestSingle(query);
	retrieval_precision_mutex.lock();

	*ret_precision += result;

	retrieval_precision_mutex.unlock();
}



double Retrieval::TestGiven( const string& id )
{
	auto sub = rdb->operator[](id);
	return TestSingle(sub);
}

double Retrieval::TestN( const RetrievalDatabase& query , int n /*= 1*/, int begin /*= 0*/ )
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

double Retrieval::ParrallelTestAll( const RetrievalDatabase& queries )
{
	isParallel = true;
	double precision = 0.0;
	auto db_it = queries.begin();
	boost::threadpool::pool threadp(parallelQueryNum);

	for (;db_it != queries.end(); db_it++)
	{
		threadp.schedule(boost::bind<void>(&Retrieval::parallelRetrieveThread, this, db_it->second, &precision));
		threadp.wait(parallelQueryNum * 2 + 1);
	}
	threadp.wait(0);
	return precision / queries.size();
}


double Retrieval::ParrallelTestN( const RetrievalDatabase& queries, int n /*= 1*/, int begin /*= 0*/ )
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
		threadp.schedule(boost::bind<void>(&Retrieval::parallelRetrieveThread, this, db_it->second, &precision));
		threadp.wait(parallelQueryNum * 2 + 1);
	}
	threadp.wait(0);
	return precision / count;
}

bool Retrieval::IsParallel() const
{
	return isParallel;
}

void Retrieval::IsParallel( bool val )
{
	isParallel = val;
}

void Retrieval::loadConfigFile( const string& filename )
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

void Retrieval::saveConfigFile( const string& filename )
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

SemanticDatabase * Retrieval::Sdb() const
{
	return sdb;
}

void Retrieval::Sdb( SemanticDatabase * val )
{
	sdb = val;
	initializeSemantic();
}

void Retrieval::initializeSemantic()
{
	W = sdb->getRelationMatrix();
	f = sdb->getFeatureMatrix();
	sigma = Mat::eye(W.size(), W.type());
}

void Retrieval::setParallel( int q, int s )
{
	parallelQueryNum = q;
	parallelScoreNum = s;
}