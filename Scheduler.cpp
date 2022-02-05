#include "Scheduler.h"
#include "ThreadManager.h"
template<typename Job>
auto ThreadedScheduler::RunJob(Job& job)->void
{

	job.RunStatistics->BeginJob();

	auto threadCount = std::thread::hardware_concurrency();

	auto threads = new std::thread[threadCount];

//    ThreadManager Threads;
//
//    auto loop = [&](auto i=0)
//    {
//        MapJob<Job>(&job);
//
//    }
//    Threads.ParallelizeLoop(0,Threads.ThreadCount(), loop );
    // Map

    for (auto i = 0; i < threadCount; i++)
	  	threads[i] = std::thread(MapJob<Job>, &job);

	for (auto i = 0; i < threadCount; i++)
	  	threads[i].join();

	// Shuffle
	job.Shuffle();

	// Reduce
	for (auto i = 0; i < threadCount; i++)
	  	threads[i] = std::thread(ReduceJob<Job>, &job);


	for (auto i = 0; i < threadCount; i++)
	  	threads[i].join();


	delete[] threads;
	job.RunStatistics->EndJob();
}

template<typename Job>
auto JobScheduler::RunJob(Job& job)->void
{
    job.RunStatistics->BeginJob();

    // Map
    MapJob<Job>(&job);

    // Shuffle
    job.Shuffle();

    // Reduce
    ReduceJob<Job>(&job);

    job.RunStatistics->EndJob();
}


template<typename Job>
auto MapJob(Job* job)->void
{
    auto runStat = job->RunStatistics->BeginMap();

    typename Job::MapPolicyType mapClass;
    typename Job::MapPolicyType::KeyType sourceKey;
    typename Job::MapPolicyType::ValueType sourceValue;

    auto runner = new typename Job::MapTaskRunner();

    while (job->Source->GetData(sourceKey, sourceValue))
    {
      	runStat->BeginTask();
       	mapClass.template
       	Map<typename Job::MapTaskRunner>
       	(*runner, sourceKey, sourceValue);
       	runStat->EndTask();
    }


    job->DataBuffer->Combine(&runner->LocalBuffer);
    delete runner;
    runStat->EndTaskCall();
}


template<typename Job>
auto ReduceJob(Job* job)->void
{
    auto reduceStat = job->RunStatistics->BeginReduce();

    typename Job::ReducePolicyType reduceClass;
    typename Job::MapPolicyType::IntermediateKeyType intermitKey;
    typename Job::ReduceIteratorType iterStart;
    typename Job::ReduceIteratorType iterEnd;

    auto runner = new typename Job::ReduceTaskRunner(job->Drain);

    while (job->DataBuffer->GetData(intermitKey, iterStart, iterEnd))
    {
      	reduceStat->BeginTask();
   		reduceClass.template
   		Reduce<typename Job::ReduceTaskRunner,typename Job::ReduceIteratorType>
   		(*runner, intermitKey, iterStart,iterEnd);
       	reduceStat->EndTask();
      }


      reduceStat->EndTaskCall();
}
