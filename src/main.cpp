#include <iostream>
#include "CBuffer.h"
#include "CProducer.h"
#include "CConsumer.h"
#include <vector>
#include <memory>

using namespace std;

void vDummyRun()
{
	auto buffer = std::make_unique<CBuffer>(5);
	typedef std::unique_ptr<CProducer> producer;
	typedef std::unique_ptr<CConsumer> consumer;

	vector<producer> producers;
	vector<consumer> consumers;
	for (int i = 0; i < 4; i++)
	{
		producers.push_back(std::make_unique<CProducer>(i + 1, *buffer));
		consumers.push_back(std::make_unique<CConsumer>(i + 1, *buffer));
	}

	producers[0]->vProduce(3000, 10);
	producers[1]->vProduce(2000, 10);
	producers[2]->vProduce(1500, 30);
	producers[3]->vProduce(3000, 20);

	consumers[0]->vConsume(2000, 10, 1);
	consumers[1]->vConsume(1500, 10, 2);
	consumers[2]->vConsume(3000, 10, 1);
	consumers[3]->vConsume(3500, 10, 3);
}

int main()
{

	vDummyRun();

	cout<<endl<<"Program finished!"<<endl;
	getchar(); getchar();
	return 0;
}


