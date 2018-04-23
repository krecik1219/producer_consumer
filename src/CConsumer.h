#ifndef SRC_CCONSUMER_H_
#define SRC_CCONSUMER_H_

#include <thread>
#include "CSynchConsoleOut.h"
#include "CBuffer.h"

class CConsumer
{
public:
	CConsumer(int iNumber, CBuffer * const cBuffer, int iConsumeInterval, int iRepetitions, int iElementsPerConsume);
	~CConsumer();

	CConsumer(CConsumer const & cOther) = delete;
	CConsumer & operator=(CConsumer const & cOther) = delete;

	void vConsume();
	void vExplicitJoin();

private:

	void v_aux_consume();

	int i_number;
	CBuffer * const c_buffer;
	int i_consume_interval;
	int i_repetitions;
	int i_elements_per_consume;
	bool b_is_consuming;
	std::thread c_consumer_thread;
};


#endif /* SRC_CCONSUMER_H_ */
