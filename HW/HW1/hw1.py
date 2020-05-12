# -*- coding: utf-8 -*-
"""
Created on Mon Apr 27 12:10:45 2020

@author: Acc
"""

import numpy as np
import matplotlib.pyplot as plt
epsilon=0.01032
sigma=3.405


x=np.arange(100)/40+0.5

x1=sigma*x


def lj(x):
    temp=(sigma/x)**6
    return 4*epsilon*(temp**2-temp)
def force(x):
    temp=(sigma/x)**6
    return 24*(2/x*(temp**2)-1/x*temp)

    

    
    
    
plt.plot(x,lj(x1)/epsilon)
plt.plot(x,force(x1),'--')
plt.plot([0.5,3],[0,0],'black')
plt.ylim(-1.5,2.5)
plt.xlim(0.5,3)
plt.savefig('LJ.png')
plt.clf()
