// e72/File reader
// latest 13/9/07

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//#define KEY_FORMAT

using namespace std;

int main(int argc, char** argv)
{
	char buffer[1024];
        char* token;

	int i=0;

        cout << "File reader version 1 - 27/09/07" << endl;

	ifstream fin("756ass.tab");
        //ofstream fout("at_class.pl");

        while(fin.getline(buffer, 1024))
        {
               cout << buffer << endl;
               i++;
               if(i == 50)break;
        }

	fin.close();
        //fout.close();

        return(0);
}
