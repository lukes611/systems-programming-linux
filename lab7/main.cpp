#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int apipe[2], apipe2[2];

int compute(string)
{
	return 5;
}

int child()
{
	while(true)
	{
		char buf[200];
		buf[read(apipe[0], buf, 200)] = 0x00;
		string st = buf;
		if(st == "quit") break;
		sprintf(buf, "%i", compute(st));
		string rv = buf;
		write(apipe2[1], rv.c_str(), rv.size());
	}
}

void ex1()
{
	if(pipe(apipe) < 0){ cout << "ew" << endl; exit(5); }
	if(pipe(apipe2) < 0){ cout << "ew2" << endl; exit(5); }
	int pid = fork();
	if(pid == 0)
	{
		child();
		exit(1);
	}
	while(true)
	{
		string st;
		getline(cin, st);
		write(apipe[1],st.c_str(), st.size());
		if(st == "quit") break;
		char buf[200];
		buf[read(apipe2[0], buf, 200)]=0x00;
		st = buf;
		cout << buf << endl;
	}
	int s;
	waitpid(pid, &s, 0);
	
}

int main()
{
	ex1();
	return 0;
}