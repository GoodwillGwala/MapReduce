#include "Drain.h"

template<typename ReducePolicy>
Drain<ReducePolicy>::Drain(InputMapType* destinationMap, InputType* outputPath)
:m_data(destinationMap)
,m_outFile{new std::ofstream(*outputPath)}
{}

template<typename ReducePolicy>
auto Drain<ReducePolicy>::AddData(typename ReducePolicy::KeyType key, typename ReducePolicy::ValueType value)->void
{
    std::lock_guard<std::mutex> guard(m_mutex);
    *m_outFile << key << ":" << value << std::endl;
    m_data->insert(std::make_pair ( key, value ) );
}
