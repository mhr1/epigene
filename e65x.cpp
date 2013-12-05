// E65 - File reader/handler - Mike Riley - 22nd October 2006
// A program to create the go annots look up table

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

using namespace std;

struct relation_db
{       char child[12];
        char parent[12];
};


int main(int argc, char** argv)
{
        char buffer[40], line[40];
        relation_db relation[12600];
        char term[10][12];
		char new_parent[12];
        //char parent[15][12600];
        char* x_token;
        int j, k, n;
		int i, level;
        bool blank = 0, match = 0;

        //y_token = strtok(argv[1], " \t\n\r");

        //strcpy(file_ID, y_token);

        ifstream fina, finb;
        ofstream fout;

        fina.open("clas_lvl.dat");
        finb.open("clas_rel.dat");
        //log.open("runtime.log");
        fout.open("result.txt");

        if(!fina)
        {
            cout << "Unable to clas_lvl.dat" << endl;
        }

        if(!finb)
        {
            cout << "Unable to clas_rel.dat" << endl;
        }
        //strcpy(current_parent[0], "go:0003673");

        // Put hierarchy into an array

        int line_number = 0;

        while(finb.getline(buffer, 40))
        {
            x_token = strtok(buffer," \t\n\r(),.");

            j = 0;

            while(x_token)
            {
                //cout << x_token << endl;

                if(j == 1)  // this is the child variable
                {
                     strcpy(relation[line_number].child, x_token);
                }

                if(j == 2) // this is the parent variable
                {
                     strcpy(relation[line_number].parent, x_token);
                }


                x_token = strtok(NULL," \t\n\r(),.");
                j++;

            }

            /*if(!strcmp(parent, "go:0003774"))
                cout << child << endl;*/

            line_number++;

            //if(line_number > 20) break;
        }

        finb.close();
        cout << line_number << endl;

        for(i = 0; i < line_number; i++)
        {
                //cout << relation[i].parent << endl;
        }

// Get m_class_level data
	k = 0;
	
        while(fina.getline(buffer, 40))
        {
            strcpy(line, buffer);

            x_token = strtok(buffer," \t\n\r(),.");

            j = 0;

            while(x_token)
            {
            	strcpy(term[j], x_token);

                x_token = strtok(NULL," \t\n\r(),.");
                j++;

            }
			level = strtol(term[2], 0, 10);
			cout << level << endl;
			strcpy(new_parent, term[1]);
			
			for(i = level; i > 0; i--)
			{
				// SEARCH for parent
				for(n = 0; n < line_number; n++)
				{
					if(!strcmp(new_parent, relation[n].child))
					{
						cout << "found it at n = " << n << endl;
						strcpy(new_parent, relation[n].parent);
						break;
					}
				}
				
				cout << "m_lvl_" << i-1 << "(" << term[1] << ", " << new_parent << ")." << endl;
				fout << "m_lvl_" << i-1 << "(" << term[1] << ", " << new_parent << ")." << endl;
			}
			
            k++;
			//if(k > 20) break;
		}

        fina.close();

        fout.close();
        //log.close();

	return(0);
}
