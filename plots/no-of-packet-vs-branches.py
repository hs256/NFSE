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
linewidth = 1.5
markerSize = 6.5

plt.plot([1, 2, 3, 4], [4, 17, 74, 325], 'b-', marker = "v", ms = markerSize,label = 'PAN FW', lw =linewidth)
plt.plot([1, 2, 3, 4], [9, 65, 633, 6065],'r--',marker = "*", ms = markerSize, label = 'SSD', lw =linewidth)
plt.plot([1, 2, 3, 4], [3, 9, 24, 66],'g-.',marker = "o", ms = markerSize, label = 'HHD', lw =linewidth)
plt.plot([1, 2, 3, 4], [6, 31, 153, 768],'m.-.',marker = "^", ms = markerSize, label = 'SYN Flood', lw =linewidth)
plt.plot([1, 2, 3, 4], [5, 13, 24, 38], 'k:',marker = "s", ms = markerSize-0.5, label = 'Rate limiter', lw =linewidth)
plt.yscale('log')

x_ticks = np.arange(0, 5, 1)
plt.xticks(x_ticks)
plt.margins(x=0.08)

plt.xlabel('No. of packets')
plt.ylabel('No. of branches (log scale)')
plt.legend(loc = 'best', fontsize=12)


# plt.show()
# trial 1 -> tried and it works, no need for trial 2
plt.savefig('PacketVsBranch.pdf')
