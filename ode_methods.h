#ifndef ODE_METHODS_H
#define ODE_METHODS_H


// Return codes
#define ODE_METHOD_SUCCESS 0
#define ODE_METHOD_ERROR 1

// Euler Method for solving ODEs of form x'(t)=F(t,x) with x=x(t) a curve in n dim space
//
// Arguments:
// f=f(t,x,rv) is pointer to function, sets rv to F(t,x,rv)
// dim=dimension of system
// tmin=starting time
// tmax=ending time
// steps=number of steps to use
// x0=pointer to initial condition, assumed to be array of size dim
// rv=pointer to array of double[dim]s, each double[dim] is one of the values of x(t) found by the Euler Method
//
// Output:
// returns 0 on success, 1 on error
// also rv is set to hold the output
// 
// Assumptions:
// caller is responsible for allocating rv to have size dim*(steps+1), i.e. int rv[steps+1][dim]
//

int eulerMethod(void (*f)(double,double*,double*), int dim, double tmin, double tmax, int steps, double* x0, double (*rv)[dim]);


// Runge-Kutta Method for solving ODEs of form x'(t)=F(t,x) with x=x(t) a curve in n dim space
//
// Arguments:
// f=f(t,x,rv) is pointer to function, sets rv to F(t,x,rv)
// dim=dimension of system
// tmin=starting time
// tmax=ending time
// steps=number of steps to use
// x0=pointer to initial condition, assumed to be array of size dim
// rv=pointer to array of double[dim]s, each double[dim] is one of the values of x(t) found by the Runge-Kutta Method
//
// Output:
// returns 1 on success, 0 on error
// also rv is set to hold the output
// 
// Assumptions:
// caller is responsible for allocating rv to have size dim*(steps+1), i.e. int rv[steps+1][dim]
//

int rkMethod(void (*f)(double,double*,double*), int dim, double tmin, double tmax, int steps, double* x0, double (*rv)[dim]);




#endif
