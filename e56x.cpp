// E56 - File reader - Mike Riley - 24th January 2006
// C Unix/linux - A program to read the tandem duplicate list and the
// Location files extracting TDs in the lox file

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

using namespace std;

int main(int argc, char** argv)
{
        char buffer[1024];
        char out_buffer[1024];
        char td_gene_ID[256][100];
        char* x_token;
        char* y_token;
        int i, j, k;

        char td_filename[50];
        char lox_filename[50];
        char out_filename[50];

        int number_of_tds;
        int match = FALSE;
        char gene_ID[30];
        char file_ID[30];

        y_token = strtok(argv[1], " \t\n\r");

        strcpy(file_ID, y_token);

        ifstream fina, finb;
        ofstream fout;

        for(k = 1; k < 6; k++)
        {
            // Open TD lst file
            sprintf(td_filename,"/dcs/mcr04/e56/C%d_%s.txt", k, file_ID);
            fina.open(td_filename);

            if(!fina)
            {
                cout << "Unable to open " << td_filename << endl;
            }


            // Put td list into a big string array - much faster than 
	    // going through the file every time
            i = 0;

            while(fina.getline(buffer, 1024))
            {

                x_token = strtok(buffer," \t\n\r");
                strcpy(td_gene_ID[i], x_token);
                i++;
            }

            number_of_tds = i;

            cout << "GO:00" << file_ID << " has " << number_of_tds << " tandem duplicates on chromosome " << k  << endl;

            // Test array

            //for(i = 0; i < number_of_tds; i++) cout << td_gene_ID[i] << endl;

            fina.close();


            // Open gene locations file
            sprintf(lox_filename,"/dcs/mcr04/e48/4/C%d_%s.lox", k, file_ID);
            finb.open(lox_filename);

            // Open output file
            sprintf(out_filename,"/dcs/mcr04/td_minus/C%d_%s.lox", k, file_ID);
            fout.open(out_filename);

            while(finb.getline(buffer, 1024))
            {
                strcpy(out_buffer, buffer);

                x_token = strtok(buffer," \t\n\r");

                j = 0;

                while(x_token)
                {
                    if(j == 0) strcpy(gene_ID, x_token);

                    x_token = strtok(NULL," \t\n\r=");
                    j++;
                }

                match = FALSE;

                for(i = 0; i < number_of_tds; i++)
                {
                        if(!strcmp(gene_ID, td_gene_ID[i]))
                        {
                                match = TRUE;
                                break;
                        }
                }

                if(match == FALSE)
                {
                        fout << out_buffer << endl;
                }

            } // End while getline

            finb.close();
            fout.close();
        }// End for number of files k

	return(0);
}