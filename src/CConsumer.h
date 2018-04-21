#ifndef SRC_CCONSUMER_H_
#define SRC_CCONSUMER_H_

#include "CBufor.h"

class CConsumer
{
public:
	CConsumer(CBufor const & cBufor);

	void vConsume();

private:

	CBufor * const c_bufor;
};


#endif /* SRC_CCONSUMER_H_ */
