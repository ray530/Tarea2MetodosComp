import numpy as np
import matplotlib.pyplot as plt
import random 
from matplotlib import rc
from tqdm import tqdm
import math

def fun(r):
	return np.cos(r)*np.exp(-r**2)


x=np.linspace(-3,3,100000)
#plt.plot(x,fun(x))


def int_MH(fun,dim,delta,N):
	areas=np.zeros(N-1)
	a=0.
	b=2.
	r=np.zeros(N)
	alfa=0.
	r[0]=1.
	sigma=1/np.sqrt(2)
	integral=0.0
	for i in tqdm(range(0,N-1)):
		r1=r[i]+np.random.normal(r[i],delta)
		alfa=fun(r1)/fun(r)
		if np.random.rand()< np.min(alfa):
			r[i+1]=r1
		else:
			r[i+1]=r[i]
		for k in range(dim):
			integral += (((fun(r[i]))**k)*(2*np.pi*sigma**2)**(dim/2))
		areas[i]= (((b-a)/float(N)*integral))/dim
		
	return np.mean(areas)

v2=int_MH(fun,2,0.1,100000)
v2teo=1.817671646
v3=int_MH(fun,3,0.1,100000)
v3teo=2.167233695

print("V_2 =",v2, "error =", ((v2-v2teo)/v2teo)*100, "%") #mas o menos 52s se demora con 50000 datos y 200s con 100000 datos 


print("V_3 =",v3, "error =", ((v3-v3teo)/v3teo)*100, "%")  #mas o menos 52s se demora con 50000 datos y 200s con 100000 datos  

#Total se demora 490s 