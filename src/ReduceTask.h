#ifndef _REDUCE_
#define _REDUCE_

#include "Job.h"

class ReduceTask
{
	public:
		typedef 	std::string KeyType;
		typedef 	int ValueType;

		template<typename Runner, typename ItorType>
		auto Reduce(Runner& runner, KeyType& key, ItorType& begin, ItorType& end)->void;

};
#endif
