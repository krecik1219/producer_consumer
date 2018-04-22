#include "CProducer.h"

CProducer::CProducer(int iNumber, CBuffer & cBuffer) :
i_number(iNumber), c_buffer(&cBuffer)
{

}

void CProducer::vProduce(int iProducingTime, int iRepetitions)
{
	CSynchConsoleOut & out = CSynchConsoleOut::pcGetInstance();
	for(int i = 0; i < iRepetitions; ++i)
	{
		out<<"Producer " + std::to_string(i_number)+" is sleeping for "+std::to_string(iProducingTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(iProducingTime));
		out<<"Producer "+std::to_string(i_number)+" is putting elem ";
		c_buffer->vPut(i);  // putting loop var to buffer, can by any number
		out<<"Producer "+std::to_string(i_number)+" produced element ";
	}
	out<<"Producer "+std::to_string(i_number)+" finished its job ";
}



