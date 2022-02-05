#include <sstream>
#include <algorithm>


#include "MapTask.cpp"
#include "ReduceTask.cpp"
#include "Scheduler.cpp"


class MapTask;
class ReduceTask;

typedef Job<
			MapTask,
			ReduceTask,
			Source<MapTask>,
			Drain<ReduceTask>,
			Buffer<MapTask>
		   > WordCountJob;


typedef std::shared_ptr<std::unordered_map<std::string,std::shared_ptr<std::vector<int>> >> MapType;



template<typename Iterator>
auto kQuery(const Iterator begin,const Iterator end, const int k)->void
{
	typedef std::pair<std::string, int> Tuple;


	std::vector<Tuple> TopKQueryVector(k);
	std::partial_sort_copy(begin, end, TopKQueryVector.begin(),TopKQueryVector.end(),[](Tuple const& mapItem,Tuple const& vectorItem)
    {
      	return mapItem.second > vectorItem.second;
    });

	for(const auto& item: TopKQueryVector )
		std::cout<<item.first<<": "<<item.second<<std::endl;

}


auto inverted_index(const MapType mapQuery, const std::string& search_words )->void
{

	std::istringstream search_stream(search_words);
	std::string word;

	while(search_stream >> word)
	{
		auto found  = mapQuery->find(word);

		if(found != mapQuery->end())
		{
		   std::cout <<"\nWord found: "<<word<<std::endl;

		   auto begin = found->second->begin();
	  	   auto end   = found->second->end();

           std::cout << (*found).first << " : ";

           for (auto count = 0; (count<50 && begin != end); begin++, count++ )
           {
              std::cout << (*begin) << " ";
           }
           std::cout<<"\n" << std::endl;
		}
		else std::cout<<"\nWord not found: "<<word<<std::endl;
	}

}


//    g++ [inputFiles separated by space] [outputFile] [-lpthread]
auto main(int argc, char* argv[])->int
{

//	  Capture Source and Drain details
	  std::vector<std::string> inputFiles(argv + 1, argv + (argc - 1));
	  std::string outputFile(argv[argc - 1]);

	  typedef std::unordered_map<std::string,int > MapType;

	  MapType outputMap;

//    Begin Threaded MapReduce
	  std::cout << "\nBeginning Threaded MapReduce Job" << std::endl;
	  std::cout << "================================\n" << std::endl;
	  {
		  WordCountJob job(inputFiles, outputMap, outputFile);

		  ThreadedScheduler threadedScheduler;
		  threadedScheduler.RunJob(job);
		  job.RunStatistics->PrintStatistics();
	  }

//    Begin Concurrent MapReduce
	  std::cout << "\nBeginning MapReduce Job" << std::endl;
	  std::cout << "================================\n" << std::endl;

	  WordCountJob job(inputFiles, outputMap, outputFile);
	  JobScheduler jobScheduler;
	  jobScheduler.RunJob(job);
	  job.RunStatistics->PrintStatistics();



//	  K-Query 10
	  auto  K = 0;
	  std::cout<<"\nEnter K Query"<<std::endl;
	  std::cout << "============" << std::endl;

	  std::cin>>K;
	  kQuery(outputMap.begin(), outputMap.end(), K);



//	  K-Query 20
	  K = 0;
	  std::cout<<"\nEnter K Query"<<std::endl;
	  std::cout << "============" << std::endl;

	  std::cin>>K;
	  kQuery(outputMap.begin(), outputMap.end(), K);

	  std::cin.ignore();

//	  Inverted index search
	  std::cout<<"\nPlease enter a list of words to search for :"<<std::endl; // words separated by space
	  std::cout << "============================================\n" << std::endl;

	  std::string search_words;

	  std::getline(std::cin, search_words);

	  inverted_index(job.DataBuffer->GetData(), search_words);

}
