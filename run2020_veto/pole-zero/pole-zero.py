#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
import json

def filter(uin, r1,r2,c):
    ic=np.zeros(len(uin))
    uout=np.zeros(len(uin))
    integral=np.float128()
    #integral=0.
    ic[0]= uin[0]/r2;
    for i in range(1,len(uin)):
        integral+=ic[i-1]*1e-0
        print(integral, ic[i-1], uin[i]/r2, ((r1+r2)/(c*r1*r2)))
        ic[i]=uin[i]/r2-((r1+r2)/(c*r1*r2))*integral
        uout[i]=uin[i]-integral/c
    return uout



def normalize(dat):
    res = np.array(dat, dtype=np.longfloat)
    res /= 4096.
    medians = np.median(res[:][0:120], axis=1)
    res = (res.transpose() - medians).transpose()
    return res





for evt in range(300):

    jj = json.load(open("../b13_ch19.json"))
    jj = normalize(jj)
    fig, ax = plt.subplots(4, figsize=(8.5,5), constrained_layout=True, gridspec_kw={'height_ratios': [30, 1,1,1]})
    orig_sig_line, = ax[0].plot(jj[evt])


    #axr1 = plt.axes([0.1, 0.2 , 0.8, 0.03])
    #axr2 = plt.axes([0.1, 0.15, 0.8, 0.03])
    #axc  = plt.axes([0.1, 0.1 , 0.8, 0.03])
    r1_slider = Slider( ax=ax[1], label='R1', valmin=1, valmax=8000, valinit=392)
    r2_slider = Slider( ax=ax[2], label='R2', valmin=1, valmax=2000 , valinit=104)
    c_slider = Slider(  ax=ax[3], label='C'  , valmin=0, valmax=.5   , valinit=0.1426)

    ax[0].grid()
    ax[0].set_xlabel("Time [samples]", in_layout=True)
    ax[0].set_ylabel("Amplitude [V]")
    line, = ax[0].plot(filter(jj[evt], r1_slider.val, r2_slider.val, c_slider.val))

    ax[0].legend((orig_sig_line, line), ("original signal",'pole-zero filtered'), loc='lower left')




    def update(val):
        line.set_ydata(filter(jj[evt], r1_slider.val, r2_slider.val, c_slider.val))

    r1_slider.on_changed(update)
    r2_slider.on_changed(update)
    c_slider.on_changed(update)


    #plt.tight_layout()
    #plt.subplots_adjust(left=.1, bottom=0.3)
    #plt.subplots_adjust(gridspec_kw={'height_ratios': [20, 1,1,1]})

    plt.show()
    #fig.savefig(f'pz-{evt}.png')

