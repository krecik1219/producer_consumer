#include "CProducer.h"

CProducer::CProducer(int iNumber, CBuffer & cBuffer) :
i_number(iNumber), c_buffer(&cBuffer), b_is_producing(false)
{

}

CProducer::~CProducer()
{
	if(c_producer_thread.joinable())
		c_producer_thread.join();
}

void CProducer::vProduce(int iProducingTime, int iRepetitions)
{
	if(!b_is_producing)
	{
		b_is_producing = true;
		c_producer_thread = std::thread(&CProducer::v_aux_produce, this, iProducingTime, iRepetitions);
	}
}

void CProducer::v_aux_produce(int iProducingTime, int iRepetitions)
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

void CProducer::vExplicitJoin()
{
	if(c_producer_thread.joinable())
		c_producer_thread.join();
}


