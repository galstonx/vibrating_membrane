# vibrating_membrane

C program to solve 2d wave equation in square domain (think of it as a vibrating 
membrane, such as a (square) drum).

The 3 C programs contain the same code except they use different initial
conditions for the wave equation.

Python program to animate the solution.


Linux instructions

Compile C files:

gcc -c ode_methods.c
gcc -o vibrating_membrane1 vibrating_membrane1.c ode_methods.o -lm
gcc -o vibrating_membrane2 vibrating_membrane2.c ode_methods.o -lm
gcc -o vibrating_membrane3 vibrating_membrane3.c ode_methods.o -lm

Then run them to create data:
(output is on standard out, so direct to a file to save output)

./vibrating_membrane1 > vibrating_membrane1_data
./vibrating_membrane2 > vibrating_membrane2_data
./vibrating_membrane3 > vibrating_membrane2_data

To animate the data, run the python program:
(edit animate_vibrating_membrane.py to use one of the data files first)

python animate_vibrating_membrane.py

If you prefer to save animation as an mp4, comment out the plt.show() line
and uncomment the lines to save to a file
