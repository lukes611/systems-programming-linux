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


LServer::LServer()
{
	
}
LServer::LServer(const LServer & in)
{
	port = in.port;
	primary = in.primary;
	client = in.client;
}
LServer & LServer::operator = (const LServer & in)
{
	if(this == &in) return *this;
	port = in.port;
	primary = in.primary;
	client = in.client;
	return *this;
}
LServer::LServer(int port)
{
	open(port);
}
void LServer::error(string er)
{
	cout << er << endl;
	exit(5);
}
void LServer::open(int port)
{
	this->port = port;
	setup();
}
void LServer::shutdown()
{
	end();
	close(primary);
}
void LServer::end()
{
	close(client);
}
string LServer::read(int max)
{
	char * tmp = new char[max];
	int N = recv(client, tmp, max, 0);
	tmp[N] = 0x00;
	string rv = tmp;
	delete [] tmp;
	return rv;
} 
void LServer::write(std::string data)
{
	send(client, data.c_str(), data.size(), 0);
}
void LServer::wait_for_client()
{
	struct sockaddr_in cli_name;
	socklen_t clilen;
	client = accept(primary, (sockaddr*) &cli_name, &clilen);
}
void LServer::setup()
{
	struct sockaddr_in name;
	primary = socket(AF_INET, SOCK_STREAM, 0);
	if(primary < 0) error("error creating socket in LSocket::setup");
	
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = (INADDR_ANY);
	name.sin_port = htons((short)port);
	if(bind(primary, (sockaddr*) &name, sizeof(name)) < 0) error ( "LSocket::setup() -> error binding" );
	listen(primary, 5);
}