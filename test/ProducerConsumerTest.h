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
	producer.vProduce(500, 20);
	consumer.vConsume(250, 20, 1);
	producer.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, more_producing_cycles_consumer_consuming_multi_elems)
{
	CBuffer buffer(5);
	CProducer producer(1, buffer);
	CConsumer consumer(1, buffer);
	producer.vProduce(500, 20);
	consumer.vConsume(250, 10, 2);

	producer.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, single_producer_many_consumers)
{
	CBuffer buffer(5);
	CProducer producer(1, buffer);
	CConsumer consumer1(1, buffer);
	CConsumer consumer2(2, buffer);
	CConsumer consumer3(3, buffer);
	producer.vProduce(500, 70);
	consumer1.vConsume(350, 10, 3);
	consumer2.vConsume(250, 10, 2);
	consumer3.vConsume(500, 20, 1);

	producer.vExplicitJoin();
	consumer1.vExplicitJoin();
	consumer2.vExplicitJoin();
	consumer3.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, many_producers_single_consumer)
{
	CBuffer buffer(5);
	CProducer producer1(1, buffer);
	CProducer producer2(2, buffer);
	CProducer producer3(3, buffer);
	CConsumer consumer(1, buffer);
	producer1.vProduce(500, 20);
	producer2.vProduce(200, 10);
	producer3.vProduce(350, 10);
	consumer.vConsume(350, 20, 2);

	producer1.vExplicitJoin();
	producer2.vExplicitJoin();
	producer3.vExplicitJoin();
	consumer.vExplicitJoin();
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
	producer1.vProduce(400, 40);
	producer2.vProduce(200, 60);
	producer3.vProduce(350, 50);
	consumer1.vConsume(350, 10, 2);
	consumer2.vConsume(250, 20, 1);
	consumer3.vConsume(500, 20, 3);
	consumer4.vConsume(100, 10, 5);

	producer1.vExplicitJoin();
	producer2.vExplicitJoin();
	producer3.vExplicitJoin();
	consumer1.vExplicitJoin();
	consumer2.vExplicitJoin();
	consumer3.vExplicitJoin();
	consumer4.vExplicitJoin();

	ASSERT_EQ(0, buffer.iCurrentCount());
}

struct ProdConsTest : testing::Test
{
	typedef std::unique_ptr<CProducer> producer;
	typedef std::unique_ptr<CConsumer> consumer;

	vector<producer> vProducers;
	vector<consumer> vConsumers;
	unique_ptr<CBuffer> buffer;


	void vSetUp(int iBufferSize, int iProducentsNum, int iConsumersNum)
	{
		buffer = make_unique<CBuffer>(iBufferSize);
		for(int i = 0; i<iProducentsNum; ++i)
		{
			vProducers.push_back(make_unique<CProducer>(i+1, *buffer));
		}

		for(int i = 0; i<iConsumersNum; ++i)
		{
			vConsumers.push_back(make_unique<CConsumer>(i+1, *buffer));
		}
	}

	void vExplicitJoinThreads()
	{
		int i_consumers_size = vConsumers.size();
		int i_producers_size = vProducers.size();

		for(int i=0; i< i_producers_size; ++i)
		{
			vProducers[i]->vExplicitJoin();
		}

		for(int i=0; i< i_consumers_size; ++i)
		{
			vConsumers[i]->vExplicitJoin();
		}
	}

	void vStartProducers(vector<int> const & vProducingTimeValues, vector<int> const & vRepetitionsValues)
	{
		int i_producers_size = vProducers.size();

		for (int i = 0; i < i_producers_size; ++i)
		{
			vProducers[i]->vProduce(vProducingTimeValues[i], vRepetitionsValues[i]);
		}
	}

	void vStartConsumers(vector<int> const & vConsumingIntervalValues, vector<int> const & vRepetitionsValues, vector<int> const & vElementsPerConsumeValues)
	{
		int i_consumers_size = vConsumers.size();

		for (int i = 0; i < i_consumers_size; ++i)
		{
			vConsumers[i]->vConsume(vConsumingIntervalValues[i], vRepetitionsValues[i], vElementsPerConsumeValues[i]);
		}
	}

