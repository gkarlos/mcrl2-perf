

import matplotlib.pyplot as plt
from matplotlib import rcParams
from mpl_toolkits.axes_grid1 import make_axes_locatable
from matplotlib import cm
import math
plt.rcdefaults()

data = [[1806,1918,1858,1815,1789,1791,1788,1799,1794,1790,1766],
        [3826,3836,5209,792,8159,793,788,791,13963,793,790],
        [1357,1356,1373,1389,1438,1461,1496,1512,1528,1553,1588],
        [1815,1817,1879,1891,1925,1977,1998,2034,2065,2111,2164],
        [2298,2289,2340,2387,2444,2487,2506,2556,2610,2668,2763],
        [2752,2761,2833,2872,2926,2980,3027,3132,3163,3120,3022],
        [2954,2951,3078,3113,3143,3244,3490,3814,3597,3528,3568],
        [3427,3399,3556,3804,3802,3894,4065,4158,4169,4371,4334]]

fig, ax = plt.subplots()
im = ax.imshow(data)
ax.set_title("ATerm creation variable nesting, variable arity")
ax.set_xlabel("Nesting")
ax.set_ylabel("Arity")
ax.set_yticks(range(len(data)))
ax.set_xticks(range(len(data[0])))
divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size="5%", pad=0.05)

plt.colorbar(im, cax=cax)
plt.tight_layout()
plt.savefig("atermpp_term_creation_unique_heatmap")
