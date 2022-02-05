#ifndef _SOURCE_
#define _SOURCE_

#include <mutex>
#include <vector>
#include <iostream>

template<typename MapPolicy>
class Source
{
	public:
  		typedef std::vector<std::string> InputType;

  		Source(InputType* directoryPaths);

  		auto Size()->int;

  		auto GetData(typename MapPolicy::KeyType& key, typename MapPolicy::ValueType& value)->bool;

 	private:
	  InputType m_source;
	  std::mutex m_mutex;
};
#endif
