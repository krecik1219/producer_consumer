#ifndef SRC_CPRODUCER_H_
#define SRC_CPRODUCER_H_

#include <thread>
#include "CSynchConsoleOut.h"
#include "CBuffer.h"

class CProducer
{
public:
	CProducer(int iNumber, CBuffer * const cBuffer, int iProducingTime, int iRepetitions);
	CProducer(CProducer const & cOther) = delete;  // copy construction may not be deterministic and lead to errors
	CProducer & operator=(CProducer const & cOther) = delete;  // copy-assignment may be dangerous while producer is producing
	// move constructor is pointless, move operator= is dangerous as the copy operator=, these functions won't be generated

	~CProducer();

	void vProduce();
	void vExplicitJoin();

private:

	void v_aux_produce();

	int i_number;
	CBuffer * const pc_buffer;
	int i_producing_time;
	int i_repetitions;
	bool b_is_producing;
	std::thread c_producer_thread;
};


#endif /* SRC_CPRODUCER_H_ */
