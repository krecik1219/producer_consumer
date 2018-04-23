#ifndef PRODUCERCONSUMERTEST_H_
#define PRODUCERCONSUMERTEST_H_

#include "gtest/gtest.h"
#include "CBuffer.h"
#include "CProducer.h"
#include "CConsumer.h"
#include <vector>

using namespace std;

TEST(BufferTest, putting_to_buffer_test)
{
	CBuffer buffer(5);
	ASSERT_EQ(0, buffer.iCurrentCount());
	buffer.vPut(1);
	ASSERT_EQ(1, buffer.iCurrentCount());
	buffer.vPut(1);
	ASSERT_EQ(2, buffer.iCurrentCount());
	buffer.vPut(1);
	ASSERT_EQ(3, buffer.iCurrentCount());
	buffer.vPut(1);
	ASSERT_EQ(4, buffer.iCurrentCount());
	buffer.vPut(1);
	ASSERT_EQ(5, buffer.iCurrentCount());
}

TEST(BufferTest, consuming_from_buffer_test)
{
	CBuffer buffer(5);
	buffer.vPut(1);
	buffer.vPut(1);
	buffer.vPut(1);
	ASSERT_EQ(3, buffer.iCurrentCount());
	buffer.vTake(2);
	ASSERT_EQ(1, buffer.iCurrentCount());
	buffer.vTake(1);
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(BufferTest, trying_consume_more_than_buffer_size)
{
	CBuffer buffer(5);
	buffer.vPut(1);
	buffer.vPut(1);
	ASSERT_EQ(2, buffer.iCurrentCount());
	buffer.vTake(6);
	ASSERT_EQ(2, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, producing_some_quantity_of_elems_then_consuming_the_same_quantity)
{
	CBuffer buffer(5);
	CProducer producer(1, buffer);
	CConsumer consumer(1, buffer);
	std::thread prod(&CProducer::vProduce, producer, 500, 20);
	std::thread cons(&CConsumer::vConsume, consumer, 250, 20, 1);

	prod.join();
	cons.join();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, more_producing_cycles_consumer_consuming_multi_elems)
{
	CBuffer buffer(5);
	CProducer producer(1, buffer);
	CConsumer consumer(1, buffer);
	std::thread prod(&CProducer::vProduce, producer, 500, 20);
	std::thread cons(&CConsumer::vConsume, consumer, 250, 10, 2);

	prod.join();
	cons.join();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, single_producer_many_consumers)
{
	CBuffer buffer(5);
	CProducer producer(1, buffer);
	CConsumer consumer1(1, buffer);
	CConsumer consumer2(2, buffer);
	CConsumer consumer3(3, buffer);
	std::thread prod(&CProducer::vProduce, producer, 500, 70);
	std::thread cons1(&CConsumer::vConsume, consumer1, 350, 10, 3);
	std::thread cons2(&CConsumer::vConsume, consumer2, 250, 10, 2);
	std::thread cons3(&CConsumer::vConsume, consumer3, 500, 20, 1);

	prod.join();
	cons1.join();
	cons2.join();
	cons3.join();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, many_producers_single_consumer)
{
	CBuffer buffer(5);
	CProducer producer1(1, buffer);
	CProducer producer2(2, buffer);
	CProducer producer3(3, buffer);
	CConsumer consumer(1, buffer);
	std::thread prod1(&CProducer::vProduce, producer1, 500, 20);
	std::thread prod2(&CProducer::vProduce, producer2, 200, 10);
	std::thread prod3(&CProducer::vProduce, producer3, 350, 10);
	std::thread cons(&CConsumer::vConsume, consumer, 350, 20, 2);

	prod1.join();
	prod2.join();
	prod3.join();
	cons.join();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, many_producers_many_consumers)
{
	CBuffer buffer(5);
	CProducer producer1(1, buffer);
	CProducer producer2(2, buffer);
	CProducer producer3(3, buffer);
	CConsumer consumer1(1, buffer);
	CConsumer consumer2(2, buffer);
	CConsumer consumer3(3, buffer);
	CConsumer consumer4(4, buffer);
	std::thread prod1(&CProducer::vProduce, producer1, 400, 40);
	std::thread prod2(&CProducer::vProduce, producer2, 200, 60);
	std::thread prod3(&CProducer::vProduce, producer3, 350, 50);
	std::thread cons1(&CConsumer::vConsume, consumer1, 350, 10, 2);
	std::thread cons2(&CConsumer::vConsume, consumer2, 250, 20, 1);
	std::thread cons3(&CConsumer::vConsume, consumer3, 500, 20, 3);
	std::thread cons4(&CConsumer::vConsume, consumer4, 100, 10, 5);

	prod1.join(); prod2.join(); prod3.join();
	cons1.join(); cons2.join(); cons3.join(); cons4.join();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

struct ProducerConsumerTest : testing::Test  // TODO
{
	typedef std::unique_ptr<CProducer> producer;
	typedef std::unique_ptr<CConsumer> consumer;

	vector<producer> vProducers;
	vector<consumer> vConsumers;
	CBuffer buffer;

	ProducerConsumerTest() :
		buffer(5)
	{

	}

	void setUp(int iProducentsNum, int iConsumersNum)
	{
		for(int i = 0; i<iProducentsNum; ++i)
		{
			vProducers.push_back(make_unique<CProducer>(i+1, buffer));
		}

		for(int i = 0; i<iConsumersNum; ++i)
		{
			vConsumers.push_back(make_unique<CConsumer>(i+1, buffer));
		}
	}

	~ProducerConsumerTest()
	{

	}

};

TEST(ProducerConsumerTest, many_producers_many_consumer_larger_scale_small_buffer)
{
	// TODO implement that test, think about some data provider, repetitions and number of items consumed at once depends on total number of items that will be produced
	auto buffer = make_shared<CBuffer>(5);
	typedef std::unique_ptr<CProducer> producer;
	typedef std::unique_ptr<CConsumer> consumer;
	vector<producer> producers;
	vector<consumer> consumers;
	for(int i=0; i<100; i++)
	{
		producers.push_back(make_unique<CProducer>(i+1, *buffer));
		consumers.push_back(make_unique<CConsumer>(i+1, *buffer));
	}

	vector<int> producents_waiting_times;

	typedef unique_ptr<std::thread> thr;
	vector<thr> producersThr;
	producersThr.push_back(make_unique<std::thread>(&CProducer::vProduce, *producers[0], 3000, 10));
	producersThr.push_back(make_unique<std::thread>(&CProducer::vProduce, *producers[1], 2000, 10));
	producersThr.push_back(make_unique<std::thread>(&CProducer::vProduce, *producers[2], 1500, 30));
	producersThr.push_back(make_unique<std::thread>(&CProducer::vProduce, *producers[3], 3000, 20));
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
}



#endif /* PRODUCERCONSUMERTEST_H_ */
