#ifndef SRC_CPRODUCER_H_
#define SRC_CPRODUCER_H_

#include <thread>
#include "CSynchConsoleOut.h"
#include "CBuffer.h"

class CProducer
{
public:
	CProducer(int iNumber, CBuffer * const cBuffer, int iProducingTime, int iRepetitions);
	~CProducer();

	CProducer(CProducer const & cOther) = delete;
	CProducer & operator=(CProducer const & cOther) = delete;

	void vProduce();
	void vExplicitJoin();

private:

	void v_aux_produce();

	int i_number;
	CBuffer * const c_buffer;
	int i_producing_time;
	int i_repetitions;
	bool b_is_producing;
	std::thread c_producer_thread;
};


#endif /* SRC_CPRODUCER_H_ */
