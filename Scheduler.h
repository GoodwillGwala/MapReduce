#pragma once

#include <iostream>
#include <thread>
#include "Job.cpp"

template<typename Job>
auto MapJob(Job* job)->void;

template<typename Job>
auto ReduceJob(Job* job)->void;


class ThreadedScheduler
{
 	public:
  		template<typename Job>
      	auto RunJob(Job& job)->void;

};


class JobScheduler
{
 public:
     template<typename Job>
     auto RunJob(Job& job)->void;
};
