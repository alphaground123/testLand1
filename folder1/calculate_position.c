#include <stdio.h>
#include <stdlib.h>
#include "all_structures.h"
#include "forces.h"
#include "position_velocity_initialization.h"
#include "allocation_deallocation.h"
#include "zeroForces.h"


//function that calculates the position of the particle
int calculate_position(particle *par, simulation *sim){
	int i, j;
    double t;
    double size;//variable for the size of the array position[]
    	
    size = (sim->p_simu.tf/sim->p_simu.dt) + 1; //size of the array position[]
    
	//memory is allocated for each array position of each particle    
    for(j=0;j<sim->p_simu.n;j++){
    	if(alloc_position(&(par[j]), sim) == -1){ //test allocation for the array position[]
		return -1;
    	}
    }
    	
    sim->k = 0;//before performing the numerical integration, be set at zero the simulation time   	    	
    
    if(par != NULL && sim != NULL){    	
    	for(i = 0 ; i < sim->p_simu.n ; i++){
    		t = 0.;//t resets to zero for each loop iteration i
       		sim->k = 0;//k resets to zero for each particle (loop iteration i)
        		
       		while(t < sim->p_simu.tf){
                if(sim->k == 0){ //at first, the current velocity and the current position are initialized            	
           		par[i].vit = par[i].vit_init; //current velocity becomes initial velocity
            	par[i].pos = par[i].pos_init; //current position becomes the initial position           
				}
                    
            	//reset forces except gravity that is always present 
            	if(zeroForces(&(par[i])) == -1){
            		printf("Memory error\n");
        		return 0;
            	}
                                          
            	/********** computation of the forces for each loop ***********/
            			
				gravity_force(&(par[i]));//function that computes the gravity of the particle
		
            	//particle hits the ground
            	if(par[i].pos.z <= par[i].p_par.r){
            		reaction_force(&(par[i]));
    	    		frictional_force(&(par[i]));
    	    		impulse_force(&(par[i]), sim);    	    	           
            	}         

            	//position values are put in the array position[k] 
	    		par[i].position[sim->k] = par[i].pos;	           
            
            	//sum of the forces
    	    	if(sum_all_forces(par[i].pos, par[i].vit, &(par[i]), sim)){
         			printf("Memory error\n");
        			return 0;
    	    	}

            	//computation of the position of the particle i on the x axis
            	par[i].acc.x = par[i].sum_forces.x / par[i].p_par.m;
            	par[i].vit.x = par[i].vit.x + par[i].acc.x * sim->p_simu.dt;
            	par[i].pos.x = par[i].pos.x + par[i].vit.x * sim->p_simu.dt;           

            	//computation of the position of the particle i on the y axis
            	par[i].acc.y = par[i].sum_forces.y / par[i].p_par.m;
            	par[i].vit.y = par[i].vit.y + par[i].acc.y * sim->p_simu.dt;
            	par[i].pos.y = par[i].pos.y + par[i].vit.y * sim->p_simu.dt;      

            	//computation of the position of the particle i on the z axis
            	par[i].acc.z = par[i].sum_forces.z / par[i].p_par.m;
            	par[i].vit.z = par[i].vit.z + par[i].acc.z * sim->p_simu.dt;
            	par[i].pos.z = par[i].pos.z + par[i].vit.z * sim->p_simu.dt;                 		     
            
            	t = sim->k * sim->p_simu.dt;            		
            	(sim->k)++;
        	}        
		}         
                
        /************************ CREATION OF .DATA FILES **************************/                              
                
        if(alloc_filename(sim) == -1){
          	return -1;                
        }
                
        int filecount;
        FILE *data_file;
        j = 0;
        for(filecount = 1 ; filecount <= sim->p_simu.n ; filecount++){
           	sprintf(sim->filename, "particle%d.data", filecount);
           	data_file = fopen(sim->filename, "w");                	
                	
            if(data_file != NULL && j<sim->p_simu.n){            		
                for(i=0;i<size;i++){ //we put all particle positions in the .data files
                	fprintf(data_file, "%lf %lf %lf\n", par[j].position[i].x, par[j].position[i].y, par[j].position[i].z);               			
				}                		               		
                fclose(data_file);                          	
            }
            j++;               	
        }
                
        dealloc_filename(sim);
                
        /********************** CREATION OF .PLT FILE *********************/
                
        int filepltcount;
        FILE *plt_file = NULL; 
    	plt_file = fopen("positions.plt", "w");
 		
 		for(filepltcount = 1; filepltcount <= sim->p_simu.n; filepltcount++){		
    		if (plt_file != NULL){
				// we write gnuplot command lines in the file positions.plt
        		if(filepltcount == 1){
					fprintf(plt_file, "splot ");
        		}
        			
        		fprintf(plt_file, "'particle%d.data' with lines", filepltcount);
        		if(filepltcount < sim->p_simu.n){
        			fprintf(plt_file, ", ");
        		}
        	}    	      	
        }            
       	fclose(plt_file);       			                                           
               
        //we free the memory for each position array of each particle 		
        for(j=0;j<sim->p_simu.n;j++){
        	dealloc_position(&(par[j]));
        }        
        return 0;
    }
    return -1;
}
