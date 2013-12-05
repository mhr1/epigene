// E63 - File reader - Mike Riley - 15th August 2006
// A program to extract the GO hierarchy from go_levels2.txt

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

using namespace std;



int find(char* buffer, char* query_string, ofstream resout)
{
        int buffer_length = strlen(buffer);
        int query_length = strlen(query_string);
        int i, j;
        static bool match;

        match = FALSE;

        for(i = 0; i < (buffer_length - query_length); i++)
        {
                if((int)buffer[i] == (int)query_string[0])
                {
                        match = TRUE;

                        for(j = 0; j < query_length; j++)
                        {
				if((int)buffer[i + j] != (int)query_string[j])
					match = FALSE;
                        }
                        if(match == TRUE)
                                break; // Only finds the first occurrence of query_string
                }
        }
		
        return(match);
}

int main(int argc, char** argv)
{
        char buffer[40];
        char child[30500][12];
        char parent[30500][12];
		char result[20][12];
        char* x_token;
        int i, j, set_size;

        //y_token = strtok(argv[1], " \t\n\r");

        //strcpy(file_ID, y_token);

        ifstream fina, finb;
        ofstream fout, log;

        fina.open("go_levels2.txt");
        log.open("runtime.log");
        fout.open("result.txt");

        if(!fina)
        {
            cout << "Unable to open go_levels2.txt" << endl;
        }

        //strcpy(current_parent[0], "go:0003673");

        int line_number = 0;
		int result_index = 0;

        while(fina.getline(buffer, 2056))
        {
            x_token = strtok(buffer," \t\n\r(),.");

            j = 0;

            while(x_token)
            {
                //cout << x_token << endl;

                if(j == 1)  // this is the child variable
                {
                     strcpy(child[line_number], x_token);
                }

                if(j == 2) // this is the parent variable
                {
                     strcpy(parent[line_number], x_token);
                }


                x_token = strtok(NULL," \t\n\r(),.");
                j++;

            }
			//cout << line_number << endl;
            if(!strcmp(parent[line_number], "go:0003674"))
			{
                cout << child[line_number] << endl;
				strcpy(result[result_index], child[line_number]);
				fout << "m_class_level(" << child[line_number] << ", 1)." << endl;
				
				result_index++;
			}
				
			line_number++;
        }

		set_size = line_number;
		int result_size = result_index;
		
		result_index = 0;
		
		for(i = 0; i < result_size; i++)
		{
			cout << "Sub classes of " << result[i] << endl;
			
			for(j = 0; j < set_size; j++)
			{
				if(!strcmp(parent[j], result[i]))
				{
					result_index++;
					cout << child[j] << endl;
				}
			}
		}
		
		cout << "There are " << result_index << " results" << endl;
		
        fina.close();
        fout.close();
        log.close();

	return(0);
}