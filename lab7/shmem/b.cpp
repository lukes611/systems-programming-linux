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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;


int main()
{
	int keyval = 5142;
	int pt = shmget(keyval, 200, 0644 | IPC_CREAT);
	void * d = shmat(pt, 0,0);
	if(d == NULL)
	{
		cout << "bad ..." << endl;
		exit(5);
		
	}
	int * a = (int*)d;
	*a = 5;
	cout << "put 5 there" << endl;
	
	if(fork() == 0)
	{
		int pt2 = shmget(keyval, 200, 0644);
		void * d2 = shmat(pt2, 0,0);
		int * a2 = (int*)d2;
		cout << *a2 << endl;
		exit(5);
	}
	int s;
	wait(&s);
	
	return 0;
}