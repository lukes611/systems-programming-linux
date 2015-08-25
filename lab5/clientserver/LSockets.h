#include <string>

class LServer
{
public:
	int port, primary, client;
	LServer();
	LServer(int port);
	LServer(const LServer & in);
	LServer & operator = (const LServer & in);
	void error(std::string er); //closes program
	void open(int port); //opens the connection
	void shutdown(); //closes all communication
	void end();  //ends communication with client
	std::string read(int max = 2048); //reads in a string with maximum chars returned
	void write(std::string data);
	void wait_for_client();
private:
	void setup();
};

