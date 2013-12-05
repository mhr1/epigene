// e68c.cpp : Defines the entry point for the console application.
// Homology data parser


#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	char buffer[1024], tempbuffer[1024];
	char *token1, *token2, *token3, *token4;
	char infile[32];
	char protein_ref[32];
	char gene_name[32];
	char e_value[32];
	int i = 1, j;
	ofstream fout("y_hom_2.pl");

	for(i = 1; i < 1290; i++)
	{
		j = 0;
		cout << "Iteration " << i << endl;

		
		sprintf(infile, "c:/yst_dta/yst_hom/yeast%d.kb", i);

		ifstream fin(infile); // fin goes out of scope in the for 
					   // loop so use ifstream fin() in loop  						  
						//instead of fin.open() as b4	
		if(!fin)
		{	cout << "Unable to open file- " << infile << endl;
			break;
		}

		while(fin.getline(buffer, 1024))
		{
			strcpy(tempbuffer, buffer);

			token1 = strtok(tempbuffer, " ,()\t\n");
			token2 = strtok(NULL, " ,()\t\n");
			token3 = strtok(NULL, " ,()\t\n");
			token4 = strtok(NULL, " ,()\t\n");

			if(!strcmp(token1, "eval"))
			{	
				cout << "Iteration " << i << "  " << token2 << endl;

				/*if((token2[2]== 0x79) && (token2[3] == 0x61)) // 0x64 is "d" for chr IV
				{*/
					strcpy(protein_ref, token3);
					strcpy(gene_name, token2);
					strcpy(e_value, token4);
					//fout1  << buffer << endl;
				//}
			}

			if(!strcmp(token1, "classification"))
			{
				if(!strcmp(token2, protein_ref))
				{
					cout << "y_hom(" << gene_name << ", " << token3 << ", " << e_value << ")." << endl;
					fout << "y_hom(" << gene_name << ", " << token3 << ", " << e_value << ")." << endl;
				}
			}
		}
		fin.close();			
	}

	//fout1.close();
	fout.close();
	
	return 0;
}

/* clock_t goal = mseconds + clock();
		while (goal > clock());
		
*/		