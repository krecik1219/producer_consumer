#ifndef SRC_CPRODUCER_H_
#define SRC_CPRODUCER_H_

#include "CBufor.h"

class CProducer
{
public:
	CProducer(CBufor const & cBufor);

	void vProduce();

private:

	CBufor * const c_bufor;

};



#endif /* SRC_CPRODUCER_H_ */
