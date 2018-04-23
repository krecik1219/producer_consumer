#include "CProdConsManager.h"

CProdConsManager::CProdConsManager() :
i_producers_count(0), i_consumers_count(0)
{
	// TODO Auto-generated constructor stub

}

CProdConsManager::~CProdConsManager()
{
	// TODO Auto-generated destructor stub
}

bool CProdConsManager::bCreateBuffer(int iBufferSize)
{
	if(!pc_buffer)
	{
		pc_buffer = make_unique<CBuffer>(iBufferSize);
		return true;
	}
	else
		return false;
}

void CProdConsManager::vCreateProducer(int iProducingTime, int iRepetitions)
{
	v_producers.push_back(make_unique<CProducer>(i_producers_count + 1, pc_buffer.get(), iProducingTime, iRepetitions));
	++i_producers_count;
}

void CProdConsManager::vCreateConsumer(int iConsumeInterval, int iRepetitions, int iElementsPerConsume)
{
	v_consumers.push_back(make_unique<CConsumer>(i_consumers_count + 1, pc_buffer.get(), iConsumeInterval, iRepetitions, iElementsPerConsume));
	++i_consumers_count;
}

CProdConsError CProdConsManager::vStartTest()
{
	if(v_consumers.empty())
		return CProdConsError::ERR_NO_CONSUMER;

	if(v_producers.empty())
			return CProdConsError::ERR_NO_PRODUCER;

	int i_producers_size = v_producers.size();
	int i_consumers_size = v_consumers.size();

	for(int i=0; i<i_producers_size; ++i)
	{
		v_producers[i]->vProduce();
	}

	for(int i=0; i<i_consumers_size; ++i)
	{
		v_consumers[i]->vConsume();
	}

	v_explicit_join();
	return CProdConsError::ERR_OK;
}

void CProdConsManager::vRunSampleTest()
{
	vResetManager();

	bCreateBuffer(5);

	vCreateProducer(3000, 10);
	vCreateProducer(2000, 10);
	vCreateProducer(1500, 30);
	vCreateProducer(3000, 20);

	vCreateConsumer(2000, 10, 1);
	vCreateConsumer(1500, 10, 2);
	vCreateConsumer(3000, 10, 1);
	vCreateConsumer(3500, 10, 3);

	vStartTest();
}

void CProdConsManager::vResetManager()
{
	pc_buffer.reset();
	v_consumers.clear();
	v_producers.clear();
	i_consumers_count = 0;
	i_producers_count = 0;
}

void CProdConsManager::v_explicit_join()
{
	int i_producers_size = v_producers.size();
	int i_consumers_size = v_consumers.size();

	for(int i=0; i<i_producers_size; ++i)
	{
		v_producers[i]->vExplicitJoin();
	}

	for (int i = 0; i < i_consumers_size; ++i)
	{
		v_consumers[i]->vExplicitJoin();
	}
}
