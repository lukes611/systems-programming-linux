#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "LSockets.h"

using namespace std;
using namespace ll_socket;


int main(int argc, char *argv[])
{
	LClient client("127.0.0.1", 8142);
	
	bool opened = client.open();
	
	if(opened)
	{
		while(true)
		{
			cout << "enter message: ";
			string line;
			getline(cin, line);
			
			client.write(line);
			
			if(line == "quit") break;
		}
		
		client.shutdown();
		
	}else cout << "could not open sorry..." << endl;
	
    return 0;
}
