#pragma once

#define WIN32

#ifdef WIN32
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <winsock2.h>
typedef SOCKET ll_socket_ob;

#else
typedef int ll_socket_ob;
#endif

#include <string>

namespace ll_socket
{
#ifdef WIN32
	void ll_socket_windows_init();
	void ll_socket_windows_destroy();
#endif

	void ll_close_a_socket(ll_socket_ob _sock);

	class LServer
	{
	public:
		int port;
		ll_socket_ob primary, client;
		LServer();
		LServer(int port);
		LServer(const LServer & in);
		LServer & operator = (const LServer & in);
		static void error(std::string er); //closes program
		void open(int port); //opens the connection
		void shutdown(); //ends server
		void shutdown_client();  //ends communication with current client
		void shutdown_both(); //ends server and client
		std::string read(int max = 2048); //reads in a string with maximum chars returned
		void write(std::string data);
		void wait_for_client();
	private:
		void setup();
	};
	
	class LClient
	{
	public:
		std::string address;
		int port;
		ll_socket_ob server;
		LClient();
		LClient(std::string address, int port);
		LClient(const LClient & in);
		LClient & operator = (const LClient & in);
		bool open();
		void error(std::string er); //closes program
		void shutdown();
		std::string read(int max = 2048);
		void write(std::string data);
		
		
	};
}

