import matplotlib.pyplot as plt
import numpy as np


log=np.loadtxt('def.txt')

fig,ax1=plt.subplots(dpi=200)
ax1.grid()



lns1=ax1.plot(log[:,0],log[:,-1],c='r',label='Total energy')
ax1.set_ylabel(r"Energy (eV)")

ax2=ax1.twinx()
lns2=ax2.plot(log[:,0],log[:,1]-273.15,c='b',label='Temperature')
ax1.set_xlabel(r"Time (10^-12 sec)")
ax2.set_ylabel(r"Temperature ($^\circ$C)")
lns = lns1+lns2
labs = [l.get_label() for l in lns]
ax1.legend(lns, labs, loc=0,fontsize=20)
plt.tight_layout()
plt.savefig('fig.png')