#ifndef _BUFFER_
#define _BUFFER_

#include <atomic>
#include <mutex>
#include <unordered_map>
#include <vector>


template<typename MapPolicy>
class Buffer
{
	public:

	  typedef std::vector<typename MapPolicy::IntermediateValueType> ValueVectorType;

	  typedef std::unordered_map<typename MapPolicy::IntermediateKeyType, std::shared_ptr<ValueVectorType>> InputType;

	  typedef std::shared_ptr<InputType> InputTypePtr;

	  typedef typename std::unordered_map<typename MapPolicy::IntermediateKeyType, std::shared_ptr<ValueVectorType>>::iterator InputTypeIterator;

      typedef typename std::unordered_map< typename MapPolicy::IntermediateKeyType, std::shared_ptr<ValueVectorType>>::const_iterator InputTypeConstIterator;

      typedef typename ValueVectorType::iterator ValueVectorIteratorType;

      template<typename KeyType, typename ValueType>

      struct Tupple
      {
		    Tupple(KeyType key, ValueType value)
		    : Key(key)
		    , Value(value)
		    {}

		    KeyType Key;
		    ValueType Value;
      };



  	  typedef Tupple<typename MapPolicy::IntermediateKeyType, std::shared_ptr<std::vector<typename MapPolicy::IntermediateValueType>>> TupleType;

  	  typedef typename std::vector<TupleType> VectorOfTupplesType;

	  Buffer();

	  ~Buffer()
	  {}

      auto Combine(Buffer<MapPolicy>* other)->void;


   auto AddData(typename MapPolicy::IntermediateKeyType key, typename MapPolicy::IntermediateValueType value)->void;


   auto Shuffle()->void;



   auto Size()->int;


   auto GetData(typename MapPolicy::IntermediateKeyType& key, ValueVectorIteratorType& iterStart, ValueVectorIteratorType& iterEnd)->bool;




  InputTypePtr GetData();


 private:
  // Source

  InputTypePtr m_data;
  std::mutex m_mutex;

  // Drain
  VectorOfTupplesType* m_drainData;
  std::atomic<int> m_currentIndex;
  int m_maxIndex;
};
#endif
