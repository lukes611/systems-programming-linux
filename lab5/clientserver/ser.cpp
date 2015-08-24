
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "LSockets.h"
#include <sys/types.h>
#include <sys/socket.h> //for socket() function
#include <netinet/in.h> //for sockaddr_in
#include <unistd.h>
using namespace std;

int main()
{
	socklen_t clilen;
	cout << "howdy " << endl;
	struct sockaddr_in name, cli_name;
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0) cout << "error creating socket" << endl;
	
	//bzero(&name, sizeof(name));
	
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = (INADDR_ANY);
	name.sin_port = htons(8142);
	if(bind(sd, (sockaddr*) &name, sizeof(name)) < 0) cout << "error binding " << endl;
	listen(sd, 5);
	cout << "listening ..." << endl;
	int psd = accept(sd, (sockaddr*) &cli_name, &clilen);
	while(true)
	{
		char tmp[1024];
		int N = recv(psd, tmp, 1023, 0);
		if(N == 0) continue;
		tmp[N] = 0x00;
		string s = tmp;
		cout << s << endl;
		if(s == "quit" || s == "quit\n") break;
		
	}
	close(psd);
	close(sd);
	return 0;
}