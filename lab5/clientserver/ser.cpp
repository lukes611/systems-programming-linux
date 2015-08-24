
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
//#include <sys/types.h>
#include <sys/socket.h> //for socket() function
#include <netinet/in.h> //for sockaddr_in
using namespace std;

int main()
{
	cout << "howdy " << endl;
	struct sockaddr_in name;
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sd, (sockaddr*) &name, sizeof(name));
	listen(sd, 5);
	int psd = accept(sd, 0, 0);
	while(true)
	{
		char tmp[1024];
		int N = recv(psd, tmp, 1023, 0);
		if(N == 0) continue;
		tmp[N] = 0x00;
		string s = tmp;
		cout << "got: " << s << endl;
		if(s == "quit" || s == "quit\n") break;
		
	}
	return 0;
}