#ifndef _MAP_
#define _MAP_
#include "Job.h"



class MapTask
{
	public:

		typedef 	std::string KeyType;
		typedef 	std::shared_ptr<std::ifstream> ValueType;
		typedef 	std::string IntermediateKeyType;
		typedef 	int IntermediateValueType;


  		template<typename Runner>
		auto Map(Runner& runner, KeyType& key, ValueType& value)->void;
	private:

		auto Trim(KeyType& word)->bool;


	private:

		typedef     std::ifstream InputFileType;
		typedef		std::istringstream InputStreamType;
		typedef		std::string WordType;
};
#endif
