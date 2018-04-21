#ifndef SRC_CBUFOR_H_
#define SRC_CBUFOR_H_

#include <mutex>
#include <condition_variable>

class CBufor
{
public:

	CBufor(int iBuforSize);
	~CBufor();

	void vPut(int iElem);
	int iTake();

private:

	std::mutex c_locker;
	std::condition_variable c_producer_full;
	std::condition_variable c_consumer_empty;

	int i_bufor_size;
	int i_input_position;
	int i_output_position;
	int i_count;
	int * pi_bufor_base;  // can be anything, integer array assumed to simplify problem
};




#endif /* SRC_CBUFOR_H_ */
