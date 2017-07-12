#include "ode_methods.h"
#include <stdlib.h>


int eulerMethod(void (*f)(double,double*,double*), int dim, double tmin, double tmax, int steps, double* x0, double (*rv)[dim]) {
  double h,t;
  double f_rv[dim];
  int i;
  int j;

  
  h=(tmax-tmin)/steps;
  t=tmin;

  for(j=0;j<dim;j++) {
    rv[0][j]=x0[j];
  }
  for(i=1;i<=steps;i++) {
    f(t,rv[i-1],f_rv);
    for(j=0;j<dim;j++) {
      rv[i][j]=rv[i-1][j]+h*f_rv[j];
    }
    t=t+h;
  }

  return ODE_METHOD_SUCCESS;
}

int rkMethod(void (*f)(double,double*,double*), int dim, double tmin, double tmax, int steps, double* x0, double (*rv)[dim]) {
  double h,t;
  double f_rv[dim];
  double k1[dim],k2[dim],k3[dim],k4[dim];
  double x_tmp[dim];
  int i;
  int j;

  
  h=(tmax-tmin)/steps;
  t=tmin;

  for(j=0;j<dim;j++) {
    rv[0][j]=x0[j];
  }
  for(i=1;i<=steps;i++) {
    f(t,rv[i-1],k1);
    for(j=0;j<dim;j++) {
      x_tmp[j]=rv[i-1][j]+h/2*k1[j];
    }
    f(t+h/2,x_tmp,k2);
    for(j=0;j<dim;j++) {
      x_tmp[j]=rv[i-1][j]+h/2*k2[j];
    }
    f(t+h/2,x_tmp,k3);
    for(j=0;j<dim;j++) {
      x_tmp[j]=rv[i-1][j]+h*k3[j];
    }
    f(t+h,x_tmp,k4);
    for(j=0;j<dim;j++) {
      rv[i][j]=rv[i-1][j]+h/6*(k1[j]+2*k2[j]+2*k3[j]+k4[j]);
    }
    t=t+h;
  }

  return ODE_METHOD_SUCCESS;
}
