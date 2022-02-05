#include "ReduceTask.h"

template<typename Runner, typename ItorType>
auto ReduceTask::Reduce(Runner& runner, KeyType& key, ItorType& begin, ItorType& end)->void
{
	int count = 0;
	for(; begin != end; begin++, count++){}
	runner.Emit(key, count);
}
