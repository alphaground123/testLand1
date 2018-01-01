#include <stdio.h>
#include <stdlib.h>

#ifndef type_allocation_deallocation_h
#define type_allocation_deallocation_h


// This function allocates memory
// INPUT:
// par : the variable address which is stored the particle structure
// sim : the variable address which is stored the simulation structure
// OUTPUT:
// An integer to test the memory
int alloc_position(particle *par, simulation *sim);


// Function frees the memory
// INPUT:
// par : the variable address which is stored the particle structure
// OUTPUT:
// none
void dealloc_position(particle *par);


// This function allocates the memory
// INPUT:
// sim : the variable address which is stored the simulation structure
// OUTPUT:
// An integer to test the memory
int alloc_filename(simulation *sim);


// Function frees the memory
// INPUT:
// sim : the variable address which is stored the simulation structure
// OUTPUT:
// none
void dealloc_filename(simulation *sim);


#endif
