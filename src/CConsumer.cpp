#include "CConsumer.h"

CConsumer::CConsumer(int iNumber, CBuffer & cBuffer) :
i_number(iNumber), c_buffer(&cBuffer)
{

}

void CConsumer::vConsume(int iConsumeInterval, int iRepetitions, int iElementsPerConsume)
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


