#!/usr/bin/env python3


import matplotlib.pyplot as plt
import json
import numpy as np



fn = "caldat.json"

caldat = json.load(open(fn))

xarr = np.linspace(0, 1023, 1024)

for dd in caldat['0'][0]:
    plt.plot(xarr, sum([dd[i]*xarr**i for i in range(4)]))

plt.show()
