#include "CProducer.h"

CProducer::CProducer(int iNumber, CBuffer * const cBuffer, int iProducingTime, int iRepetitions) :
i_number(iNumber), c_buffer(cBuffer), b_is_producing(false),
i_producing_time(iProducingTime), i_repetitions(iRepetitions)
{

}

CProducer::~CProducer()
{
	if(c_producer_thread.joinable())
		c_producer_thread.join();
}

void CProducer::vProduce()
{
	if(!b_is_producing)
	{
		b_is_producing = true;
		c_producer_thread = std::thread(&CProducer::v_aux_produce, this);
	}
}

void CProducer::v_aux_produce()
{
	CSynchConsoleOut & out = CSynchConsoleOut::pcGetInstance();
	for(int i = 0; i < i_repetitions; ++i)
	{
		out<<"Producer " + std::to_string(i_number)+" is sleeping for "+std::to_string(i_producing_time);
		std::this_thread::sleep_for(std::chrono::milliseconds(i_producing_time));
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


