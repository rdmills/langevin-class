#!/usr/bin/env python3

import numpy as np
import math
import matplotlib.pyplot as plt

class PostProcessor:

    def __init__(self, data, opts_plot):
        self.opts = opts_plot
        self.data = data
        self.time = data[-1,:]
        self.opts_plot = opts_plot

    def plot(self):
        ax = plt.axes()
        ax.plot(self.time,self.data[0,:],'k-')
        plt.show()

    def hist(self):
        _ = plt.hist(self.data[:,-1], bins='auto')
        plt.show()


if __name__ == "__main__":

    data = np.genfromtxt('overdamped_langevin.dat',
                         dtype=float,
                         delimiter=' ')
    
    mckean_vlasov = PostProcessor(data,None)
    print("Number of samples = {}".format(np.size(mckean_vlasov.data[0,:])))
    mckean_vlasov.hist()

    # tt = data[-1,:]
    # sol_a = np.exp(-data[-1,:])

    # ax = plt.axes()

    # ax.plot(tt,sol_a,'r-')
    # ax.plot(tt,data[0,:],'b-')
    # ax.plot(tt,data[1,:],'m-')
    # ax.plot(tt,data[2,:],'c-')

    # rel_error = np.abs(data[0,:]-sol_a)/np.abs(sol_a)

    # # ax.plot(tt,rel_error,'k-')

    # plt.show()

