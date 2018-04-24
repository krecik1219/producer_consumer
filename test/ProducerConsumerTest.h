#ifndef PRODUCERCONSUMERTEST_H_
#define PRODUCERCONSUMERTEST_H_

#include "gtest/gtest.h"
#include "CBuffer.h"
#include "CProducer.h"
#include "CConsumer.h"
#include "CProdConsManager.h"
#include <vector>

using namespace std;

TEST(BufferTest, buffer_size_is_correct)
{
	CBuffer buffer(5);
	ASSERT_EQ(5, buffer.iGetSize());
}

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

TEST(BufferTest, clearing_buffer_test)
{
	CBuffer buffer(5);
	buffer.vPut(1);
	buffer.vPut(1);
	buffer.vPut(1);
	ASSERT_EQ(3, buffer.iCurrentCount());
	buffer.vClearBuffer();
	ASSERT_EQ(0, buffer.iCurrentCount());
	buffer.vPut(1);
	buffer.vPut(1);
	ASSERT_EQ(2, buffer.iCurrentCount());
	buffer.vTake(2);
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

TEST(ProducerConsumerTest, one_producer_one_consumer_single_elem_buffer)
{
	CBuffer buffer(1);
	CProducer producer(1, &buffer, 300, 1);
	CConsumer consumer(1, &buffer, 200, 1, 1);
	producer.vProduce();
	consumer.vConsume();
	producer.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, one_producer_one_consumer_single_elem_buffer_many_cycles)
{
	CBuffer buffer(1);
	CProducer producer(1, &buffer, 300, 10);
	CConsumer consumer(1, &buffer, 200, 10, 1);
	producer.vProduce();
	consumer.vConsume();
	producer.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, one_producer_one_consumer_many_elem_buffer_additional_producer_filling_sparse_space)
{
	CBuffer buffer(10);
	CProducer producer1(1, &buffer, 300, 6);
	CProducer producer2(1, &buffer, 300, 4);
	CConsumer consumer(1, &buffer, 200, 2, 3);
	producer1.vProduce();
	producer2.vProduce();
	consumer.vConsume();
	producer1.vExplicitJoin();
	producer2.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(4, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, producing_some_quantity_of_elems_then_consuming_the_same_quantity)
{
	CBuffer buffer(5);
	CProducer producer(1, &buffer, 500, 20);
	CConsumer consumer(1, &buffer, 250, 20, 1);
	producer.vProduce();
	consumer.vConsume();
	producer.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, more_producing_cycles_consumer_consuming_multi_elems)
{
	CBuffer buffer(5);
	CProducer producer(1, &buffer, 500, 20);
	CConsumer consumer(1, &buffer, 250, 10, 2);
	producer.vProduce();
	consumer.vConsume();

	producer.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, single_producer_many_consumers)
{
	CBuffer buffer(5);
	CProducer producer(1, &buffer, 500, 70);
	CConsumer consumer1(1, &buffer, 350, 10, 3);
	CConsumer consumer2(2, &buffer, 250, 10, 2);
	CConsumer consumer3(3, &buffer, 500, 20, 1);
	producer.vProduce();
	consumer1.vConsume();
	consumer2.vConsume();
	consumer3.vConsume();

	producer.vExplicitJoin();
	consumer1.vExplicitJoin();
	consumer2.vExplicitJoin();
	consumer3.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, many_producers_single_consumer)
{
	CBuffer buffer(5);
	CProducer producer1(1, &buffer, 500, 20);
	CProducer producer2(2, &buffer, 200, 10);
	CProducer producer3(3, &buffer, 350, 10);
	CConsumer consumer(1, &buffer, 350, 20, 2);
	producer1.vProduce();
	producer2.vProduce();
	producer3.vProduce();
	consumer.vConsume();

	producer1.vExplicitJoin();
	producer2.vExplicitJoin();
	producer3.vExplicitJoin();
	consumer.vExplicitJoin();
	ASSERT_EQ(0, buffer.iCurrentCount());
}

TEST(ProducerConsumerTest, many_producers_many_consumers)
{
	CBuffer buffer(5);
	CProducer producer1(1, &buffer, 400, 40);
	CProducer producer2(2, &buffer, 200, 60);
	CProducer producer3(3, &buffer, 350, 50);
	CConsumer consumer1(1, &buffer, 350, 10, 2);
	CConsumer consumer2(2, &buffer, 250, 20, 1);
	CConsumer consumer3(3, &buffer, 500, 20, 3);
	CConsumer consumer4(4, &buffer, 100, 10, 5);
	producer1.vProduce();
	producer2.vProduce();
	producer3.vProduce();
	consumer1.vConsume();
	consumer2.vConsume();
	consumer3.vConsume();
	consumer4.vConsume();

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


	void vSetUpBuffer(int iBufferSize)
	{
		buffer = make_unique<CBuffer>(iBufferSize);
	}

	void vSetUpProducers(int iProducentsNum, vector<int> const & vProducingTimeValues, vector<int> const & vRepetitionsValues)
	{
		for(int i = 0; i<iProducentsNum; ++i)
		{
			vProducers.push_back(make_unique<CProducer>(i + 1, buffer.get(), vProducingTimeValues[i], vRepetitionsValues[i]));
		}
	}

	void vSetUpConsumers(int iConsumersNum, vector<int> const & vConsumingIntervalValues, vector<int> const & vRepetitionsValues, vector<int> const & vElementsPerConsumeValues)
	{
		for(int i = 0; i<iConsumersNum; ++i)
		{
			vConsumers.push_back(make_unique<CConsumer>(i + 1, buffer.get(), vConsumingIntervalValues[i], vRepetitionsValues[i], vElementsPerConsumeValues[i]));
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

	void vStartProducers()
	{
		int i_producers_size = vProducers.size();

		for (int i = 0; i < i_producers_size; ++i)
		{
			vProducers[i]->vProduce();
		}
	}

	void vStartConsumers()
	{
		int i_consumers_size = vConsumers.size();

		for (int i = 0; i < i_consumers_size; ++i)
		{
			vConsumers[i]->vConsume();
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

	vSetUpBuffer(1000);

	vSetUpProducers(100, vProducingTimeValues, vRepetitionsValuesProducers);

	vSetUpConsumers(100, vConsumingIntervalValues, vRepetitionsValuesConsumers, vElementsPerConsume);

	buffer->vPut(1);
	ASSERT_EQ(1, buffer->iCurrentCount());
	buffer->vTake(1);
	ASSERT_EQ(0, buffer->iCurrentCount());

	vStartConsumers();
	vStartProducers();

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

	vSetUpBuffer(1000);

	vSetUpProducers(100, vProducingTimeValues, vRepetitionsValuesProducers);

	vSetUpConsumers(100, vConsumingIntervalValues, vRepetitionsValuesConsumers,
			vElementsPerConsume);

	buffer->vPut(1);
	ASSERT_EQ(1, buffer->iCurrentCount());
	buffer->vTake(1);
	ASSERT_EQ(0, buffer->iCurrentCount());

	vStartConsumers();
	vStartProducers();

	vExplicitJoinThreads();

	ASSERT_EQ(0, buffer->iCurrentCount());
}

TEST(ProdConsManagerTest, buffer_missing_error_expected)
{
	CProdConsManager manager;
	manager.vCreateProducer(400, 10);
	manager.vCreateConsumer(400, 10, 1);
	CProdConsError err_code = manager.vStartTest();
	ASSERT_EQ(CProdConsError::ERR_NO_BUFFER, err_code);
}

TEST(ProdConsManagerTest, try_of_creating_more_than_one_buffer_returns_false)
{
	CProdConsManager manager;
	bool result = manager.bCreateBuffer(5);
	ASSERT_EQ(true, result);
	result = manager.bCreateBuffer(3);
	ASSERT_EQ(false, result);
}

TEST(ProdConsManagerTest, producer_missing_error_expected)
{
	CProdConsManager manager;
	manager.bCreateBuffer(5);
	manager.vCreateConsumer(400, 10, 1);
	CProdConsError err_code = manager.vStartTest();
	ASSERT_EQ(CProdConsError::ERR_NO_PRODUCER, err_code);
}

TEST(ProdConsManagerTest, consumer_missing_error_expected)
{
	CProdConsManager manager;
	manager.bCreateBuffer(5);
	manager.vCreateProducer(400, 10);
	CProdConsError err_code = manager.vStartTest();
	ASSERT_EQ(CProdConsError::ERR_NO_CONSUMER, err_code);
}

TEST(ProdConsManagerTest, started_successfully)
{
	CProdConsManager manager;
	manager.bCreateBuffer(5);
	manager.vCreateProducer(400, 10);
	manager.vCreateProducer(500, 20);
	manager.vCreateProducer(350, 30);
	manager.vCreateConsumer(400, 2, 5);
	manager.vCreateConsumer(100, 10, 2);
	manager.vCreateConsumer(300, 10, 3);
	CProdConsError err_code = manager.vStartTest();
	ASSERT_EQ(CProdConsError::ERR_OK, err_code);
}

#endif /* PRODUCERCONSUMERTEST_H_ */
