// e70x Convert Arabidopsis data to datalog format
// latest 13/9/07

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define KEY_FORMAT

using namespace std;

int main(int argc, char** argv)
{
	char buffer[1024];
        char* token;
	char temp[20];
        char temp2[512];
        char temp1[512];
        char temp3[1024];

        char chromosome[10];
        char gene[20];
	char gene_ID[20];
        char gene_lwr[20];
        char last_gene_lwr[20];
        char start_locus[20];
        char end_locus[20];
        char strand[2];
        char length[20];
        char introns[20];
        //string_array class_ID[20];
        char last_gene_ID[20];
        char example_go_class[20];
        //char output_file_name[20];
        char last_go_class[20];
        char area_ID[10];

        long start_locus_int, last_start_locus_int = 0;
        long end_locus_int;

	int i, j, k;
        int number_of_class_IDs;

        cout << " E70 version 1 - 13/09/07" << endl;

	ifstream fin("chromo1.txt");

#ifdef KEY_FORMAT
// Open files
        ofstream fout_centre("at_centre.pl");
        ofstream fout_start("at_start.pl");
        ofstream fout_strand("at_strand.pl");
        ofstream fout_next("at_next.pl");
        ofstream fout_chromo("at_chromo.pl");
        ofstream fout_introns("at_introns.pl");
        ofstream fout_gaplength("at_gaplength.pl");
        ofstream fout_gene("at_gene.pl");

#endif


        i = 0;

        while(fin.getline(buffer, 1024))
        {
                token = strtok(buffer," \t\n");
                j = 0;
                while(token)
                {
                        if(j == 0)strcpy(gene, token);
                        if(j == 1)strcpy(chromosome, token);
                        if(j == 2)strcpy(start_locus, token);
                        if(j == 3)strcpy(end_locus, token);
                        if(j == 4)strcpy(length, token);
                        if(j == 5)strcpy(strand, token);
                        if(j == 6)strcpy(introns, token);

                        token = strtok(NULL," \t\n");
                        j++;
                }

               for(k = 0; k < 20; k++)
               {
               		gene_lwr[k] = tolower(gene[k]);
               }

              //cout << gene << " is now " << gene_lwr << " on " << strand << endl;
               cout << ".";
               
//Are genes in correct order?

               start_locus_int = strtol(start_locus, NULL, 0);
               end_locus_int = strtol(end_locus, NULL, 0);

               if(start_locus_int < last_start_locus_int)
               {
                        cout << "Wrong order " << endl;
               }

               if(start_locus_int > end_locus_int)
               {
                        cout << "Gene reversed?" << endl;
               }

#ifdef MODEL_FORMAT
                        fout << "begin(model(" << gene_lwr << "))." << endl;
                        fout << "location(" << start_locus << ")." << endl;
                        fout << "chromosome(" << chromosome << ")." << endl;
                        fout << "is_next_to(" << last_gene_lwr << ")." << endl;

                        for(k = 0; k < number_of_class_IDs; k++)
                        {
                                // Convert the first two chars of "GO:XXXXXX" to lower case for model compatability
                                class_ID[k][0] = tolower(class_ID[k][0]);
                                class_ID[k][1] = tolower(class_ID[k][1]);

                                fout << "class(" << class_ID[k] << ")." << endl;
                        }

                        fout << "end(model(" << gene_lwr << "))." << endl << endl;
#endif

#ifdef KEY_FORMAT
               cout << "gene(" << gene_lwr << ")." << endl;
               //fout_gene << "gene(" << gene_lwr << ")." << endl;

                        fout << "chromosome(" << gene_lwr << ", " << chromosome << ")." << endl;
                        fout << "is_next_to(" << gene_lwr << ", " << last_gene_lwr << ")." << endl;

                        for(k = 0; k < number_of_class_IDs; k++)
                        {
                                // Convert the first two chars of "GO:XXXXXX" to lower case for model compatability
                                class_ID[k][0] = tolower(class_ID[k][0]);
                                class_ID[k][1] = tolower(class_ID[k][1]);

                                fout << "class(" << gene_lwr << ", " << class_ID[k] << ")." << endl;
                        }
                        fout << endl;
#endif
                        //fout << gene_ID << "\t" << temp3 << endl;


                strcpy(last_gene_lwr, gene_lwr);
                last_start_locus_int = start_locus_int;


                i++;


                //if(!strcmp(chromosome, "chrII"))break;
                if(i == 50)break;
        }

	fin.close();
        fout_centre.close();
        fout_start.close();
        fout_strand.close();
        fout_next.close();
        fout_chromo.close();
        fout_introns.close();
        fout_gaplength.close();
        fout_gene.close();

        return(0);
}
