#include <iostream>
#include <cstring>
#include <vector>

extern char** environ;

inline bool findPatch(std::string line, std::string& value)
{
	std::string key = "PATH=";
	if (line.find(key) != std::string::npos)
	{
		if (line.substr(0 ,key.size()) == key)
		{
			value = line.substr(key.size(), line.size());
			//std::cout << "17 evem PATjh "<< value << std::endl;
			return true;
		}
	}
	return false;
}


inline std::vector<std::string> strTokenizer(std::string line, std::string delimeter)
{	
	std::vector<std::string> tokens;

	size_t startPos = 0;
	size_t endPos ;
	while (endPos != std::string::npos)
	{
		endPos = line.find(delimeter, startPos);
		tokens.push_back(line.substr(startPos, (endPos == std::string::npos) ? std::string::npos :  endPos - startPos) );
		startPos = (endPos >  (std::string::npos - delimeter.size()) ? std::string::npos : endPos + delimeter.size());
	}

	return tokens;
}


inline bool findCommand(std::string& com)
{
		char** env = environ;
		std::string val;
		
		while(*env != nullptr) {
			if(findPatch(*env, val))
			{
				//std::cout << "evem PATjh "<< val << std::endl;
				std::vector<std::string> paths = strTokenizer(val, ":");	
				for (auto path : paths)
				{
					std::string fullPath = path +  std::string("/") + com; 
					//std::cout << "full p "<<fullPath << std::endl;
					if( access(fullPath.c_str(), 0) == 0 ) 
					{
						com = fullPath;
						return true;
					}
				}
			}
			++env;
		}
		return false;
}

inline void exitIfNotSucceed(const int err, const std::string& msg)
{
	if (err == -1)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);	
	}
}