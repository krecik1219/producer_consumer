#include "CBufor.h"

CBufor::CBufor(int iBuforSize) :
i_bufor_size(iBuforSize), i_count(0), i_input_position(0), i_output_position(0)
{
	pi_bufor_base = new int[i_bufor_size];
}

CBufor::~CBufor()
{
	delete [] pi_bufor_base;
}

void CBufor::vPut(int iElem)
{
	std::unique_lock<std::mutex> lock (c_locker);

	c_producer_full.wait(lock, [this]()->bool{return i_count<i_bufor_size;});



	//TODO implement critical section
}

int CBufor::iTake()
{
	//todo implement critical section
	return 0;
}


