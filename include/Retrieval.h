//#include "retrieval.h"
#include <boost/thread.hpp>
#include <boost/threadpool.hpp>
#include <vector>
#include "RetrievalDatabase.h"
#include "SemanticDatabase.h"
#define RETRIVAL_COUNT 50

using namespace std;

struct RetrievalItem {
	string id;
	vector<string> label;
	double score;

	bool operator<(const RetrievalItem& other) const
	{
		return this->score < other.score;
	}
};

class Retrieval{
public:
	// Constructors
	Retrieval(double g1 = 0.1, double g2 = 0, double b = 1e-5);
	Retrieval(const Retrieval& other);
	// Functionality Methods

	// Testing Methods
	double TestSingle(const RetrievalDatabaseItem& query);
	double TestAll(const RetrievalDatabase& query);
	double TestGiven(const string& id);
	double TestN(const RetrievalDatabase& query , int n = 1, int begin = 0);
	double ParrallelTestN(const RetrievalDatabase& queries, int n = 1, int begin = 0);
	double ParrallelTestAll(const RetrievalDatabase& queries);

	// Process Query
	vector<string> processQuery(Mat queryFea, int topNum);

	// Property Access Methods
	double Gamma1() const;
	void Gamma1(double val);

	double Gamma2() const;
	void Gamma2(double val);

	double Beta() const;
	void Beta(double val);

	RetrievalDatabase* RDb() const;
	void RDb(RetrievalDatabase* val);

	SemanticDatabase * Sdb() const;
	void Sdb(SemanticDatabase * val);

	int ThreadNum() const;
	void ThreadNum(int val);

	void setParallel(int q, int s = 1);

	bool IsParallel() const;
	void IsParallel(bool val);

	void loadConfigFile(const string& filename);
	void saveConfigFile(const string& filename);



protected:
	// Parameter
	double gamma1;// = 0.1;
	double gamma2;// = 0;
	double beta;// = 1e-5;

	Mat sigma;
	Mat f;
	Mat W;

	// Configuration
	bool isParallel;
	int parallelScoreNum;
	int parallelQueryNum;

	RetrievalDatabase *rdb;
	SemanticDatabase *sdb;

	// Thread stuff

	void initializeSemantic();

	vector<RetrievalItem> retrieve( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabase& database );
	vector<RetrievalItem> parallelRetrieve( const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabase& database );

	void parallelRetrieveScoreThread(const InputArray& queryFea, const InputArray& codebook, const RetrievalDatabaseItem db_it, vector<RetrievalItem> *retrievalList);
	void parallelRetrieveThread(RetrievalDatabaseItem query, double* ret_precision);
	void loadDefaultConfig();

	boost::mutex retrieval_list_mutex;
	boost::mutex retrieval_precision_mutex;
};
