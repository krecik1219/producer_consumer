#include "CConsumer.h"

CConsumer::CConsumer(int iNumber, CBuffer & cBuffer) :
i_number(iNumber), c_buffer(&cBuffer), b_is_consuming(false)
{

}

CConsumer::~CConsumer()
{
	if(c_consumer_thread.joinable())
		c_consumer_thread.join();
}

void CConsumer::vConsume(int iConsumeInterval, int iRepetitions, int iElementsPerConsume)
{
	if(!b_is_consuming)
	{
		b_is_consuming = true;
		c_consumer_thread = std::thread(&CConsumer::v_aux_consume, this, iConsumeInterval, iRepetitions, iElementsPerConsume);
	}
}

void CConsumer::v_aux_consume(int iConsumeInterval, int iRepetitions, int iElementsPerConsume)
{
	CSynchConsoleOut& out = CSynchConsoleOut::pcGetInstance();

		for(int i = 0; i < iRepetitions; ++i)
		{
			out<<("Consumer "+std::to_string(i_number)+" is sleeping for "+std::to_string(iConsumeInterval));
			std::this_thread::sleep_for(std::chrono::milliseconds(iConsumeInterval));
			out<<"Consumer "+std::to_string(i_number)+" is consuming "+std::to_string(iElementsPerConsume)+" elements";
			c_buffer->vTake(iElementsPerConsume);
			out<<"Consumer "+std::to_string(i_number)+" consumed "+std::to_string(iElementsPerConsume)+" elements";
		}
		out<<"Consumer "+std::to_string(i_number)+" finished its job ";
}

void CConsumer::vExplicitJoin()
{
	if(c_consumer_thread.joinable())
		c_consumer_thread.join();
}
