#include "Source.h"

template<typename MapPolicy>
Source<MapPolicy>::Source(InputType* directoryPaths)
: m_source(*directoryPaths)
{}


template<typename MapPolicy>
auto Source<MapPolicy>::Size()->int
{
	return m_source.size();
}

template<typename MapPolicy>
auto Source<MapPolicy>::GetData(typename MapPolicy::KeyType& key, typename MapPolicy::ValueType& value)->bool
{
	m_mutex.lock();
	if (m_source.empty())
	{
		m_mutex.unlock();
		return false;
	}

	key = m_source.back();
	m_source.pop_back();
	m_mutex.unlock();
	std::shared_ptr<std::ifstream> stream (new std::ifstream(key.c_str()));

	if (!stream)
	{
		std::cout << "failed to load file " << key << std::endl;
		return false;
	}
	value = stream;
	return true;
}
