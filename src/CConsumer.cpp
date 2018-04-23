#include "CConsumer.h"

CConsumer::CConsumer(int iNumber, CBuffer * const cBuffer, int iConsumeInterval, int iRepetitions, int iElementsPerConsume) :
i_number(iNumber), c_buffer(cBuffer), b_is_consuming(false), i_consume_interval(iConsumeInterval),
i_repetitions(iRepetitions), i_elements_per_consume(iElementsPerConsume)
{

}

CConsumer::~CConsumer()
{
	if(c_consumer_thread.joinable())
		c_consumer_thread.join();
}

void CConsumer::vConsume()
{
	if(!b_is_consuming)
	{
		b_is_consuming = true;
		c_consumer_thread = std::thread(&CConsumer::v_aux_consume, this);
	}
}

void CConsumer::v_aux_consume()
{
	CSynchConsoleOut& out = CSynchConsoleOut::pcGetInstance();

		for(int i = 0; i < i_repetitions; ++i)
		{
			out<<("Consumer "+std::to_string(i_number)+" is sleeping for "+std::to_string(i_consume_interval));
			std::this_thread::sleep_for(std::chrono::milliseconds(i_consume_interval));
			out<<"Consumer "+std::to_string(i_number)+" is consuming "+std::to_string(i_elements_per_consume)+" elements";
			c_buffer->vTake(i_elements_per_consume);
			out<<"Consumer "+std::to_string(i_number)+" consumed "+std::to_string(i_elements_per_consume)+" elements";
		}
		out<<"Consumer "+std::to_string(i_number)+" finished its job ";
}

void CConsumer::vExplicitJoin()
{
	if(c_consumer_thread.joinable())
		c_consumer_thread.join();
}
