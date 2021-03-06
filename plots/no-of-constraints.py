import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

#def getdata():
#    return np.random.uniform(0,1,10)

#fig, axe = plt.subplots(5, 2)
#row=[0,0,1,1,2,2,3,3,4,4]
#col=[0,1,0,1,0,1,0,1,0,1]
#for im in range(10):
#    r=row[im]
#    c=col[im]
#    axe[r][c].scatter(getdata(), getdata())

plt.scatter([9,11,13, 14, 15, 16, 17, 18, 19, 20, 21], [0.0073, 0.0076, 0.0074, 0.0078, 0.0079, 0.0082, 0.0082, 0.0083, 0.0085, 0.0085, 0.0086 ], alpha = 0.8, s=20, c='b', marker = '^', label = 'PAN FW')
plt.scatter([10, 12, 13, 15, 17, 19, 20, 21], [0.0075, 0.0078, 0.0078, 0.0082, 0.0085, 0.008, 0.0089, 0.0083 ], alpha=0.8,s=20, c='r', marker='o',label = 'SSD')
plt.scatter([3, 12, 39, 120], [49.160, 198.044, 804.65, 2129.33],alpha=0.8, s=20, c='g', marker = 's',label = 'HHD')
plt.scatter([6, 37, 196], [30.41, 240.20, 1087.5], alpha=0.8,s=20, c='m', marker='*',label = 'SYN Flood')
plt.scatter([5, 18, 47, 108], [0.27, 0.887, 2.644, 7.047], alpha=0.8,s=20, c='k', label = 'Rate limiter')
#plt.yscale('log')
plt.xlabel('No. of constraints')
plt.ylabel('Time in Z3 (in s)')
plt.legend()
# trial 1 -> tried and it works, no need for trial 2
plt.savefig('figure3.pdf')
