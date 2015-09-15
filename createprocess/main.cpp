#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "LCreateProcess.h"
using namespace ll_cprocess;
using namespace std;


int main()
{
	
	cout << "sup yo!" << endl;
	string program = "./p2.exe";
	ll_process_id id;
	vector<string> args;
	args.push_back("luke");
	args.push_back("is");
	args.push_back("the");
	args.push_back("man");
	if(create_process(program, args, id))
	{
		cout << wait_for_process(id) << endl;
		cout << "yay it worked" << endl;
	}
	
	return 0;
}