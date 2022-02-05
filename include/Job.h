#ifndef _JOB_
#define _JOB_

#include "Drain.cpp"
#include "Source.cpp"
#include "Statistics.cpp"
#include "Buffer.cpp"


template<
			typename MapPolicy,
			typename ReducePolicy,
			typename SourcePolicy = Source<MapPolicy>,
			typename DrainPolicy  = Drain<ReducePolicy>,
			typename BufferPolicy = Buffer<MapPolicy>
    	>

class Job
{
	public:
          typedef MapPolicy MapPolicyType;
          typedef ReducePolicy ReducePolicyType;
          typedef typename SourcePolicy::InputType SourceInputType;
          typedef typename DrainPolicy::InputMapType DrainMapInputType;
          typedef typename DrainPolicy::InputType DrainInputType;
          typedef typename BufferPolicy::ValueVectorIteratorType ReduceIteratorType;

          class MapTaskRunner
          {
		        public:
		        auto Emit(typename MapPolicy::IntermediateKeyType key,typename MapPolicy::IntermediateValueType value)->void;


		        BufferPolicy LocalBuffer;
          };

          class ReduceTaskRunner
          {
		       public:
				    ReduceTaskRunner(std::shared_ptr<DrainPolicy> drain);


				    inline auto Emit(typename ReducePolicy::KeyType key, typename ReducePolicy::ValueType value)->void;


		       private:
		        	std::shared_ptr<DrainPolicy> m_drain;
		        	friend class Job;
          };


          Job(SourceInputType& source, DrainMapInputType& drain, DrainInputType& outputPath);


          ~Job()
          {}

          auto Shuffle()->void;


	public:

          std::shared_ptr<BufferPolicy> DataBuffer;
          std::shared_ptr<SourcePolicy> Source;
          std::shared_ptr<DrainPolicy> Drain;
          std::shared_ptr<JobRunStatistics> RunStatistics;
};
#endif
