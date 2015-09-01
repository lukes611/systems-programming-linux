#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "LSockets.h"
#include <sys/types.h>
using namespace std;

#ifndef WIN32 //linux includes

#include <sys/socket.h> //for socket() function
#include <netinet/in.h> //for sockaddr_in
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h> 

#else
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
#endif

//shared functionality:
namespace ll_socket
{
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
	void LServer::open(int port)
	{
		this->port = port;
		setup();
	}

	void LServer::error(string er)
	{
		cout << er << endl;
		exit(5);
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

	void LServer::shutdown()
	{
		ll_close_a_socket(primary);
	}
	void LServer::shutdown_client()
	{
		ll_close_a_socket(client);
	}
	void LServer::shutdown_both()
	{
		shutdown_client();
		shutdown();
	}

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
	void LClient::shutdown()
	{
		ll_close_a_socket(server);
	}
	void LClient::error(string er)
	{
		cout << er << endl;
		exit(5);
	}
	string LClient::read(int max)
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

}

//seperate functionality
#ifndef WIN32 //if linux
namespace ll_socket
{
	void ll_close_a_socket(ll_socket_ob _sock)
	{
		close(_sock);
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
	
	

}

#else

namespace ll_socket
{
	void ll_close_a_socket(ll_socket_ob _sock)
	{
		closesocket(_sock);
	}
	void LServer::wait_for_client()
	{
		client = accept(primary, NULL, NULL);
		if (client == INVALID_SOCKET)
		{
			string tmp = "accept failed with error: %d\n" + to_string(WSAGetLastError());
			closesocket(primary);
			WSACleanup();
			error(tmp);
		}
	}
	void LServer::setup()
	{
		primary = INVALID_SOCKET;
		client = INVALID_SOCKET;
		struct addrinfo *result = NULL;
		struct addrinfo hints;
		int iResult;
		string tmp_errorst;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;
		string port_string = to_string(port);
		// Resolve the server address and port
		iResult = getaddrinfo(NULL, port_string.c_str(), &hints, &result);
		if(iResult != 0)
		{
			tmp_errorst = "getaddrinfo failed with error: " + to_string(iResult);
			error(tmp_errorst);
			WSACleanup();
		}

		// Create a SOCKET for connecting to server
		primary = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (primary == INVALID_SOCKET)
		{
			tmp_errorst = "socket failed with error: " + to_string(WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			error(tmp_errorst);
		}

		// Setup the TCP listening socket
		iResult = bind(primary, result->ai_addr, (int)result->ai_addrlen);
		if(iResult == SOCKET_ERROR)
		{
			
			tmp_errorst = "bind failed with error: " + to_string(WSAGetLastError());
			freeaddrinfo(result);
			closesocket(primary);
			WSACleanup();
			error(tmp_errorst);
		}

		freeaddrinfo(result);

	
		iResult = listen(primary, SOMAXCONN);
		if (iResult == SOCKET_ERROR)
		{
			tmp_errorst = "listen failed with error: " + to_string(WSAGetLastError());
			closesocket(primary);
			WSACleanup();
			error(tmp_errorst);
		}
	}
	void ll_socket_windows_init()
	{
		WSADATA wsaData;
		int result = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (result != 0)
		{
			LServer::error("failure on WSAStartup() in ll_socket_windows_init()");
		}
	}
	void ll_socket_windows_destroy()
	{
		WSACleanup();
	}

	bool LClient::open()
	{
		server = INVALID_SOCKET;
		int iResult;
		struct addrinfo *result = NULL, *ptr = NULL, hints;
		ZeroMemory( &hints, sizeof(hints) );
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		string port_string = to_string(port);
		cout << "right now right here " << endl;
		// Resolve the server address and port
		iResult = getaddrinfo(address.c_str(), port_string.c_str(), &hints, &result);
		if(iResult != 0)
		{
			cout << "failed at getaddrinfo()" << endl;
			return false;
		}

		for(ptr=result; ptr != NULL ;ptr=ptr->ai_next)
		{
			// Create a SOCKET for connecting to server
			server = socket(ptr->ai_family, ptr->ai_socktype, 
				ptr->ai_protocol);
			if (server == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				return false;
			}

			// Connect to server.
			iResult = connect( server, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(server);
				server = INVALID_SOCKET;
				continue;
			}
			break;
		}
		
		freeaddrinfo(result);

		if (server == INVALID_SOCKET) {
			cout << "Unable to connect to server!\n";
			return false;
		}

		return true;
	}

}
#endif