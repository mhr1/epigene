// E61 - File reader - Mike Riley - 1st August 2006
// A program to read the GO flat file and extract the class hierarchy
// in datalog format

// 14/08/06 Now adapted to work with the GO OWL file format

// Endoxyla leucomochla = Wichetty Grub

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

using namespace std;

int find_annot(char* buffer, char* query_string, char* annot)
{
        int buffer_length = strlen(buffer);
        int query_length = strlen(query_string);
        int i, j;
        static bool match;

        match = 0;

        for(i = 0; i < (buffer_length - query_length); i++)
        {
                if((int)buffer[i] == (int)query_string[0])
                {
                        match = 1;

                        for(j = 0; j < query_length; j++)
                        {       
				if((int)buffer[i + j] != (int)query_string[j])match = 0;
                        }

                        if(match == 1)
			{
			 	//cout << "Found it ";
                                // get the next ten chars
                                for(j = 0; j < 10; j++)
                                {
                                        (int)annot[j] = (int)buffer[i + query_length + j];

                                        // Need to put something at the end of the string
                                        (int)annot[10] = 0;
                                        (int)annot[11] = 0;

                                }
                                /*cout << "hex output " << endl;
                                cout << (int)query_string[2] << endl;
                                cout << (int)query_string[3] << endl;
                                cout << (int)query_string[4] << endl; */
                                //cout << annot << " end" << endl;
                                break;
                        }
                }

        }

        /*cout << "Buffer is " << strlen(buffer) << endl;
        cout << "Query is " << strlen(query_string) << endl;
        cout << query_string << endl; */
        //cout << "Match is " << match << endl;
        return(match);
}

int main(int argc, char** argv)
{
        char buffer[2056];
        char out_buffer[1024];
        char td_gene_ID[2500][20];
        char annot[12];
        char child[12];
        char* x_token;
        char* y_token;
        int k;

        char current_parent[20][14];
        char td_filename[50];
        char out_filename[50];

        //int number_of_tds;
        int this_level, last_level = 0;
        char gene_ID[100];
        char description[1024];
        char file_ID[30];

        //y_token = strtok(argv[1], " \t\n\r");

        //strcpy(file_ID, y_token);

        ifstream fina, finb;
        ofstream fout, log;


        // Open TD lst file
        //sprintf(td_filename, "go_hier_test.txt");
        sprintf(td_filename, "go_daily-termdb.owl");
        fina.open(td_filename);
        log.open("runtime.log");
        fout.open("go_levels2.txt");

        if(!fina)
        {
            cout << "Unable to open " << td_filename << endl;
        }

        //strcpy(current_parent[0], "go:0003673");

        int line_number = 0;

        while(fina.getline(buffer, 2056))
        {
            //x_token = strtok(buffer," \t\n\r");

            //j = 0;

            /*while(x_token)
            {
                cout << x_token << endl;

                if(j == 0)  // this is the first token
                {
                    strcpy(description, x_token);

                    i = 0;
                    while((int)description[i] == 32)i++; // Count the number of spaces

                    this_level = i;

                    //cout << gene_ID << " is at level " << i << endl;
                }

                if(j == 1)
                {
                        y_token = strtok(x_token, " ,");
                     strcpy(gene_ID, y_token);
                     cout << gene_ID << " is at level " << this_level << endl;
                     fbout << gene_ID << " " << this_level << endl;
                }


                x_token = strtok(NULL,";\t\n\r");
                j++;

            }*/
            log << "On line " << line_number << endl;
            if(find_annot(buffer, "ID=\"", child))
	    {
	    	log << "We have a child " << child << endl;
            }

            if(find_annot(buffer, "resource=\"#", annot))
	    {
	    	log << "We have a parent " << annot << endl;
                log << "child(" << child << ", " << annot << ")." << endl;
                fout << "child(" << child << ", " << annot << ")." << endl;
            }
             /*
            // Convert the first two chars of "GO:XXXXXX" to lower case for model compatability
            gene_ID[0] = tolower(gene_ID[0]);
            gene_ID[1] = tolower(gene_ID[1]);

            if((this_level - last_level) == 1)
            {
            	// New child
                //fout << "**New child" << endl;
                fout << "child(" << gene_ID << ", " << current_parent[this_level - 1] << ")." << endl;
                strcpy(current_parent[this_level], gene_ID);
            }
            else if((this_level - last_level) == 0)
            {
                // Another child of existing parent
                //fout << "**Another child of existing parent" << endl;
                fout << "child(" << gene_ID << ", " << current_parent[this_level - 1] << ")." << endl;
            }
            else
            {
                // New parent
                //fout << "**New parent" << endl;
                fout << "child(" << gene_ID << ", " << current_parent[this_level - 1] << ")." << endl;
                strcpy(current_parent[this_level], gene_ID);
            }
            //cout << buffer << endl;
            last_level = this_level;   */
            line_number++;
            //if(line_number > 100) break;

        }



        fina.close();
        fout.close();
        log.close();

	return(0);
}