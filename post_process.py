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
                        dtype=None,
                        delimiter=' ')
    sol_a = np.exp(-data[:,0])

    ax = plt.axes()

    ax.plot(data[:,0],data[:,1],'b-')
    ax.plot(data[:,0],sol_a,'r-')

    rel_error = np.abs(data[:,1]-sol_a)/np.abs(sol_a)

    ax.plot(data[:,0],rel_error,'k-')

    plt.show()

