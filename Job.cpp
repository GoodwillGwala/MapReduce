#include "Job.h"


template<
			typename MapPolicy,
			typename ReducePolicy,
			typename SourcePolicy ,
			typename DrainPolicy  ,
			typename BufferPolicy
    	>

Job<MapPolicy,ReducePolicy,SourcePolicy,DrainPolicy, BufferPolicy>::Job(SourceInputType& source, DrainMapInputType& drain, DrainInputType& outputPath)
: DataBuffer(new BufferPolicy())
, Source(new SourcePolicy(&source))
, Drain(new DrainPolicy(&drain,&outputPath))
, RunStatistics(new JobRunStatistics())
{}

template<
			typename MapPolicy,
			typename ReducePolicy,
			typename SourcePolicy ,
			typename DrainPolicy  ,
			typename BufferPolicy
    	>

auto Job<MapPolicy,ReducePolicy,SourcePolicy,DrainPolicy, BufferPolicy>::MapTaskRunner::Emit(typename MapPolicy::IntermediateKeyType key,typename MapPolicy::IntermediateValueType value)->void
{

	LocalBuffer.AddData(key, value);
}



template<
			typename MapPolicy,
			typename ReducePolicy,
			typename SourcePolicy ,
			typename DrainPolicy  ,
			typename BufferPolicy
    	>

Job<MapPolicy,ReducePolicy,SourcePolicy,DrainPolicy, BufferPolicy>::ReduceTaskRunner::ReduceTaskRunner(std::shared_ptr<DrainPolicy> drain)
: m_drain(drain)
{}

template<
			typename MapPolicy,
			typename ReducePolicy,
			typename SourcePolicy ,
			typename DrainPolicy  ,
			typename BufferPolicy
    	>

auto Job<MapPolicy,ReducePolicy,SourcePolicy,DrainPolicy, BufferPolicy>::ReduceTaskRunner::Emit(typename ReducePolicy::KeyType key,typename ReducePolicy::ValueType value)->void
{

	m_drain->AddData(key, value);
}

template<
			typename MapPolicy,
			typename ReducePolicy,
			typename SourcePolicy ,
			typename DrainPolicy  ,
			typename BufferPolicy
    	>

auto Job<MapPolicy,ReducePolicy,SourcePolicy,DrainPolicy, BufferPolicy>::Shuffle()->void
{
	RunStatistics->BeginShuffle();
	DataBuffer->Shuffle();
	RunStatistics->EndShuffle();
}
