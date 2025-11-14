#pragma once
#include <iostream>
#include <fstream>
#include "Room.hpp"
class Commands
{
public:
	static void help()
	{
		std::cout << "The following commands are supported:" << std::endl;
		std::cout <<"open <file>\t ---> opens and loads data from <file>" << std::endl;
		std::cout <<"close \t\t ---> closes currently opened file" << std::endl;
		std::cout <<"save \t\t ---> saves the changes to the currently opened file" << std::endl;
		std::cout <<"saveas <file> \t ---> save the currently opened file and its changes in <file>" << std::endl;
		std::cout <<"help \t\t ---> prints this information :)" << std::endl;
		std::cout <<"exit \t\t ---> exits the program" << std::endl;
	}
	static void exit(int exitCode)
	{
		std::cout << "exiting the program" << std::endl;
		std::exit(exitCode);
	}

	static Room& open(const char* fileLoc)
	{
		std::ifstream ifstr(fileLoc);
		Room r(ifstr);
		return r;
	}
};


bool strStartsWith(const char* fullStr, const char* possBegin)
{
	size_t fullSize = strlen(fullStr), possSize = strlen(possBegin);
	if (fullSize < possSize) return false;
	for (int i = 0; i < possSize; i++)
	{
		if (fullStr[i] != possBegin[i]) return false;
	}
	return true;
}