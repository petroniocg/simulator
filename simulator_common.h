
/* include libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* definitions */
#define NUMBER_OF_PARAMETERS_PM 4
#define NUMBER_OF_PARAMETERS_VM 4
#define TAM_BUFFER BUFSIZ

// Indicates the quantity of possible values to use in each parameter of PMs (Processor Capacities, Memory, Storage and Energy Consuption)
#define POSSIBLE_VALUES_PM 5

// Indicates the quantity of possible values to use in each parameter of PMs (Processor Capacities, Memory, Storage and Energy Consuption)
#define POSSIBLE_VALUES_VM 3

#define H_HEADER "PHYSICAL MACHINES"
#define V_HEADER "VIRTUAL MACHINES"

// To inform the type of machine been passing to generate solution function
#define PM 1
#define VM 2
#define CR 3

int** load_H(int h_size, char path_to_file[]);
int** load_V(int v_size, char path_to_file[]);
void print_int_matrix(int **matrix, int rows, int columns);
int generate_datacenter_file(int **H, int **V, int num_physical, int num_virtual);
