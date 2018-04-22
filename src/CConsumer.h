#ifndef SRC_CCONSUMER_H_
#define SRC_CCONSUMER_H_

#include <thread>
#include "CSynchConsoleOut.h"
#include "CBuffer.h"

class CConsumer
{
public:
	CConsumer(int iNumber, CBuffer & cBuffer);

	void vConsume(int iConsumeInterval, int iRepetitions, int iElementsPerConsume);

private:

	int i_number;
	CBuffer * const c_buffer;
};


#endif /* SRC_CCONSUMER_H_ */
