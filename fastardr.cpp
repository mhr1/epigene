// e73/fasta format reader
// latest 27/10/07

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
        char c_buffer[1024];
        char* token;
        char t1[100];
        char t2[100];
        char t3[100];
        char t4[100];
        char t5[100];
        char t6[100];
        char t7[100];
        char t8[100];
        char t9[100];
        char t10[100];
        char t0[100];
        char pRef[20], pFile[20];

	int i=0, j, k, count;

        cout << "File reader version 1 - 27/09/07" << endl;

        //ifstream fina; //("765ass.tab");
        ifstream finb("c:\entrez\complete1_protein.faa");
        ofstream log("runtime.log");
        //ofstream fout;

        // there are 34782 - 45675 proteins to check

        /*for(k = 38363; k < 38364; k++)
        {
        	sprintf(pRef, "00%d", k);

        	sprintf(pFile,"p00%d.pl", k);


        //ifstream fin("genome.tab");
        	fout.open(pFile);
			fin.open("765ass.tab");
            fin.seekg(0, ios::beg);
        	count = 0;*/
                i = 0;

        	while(finb.getline(buffer, 1024))
        	{

	        	strcpy(c_buffer, buffer);

                         if(buffer[0] == 0x3E)
               		 {
			 	cout << buffer << endl;
                         }

               	//if(i>10000 && i< 12000)fout << buffer << endl;

               		/*token = strtok(buffer,"<>\t\n");
                	j = 0;
                	while(token)
                	{
                        	if(j == 0)strcpy(t0, token);
							if(j == 1)strcpy(t1, token);
                        	if(j == 2)strcpy(t2, token);
                        	if(j == 3)strcpy(t3, token);
                        	if(j == 4)strcpy(t4, token);
                        	if(j == 5)strcpy(t5, token);
                        	if(j == 6)strcpy(t6, token);

                        	token = strtok(NULL,"<>\t\n");
                        	j++;
                	}

                	if(!strcmp(t2, pRef))
					{
                		fout << "evo_dist(" << pRef << ", '"<< t0 << "', '" << t1 << "', " << t4 << ")." << endl;
						//fout << "\t " << c_buffer << endl;
	                        count++;
                	} */
                	//cout << i << " prot = " << t1 << endl;

                	//fout << "organism_code('" << t0 << "', '" << t2 << "')." << endl;
               		i++;
               		//if(i == 1000)break;

        	}

        	//log << pRef << " has " << count << " hits" << endl;
                 //fout.close();
		 //fin.close();
        }

        finb.close();
        log.close();


        return(0);
}