	~ProdConsTest()
	{
		vExplicitJoinThreads();
	}

};

TEST_F(ProdConsTest, many_producers_many_consumer_larger_scale_large_buffer)
{
	srand(time(NULL));
	vector<int> vProducingTimeValues;
	for(int i=0; i<100;i++)
	{
		vProducingTimeValues.push_back((rand() % 50 + 50));
	}
	vector<int> vConsumingIntervalValues;
	for(int i=0; i<100; i++)
	{
		vConsumingIntervalValues.push_back((rand() % 50 + 50));
	}
	vector<int> vRepetitionsValuesProducers;
	for(int i=0; i<100; i++)
	{
		if(i<33)  // 33 values
			vRepetitionsValuesProducers.push_back(10);
		else if(i>=33 && i<66)  // 33 values
			vRepetitionsValuesProducers.push_back(20);
		else  // 34 values
			vRepetitionsValuesProducers.push_back(30);
	}
	vector<int> vRepetitionsValuesConsumers;
	vector<int> vElementsPerConsume;
	for(int i=0; i<100; i++)
	{
		if (i < 33)  // 33 values
		{
			vRepetitionsValuesConsumers.push_back(10);
			vElementsPerConsume.push_back(1);
		}
		else if(i>=33 && i<66)  // 33 values
		{
			vRepetitionsValuesConsumers.push_back(10);
			vElementsPerConsume.push_back(2);
		}
		else  // 34 values
		{
			vRepetitionsValuesConsumers.push_back(6);
			vElementsPerConsume.push_back(5);
		}
	}

	vSetUp(1000, 100, 100);

	buffer->vPut(1);
	ASSERT_EQ(1, buffer->iCurrentCount());
	buffer->vTake(1);
	ASSERT_EQ(0, buffer->iCurrentCount());

	vStartConsumers(vConsumingIntervalValues, vRepetitionsValuesConsumers, vElementsPerConsume);
	vStartProducers(vProducingTimeValues, vRepetitionsValuesProducers);

	vExplicitJoinThreads();

	ASSERT_EQ(0, buffer->iCurrentCount());
}

TEST_F(ProdConsTest, many_producers_many_consumer_larger_scale_small_buffer)
{
	srand(time(NULL));
	vector<int> vProducingTimeValues;
	for(int i=0; i<100;i++)
	{
		vProducingTimeValues.push_back((rand() % 50 + 50));
	}
	vector<int> vConsumingIntervalValues;
	for(int i=0; i<100; i++)
	{
		vConsumingIntervalValues.push_back((rand() % 50 + 50));
	}
	vector<int> vRepetitionsValuesProducers;
	for(int i=0; i<100; i++)
	{
		if(i<33)  // 33 values
			vRepetitionsValuesProducers.push_back(10);
		else if(i>=33 && i<66)  // 33 values
			vRepetitionsValuesProducers.push_back(20);
		else  // 34 values
			vRepetitionsValuesProducers.push_back(30);
	}
	vector<int> vRepetitionsValuesConsumers;
	vector<int> vElementsPerConsume;
	for(int i=0; i<100; i++)
	{
		if (i < 33)  // 33 values
		{
			vRepetitionsValuesConsumers.push_back(10);
			vElementsPerConsume.push_back(1);
		}
		else if(i>=33 && i<66)  // 33 values
		{
			vRepetitionsValuesConsumers.push_back(10);
			vElementsPerConsume.push_back(2);
		}
		else  // 34 values
		{
			vRepetitionsValuesConsumers.push_back(6);
			vElementsPerConsume.push_back(5);
		}
	}

	vSetUp(5, 100, 100);

	buffer->vPut(1);
	ASSERT_EQ(1, buffer->iCurrentCount());
	buffer->vTake(1);
	ASSERT_EQ(0, buffer->iCurrentCount());

	vStartConsumers(vConsumingIntervalValues, vRepetitionsValuesConsumers, vElementsPerConsume);
	vStartProducers(vProducingTimeValues, vRepetitionsValuesProducers);

	vExplicitJoinThreads();

	ASSERT_EQ(0, buffer->iCurrentCount());
}



#endif /* PRODUCERCONSUMERTEST_H_ */
