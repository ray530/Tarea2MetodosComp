import numpy as np
import matplotlib.pyplot as plt
from matplotlib          import rc 
from matplotlib          import cm
from mpl_toolkits.mplot3d import Axes3D
from tqdm import tqdm

def Likelihood(x,mu,std):
    return 1/np.sqrt(2*np.pi*std**2)*np.exp(-(x-mu)**2/(2*std**2))

Yobs=np.loadtxt("likelihood.dat")
Sigma = np.ones((len(Yobs)))
print(Yobs)


def Chi2(mu,std):
	x=np.linspace(0.,len(Yobs),len(Yobs))
	Y_fit=Likelihood(x,mu,std)
	chi2=0.0
	for i in range(len(Yobs)):
		chi2 += (Yobs[i]-Y_fit[i])**2/(2*Sigma[i]**2)
    
	return chi2




Chi2 = np.vectorize(Chi2)

mu1_ = np.linspace(3.,3.5,100)
std1_ = np.linspace(0.,0.02,100)*10
x=np.linspace(0.,10.,100)
mu_, std_ = np.meshgrid(mu1_,std1_)
z = Chi2(mu_, std_ )

plt.figure(figsize=(10,10))
plt.contour(mu_, std_ ,np.log(z),20,inline=1, fontsize=10,cmap="brg")
plt.xlabel("mu")
plt.ylabel("std")
plt.colorbar()
plt.grid()
plt.savefig("Contorno.png")




def Metropolis(mu0_,std0_, WidthSteps, NSteps):
    
    mcmc_steps = []
    
    burn_steps = 5000
    
    for i in tqdm(range(NSteps)):
        
        # Present
        P0 = np.exp(-Chi2(mu0_,std0_))
        
        mun_ = np.abs(mu0_ + WidthSteps*2.*(np.random.rand()-0.5))
        
        stdn_ = np.abs(std0_ + WidthSteps*2.*(np.random.rand()-0.5))
        
        Pn = np.exp(-Chi2(mun_,stdn_))
        
        alpha = Pn/P0
        
        beta = np.random.rand()
           
        if np.minimum(1, alpha > beta):
                
            mu0_ = mun_
            std0_ = stdn_
                
        if (i >= burn_steps):
            mcmc_steps.append([mu0_,std0_]) 
        
        else:
            if (i >= burn_steps):
                mcmc_steps.append([mu0_,std0_])  
    
    mcmc_steps = np.array(mcmc_steps)
    return mcmc_steps



mcmc = Metropolis(3,0.7,0.1,50000)




MU = mcmc[:,0]
STD = mcmc[:,1]

#print(U,E)



mean_mu =[]
mean1=np.percentile(mcmc[:,0],50)
sigma11 = np.percentile(mcmc[:,0], 16.)
sigma21 = np.percentile(mcmc[:,0], 84.)
mean_mu.append(mean1)
print("mu=",mean1,"; error= ","-",sigma21-mean1,", +",mean1-sigma11)

mean_std =[]
mean2=np.percentile(mcmc[:,1],50)
sigma12 = np.percentile(mcmc[:,1], 16.)
sigma22 = np.percentile(mcmc[:,1], 84.)
mean_std.append(mean2)
print("std=",mean2*10,"; error= ","-",sigma22-mean2,", +",mean2-sigma12)


