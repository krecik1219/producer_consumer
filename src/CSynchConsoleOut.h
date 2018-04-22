#ifndef SRC_CSYNCHCONSOLEOUT_H_
#define SRC_CSYNCHCONSOLEOUT_H_

#include <mutex>
#include <iostream>

class CSynchConsoleOut
{
public:

	static CSynchConsoleOut & pcGetInstance();
	CSynchConsoleOut & operator=(CSynchConsoleOut const & cOther) = delete;
	CSynchConsoleOut(CSynchConsoleOut const & cOther) = delete;

	friend void operator<<(CSynchConsoleOut & synchOut, std::string text);

private:

	CSynchConsoleOut();

	static std::mutex locker;
	static CSynchConsoleOut * instance;
};


#endif /* SRC_CSYNCHCONSOLEOUT_H_ */
