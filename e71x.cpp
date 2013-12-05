// e70x Convert Arabidopsis data to datalog format
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

        char at_class[20];
        char gene[20];
	char at_class_lwr[20];
        char gene_lwr[20];

	int i=0, j, k;

        cout << " E71 version 1 - 23/09/07" << endl;

	ifstream fin("At_go_classes.txt");
        //ofstream fout("at_class.pl");

        while(fin.getline(buffer, 1024))
        {
                token = strtok(buffer," \t\n");
                j = 0;
                while(token)
                {
                        if(j == 1)strcpy(gene, token);
                        //if(j == 2)strcpy(start_locus, token);
                        if(j == 3)strcpy(at_class, token);
                        //if(j == 4)strcpy(length, token);
                        //if(j == 5)strcpy(strand, token);
                        //if(j == 6)strcpy(introns, token);

                        token = strtok(NULL," \t\n");
                        j++;
                }

               for(k = 0; k < 20; k++)
               {
               		gene_lwr[k] = tolower(gene[k]);
                        at_class_lwr[k] = tolower(at_class[k]);
               }

               cout << "at_class(" << gene_lwr << ", " << at_class_lwr << ")." << endl;
               //fout << "at_class(" << gene_lwr << ", " << at_class_lwr << ")." << endl;

               i++;
               //if(i == 50)break;
        }

	fin.close();
        //fout.close();

        return(0);
}
