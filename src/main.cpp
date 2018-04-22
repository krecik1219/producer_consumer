#include <iostream>
#include "CBuffer.h"
#include "CProducer.h"
#include "CConsumer.h"
#include <vector>
#include <memory>

using namespace std;

int main()
{
	auto buffer = std::make_shared<CBuffer>(5);
	typedef std::unique_ptr<CProducer> producer;
	typedef std::unique_ptr<CConsumer> consumer;
	vector<producer> producers;
	vector<consumer> consumers;
	for(int i=0; i<4; i++)
	{
		producers.push_back(std::make_unique<CProducer>(i+1, *buffer));
		consumers.push_back(std::make_unique<CConsumer>(i+1, *buffer));
	}


	typedef unique_ptr<std::thread> thr;
	vector<thr> producersThr;
	producersThr.push_back(std::make_unique<std::thread>(&CProducer::vProduce, *producers[0], 3000, 10));
	producersThr.push_back(std::make_unique<std::thread>(&CProducer::vProduce, *producers[1], 2000, 10));
	producersThr.push_back(std::make_unique<std::thread>(&CProducer::vProduce, *producers[2], 1500, 30));
	producersThr.push_back(std::make_unique<std::thread>(&CProducer::vProduce, *producers[3], 3000, 20));

	vector<thr> consumersThr;
	consumersThr.push_back(std::make_unique<std::thread>(&CConsumer::vConsume, *consumers[0], 2000, 10, 1));
	consumersThr.push_back(std::make_unique<std::thread>(&CConsumer::vConsume, *consumers[1], 1500, 10, 2));
	consumersThr.push_back(std::make_unique<std::thread>(&CConsumer::vConsume, *consumers[2], 3000, 10, 1));
	consumersThr.push_back(std::make_unique<std::thread>(&CConsumer::vConsume, *consumers[3], 3500, 10, 3));

	for(int i=0; i<4; i++)
	{
		producersThr[i]->join();
		consumersThr[i]->join();
	}

	cout<<endl<<"Program finished"<<endl;
	getchar(); getchar();
	return 0;
}


