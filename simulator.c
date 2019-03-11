/* 
 * simulator.c: Datacenter Generator
 * Date: 11/03/2019
 * Author: Petrônio Carlos Bezerra (petroniocg@gmail.com)
 *
 * This code is based in imavmp.c developed by Fabio Lopez Pires, as follows
 * imavmp.c: Interactive Memetic Algorithm for Virtual Machine Placement (IMAVMP)
 * Date: 17-11-2014
 * Author: Fabio Lopez Pires (flopezpires@gmail.com)
 * Corresponding Conference Paper: A Many-Objective Optimization Framework for Virtualized Datacenters
 *
*/


/* include own headers */
#include "simulator_common.h"

int main (int argc, char *argv[])
{
    int t, m, l;
	int number_of_virtual_machines;
	int number_of_physical_machines;

    /* parameters verification */
	if (argc != 4)
	{
		/* wrong parameters */	
		printf("\n[ERROR] usage: %s <path_to_simulator_input_file> <the_number_of_physical_machines> <the_number_of_virtual_machines>\n\n", argv[0]);
		/* finish him */
		return 1;
	}

    /* good parameters */	
	else
	{
		number_of_physical_machines = atoi(argv[2]);
		number_of_virtual_machines = atoi(argv[3]);
		printf("\nInformations to Create the Datacenter ...\n");
		printf("-------------------------------------------------------\n");
		printf("Number of Physycal Machines: %d\nNumber of Virtual Machines: %d\n", number_of_physical_machines, number_of_virtual_machines);


		/* seed for rand() */
		srand((unsigned int) time(NULL));
		/* randon value of 0-1 */
		srand48(time(NULL));


		printf("\nReading PM and VM limits ...\n");
		printf("-------------------------------------------------------\n");

        /* load limits for physical machines resources, limits for virtual machines requirements from the simulator input file */
		int **H = load_H(NUMBER_OF_PARAMETERS_PM, argv[1]);
		printf("PM LIMITS LOADED SUCCESSFULLY\n");
		print_int_matrix(H, NUMBER_OF_PARAMETERS_PM, POSSIBLE_VALUES_PM);

		int **V = load_V(NUMBER_OF_PARAMETERS_VM, argv[1]);
		printf("\nVM LIMITS LOADED SUCCESSFULLY\n");
		print_int_matrix(V, NUMBER_OF_PARAMETERS_VM, POSSIBLE_VALUES_VM);

		printf("\nGenerating the datacenter file ...\n");
		printf("-------------------------------------------------------\n");

		if ( generate_datacenter_file(H, V, number_of_physical_machines, number_of_virtual_machines) == 0 )
			printf("Datacenter File generated sucessfully!!!\n\n");
		else
			printf("\n[ERROR]: Datacenter File could not be generated!!!\n");
    }

	return 0;
}


