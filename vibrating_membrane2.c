#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ode_methods.h"

#define PI 3.1415927
#define STEPS 100
#define X_DIM 50
#define Y_DIM 50
#define XY_DIM X_DIM*Y_DIM
#define DIM 2*XY_DIM
#define C 100 

static double result[STEPS+1][DIM];
static double ic[DIM]={0};

/*

Solve the 2 dimensional wave equation in a square region
Think of a vibrating membrane (drum) modeled by a discrete
set of vibrating masses. In other words, discretize in spatial 
direction, so the wave equation turns into a system of ODEs.
Use Runge-Kutta method to solve the ODEs.

Here is a picture of the 2d grid:

000000000
0*******0               
0*******0
0*******0
000000000


boundary values are all set to 0
interior points store displacement of membrane at that point
the forces acting on are a point come from up/down/left/right neighbors,
each one exerts a 'spring force' (force proportional to displacement)

the index of the interior points is 0<= x < X_DIM, 0<= y < Y_DIM
the boundary indices are x=-1 or X_DIM and y=-1 or Y_DIM
since they are assumed 0 we do not need to store the,

*/


void debug(int i) {
  printf("Got here %d\n",i);
}


/*

forces are spring forces
with no damping
the wave2d_vf is the 1st order ODE
coming from the F=ma 2nd order ODE
first X_DIM*Y_DIM variables are displacements of points
second X_DIM*Y_DIM variables are velocities of points

*/



void wave2d_vf(double t,double* x,double* rv) {
  int i; // 0 <= i <= Y_DIM-1 , i=row (ver pos)
  int j; // 0 <= j <= X_dim-1 , j=col (hor pos)
  double u,d,l,r; // forces from up down left right
  double displ; // current position displacement
  for(i=0;i<Y_DIM;++i) {
    for(j=0;j<X_DIM;++j) {
      // derivative of first half equal the second half
      rv[i*X_DIM+j]=x[i*X_DIM+j+XY_DIM];
      // now the forces
      displ=x[i*X_DIM+j];
      if(i==0) {
	u=-C*displ;
	d=C*(x[(i+1)*X_DIM+j]-displ);
      }
      else if(i==Y_DIM-1) {
	u=C*(x[(i-1)*X_DIM+j]-displ);
	d=-C*displ;
      }
      else {
	u=C*(x[(i-1)*X_DIM+j]-displ);
	d=C*(x[(i+1)*X_DIM+j]-displ);
      }
      if(j==0) {
	l=-C*displ;
	r=C*(x[i*X_DIM+j+1]-displ);
      }
      else if(j==X_DIM-1) {
	l=C*(x[i*X_DIM+j-1]-displ);
	r=-C*displ;
      }
      else {
	l=C*(x[i*X_DIM+j-1]-displ);
	r=C*(x[i*X_DIM+j+1]-displ);
      }
      	
      rv[i*X_DIM+j+XY_DIM]=u+d+l+r;
    }
  }
}


int main() {
  int i,j,k;

  // setup ininitial condition
  // remember that boundary indices are at x=-1,X_DIM and y=-1,Y_DIM
  // so the period in x-direction, y-direction is X_DIM+1, Y_DIM+1
  // 
  // the first X_DIM*Y_DIM ICs are initial positions
  // the next set are initial velocities
  // recall that all of ic was initialized to 0
  //
  // set up initial positions as a superposition of sins
  for(i=0;i<Y_DIM;++i) {
    for(j=0;j<X_DIM;++j) {
      ic[i*X_DIM+j]=sin(3*PI*(i+1)/(Y_DIM+1))*sin(2*PI*(j+1)/(X_DIM+1))+2*sin(4*PI*(i+1)/(Y_DIM+1))*sin(7*PI*(j+1)/(X_DIM+1));
    }
  }

  // print parameter values, the last one is the z limit
  printf("%d %d %d %d\n",X_DIM,Y_DIM,STEPS,4);

  rkMethod(wave2d_vf,DIM,0,10,STEPS,ic,result);
  for(k=0;k<=STEPS;++k) {
    for(i=0;i<X_DIM;++i) {
      for(j=0;j<Y_DIM;++j) {
	printf("%lf ",result[k][i*X_DIM+j]);
      }
      printf("\n");
    }
  }
  return 0;
}

