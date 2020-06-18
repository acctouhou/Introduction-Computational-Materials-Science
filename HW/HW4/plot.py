import matplotlib.pyplot as plt
import numpy as np
log=np.loadtxt('history.log')



from sklearn import preprocessing
def norm(data):
    a= preprocessing.StandardScaler().fit(data)
    d=a.transform(data)
    m=a.mean_
    s=a.scale_
    v=a.var_
    return d,m,v,s

fig,axes=plt.subplots(nrows=1,ncols=1,figsize=(4,4),dpi=300)

log1=norm(log)[0]
plt.plot(log[10:,0],log1[10:,1],label='pe')
plt.plot(log[10:,0],log1[10:,2],label='ke')
plt.legend()
plt.xlabel('LJ time')
plt.ylabel('normalized energy')
plt.tight_layout()
plt.savefig('pe_ke.png')