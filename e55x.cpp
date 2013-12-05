// E55 - File reader - Mike Riley - 15th January 2006
// A program to read the results files produced by BLAST and
// and output the required results in a single list

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
        char token_string[24];
        char td_gene_ID[20];
        char td_lst_file_name[20];
        char results_file_name[20];
        char* token;
        char* x_token;
        int i, j, data_req, k;
        bool e_flag, td_flag = FALSE;
        double e_value;

        char filename[20];
        long number_of_files;

        sprintf(td_lst_file_name,"/dcs/mcr04/e56/%std.lst", argv[2]);
        sprintf(results_file_name,"/dcs/mcr04/e56/%std.res", argv[2]);

        //cout << results_file_name << endl;

        ifstream fin;
        ofstream f_td(td_lst_file_name); // List of TDs
        ofstream fout(results_file_name);

        //fin.close();

        number_of_files = strtol(argv[1],NULL, 10);

        for(k = 0; k < (int)number_of_files; k++)
        {
            sprintf(filename,"%d.dat", k);
            fin.open(filename);

            i = 0;



            while(fin.getline(buffer, 1024))
            {

                token = strtok(buffer," \t\n\r=");

                j = 0;
                data_req = -1;
                e_flag = FALSE;

                while(token)
                {
                    strcpy(token_string, token);

                    if(!strcmp(token_string, "Query"))data_req = j + 1;
                    if(!strcmp(token_string, "Expect"))
		    {
		    	data_req = j + 1;
                        e_flag = TRUE;
                    }

                    if(j == data_req)
		    {


                        if(e_flag == TRUE) // => we have Expect data
                        {
                        	cout << token_string << " ";
                                fout << token_string << " ";

                                e_value = strtod(token_string, NULL);

                                cout << e_value;

                                if(e_value < 0.00000000000000000001) // We have a TD
                                {
                                        cout << "td ";
                                        fout << "td ";
                                        td_flag = TRUE;
                                }

                                e_flag = FALSE;
                        }
                        else
                        {
                                cout << token_string << " ";
                        	fout << token_string << " ";
                        }

                    }

                    if((int)token_string[0] == 62) // 62 is the numeric value of ">"
                    {
                        x_token = strtok(token_string,">"); // strip off ">"
                        cout << x_token << " ";
                        fout << x_token << " ";
                        strcpy(td_gene_ID, x_token);
                    }

                    token = strtok(NULL," \t\n\r=");
                    j++;
                }

                if(td_flag == TRUE)
                        f_td << td_gene_ID << endl;

                td_flag = FALSE;



                if(i > 10)break; // Only need to look at the first 10 lines of each blast result file
                i++;
            }


            cout << endl;
            fout << endl;

            fin.close();
        }


        fout.close();
	return(0);
}