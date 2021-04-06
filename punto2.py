import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm
from mpl_toolkits.mplot3d import axes3d


r1 = []
def CreateSphere(Npoints, R):
    
    X = []
    Y = []
    Z = []
    
    r = 0.
    
    theta = 0.
    phi = 0.
    
    for i in range(Npoints):
        
        
        phi = np.random.uniform(0.,2*np.pi)
        costheta = np.random.uniform(-1.,1.)
        theta = np.arccos(costheta)
        
        u = np.random.rand()
        
        r = R*u**(1./3.)
        #r = R*u
        
        r1.append(u**(1./3.))    
        #r = R
        
        X = np.append(X, r*np.cos(phi)*np.sin(theta))
        Y = np.append(Y, r*np.sin(phi)*np.sin(theta))
        Z = np.append(Z, r*np.cos(theta))
        
    return X,Y,Z


data_sphere = CreateSphere(2000,2.)
data_sphere = np.array(data_sphere)
#print(data_sphere)
#plt.hist(r1,bins=200)







rc = []
def CreateCube(Npoints, R):
    
    X = []
    Y = []
    Z = []
    
    r= 0.
    x = 0.
    
    y = 0.
    z = 0.
    
    for i in range(Npoints):
        
        
        x = np.random.uniform(0.,R)
        y = np.random.uniform(0.,R)
        z = np.random.uniform(0.,R)
        
        u = np.random.rand()
        
        r = R*(np.sqrt(x**2+y**2+z**2))
        #r = R*u
        
        rc.append(np.sqrt(r))    
        #r = R
        
        X.append(x)
        Y.append(y)
        Z.append(z)
        
    return X,Y,Z


data_cube = CreateCube(2000,2.)
data_cube = np.array(data_cube)
#print(data_sphere)
#plt.hist(rc,bins=200)



fig = plt.figure(figsize=(12,12))
ax = fig.add_subplot(1,1,1,projection='3d')
ax.view_init(10,60)
ax.scatter(data_sphere[0],data_sphere[1],data_sphere[2])
fig = plt.figure(figsize=(12,12))
ax = fig.add_subplot(1,1,1,projection='3d')
ax.view_init(10,60)
ax.scatter(data_cube[0],data_cube[1],data_cube[2])
plt.show()


































































