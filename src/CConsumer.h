#ifndef SRC_CCONSUMER_H_
#define SRC_CCONSUMER_H_

#include <thread>
#include "CSynchConsoleOut.h"
#include "CBuffer.h"

class CConsumer
{
public:
	CConsumer(int iNumber, CBuffer & cBuffer);
	~CConsumer();

	CConsumer(CConsumer const & cOther) = delete;
	CConsumer & operator=(CConsumer const & cOther) = delete;

	void vConsume(int iConsumeInterval, int iRepetitions, int iElementsPerConsume);
	void vExplicitJoin();

private:

	void v_aux_consume(int iConsumeInterval, int iRepetitions, int iElementsPerConsume);

	int i_number;
	CBuffer * const c_buffer;
	bool b_is_consuming;
	std::thread c_consumer_thread;
};


#endif /* SRC_CCONSUMER_H_ */
