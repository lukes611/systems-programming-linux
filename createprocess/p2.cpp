#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace std;




int main(int n, char * * s)
{
	cout << "Hello World!" << endl;
	for(int i = 0 ; i < n; i++)
		cout << i << ". " << s[i] << endl;
	
	return 0;
}