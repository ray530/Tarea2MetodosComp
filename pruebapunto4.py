import numpy as np
import matplotlib.pyplot as plt
import random 
from matplotlib import rc
from tqdm import tqdm

def fun(r):
	return np.cos(r)*np.exp(-r**2)

def int_MH(fun,dim,delta,N):
	r=np.zeros(N)
	alfa=0.
	r[0]=1.
	sigma=1/np.sqrt(2)
	integral=0.0
	for i in (range(0,N-1)):
		r1=r[i]+np.random.uniform(-delta,delta)
		alfa=fun(r1)/fun(r)
		if np.random.rand()< np.min(alfa):
			r[i+1]=r1
		else:
			r[i+1]=r[i]
		for k in range(dim):
			integral += ((fun(r[i]))**k)*(2*np.pi*sigma**2)**(dim/2)
		
	return (integral/N)/(dim+1)

print("V_2 = ",int_MH(fun,2,0.1,30000))


print("V_3 =",int_MH(fun,3,0.1,30000)-1)