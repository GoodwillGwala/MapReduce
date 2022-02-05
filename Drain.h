#ifndef _DRAIN_
#define _DRAIN_
#include <mutex>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <memory>


template<typename ReducePolicy>
class Drain
{
 public:

    typedef std::unordered_map<typename ReducePolicy::KeyType, typename ReducePolicy::ValueType > InputMapType;
    typedef std::string InputType;

  	Drain(InputMapType* destinationMap, InputType* outputPath = "output.txt");

    ~Drain()
    {
    	m_outFile->close();

    }

    // Thread Safe
    void AddData(typename ReducePolicy::KeyType key, typename ReducePolicy::ValueType value);

 private:
  	std::shared_ptr<InputMapType> 	m_data;
  	std::shared_ptr<std::ofstream>  m_outFile;
  	std::mutex   					m_mutex;
};
#endif
