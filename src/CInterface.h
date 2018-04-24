#ifndef SRC_CINTERFACE_H_
#define SRC_CINTERFACE_H_

#include <iostream>
#include <string>
#include <vector>
#include "CProdConsManager.h"
using namespace std;

static const string sMAIN_CMD_LIST =
		"Producer <-> Consumer problem\n"
		"Select on of the following options:\n"
		"init - initializes new producer consumer problem entity\n"
		"test - runs sample problem entity\n"
		"exit - exit the program\n";

static const string sINIT_CMD_LIST =
		"Let's create buffer, then producers and consumers\n"
		"CAUTION: total number of consumed elements should be equal to number of produced elements\n\n"
		"buffer <buffer_size: int> - creates buffer with size of <buffer_size>\n"
		"producer <producing_time [ms]: int> <number_of_producing_cycles: int> - creates producer with given parameters\n"
		"consumer <consuming_time_interval [ms]: int> <number_of_consuming_cycles: int> <number_of_elements_consumed_per_cycle: int> - creates consumer with given parameters\n"
		"start - runs this problem entity\n"
		"quit - discards this problem entity\n";

static const char cSPACE = ' ';
static const string sEMPTY_CMD = "";
static const string sINIT_CMD = "init";
static const string sTEST_CMD = "test";
static const string sEXIT_CMD = "exit";
static const string sTEST_RUN_MSG = "Sample test";
static const string sTEST_FINISHED_MSG = "Test finished";
static const string sCMD_NOT_FOUND_MSG = "Command not found";
static const string sBUFFER_CMD = "buffer";
static const string sBUFFER_ALREADY_CREATED_ERR_MSG = "Buffer has been already created";
static const string sBUFFER_CREATED_MSG = "Buffer created";
static const string sPRODUCER_CMD = "producer";
static const string sCONSUMER_CMD = "consumer";
static const string sPRODUCER_CREATED_MSG = "Producer created";
static const string sCONSUMER_CREATED_MSG = "Consumer created";
static const string sSTART_CMD = "start";
static const string sQUIT_CMD = "quit";
static const string sBUFFER_SIZE_ERROR = "Buffer size must be positive integer";
static const string sPRODUCING_CYCLES_VALUE_ERROR = "Number of producing cycles must be positive integer";
static const string sPRODUCING_TIME_VALUE_ERROR = "Producing time must be positive integer: milliseconds";
static const string sELEMENTS_CONSUMED_PER_CYCLE_ERROR = "Number of elements consumed per cycle must be positive integer";
static const string sCONSUMING_CYCLES_VALUE_ERROR = "Number of consuming cycles must be positive integer";
static const string sCONSUMING_TIME_VALUE_ERROR = "Consuming time interval must be positive integer: milliseconds";
static const string sPROD_CONS_ERR_OK_MSG = "Problem run has finished";
static const string sPROD_CONS_ERR_NO_CONSUMER_MSG = "You must create at least one consumer";
static const string sPROD_CONS_ERR_NO_PRODUCER_MSG = "You must create at least one producer";
static const string sPROD_CONS_ERR_NO_BUFFER_MSG = "You must create buffer";

class CInterface
{
public:
	CInterface();
	CInterface(CInterface const & cOther) = delete;
	CInterface & operator=(CInterface const & cOther) = delete;
	~CInterface();

	void vRun();

private:

	void v_print_main_menu();
	void v_get_user_input();
	void v_select_main_action();
	void v_single_arg(string const & sSubStr);
	void v_run_init_submenu();
	void v_run_test();
	void v_print_sub_menu();
	void v_select_sub_action();
	void v_process_buffer_input(string const & sSubStr);
	void v_process_producer_input(string const & sSubStr);
	void v_process_consumer_input(string const & sSubStr);
	void v_match_err_code(CProdConsError errCode);
	void v_print_err_msg();
	void v_print_msg(string const & sMsg);

	static const int i_INPUT_TO_PARSE_ARRAY_SIZE = 2;

	bool b_run_interface;
	bool b_input_correct;
	bool b_run_sub_interface;
	string s_input;
	string ps_input_to_parse[i_INPUT_TO_PARSE_ARRAY_SIZE]; // [0] string is the one that is being parsed at the moment, [1] is the rest of input waiting for parsing
	vector<string> vs_command_set;
	string s_error_msg;

	unique_ptr<CProdConsManager> pc_manager;
};

static bool bIsInteger(string const & sToCheck);

#endif /* SRC_CINTERFACE_H_ */
