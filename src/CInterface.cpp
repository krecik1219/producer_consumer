#include "CInterface.h"

CInterface::CInterface() :
b_run_interface(false), b_input_correct(false), b_run_sub_interface(false)
{
	pc_manager = make_unique<CProdConsManager>();
}

CInterface::~CInterface()
{
	// TODO Auto-generated destructor stub
}

void CInterface::vRun()
{
	b_run_interface = true;

	v_print_main_menu();

	while(b_run_interface)
	{
		v_get_user_input();
		v_select_main_action();
	}

}

void CInterface::v_get_user_input()
{
	getline(cin, s_input);
}

// copy-pasted from some old project
void CInterface::v_single_arg(string const & sSubStr)
{
	int i_substr_length = sSubStr.length();
	int i_arg_end = 0;
	int i_arg_start = 0;
	bool b_arg_start = false;
	bool b_arg_end = false;
	for (int ii = 0; ii < i_substr_length && !b_arg_end; ii++)
	{
		if (!b_arg_start && sSubStr[ii] != cSPACE)
		{
			i_arg_start = ii;
			b_arg_start = true;
		}
		if (b_arg_start && ((sSubStr[ii + 1] == '\0') || (sSubStr[ii + 1] == cSPACE)))
		{
			i_arg_end = ii;
			b_arg_end = true;
		}
	}
	if (sSubStr[0] != '\0')
	{
		ps_input_to_parse[0] = sSubStr.substr(i_arg_start, i_arg_end - i_arg_start + 1);
		ps_input_to_parse[1] = sSubStr.substr(i_arg_end + 1, i_substr_length - i_arg_end);
	}
	else
	{
		ps_input_to_parse[0] = sEMPTY;
		ps_input_to_parse[1] = sEMPTY;
	}
}

void CInterface::v_select_main_action()
{
	v_single_arg(s_input);
	if(ps_input_to_parse[0] == "init")
	{
		v_run_init_submenu();
		v_print_main_menu();
	}
	else if(ps_input_to_parse[0] == "test")
	{
		cout << "Sample test" << endl;
		v_run_test();
		cout << endl << "Test finished" << endl;
		v_print_main_menu();
	}
	else if(ps_input_to_parse[0] == "exit")
	{
		b_run_interface = false;
	}
	else
	{
		s_error_msg = "command not found";
		v_print_err_msg();
	}

	vs_command_set.clear();
}

void CInterface::v_run_init_submenu()
{
	b_run_sub_interface = true;

	v_print_sub_menu();

	while (b_run_sub_interface)
	{
		v_get_user_input();
		v_select_sub_action();
	}
}

void CInterface::v_print_main_menu()
{
	cout << sMAIN_CMD_LIST << endl;
}

void CInterface::v_run_test()
{
	pc_manager->vRunSampleTest();
}

void CInterface::v_print_sub_menu()
{
	cout << sINIT_CMD_LIST << endl;
}

void CInterface::v_select_sub_action()
{
	v_single_arg(s_input);
	if(ps_input_to_parse[0] == "buffer")
	{
		v_process_buffer_input(ps_input_to_parse[1]);
		if(b_input_correct)
		{
			int i_buffer_size = stoi(vs_command_set.at(0));
			bool b_buffer_created = pc_manager->bCreateBuffer(i_buffer_size);
			if(!b_buffer_created)
			{
				s_error_msg = "Buffer has been already created";
				v_print_err_msg();
			}
		}
		else
			v_print_err_msg();
	}
	else if(ps_input_to_parse[0] == "producer")
	{
		// TODO
	}
	else if(ps_input_to_parse[0] == "consumer")
	{
		// TODO
	}
	else if(ps_input_to_parse[0] == "start")
	{
		// TODO
	}
	else if (ps_input_to_parse[0] == "quit")
	{
		b_run_sub_interface = false;
		pc_manager->vResetManager();
	}
	else
	{
		s_error_msg = "command not found";
		v_print_err_msg();
	}

	vs_command_set.clear();
}

void CInterface::v_process_buffer_input(const string& sSubStr)
{
	v_single_arg(sSubStr);
	b_input_correct = true;
	if(bIsInteger(ps_input_to_parse[0]))
	{
		if(stoi(ps_input_to_parse[0]) > 0)
		{
			vs_command_set.push_back(ps_input_to_parse[0]);
		}
		else
		{
			b_input_correct = false;
			s_error_msg = "Buffer size must be positive integer";
		}
	}
	else
	{
		b_input_correct = false;
		s_error_msg = "Buffer size must be positive integer";
	}
}

void CInterface::v_print_err_msg()
{
	cout << s_error_msg << endl;
}

// copy-pasted from some old project
bool bIsInteger(const string& sToCheck)
{
	int i_str_length = sToCheck.length();
	bool b_is_number = true;
	if (sToCheck[0] == 48 && i_str_length > 1)
		b_is_number = false;
	if (sToCheck[0] < 48 || sToCheck[0] > 57)
		b_is_number = false;
	if (sToCheck[0] == 45)
		b_is_number = true;
	for (int ii = 1; ii < i_str_length && b_is_number; ii++)
	{
		if (sToCheck[ii] < 48 || sToCheck[ii] > 57)
			b_is_number = false;
	}
	if ((sToCheck[0] == 45 && i_str_length == 1) || sToCheck[0] == '\0')
		b_is_number = false;
	return b_is_number;
}
