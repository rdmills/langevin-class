#!/usr/bin/env python3

from post_processor import PostProcessor
    
opts_plot = {"num_bins" : 50,
                "alpha" : 0.5,
                "bin_rule" : "auto",
                "edge_colour" : "white", 
                "face_colour" : "magenta"}

mckean_vlasov = PostProcessor('gauss', opts_plot)
mckean_vlasov.dynamic_dist()
# mckean_vlasov.equilibrium_dist()

