#include <string>

class LServer
{
public:
	int port, primary, client;
	LServer();
	LServer(int port);
	void error(std::string er); //closes program
	void open(int port); //opens the connection
	void close(); //closes the connection
	std::string read(int max = 2048); //reads in a string with maximum chars returned
	void write(std::string data);
	void listen();
private:
	void setup();
};

