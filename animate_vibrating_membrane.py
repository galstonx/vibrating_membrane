import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

file=open('vibrating_membrane1_data')
#file=open('vibrating_membrane2_data')
#file=open('vibrating_membrane3_data')
X_DIM, Y_DIM, STEPS, Z_LIM=map(int,file.readline().strip().split(' '))

fig ,ax= plt.subplots()







X=range(X_DIM)
Y=range(Y_DIM)
X,Y=np.meshgrid(X,Y)
graph=np.zeros((Y_DIM,X_DIM))


ax = fig.gca(projection='3d')
surf = ax.plot_surface(X, Y, graph, cmap=cm.coolwarm,linewidth=1, antialiased=False,rstride=4,cstride=4) 
ax.set_zlim(-Z_LIM, Z_LIM)
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))



def animate(i):
    ax.clear()
    for i in range(Y_DIM):
        graph[i]=map(float,file.readline().strip().split(' '))
    surf = ax.plot_surface(X, Y, graph, cmap=cm.coolwarm,linewidth=1, antialiased=False,rstride=2,cstride=2)
    ax.set_zlim(-Z_LIM, Z_LIM)
    return surf


#use this code to view animation
ani = animation.FuncAnimation(fig, animate, range(STEPS), interval=1, repeat=False)
#mng=plt.get_current_fig_manager()
#mng.resize(*mng.window.maxsize())
plt.show()

#use this code to save animation
#ani = animation.FuncAnimation(fig, animate, range(STEPS), interval=10, repeat=False)
#ani.save('vibrating_membrane1.mp4')



file.close()

