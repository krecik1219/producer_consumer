#ifndef SRC_CPRODUCER_H_
#define SRC_CPRODUCER_H_

#include <thread>
#include "CSynchConsoleOut.h"
#include "CBuffer.h"

class CProducer
{
public:
	CProducer(int iNumber, CBuffer & cBuffer);

	void vProduce(int iProducingTime, int iRepetitions);

private:

	int i_number;

	CBuffer * const c_buffer;

};


#endif /* SRC_CPRODUCER_H_ */
