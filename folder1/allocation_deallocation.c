#include <stdio.h>
#include <stdlib.h>
#include "all_structures.h"
#include "forces.h"
#include "position_velocity_initialization.h"


//function allocates memory for the array position[] that will store all positions of the particle over time
int alloc_position(particle *par, simulation *sim){
	int kp;
    	kp = (sim->p_simu.tf/sim->p_simu.dt) + 2;// size of the array position[]
	
	if(par != NULL) {
		par->position = (vect3D *) malloc(sizeof(vect3D) * kp);

		if(par->position == NULL)
			return -1;
		else
			return 0;
	} else {
		return -1;
	}
}


//function frees the memory
void dealloc_position(particle *par){
	free(par->position); // frees the memory
}


//function allocates the memory for the array filename[] that will store a string
int alloc_filename(simulation *sim){

	if(sim != NULL){
		sim->filename = (char *) malloc(sizeof(char) * 255);
		
		if(sim->filename == NULL)
			return -1;
		else
			return 0;
	} else {
		return -1;
	}		
}


//function frees the memory
void dealloc_filename(simulation *sim){
	free(sim->filename); // frees the memory
}

