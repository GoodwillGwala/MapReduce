#include "Statistics.h"

RunStatistic::RunStatistic()
: RunTimeNs(-1)
, m_runStartTime(std::chrono::high_resolution_clock::now())
, m_lastTaskBeginTime(std::chrono::high_resolution_clock::now())
{}



auto RunStatistic::EndTaskCall()->void
{
	auto endTime = std::chrono::high_resolution_clock::now();
	RunTimeNs = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_runStartTime).count();
}

auto RunStatistic::BeginTask()->void
{
	m_lastTaskBeginTime = std::chrono::high_resolution_clock::now();
}

auto RunStatistic::EndTask()->void
{
	auto endTime = std::chrono::high_resolution_clock::now();
	int time = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_lastTaskBeginTime).count();
	TaskTimesMicroS.push_back(time);
}


JobRunStatistics::JobRunStatistics()
: m_jobRunTimeMicroS(-1)
{}

auto JobRunStatistics::BeginMap()->RunStatistic*
{
    std::lock_guard<std::mutex> guard(m_mutex);

    RunStatistic* runStat = new RunStatistic();
    m_mapRuns.push_back(runStat);
    return runStat;
}


 auto JobRunStatistics::BeginReduce()->RunStatistic*
{
    std::lock_guard<std::mutex> guard(m_mutex);

    RunStatistic* runStat = new RunStatistic();
    m_reduceRuns.push_back(runStat);

    return runStat;
}


auto JobRunStatistics::BeginJob()->void
{
    m_jobStartTime = std::chrono::high_resolution_clock::now();
}

auto JobRunStatistics::EndJob()->void
{
    auto endTime = std::chrono::high_resolution_clock::now();
    m_jobRunTimeMicroS = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_jobStartTime).count();
}

auto JobRunStatistics::BeginShuffle()->void
{
    m_shuffleStartTime = std::chrono::high_resolution_clock::now();
}

auto JobRunStatistics::EndShuffle()->void
{
    auto endTime = std::chrono::high_resolution_clock::now();
    m_shuffleRunTimeMicroS = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_shuffleStartTime).count();
}

auto JobRunStatistics::PrintStatistics()->void
{
	double jobDurration = TO_SEC(m_jobRunTimeMicroS);
	double shuffleDurration = TO_SEC(m_shuffleRunTimeMicroS);
    unsigned coresCount = std::thread::hardware_concurrency();

	std::cout << "Job:" << std::endl;
	std::cout << "  - Run Time:      	" << jobDurration << std::endl;
	std::cout << "  - Avalable Threads:   " << coresCount << std::endl;
	std::cout << "\nMap:" << std::endl;
	PrintRunStats(m_mapRuns);
	std::cout << "\nShuffle:" << std::endl;
	std::cout << "  - Run Time:      	" << shuffleDurration<< std::endl;
	std::cout << "\nReduce:" << std::endl;
	PrintRunStats(m_reduceRuns);
}




auto JobRunStatistics::PrintRunStats(std::vector<RunStatistic*>& runs)->void
{
	// Per Runner
	auto minRun = std::numeric_limits<double>::max();
	auto maxRun = std::numeric_limits<double>::min();
	auto   totalRunTime = 0.0;
	auto   avgRunTime = -1.0;

	// Per-Task
	int taskcount = 0;
	auto minTask = std::numeric_limits<double>::max();
	auto maxTask = std::numeric_limits<double>::min();
	auto totalTaskRunTime = 0.0;
	auto avgTaskRunTime = -1.0;

	// Foreach Runner:
	for (auto i = 0; i < runs.size(); i++)
	{
	  	auto runTime = TO_SEC(runs[i]->RunTimeNs);
	  	minRun = (runTime < minRun) ? runTime : minRun;
	  	maxRun = (runTime > maxRun) ? runTime : maxRun;
	  	totalRunTime += runTime;

   	    // Foreach task:
	    for (auto t = 0; t < runs[i]->TaskTimesMicroS.size(); t++)
	    {
	        taskcount++;
	    	auto taskTime = TO_SEC(runs[i]->TaskTimesMicroS[t]);
	    	minTask = (taskTime < minRun) ? taskTime : minRun;
	    	maxTask = (taskTime > maxRun) ? taskTime : maxRun;
	    	totalTaskRunTime += taskTime;
	    }
   	}

	avgRunTime = totalRunTime / (double) runs.size();
	avgTaskRunTime = totalTaskRunTime / (double) taskcount;

	std::cout << "  - Runners:  " << runs.size() << std::endl;
	std::cout << "    - Total Run Time:   " << totalRunTime << std::endl;
	std::cout << "    - Average Run Time: " << avgRunTime << std::endl;
	std::cout << "    - Minimum Run Time: " << minRun << std::endl;
	std::cout << "    - Maximum Run Time: " << maxRun << std::endl;
	std::cout << "  - Tasks:            " << taskcount << std::endl;
	std::cout << "    - Average Run Time: " << avgTaskRunTime << std::endl;
	std::cout << "    - Minimum Run Time: " << minTask << std::endl;
	std::cout << "    - Maximum Run Time: " << maxTask << std::endl;
}
