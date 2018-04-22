#include "CSynchConsoleOut.h"

CSynchConsoleOut * CSynchConsoleOut::instance = nullptr;
std::mutex CSynchConsoleOut::locker;

CSynchConsoleOut::CSynchConsoleOut()
{

}

CSynchConsoleOut & CSynchConsoleOut::pcGetInstance()
{
	if(instance == nullptr)
		instance = new CSynchConsoleOut();
	return *instance;
}

void operator<<(CSynchConsoleOut & cSyncOut, std::string text)
{
	std::lock_guard<std::mutex> lock(cSyncOut.locker);
	std::cout<<text<<std::endl;
}



