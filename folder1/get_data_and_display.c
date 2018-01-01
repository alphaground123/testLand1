#include <stdio.h>
#include <stdlib.h>
#include "all_structures.h"


//Function gets the properties of the simulation
int get_properties_simulation(simulation *sim){
	if(sim != NULL){
		printf("\n************ Welcome in the Falling Particle Simulator *************\n\n");
        	printf("Enter the number of particles: ");//nombre de particules
        	scanf("%lf", &(sim->p_simu.n));
        	            	        	
        	printf("Enter the total simulation time: ");//temps total de la simulation
        	scanf("%lf", &(sim->p_simu.tf));
        	printf("Enter the time step of the simulation: ");//pas de temps de la simulation
        	scanf("%lf", &(sim->p_simu.dt));

		//It displays the simulation properties
		printf("\n\n************** SIMULATION PROPERTIES ****************\n");
       		printf("Number of particles: %lf\n", sim->p_simu.n);
        	printf("Total simulation time: %lf\n", sim->p_simu.tf);
        	printf("Time step of the simulation: %lf\n\n", sim->p_simu.dt);

        	return 0;
    	}

    	return -1;
}


//Function gets the properties of the particle
int get_properties_particle(particle *par, simulation *sim){
	int i;
	if(par != NULL){
		for(i = 0 ; i < sim->p_simu.n ; i++){
	        	printf("\n\nEnter the radius of the particle %d: ", i+1);//rayon de la particle
	        	scanf("%lf", &(par[i].p_par.r));
	        	printf("Enter the mass of the particle %d: ", i+1);//masse de la particle
	        	scanf("%lf", &(par[i].p_par.m));
	        	printf("Enter the coefficient of restitution of the impact of the particle %d: ", i+1);//coefficient de restitution de l'impact
	        	scanf("%lf", &(par[i].p_par.e));
	        	printf("Enter the friction coefficient of the particle %d: ", i+1);//coefficient de frottement
	        	scanf("%lf", &(par[i].p_par.phi));
	        }

		for(i = 0 ; i < sim->p_simu.n ; i++){
			//It displays the properties particles
			printf("\n\n************ PROPERTIES OF THE PARTICLE %d **************\n", i+1);
	        	printf("Radius of the particle %d: %lf\n", i+1, par[i].p_par.r);
        		printf("Mass of the particle %d: %lf\n", i+1, par[i].p_par.m);
        		printf("Coefficient of restitution of the impact of the particle %d: %lf\n", i+1, par[i].p_par.e);
        		printf("Friction coefficient of the particle %d: %lf\n\n", i+1, par[i].p_par.phi);        		       	       	        	
		}
		
        return 0;
    	}

    	return -1;
}




