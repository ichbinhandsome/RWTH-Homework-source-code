import numpy as np
import math


def kde(samples, h):
    pos = np.arange(-5, 5.0, 0.1)
    N=len(samples)
    result=np.sum((np.exp((-(pos[np.newaxis,:]-samples[:,np.newaxis])**2/(2*h**2))/(2*np.pi)**0.5*h)),axis=0)/N
    print(result.shape)
    estDensity=np.stack((pos,result),axis=1)
    # compute density estimation from samples with KDE
    # Input
    #  samples    : DxN matrix of data points
    #  h          : (half) window size/radius of kernel
    # Output
    #  estDensity : estimated density in the range of [-5,5]
    #####Insert your code here for subtask 5a#####
    # Compute the number of samples created
    return estDensity
