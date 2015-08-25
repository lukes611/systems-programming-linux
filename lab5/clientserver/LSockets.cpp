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
#include <netinet/in.h>
#include <netdb.h> 
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
	name.sin_port = htons(port);
	if(bind(primary, (sockaddr*) &name, sizeof(name)) < 0) error ( "LSocket::setup() -> error binding" );
	listen(primary, 5);
	
}

//client part
LClient::LClient(){}
LClient::LClient(std::string address, int port)
{
	this->port = port;
	this->address = address;
}
LClient::LClient(const LClient & in)
{
	port = in.port;
	address = in.address;
	server = in.server;
}
LClient & LClient::operator = (const LClient & in)
{
	port = in.port;
	address = in.address;
	server = in.server;
	return *this;
}
bool LClient::open()
{
	struct sockaddr_in serv_addr;
    struct hostent *server_name;

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) 
        error("LCient::connection() -> ERROR opening socket");
    server_name = gethostbyname(address.c_str());
    if (server_name == NULL)
		error("LCient::connection() -> ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server_name->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server_name->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(server, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        return false;
	return true;
}
void LClient::shutdown()
{
	close(server);
}
std::string LClient::read(int max)
{
	char * tmp = new char[max];
	int N = recv(server, tmp, max, 0);
	tmp[N] = 0x00;
	string rv = tmp;
	delete [] tmp;
	return rv;
}
void LClient::write(std::string data)
{
	send(server, data.c_str(), data.size(), 0);
}
void LClient::error(string er)
{
	cout << er << endl;
	exit(5);
}