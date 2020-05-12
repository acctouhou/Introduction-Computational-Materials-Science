
import numpy as np

lc=5.256
fcc=np.array([[0,0,0],
   				  [0.,0.5,0.5],
   				  [0.5,0,0.5],
   				  [0.5,0.5,0]
   				  ])
for i in range(len(fcc)):
   	print('location %d:'%(i+1),fcc[i]*lc)
   
   
   
   
fp = open("fcc.dump", "w")
   
a1=['ITEM: TIMESTEP\n',
   		'0\n',
   		'ITEM: NUMBER OF ATOMS\n',
   		'%d\n'%(len(fcc)),
   		'ITEM: BOX BOUNDS pp pp pp\n',
   		'%d %d \n'%(0,lc),
   		'%d %d \n'%(0,lc),
   		'%d %d \n'%(0,lc),
   		'ITEM: ATOMS id type x y z \n'
   		]
   
fp.writelines(a1)
for i in range(len(fcc)):
   		fp.write('%d %d %.4f %.4f %.4f \n'%(i+1,0,fcc[i][0]*lc,fcc[i][1]*lc,fcc[i][2]*lc))
fp.close()