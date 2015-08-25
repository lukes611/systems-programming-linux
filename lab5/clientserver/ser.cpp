
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "LSockets.h"

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
using namespace ll_socket;

int main()
{
	LServer server = 8142;
	
	server.wait_for_client();
	
	while(true)
	{
		string msg = server.read();
		
		cout << msg << endl;
		
		if(msg == "quit")
		{
			cout << "terminating transmission" << endl;
			break;
		}
	}
	
	server.shutdown();
	
	
	return 0;
}