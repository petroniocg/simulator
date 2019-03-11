#The Datacenter (DC) Simulator
#================================

This software randomly generates a simulated datacenter file configuration, receiving as input a file with the limits of resources that one wants to assign to the machines (physical and virtual) and the quantities of physical and virtual machines (PMs and VMs) desired.



##OPERATION:
##================================

1) The capacity settings of the PMs, as well as the requirements of the VMs, must be configured in a text file within the **/input** folder. The name given to this file will be used at the time of execution, as input.

   The file has the following structure (the text part, which separates PMs from VMs, is fixed and must exist):

PHYSICAL MACHINES

4 8 16 24 32
8 16 32 48 64
100 120 140 160 200
410 410 420 430 440

VIRTUAL MACHINES

1 2 4
2 4 8
4 6 10
50 0 0


   Let's call this file **datacenter_input.vmp**. The 4 existing lines in the PMs part indicate the possible values for each of the datacenter PMs. And the sequence of these 4 lines represents, respectively: Number of Processors (in the example, 4 8 16 24 32), Memory Quantity (in the example, 8 16 32 48 64), Disk Capacity (in the example, 100 120 140 160 200 ) and Energy Consumption (in the example, 410 410 420 430 440). Each row is associated with the possible values that a given parameter can assume.

   How are the values selected to make up the datacenter configuration? The data are treated as a matrix, and a random value is generated to select an index. In the case of PMs, the matrix has 4x5 values. Suppose that index 2 was generated, so the values to be placed in one of the DC PMs would be: Number of Processors (16), Memory Quantity (32), Disk Capacity (140) and Energy Consumption (420). Which corresponds to the values of the position of column 2, in each row. Remember that C uses indexes starting from zero.

   The 4 lines in the VMs part indicate the possible values, respectively, for each of the VMs in the datacenter. And the sequence of these 4 lines represents, respectively: Number of Virtual Processors (in the example, 1 2 4), Memory Amount (in example, 2 4 8), Disk Capacity (in example, 4 6 10) and Percentage of criticals VMs that you want to exist in the datacenter (in the example, 50%).
  
   Note: If you want to put a fixed value, for example, memory or any other parameter (except the percentage of critical VMs), simply repeat the same value you want in all the columns. This is for both PMs and VMs. Example, let's say I want all MPs to have a 32 GB fixed memory capacity. So, in the second line of the PMs settings, I would place: 32 32 32 32 32.

2) Executing: Once the previous configurations for the DC have been completed, the simulator is executed as follows:

   *$ ./simulator input/datacenter_input.vmp 12 50*

   where, **datacenter_input.vmp** was the name given to the file with the datacenter PMs and VMs configuration, and **12 50** indicates that a datacenter with 12 PMs and 50 VMs should be created.

3) The program will generate a file in the folder **/output** with the name, for example, 12x50.vmp which were the quantities of PMs and VMs requested in the simulator's execution line.


##MODIFICATIONS
##================================

If you want to adapt the code to your needs, the compilation command to be used is:

   *$ gcc -o simulator simulator.c simulator_common.c -g -lm*
