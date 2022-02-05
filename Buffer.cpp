#include "Buffer.h"

template<typename MapPolicy>
Buffer<MapPolicy>::Buffer()
: m_data(new InputType())
, m_drainData(nullptr)
{}

template<typename MapPolicy>
auto Buffer<MapPolicy>::Combine(Buffer<MapPolicy>* other)->void
{
    std::lock_guard<std::mutex> guard(m_mutex);


	InputTypeIterator Otheriter = other->m_data->begin();

	for (; Otheriter != other->m_data->end(); Otheriter++)
	{

	    InputTypeConstIterator kvpLookup = m_data->find(Otheriter->first);

		if (kvpLookup == m_data->end())
		{
		    std::shared_ptr<ValueVectorType> vector { new ValueVectorType() };
			vector->template insert<ValueVectorIteratorType>(vector->end(), Otheriter->second->begin(), Otheriter->second->end());
			m_data->insert( { Otheriter->first, vector } );
		}
		else
		kvpLookup->second->template insert<ValueVectorIteratorType>
		(
		    kvpLookup->second->end(), Otheriter->second->begin(),Otheriter->second->end()
		);
	}
}

template<typename MapPolicy>
auto Buffer<MapPolicy>::AddData(typename MapPolicy::IntermediateKeyType key, typename MapPolicy::IntermediateValueType value)->void
{
    InputTypeConstIterator kvpLookup = m_data->find(key);

	if (kvpLookup == m_data->end())
	{
	    std::shared_ptr<ValueVectorType> vector { new ValueVectorType() };
		vector->reserve(100);
		vector->push_back(value);
		m_data->insert(std::pair<typename MapPolicy::IntermediateKeyType, std::shared_ptr<ValueVectorType>>(key, vector));
	}
    else
    kvpLookup->second->push_back(value);
}


template<typename MapPolicy>
auto Buffer<MapPolicy>::Shuffle()->void
{
   	m_drainData =  new VectorOfTupplesType();
	for (InputTypeIterator iter = m_data->begin(); iter != m_data->end(); iter++)
	  	m_drainData->push_back(TupleType(iter->first, iter->second));

    m_currentIndex = 0;
    m_maxIndex = m_drainData->size() - 1;
}


template<typename MapPolicy>
auto Buffer<MapPolicy>::Size()->int
{
    return m_drainData->size();
}

template<typename MapPolicy>
auto Buffer<MapPolicy>::GetData(typename MapPolicy::IntermediateKeyType& key, ValueVectorIteratorType& iterStart, ValueVectorIteratorType& iterEnd)->bool
{
    auto thisIndex = std::atomic_fetch_add(&m_currentIndex, 1);

    if (thisIndex > m_maxIndex)
      	return false;

    key = (*m_drainData)[thisIndex].Key;
    iterStart = (*m_drainData)[thisIndex].Value->begin();
    iterEnd = (*m_drainData)[thisIndex].Value->end();

    return true;
}


template<typename MapPolicy>
auto Buffer<MapPolicy>::GetData()->InputTypePtr
{

  	return m_data;

}
