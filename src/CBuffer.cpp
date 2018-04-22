#include "CBuffer.h"

CBuffer::CBuffer(int iBuforSize) :
i_buffer_size(iBuforSize), i_count(0), i_input_position(0), i_output_position(0)
{
	pi_buffer_base = new int[i_buffer_size];
}

CBuffer::~CBuffer()
{
	delete [] pi_buffer_base;
}

void CBuffer::vPut(int iElem)
{
	std::unique_lock<std::mutex> lock (c_locker);

	c_producer_full.wait(lock, [this]()->bool{return i_count<i_buffer_size;});

	pi_buffer_base[i_input_position] = iElem;
	i_input_position = (i_input_position + 1) % i_buffer_size;
	++i_count;

	lock.unlock();

	c_consumer_empty.notify_one();

}

void CBuffer::vTake(int iQuantity)
{
	if(iQuantity <= i_buffer_size)
	{
		std::unique_lock<std::mutex> lock (c_locker);

			c_consumer_empty.wait(lock, [this, iQuantity]()->bool{return i_count >= iQuantity;});

			i_output_position = (i_output_position + iQuantity) % i_buffer_size;
			i_count-=iQuantity;

			lock.unlock();

			c_producer_full.notify_one();
	}
}

int CBuffer::iCurrentCount()
{
	return i_count;
}


