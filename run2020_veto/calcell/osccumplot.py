#!/usr/bin/env python

import argparse
import ROOT as root
import matplotlib.pyplot as plt
import numpy as np
import json
import ROOT as root
import json
import pickle
import numpy
import matplotlib.pyplot as plt
import scipy.sparse
import glob
from pprint import pprint
import re
from scipy.optimize import curve_fit
import collections





def hist2arr(th):
    js=root.TBufferJSON.ToJSON(th)
    hist=json.loads(js.Data())
    for i in hist:
        if i=='fArray': break
    xbins=hist['fXaxis']['fNbins']
    xmin=hist['fXaxis']['fXmin']
    xmax=hist['fXaxis']['fXmax']
    ybins=hist['fYaxis']['fNbins']
    ymin=hist['fYaxis']['fXmin']
    ymax=hist['fYaxis']['fXmax']
    if ybins==1: # TH1F
        pos=numpy.linspace(0,xbins,10)
        posval=pos*(xmax-xmin)/xbins+xmin

        #plt.xticks(pos,posval)
        arr=numpy.array(hist['fArray']).reshape(xbins+2)
        arr=arr[1:-1]
        xvals=numpy.linspace(xmin,xmax,xbins,endpoint=False)
        return xvals,arr

    else: #TH2F
        arr=numpy.array(hist['fArray']).reshape((ybins+2, xbins+2))
        lover,arr,rover=numpy.split(arr,[1,-1],axis=1)
        uover,arr,bover=numpy.split(arr,[1,-1],axis=0)
        xvals=numpy.linspace(xmin,xmax,xbins,endpoint=True)
        yvals=numpy.linspace(ymin,ymax,ybins,endpoint=True)
        return xvals,yvals,arr

        #coomat=scipy.sparse.coo_matrix(arr)
        #x=coomat.row
        #y=coomat.col
        #dat=coomat.data




def gaus(x,*p): return p[ 0]/numpy.sqrt(2*numpy.pi)/p[2]*numpy.exp(-(x-p[ 1])**2/2/p[ 2]**2)
gausvec=numpy.vectorize(gaus)



def osc_cum(name,inroot,ax0, ax1=None, mpv=False):
    hist=inroot.FindObjectAny(name)
    xarr,yarr,arr=hist2arr(hist)
    coomat=scipy.sparse.coo_matrix(arr)
    datx=[ xarr[i] for i in coomat.col]
    daty=[ yarr[i] for i in coomat.row]
    dat=coomat.data
    ticks=numpy.linspace(0,1000,11)
    #ax.scatter(datx,daty,marker='.',s=4,c=dat,cmap='rainbow', vmin=100, vmax=500)
    power=.29

    from matplotlib import cm
    from matplotlib.colors import ListedColormap, LinearSegmentedColormap
    rainbow = cm.get_cmap('rainbow', 256)
    newcolors = rainbow(np.linspace(0, 1, 256))
    white = np.array([1,1,1, 1])
    newcolors[:1, :] = white
    newcmp = ListedColormap(newcolors)

    ax0.pcolorfast(xarr,yarr,arr**(power), cmap=newcmp)
    ax0.set_xlabel('Time[samples]')
    ax0.set_ylabel('Amplitude[ADU]')
    ax0.set_ylim(3490, 3605)
    ax0.set_xticks(ticks)
    #ax0.set_xticklabels((ticks/5).astype(int))

    ax0.grid(linestyle=':')
    if ax1:

        histosccum = arr.sum(axis=1)
        ax1.plot(histosccum, yarr, label='data')
        if mpv:
            mpv_idx = np.where(histosccum==histosccum.max())[0][0]
            mpv_y = yarr[mpv_idx]
            ax1.plot([0, 1e9],[mpv_y, mpv_y],'-c', label='MPV')
        else:
            popt=[500000*7.5, 3550, 3]
            popt,covt=curve_fit(gaus,yarr,arr.sum(axis=1),p0=popt)
            ax1.plot(gausvec(yarr, *popt), yarr, '--r', linewidth=1, label=f'$\mu={popt[1]:4.0f}$\n$\sigma={popt[2]:3.1f}$')
            print(popt)

        ax1.set_xlim(0,.85e6)
        ax1.grid(linestyle=':')
        ax1.set_xticks(np.linspace(0, .85e6,5))
        ax1.set_xticklabels('')
        #ax[0].set_xticklabels('')
        ax1.legend(loc='lower right',handlelength=1.0, fontsize='small', markerscale=.3)


filename = '../cosmicrun-CALcosmic-poly5.root'
ifile = root.TFile(filename)


def before_after():
    fig, ax = plt.subplots(2,2, sharey=True, squeeze=True, figsize=(6,4), gridspec_kw={'width_ratios': [13, 3]})
#fig.suptitle('run 0030375, random trigger, ADC 25, channel 11')
#osc_cum('b25_PedestalCell_ch23'        ,ifile,ax)
    osc_cum('b25_Pedestal_nocal_time_ch11',ifile,*ax[0])
    osc_cum('b25_Pedestal_cal_time_ch11',ifile,*ax[1])
    ax[0][1].set_xticklabels('')
    ax[0][0].set_xticklabels('')
#fig.text(1,.75, 'Factory calibration', rotation='vertical', in_layout=True, ha='right', va='center')
#fig.text(1,.32, 'Self-made calibration', rotation='vertical', in_layout=True, ha='right', va='center')
    ax[0][0].set_ylabel('drs4corr')
    ax[1][0].set_ylabel('Poly5')
    fig.tight_layout()
    fig.subplots_adjust(hspace=0.03, wspace=0.03)
    fig.savefig('before_vs_after_calibration.pdf')

#before_after()

fig, ax = plt.subplots(2,2, sharey=True, squeeze=True, figsize=(6,3), gridspec_kw={'width_ratios': [13, 3]})
osc_cum('b27_Pedestal_nocal_Cell_ch12'    ,ifile,*ax[0])
osc_cum('b27_ch12_Cells_time_cap_5'        ,ifile,*ax[1], mpv=True)
ax[0][0].set_ylim(3760,3834)
ax[1][0].set_ylim(3760,3834)
ax[0][0].set_ylabel('Amplitude')
ax[1][0].set_ylabel('Amplitude')
ax[0][0].set_xlabel('Cell index')
ax[1][0].set_xlabel('Time [Samples]')
ax[1][1].set_xlim(0,7e2)
ax[0][1].get_legend().remove()
fig.tight_layout()
fig.subplots_adjust(wspace=0.03)
ax[1][0].text(50, 3770, 'Cell index = 5')
fig.savefig('osccum-cellid.pdf')
plt.show()
exit()

#fig, ax = plt.subplots(figsize=(8.5,5))
fig, ax = plt.subplots(1,2, sharey=True, squeeze=True, figsize=(8.5,5), gridspec_kw={'width_ratios': [5, 1]})
osc_cum('b25_PedestalNoCellPedCor_ch3',ifile,*ax)
ax[1].set_xlim(0,500000)
fig.tight_layout()
fig.savefig('amplitudes_factory_calib.pdf')
