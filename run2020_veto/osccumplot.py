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



def osc_cum(name,inroot,ax0, ax1=None):
    hist=inroot.FindObjectAny(name)
    xarr,yarr,arr=hist2arr(hist)
    coomat=scipy.sparse.coo_matrix(arr)
    datx=[ xarr[i] for i in coomat.col]
    daty=[ yarr[i] for i in coomat.row]
    dat=coomat.data
    ticks=numpy.linspace(0,1000,11)
    #ax.scatter(datx,daty,marker='.',s=4,c=dat,cmap='rainbow', vmin=100, vmax=500)
    power=.29
    ax0.pcolorfast(xarr,yarr,arr**(power), cmap='rainbow')
    ax0.set_xlabel('Time[samples]')
    ax0.set_ylabel('Amplitude[ADU]')
    ax0.set_ylim(3534, 3561)
    ax0.set_xticks(ticks)
    #ax0.set_xticklabels((ticks/5).astype(int))
    if ax1:

        popt=[500000*7.5, 3550, 3]
        popt,covt=curve_fit(gaus,yarr,arr.sum(axis=1),p0=popt)
        ax1.plot(arr.sum(axis=1), yarr, label='data')
        ax1.plot(gausvec(yarr, *popt), yarr, '--r', linewidth=1, label=f'$\mu={popt[1]:4.0f}$\n$\sigma={popt[2]:3.1f}$')
        ax1.legend(loc='lower right',handlelength=1.5, fontsize='small')
        print(popt)

        ax1.set_xlim(0,700000)
        ax1.grid(linestyle=':')
        ax1.set_xticks([0,250000,500000])
        ax1.set_xticklabels('')
        #ax[0].set_xticklabels('')


filename = 'tt.root'
ifile = root.TFile(filename)


fig, ax = plt.subplots(2,2, sharey=True, squeeze=True, figsize=(8.5,5), gridspec_kw={'width_ratios': [5, 1]})
#osc_cum('b25_PedestalCell_ch23'        ,ifile,ax)
osc_cum('b25_Pedestal_ch3'            ,ifile,*ax[1])
osc_cum('b25_PedestalNoCellPedCor_ch3',ifile,*ax[0])
ax[0][1].set_xticklabels('')
ax[0][0].set_xticklabels('')
fig.text(1,.75, 'Factory calibration', rotation='vertical', in_layout=True, ha='right', va='center')
fig.text(1,.32, 'Self-made calibration', rotation='vertical', in_layout=True, ha='right', va='center')
fig.tight_layout()
fig.subplots_adjust(hspace=0.03, wspace=0.03)
fig.savefig('factory_vs_selfmade_calibration.pdf')


#fig, ax = plt.subplots(figsize=(8.5,5))
fig, ax = plt.subplots(1,2, sharey=True, squeeze=True, figsize=(8.5,5), gridspec_kw={'width_ratios': [5, 1]})
osc_cum('b25_PedestalCell_ch3'        ,ifile,*ax)
ax[1].set_xlim(0,500000)
ax[0].set_xlabel('Cell index')
fig.tight_layout()
fig.savefig('amplitudes_by_cell_index.pdf')

#fig, ax = plt.subplots(figsize=(8.5,5))
fig, ax = plt.subplots(1,2, sharey=True, squeeze=True, figsize=(8.5,5), gridspec_kw={'width_ratios': [5, 1]})
osc_cum('b25_PedestalNoCellPedCor_ch3',ifile,*ax)
ax[1].set_xlim(0,500000)
fig.tight_layout()
fig.savefig('amplitudes_factory_calib.pdf')
