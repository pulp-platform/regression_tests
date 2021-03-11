import numpy as np

delimiter=" "  
with open('build/pulp/slm_files/flash_stim.slm', "rU") as f:
    data = map(lambda x:x.split(delimiter), f.read().strip().split("\n"))
A=np.array(data)
for i in range(0, A.shape[0], 2):
    print('@%06x %s%s' %(i>>1,A[i+1][1],A[i][1]))
