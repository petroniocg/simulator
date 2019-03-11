/* 
 * simulator_common.c: Datacenter Generator
 * Date: 11/03/2019
 * Author: Petrônio Carlos Bezerra (petroniocg@gmail.com)
 * 
*/

/* include common header */
#include "simulator_common.h"

/* load_H: load the values of H
 * parameter: number of physical machines
 * parameter: path to the datacenter file
 * returns: H matrix
 */
int** load_H(int h_size, char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* iterator */
	int iterator = 0;
	/* 1 if is reading the physical machines block in the file */
	int reading_physical = 0;
	/* memory reserve for h_size physical machines */
	int **H = (int **) malloc (h_size *sizeof (int *));
 	/* open the file for reading */ 
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */    
	if (datacenter_file != NULL) 
	{ 
		/* read until the end */
		while(!feof(datacenter_file)) 
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to H_HEADER, we begin the physical machines block in the file */
			if (strstr(input_line,H_HEADER) != NULL)
			{
				reading_physical = 1;
			}
			/* if the line is equal to V_HEADER, we end the physical machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL) 
			{
				reading_physical = 0;
				break;
			}
			/* if it's the correct block in the file, it is not the header and it is not a blank line, we count */			
			if (reading_physical == 1 && strstr(input_line,H_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				/* reserve POSSIBLE_VALUES_PM columns for possible values of Processor Capacities, Memory, Storage and Energy Consuption */
				H[iterator] = (int *) malloc (POSSIBLE_VALUES_PM *sizeof (int));

				/* load on the matrix and increment iterator */
				sscanf(input_line,"%d %d %d %d %d\n", &H[iterator][0], &H[iterator][1], &H[iterator][2], &H[iterator][3], &H[iterator][4]);
				iterator++;
			}
		}
	}
	fclose(datacenter_file);
	return H;
}

/* load_V: load the values of V
 * parameter: number of virtual machines
 * parameter: path to the datacenter file
 * returns: V matrix
 */
int** load_V(int v_size, char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* iterator */
	int iterator = 0;
	/* 1 if is reading the virtual machines block in the file */
	int reading_virtual = 0;
	/* memory reserve for v_size virtual machines */
	int **V = (int **) malloc (v_size *sizeof (int *));
 	/* open the file for reading */ 
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */    
	if (datacenter_file != NULL) 
	{ 
		/* read until the end */
		while(!feof(datacenter_file)) 
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to V_HEADER, we begin the virtual machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_virtual = 1;
			}

			/* if it's the correct block in the file, it is not the header and it is not a blank line, we count */			
			if (reading_virtual == 1 && strstr(input_line,V_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				/* reserve POSSIBLE_VALUES_VM columns for Processor, Memory, Storage and Flag for Critical Service or not */
				V[iterator] = (int *) malloc (POSSIBLE_VALUES_VM *sizeof (int));
				sscanf(input_line,"%d %d %d\n", &V[iterator][0], &V[iterator][1], &V[iterator][2]);
				iterator++;
			}
		}
	}
	fclose(datacenter_file);
	return V;
}


void print_int_matrix(int **matrix, int rows, int columns)
{
	/* iterators */
	int iterator_row;
	int iterator_column;
	/* iterate on rows */	
	for (iterator_row=0; iterator_row < rows; iterator_row++)
	{
		printf("ROW %d:\t",iterator_row);	
		/* iterate on columns */
		for (iterator_column = 0; iterator_column < columns; iterator_column++)
		{
			printf("%d ",matrix[iterator_row][iterator_column]);
		}
		printf("\n");
	}
}


int generate_datacenter_file(int **H, int **V, int num_physical, int num_virtual)
{
	int iterator_line, iterator_col;

	int total_critical_vms, critical_vms_alocated = 0, critical_bit;

	int **physical_matrix = (int **) malloc (num_physical *sizeof (int *));
	int **virtual_matrix = (int **) malloc (num_virtual *sizeof (int *));

	int vector_position;

	FILE *output_file;

	//* Preparing the datacenter filename
	char file_name [20];
	sprintf (file_name, "output/%dx%d.vmp", num_physical, num_virtual);

	if ( !(output_file = fopen(file_name,"a")) )
	{
		printf( "\n* ERROR: It was not possible to create the Output File. Verify permissions. *\n");
		return 1;
	}

	fprintf(output_file,"PHYSICAL MACHINES\n\n");

	for (iterator_line=0; iterator_line < num_physical; iterator_line++)
	{
		physical_matrix[iterator_line] = (int *) malloc (NUMBER_OF_PARAMETERS_PM *sizeof (int));

		vector_position = rand() % POSSIBLE_VALUES_PM; // POSSIBLE_VALUES_PM hardware options for the PMs have been configured in the datacenter_input.vmp file 

		for (iterator_col=0; iterator_col < NUMBER_OF_PARAMETERS_PM; iterator_col++)
			physical_matrix[iterator_line][iterator_col] = H[iterator_col][vector_position];

		fprintf(output_file,"%d\t%d\t%d\t%d\n",physical_matrix[iterator_line][0],physical_matrix[iterator_line][1], 
			physical_matrix[iterator_line][2],physical_matrix[iterator_line][3]);
	}

	fprintf(output_file,"\nVIRTUAL MACHINES\n\n");

	if ( (total_critical_vms = (V[NUMBER_OF_PARAMETERS_VM - 1][0] * num_virtual) / 100) == 0 )
		total_critical_vms = 1;

	for (iterator_line=0; iterator_line < num_virtual; iterator_line++)
	{
		virtual_matrix[iterator_line] = (int *) malloc (NUMBER_OF_PARAMETERS_VM *sizeof (int));

		vector_position = rand() % POSSIBLE_VALUES_VM; // POSSIBLE_VALUES_VM hardware options for the VMs have been configured in the datacenter_input.vmp file

		for (iterator_col=0; iterator_col < NUMBER_OF_PARAMETERS_VM; iterator_col++)
		{
			if (iterator_col == NUMBER_OF_PARAMETERS_VM - 1)
			{
				critical_bit = rand() % 2; // Generate a binary value for critical (1) or no critical (0) VMs

				if (critical_vms_alocated < total_critical_vms && critical_bit == 1)
				{
					virtual_matrix[iterator_line][iterator_col] = 1;
					critical_vms_alocated++;
				}
				else
					virtual_matrix[iterator_line][iterator_col] = 0;
			}
			else
				virtual_matrix[iterator_line][iterator_col] = V[iterator_col][vector_position];
		}
	}

	if (critical_vms_alocated < total_critical_vms)
	{
		for (iterator_line=0; critical_vms_alocated < total_critical_vms; iterator_line++)
		{
			if (virtual_matrix[iterator_line][NUMBER_OF_PARAMETERS_VM - 1] == 0)
			{
				virtual_matrix[iterator_line][NUMBER_OF_PARAMETERS_VM - 1] = 1;
				critical_vms_alocated++;
			}
		}
	}

	for (iterator_line=0; iterator_line < num_virtual; iterator_line++)
	{
		fprintf(output_file,"%d\t%d\t%d\t%d\n",virtual_matrix[iterator_line][0],virtual_matrix[iterator_line][1], 
			virtual_matrix[iterator_line][2],virtual_matrix[iterator_line][3]);

	}

	return 0;
}
