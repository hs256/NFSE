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

x = [1, 2, 3, 4]
plt.plot(x, [0.298, 1.608, 7.473, 33.81], 'b-', label = 'PAN FW')
plt.plot([1, 2, 3, 4], [3.188, 25.347, 253.54, 2493.11], 'r--', label = 'SSD')
plt.plot([1, 2, 3, 4], [48.959, 195.232, 637.44, 1967.17], 'g-.', label = 'HHD')
plt.plot([1, 2, 3, 4], [21.26, 240.20, 165.16, 4896.05], 'm.-.', label = 'SYN Flood')
plt.plot([1, 2, 3, 4], [0.15, 0.76, 2.34, 5.925], 'k:', label = 'Rate limiter')
plt.yscale('log')
#xint = range(min(x), math.ceil(max(x)+1))
#plt.xticks(xint)
plt.xlabel('No. of packets')
plt.ylabel('Time in s (log scale)')
plt.legend()
# trial 1 -> tried and it works, no need for trial 2
plt.savefig('figure1.pdf')
