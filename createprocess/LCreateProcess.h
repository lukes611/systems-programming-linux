//LCreateProcess allows you to start processes under linux or Windows

#pragma once


#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#include <processthreadsapi.h>
typedef PROCESS_INFORMATION ll_process_id;

#else
#include <unistd.h>
#include <sys/wait.h>
typedef int ll_process_id;
#endif 


namespace ll_cprocess
{

#ifdef WIN32


	//Linux edition
bool create_process(std::string process_name, std::vector<std::string> args, ll_process_id & id_out)
{
	STARTUPINFO info={sizeof(info)};
	PROCESS_INFORMATION processInfo;
	std::string runthis = process_name;
	for(int i = 0; i < args.size(); i++) runthis += " " + args[i];
	WCHAR * cmd = new WCHAR[runthis.size()+1];
	for(int i = 0; i < runthis.size(); i++) cmd[i] = (WCHAR) runthis[i];
	cmd[runthis.size()] = (WCHAR)0x00;

	if (CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		id_out = processInfo;
		delete [] cmd;
		return true;
	}

	delete [] cmd;
	return false;
}

int wait_for_process(ll_process_id pid)
{
	WaitForSingleObject(pid.hProcess, INFINITE);
	CloseHandle(pid.hProcess);
	CloseHandle(pid.hThread);
	return 0;
}

#else
	
//Linux edition
bool create_process(std::string process_name, std::vector<std::string> args, ll_process_id & id_out)
{
	int pid = fork();
	if(pid < 0)
	{
		return false;
	}
	else if(pid == 0)
	{
		char * * cargs = new char * [args.size()+1];
		char * cmd = new char[process_name.size()];
		strcpy(cmd, process_name.c_str());
		for(int i = 0; i < args.size(); i++)
		{
			cargs[i] = new char[args[i].size()];
			strcpy(cargs[i], args[i].c_str());
		}
		cargs[args.size()] = NULL;
		int rv = execvp(cmd, cargs);
		if(rv < 0)
		{
			std::cout << "execv didnt work" << std::endl; 
		}
		for(int i = 0; i < args.size(); i++)
		{
			delete [] cargs[i];
		}
		delete [] cargs;
		delete [] cmd;
		exit(1);
	}
	id_out = pid;
	return true;
}

int wait_for_process(ll_process_id pid)
{
	int stat_lck;
	int tmp = waitpid(pid, &stat_lck, 0);
	return WEXITSTATUS(stat_lck);
}


#endif

}