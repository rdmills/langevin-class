#!/usr/bin/env python3

import numpy as np
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class PostProcessor:

    def __init__(self, data, opts_plot):
        self.opts = opts_plot
        self.data = data[:-1,:]
        self.time = data[-1,:]
        self.state_data = self.data.T
        self.opts_plot = opts_plot
        self.num_particles = np.size(self.data[:,0])
        self.num_frames = np.size(self.time)

    def plot(self):
        ax = plt.axes()
        ax.plot(self.time,self.data[0,:],'k-')
        plt.show()

    def equilibrium_dist(self):
        hist_eq = self.data[:,-1]
        _ = plt.hist(hist_eq, bins='auto', edgecolor='white')
        plt.show()

    # def dynamic_dist(self):    

    #     number_of_frames = self.num_frames
    #     state_data = self.state_data

    #     def update_hist(num, data):
    #         plt.cla()
    #         plt.hist(data[num])

    #     fig = plt.figure()
    #     hist = plt.hist(state_data[0])

    #     animation.FuncAnimation(fig, update_hist, number_of_frames, fargs=(state_data, ) )
    #     # animation = animation.FuncAnimation(fig, update_hist, number_of_frames, fargs=(data, ) )
    #     plt.show()


if __name__ == "__main__":

    data = np.genfromtxt('overdamped_langevin.dat',
                         dtype=float,
                         delimiter=' ')
    
    mckean_vlasov = PostProcessor(data,None)
    # print("Number of particles = {}".format(mckean_vlasov.num_particles))
    mckean_vlasov.equilibrium_dist()
