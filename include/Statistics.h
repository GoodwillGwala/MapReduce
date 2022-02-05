#ifndef _STATS_
#define _STATS_

#include <chrono>
#include <limits>
#include <thread>

#define TO_SEC(val) ((double)val / 1000000.0L)



class RunStatistic
{
 public:
	  RunStatistic();


	  auto EndTaskCall()->void;


	  auto BeginTask()->void;


	  auto EndTask()->void;


 public:
  	  std::vector<int> TaskTimesMicroS;
  	  int RunTimeNs;

 private:
	  typedef std::chrono::high_resolution_clock::time_point Time;
	  Time m_runStartTime;
	  Time m_lastTaskBeginTime;
};

class JobRunStatistics
{
 public:
  JobRunStatistics();

  auto BeginMap()->RunStatistic*;


  auto BeginReduce()->RunStatistic*;


  auto BeginJob()->void;


  auto EndJob()->void;


  auto BeginShuffle()->void;


  auto EndShuffle()->void;


  auto PrintStatistics()->void;


 private:
  	auto PrintRunStats(std::vector<RunStatistic*>& runs)->void;


 private:
	  typedef std::chrono::high_resolution_clock::time_point Time;

	  std::mutex m_mutex;
	  Time m_jobStartTime;
	  Time m_shuffleStartTime;
	  int m_jobRunTimeMicroS;
	  int m_shuffleRunTimeMicroS;
	  std::vector<RunStatistic*> m_mapRuns;
	  std::vector<RunStatistic*> m_reduceRuns;
};
#endif
