#include "MapTask.h"

template<typename Runner>
auto MapTask::Map(Runner& runner, KeyType& key, ValueType& value)->void
{
	auto line_number = 0;
	std::string line;
    KeyType stopWords;

    InputFileType stopFile;
	stopFile.open("stopWords.txt");
	std::getline( stopFile , stopWords);

	while (std::getline(*value, line))
		if(!line.empty(), line_number++)
		{
     		InputStreamType line_stream( line );
			KeyType word;
			while( line_stream >> word )
	    	(Trim(word) && (stopWords.find(word) == std::string::npos)) ? runner.Emit(word, line_number) : void() ;
		}

	stopFile.close();
}


auto MapTask::Trim(KeyType& word)->bool
{
	word.erase( std::remove_if( word.begin(), word.end() , ::ispunct), word.end());
	word.erase( std::remove_if( word.begin(), word.end() , ::isdigit), word.end());
  	std::transform(begin(word),end(word),begin(word), ::tolower);

  	return word.size()>3 && !word.empty();
}
