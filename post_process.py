#!/usr/bin/env python3

import numpy as np
import math
import matplotlib.pyplot as plt

class PostProcessor:

    def __init__(self, data, opts_plot):
        self.opts = opts_plot
        self.data = data


if __name__ == "__main__":

    data = np.genfromtxt('overdamped_langevin.dat',
                        dtype=float,
                        delimiter=' ')
    
    tt = data[-1,:]
    sol_a = np.exp(-data[-1,:])

    ax = plt.axes()

    ax.plot(tt,sol_a,'r-')
    ax.plot(tt,data[0,:],'b-')
    ax.plot(tt,data[1,:],'m-')
    ax.plot(tt,data[2,:],'c-')
    

    rel_error = np.abs(data[0,:]-sol_a)/np.abs(sol_a)

    # ax.plot(tt,rel_error,'k-')

    plt.show()

