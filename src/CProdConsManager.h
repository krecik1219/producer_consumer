#ifndef SRC_CPRODCONSMANAGER_H_
#define SRC_CPRODCONSMANAGER_H_

#include "CBuffer.h"
#include "CProducer.h"
#include "CConsumer.h"
#include <vector>

using namespace std;

enum class CProdConsError;

class CProdConsManager
{
public:
	CProdConsManager();
	CProdConsManager(CProdConsManager const & cOther) = delete;  // copy construction is nonsense because of not copy-able member vars
	CProdConsManager & operator=(CProdConsManager const & cOther) = delete;  // copy assignment is nonsense because of not copy-able member vars
	~CProdConsManager();

	bool bCreateBuffer(int iBufferSize);
	void vCreateProducer(int iProducingTime, int iRepetitions);
	void vCreateConsumer(int iConsumeInterval, int iRepetitions, int iElementsPerConsume);
	CProdConsError vStartTest();
	void vRunSampleTest();
	void vResetManager();

private:

	void v_explicit_join();

	unique_ptr<CBuffer> pc_buffer;
	typedef unique_ptr<CProducer> producer;
	typedef unique_ptr<CConsumer> consumer;
	vector<producer> v_producers;
	vector<consumer> v_consumers;
	int i_producers_count;
	int i_consumers_count;
};

enum class CProdConsError
{
	ERR_OK = 0,
	ERR_NO_CONSUMER = 1,
	ERR_NO_PRODUCER = 2,
	ERR_NO_BUFFER = 3,
};

#endif /* SRC_CPRODCONSMANAGER_H_ */
