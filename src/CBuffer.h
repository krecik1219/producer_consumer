#ifndef SRC_CBUFFER_H_
#define SRC_CBUFFER_H_

#include <mutex>
#include <condition_variable>

// cyclic buffer implementation
class CBuffer
{
public:

	CBuffer(int iBuforSize);
	~CBuffer();

	void vPut(int iElem);
	void vTake(int iQuantity);
	int iCurrentCount();

private:

	std::mutex c_locker;
	std::condition_variable c_producer_full;
	std::condition_variable c_consumer_empty;

	int i_buffer_size;
	int i_input_position;
	int i_output_position;
	int i_count;
	int * pi_buffer_base;  // can be anything, integer array assumed to simplify problem
};




#endif /* SRC_CBUFFER_H_ */
