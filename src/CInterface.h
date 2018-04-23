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
static const string sEMPTY = "";

class CInterface
{
public:
	CInterface();
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

	void v_print_err_msg();

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
