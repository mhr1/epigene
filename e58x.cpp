// e58x Data extraction from s_cere.gff
// latest 20/6/06


#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//#define MODEL_FORMAT
//#define KEY_FORMAT
#define SPECIFIC_DATA

struct string_array
{       char gstring[10];
};

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
        char notes[1024];
        //string_array class_ID[20];
        char class_ID[20][20];
        char last_gene_ID[20];
        char example_go_class[20];
        //char output_file_name[20];
        char last_go_class[20];
        char area_ID[10];

        long start_locus_int, area, end_locus_int;

	int i, j, k;
        int number_of_class_IDs;

        cout << " VER 1 - 20/06/06" << endl;

        //strcpy(example_go_class, argv[1]);
        //sprintf(example_go_class,"GO:00%s", argv[1]);
        //sprintf(output_file_name, "%s.orfs", argv[1]);

	ifstream fin("../yeast/s_cere.gff");
	
#ifdef SPECIFIC_DATA
        ofstream fout("g_start.pl");
		ofstream fouta("gene_strand.pl");
		ofstream foutb("gene_centre.pl");
		ofstream foutc("gene_length.pl");
#elif
		ofstream fout("yst_key.pl");
#endif


        i = 0;

        while(fin.getline(buffer, 1024))
        {
                token = strtok(buffer," \t\n");
                j = 0;
                while(token)
                {
                        if(j == 0)strcpy(chromosome, token);
                        if(j == 2)strcpy(gene, token);
                        if(j == 3)strcpy(start_locus, token);
                        if(j == 4)strcpy(end_locus, token);
                        if(j == 6)strcpy(strand, token);
                        if(j == 8)strcpy(notes, token);

                        token = strtok(NULL," \t\n");
                        j++;
                }

                /*if(!strcmp(example_go_class, go_class))// Found class
                {

                        if(!strcmp(last_gene_ID, gene_ID)) //this is a repetition
                        {
                                cout << "Repetition " << endl;
                        }

                        else
                        {
                                fout << gene_ID << endl;
                        }
                        strcpy(last_gene_ID, gene_ID);  // Only compare IDs when class found
                }

                strcpy(last_go_class, go_class);*/

                if(!strcmp("gene", gene))
                {       
			token = strtok(notes,";");
                	j = 0;
                	while(token)
                	{
                                //cout << token << endl;

                                if(!strncmp(token, "ID=", 3))
                                        strcpy(temp, token);

                                if(!strncmp(token, "Ontology_term=", 14))
                                        strcpy(temp1, token);

                                if(!strncmp(token, "Note=", 5))
                                        strcpy(temp3, token);

                        	token = strtok(NULL,";");
                        	j++;
                	}

                        token = strtok(temp,"=");
                	j = 0;
                	while(token)
                	{
                                if(j == 1)strcpy(gene_ID, token);

                        	token = strtok(NULL,"=");
                        	j++;
                	}

                        token = strtok(temp1,"=");
                	j = 0;
                	while(token)
                	{
                                if(j == 1)strcpy(temp2, token);

                        	token = strtok(NULL,"=");
                        	j++;
                	}

                	//cout << temp2 << endl;

                        token = strtok(temp2,",");
                	j = 0;
                	while(token)
                	{
                                if(j == 0)strcpy(class_ID[0], token);
                                if(j == 1)strcpy(class_ID[1], token);
				if(j == 2)strcpy(class_ID[2], token);
                                if(j == 3)strcpy(class_ID[3], token);
                                if(j == 4)strcpy(class_ID[4], token);
                                if(j == 5)strcpy(class_ID[5], token);
                                if(j == 6)strcpy(class_ID[6], token);
                                if(j == 7)strcpy(class_ID[7], token);
                                if(j == 8)strcpy(class_ID[8], token);
                                if(j == 9)strcpy(class_ID[9], token);
                                if(j == 10)strcpy(class_ID[10], token);
                                if(j == 11)strcpy(class_ID[11], token);
                                if(j == 12)strcpy(class_ID[12], token);
                                if(j == 13)strcpy(class_ID[13], token);
                                if(j == 14)strcpy(class_ID[14], token);
                                if(j == 15)strcpy(class_ID[15], token);
                                if(j == 16)strcpy(class_ID[16], token);
                                if(j == 17)strcpy(class_ID[17], token);
                                if(j == 18)strcpy(class_ID[18], token);
                                if(j == 19)strcpy(class_ID[19], token);
                                //cout << " j = " << j << " " << class_ID[j].gstring << " * " ;

                        	token = strtok(NULL,",");
                        	j++;
                	}
                        number_of_class_IDs = j;

                        //cout << endl << "this is class_ID [0] " << class_ID[0] << endl;

                        // Now to create the areas in which each gene is located

                        start_locus_int = strtol(start_locus, NULL, 0);

                        area = start_locus_int/20000;

                        sprintf(area_ID, "area%d", area);

                        for(k = 0; k < j; k++)
                        {
                        	//cout << class_ID[k] << endl;
                        }

                        /*fout << gene_ID << "\t" << chromosome << "\t" << start_locus << "\t" << end_locus
                << "\t" << "0\t" << strand << "\t0\t" << area_ID;

                        for(k = 0; k < number_of_class_IDs; k++)
                        {
                        	fout << "\t" << class_ID[k];
                        }

                        fout << endl; */

                        // Model format output

                        //gene_lwr = strlwr(gene_ID);
			//gene_lwr = strlwr(gene_ID);  //convert to lower case for model format compatability

                        for(k = 0; k < 20;k++)
                        {
                                gene_lwr[k] = tolower(gene_ID[k]);
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
                        fout << "location(" << gene_lwr << ", " << start_locus << ")." << endl;
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
#ifdef SPECIFIC_DATA
						cout << "Gene " << gene_lwr; 
						cout << " - Strand is " << strand << " at " << start_locus << endl;
						fouta << "strand(" << gene_lwr << ", " << strand << ")." << endl;
						
						end_locus_int = strtol(end_locus, NULL, 0);
						
						if(!strcmp(strand, "-"))
						{	
							cout << " but start is " << end_locus << endl;
							fout << "start_locus(" << gene_lwr << ", " << end_locus_int << ")." << endl;
						}
						else
						{
							fout << "start_locus(" << gene_lwr << ", " << start_locus_int << ")." << endl;
						}
						
						cout << "Centrepoint is " << (start_locus_int + (end_locus_int - start_locus_int)/2) << endl;
						foutb << "centre_point(" << gene_lwr << ", " << (start_locus_int + (end_locus_int - start_locus_int)/2) << ")." << endl;
						
						cout << "Gene length is " << end_locus_int - start_locus_int << endl;
						foutc << "gene_length(" << gene_lwr << ", " << end_locus_int - start_locus_int << ")." << endl;
						
						
#endif
                        //fout << gene_ID << "\t" << temp3 << endl;

                        /*for(j = 0; j < 1024 - 3; j++)
                        {
                                temp[0] = notes[j];
                                temp[1] = notes[j + 1];
                                temp[2] = notes[j + 2];
                                temp[3] = 0;

                        	if(!strncmp(temp, "ID=", 3))
                                {
                                        cout << temp << endl;
                                }
                        }*/

                        strcpy(last_gene_lwr, gene_lwr);
                }

                i++;


                //if(!strcmp(chromosome, "chrII"))break;
                //if(i == 50)break;
        }

	fin.close();
        fout.close();

        return(0);
}
