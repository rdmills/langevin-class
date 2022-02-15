#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import mpl_toolkits.axes_grid1
import matplotlib.widgets

class PostProcessor:

    def __init__(self, data_file_name, opts_plot):
        
        self.opts_plot = opts_plot
        self.data_file_name = data_file_name
        self.data        = None
        self.Time        = None
        self.state_data  = None
        self.read_data()

        self.T_max         = None
        self.num_steps     = None
        self.step_size     = None
        self.initial_data  = None
        self.y_min_y_max   = None
        self.num_particles = None
        self.get_phys_num_opts()

        self.num_frames = self.num_steps

    def read_data(self):    
        print("Reading " + self.data_file_name + " data...")
        data = np.genfromtxt(self.data_file_name + '_data.dat',
                                 dtype=float,
                                 delimiter=' ')
        self.data = data[:-1,:]
        self.time = data[-1,:]
        self.state_data = self.data.T
        print("...done.")

    def get_phys_num_opts(self):    
        num_list = np.genfromtxt(self.data_file_name + '_num.dat',
                                 dtype=float,
                                 delimiter=' ')
        
        print("num_list = {}".format(num_list))     
        self.T_max     = num_list[0]                                    
        self.num_steps = num_list[1]                                    
        self.step_size = num_list[2]                                                                   

        phys_list = np.genfromtxt(self.data_file_name + '_phys.dat',
                                 dtype=float,
                                 delimiter=' ')
        print("phys_list = {} \n".format(phys_list))
        self.y_min_y_max   = phys_list[0:2]                                 
        self.num_particles = phys_list[2]                                 

    def equilibrium_dist(self):
        h = 0.2    
        a = 5.0
        HIST_BINS = np.linspace(-a-h, a+h, opts_plot["num_bins"])     
        hist_eq = self.data[:,-1]
        _ = plt.hist(hist_eq, 
                     HIST_BINS,
                     edgecolor=self.opts_plot["edge_colour"],
                     facecolor=self.opts_plot["face_colour"],
                     density = True)
        
        print("Plotting equilibrium density...")
        plt.show()

    def dynamic_dist(self):    

        h = 0.2    
        a = 5.0
        HIST_BINS = np.linspace(-a-h, a+h, opts_plot["num_bins"])     

        fig, ax = plt.subplots()
        _, _, bars = ax.hist(self.data[:,0], 
                             HIST_BINS, 
                             lw=1,
                             edgecolor=self.opts_plot["edge_colour"], 
                             facecolor=self.opts_plot["face_colour"], 
                             alpha=self.opts_plot["alpha"],
                             density=True)

        def prepare_animation(bar_container):
            
            def animate(frame_number):
                n, _ = np.histogram(self.data[:,frame_number], HIST_BINS, density=True)
                for count, rect in zip(n, bar_container.patches):
                    rect.set_height(count)
                return bar_container.patches
            return animate

        ax.set_ylim(top=3.0) 
        
        print("Plotting dynamics...")
        ani = Player(fig, prepare_animation(bars), maxi=self.num_frames)

        plt.show()

class Player(FuncAnimation):
    
    def __init__(self, fig, func, frames=None, init_func=None, fargs=None,
                 save_count=None, mini=0, maxi=100, pos=(0.125, 0.92), **kwargs):
        self.i = 0
        self.min=mini
        self.max=maxi
        self.runs = True
        self.forwards = True
        self.fig = fig
        self.func = func
        self.setup(pos)
        FuncAnimation.__init__(self,self.fig, self.update, frames=self.play(), 
                                           init_func=init_func, fargs=fargs,
                                           save_count=save_count, **kwargs )    

    def play(self):
        while self.runs:
            self.i = self.i+self.forwards-(not self.forwards)
            if self.i > self.min and self.i < self.max:
                yield self.i
            else:
                self.stop()
                yield self.i

    def start(self):
        self.runs=True
        self.event_source.start()

    def stop(self, event=None):
        self.runs = False
        self.event_source.stop()

    def forward(self, event=None):
        self.forwards = True
        self.start()

    def backward(self, event=None):
        self.forwards = False
        self.start()
    
    def oneforward(self, event=None):
        self.forwards = True
        self.onestep()
    
    def onebackward(self, event=None):
        self.forwards = False
        self.onestep()

    def onestep(self):
        if self.i > self.min and self.i < self.max:
            self.i = self.i+self.forwards-(not self.forwards)
        elif self.i == self.min and self.forwards:
            self.i+=1
        elif self.i == self.max and not self.forwards:
            self.i-=1
        self.func(self.i)
        self.slider.set_val(self.i)
        self.fig.canvas.draw_idle()

    def setup(self, pos):
        playerax = self.fig.add_axes([pos[0],pos[1], 0.64, 0.04])
        divider = mpl_toolkits.axes_grid1.make_axes_locatable(playerax)
        bax = divider.append_axes("right", size="80%", pad=0.05)
        sax = divider.append_axes("right", size="80%", pad=0.05)
        fax = divider.append_axes("right", size="80%", pad=0.05)
        ofax = divider.append_axes("right", size="100%", pad=0.05)
        sliderax = divider.append_axes("right", size="500%", pad=0.07)
        self.button_oneback = matplotlib.widgets.Button(playerax, label='$\u29CF$')
        self.button_back = matplotlib.widgets.Button(bax, label='$\u25C0$')
        self.button_stop = matplotlib.widgets.Button(sax, label='$\u25A0$')
        self.button_forward = matplotlib.widgets.Button(fax, label='$\u25B6$')
        self.button_oneforward = matplotlib.widgets.Button(ofax, label='$\u29D0$')
        self.button_oneback.on_clicked(self.onebackward)
        self.button_back.on_clicked(self.backward)
        self.button_stop.on_clicked(self.stop)
        self.button_forward.on_clicked(self.forward)
        self.button_oneforward.on_clicked(self.oneforward)
        self.slider = matplotlib.widgets.Slider(sliderax, '', 
                                                self.min, self.max, valinit=self.i)
        self.slider.on_changed(self.set_pos)

    def set_pos(self,i):
        self.i = int(self.slider.val)
        self.func(self.i)

    def update(self,i):
        self.slider.set_val(i)

if __name__ == "__main__":
    
    opts_plot = {"num_bins" : 50,
                 "alpha" : 0.5,
                 "bin_rule" : "auto",
                 "edge_colour" : "white", 
                 "face_colour" : "magenta"}

    mckean_vlasov = PostProcessor('gauss', opts_plot)
    mckean_vlasov.dynamic_dist()
    # mckean_vlasov.equilibrium_dist()

