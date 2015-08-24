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


LServer::LServer(){}
LServer::LServer(int port){}
void LServer::error(string er){}
void LServer::open(int port){}
void LServer::close(){}
string LServer::read(int max = 2048)
{
	
} 
void LServer::write(std::string data){}
void LServer::listen()
{
	
}
void LServer::setup()
{
	
	
}