#!/usr/bin/env python3

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

safecolors=[ "#88CCEE", "#CC6677", "#DDCC77", "#117733", "#332288", "#AA4499", "#44AA99", "#999933", "#882255", "#661100", "#6699CC", "#888888" ]
vibrant_colors=[
        "#0077BB",
        "#33BBEE",
        "#009988",
        "#EE7733",
        "#CC3311",
        "#EE3377",
        "#BBBBBB",
        ]
muted_colors=[
        "#332288",
        "#88CCEE",
        "#44AA99",
        "#117733",
        "#999933",
        "#DDCC77",
        "#CC6677",
        "#882255",
        "#AA4499",
        "#DDDDDD",
        ]
safecolors=[
        "#332288",
        "#88CCEE",
        "#44AA99",
        "#117733",
        "#999933",
        "#DDCC77",
        "#CC6677",
        "#882255",
        "#AA4499",
        "#EE7733",
        "#CC3311",
        "#EE3377",
        ]
markers='pP*Xdv^<>o1234'

class PlotFile():
    def __init__(self,filename='',nrows=1,ncols=1,filetype='pdf'):
        self.filename=filename
        self.figure,self.axis=plt.subplots(nrows=nrows,ncols=ncols)
        self.filetype=filetype
        self.axis.grid(b=True,which='major', linewidth=.5,color='gray', linestyle='--')
    def __enter__(self):
        return self
    def __del__(self):
        pass
    def __exit__(self, exct_type, exce_value, traceback):
        #self.filename=False
        if self.filename:
            self.figure.tight_layout()
            self.figure.savefig(self.filename+'.'+self.filetype)
            plt.close(self.figure)
        else:
            plt.show()
            #self.figure.show()
            #input('pres enter')

def rebin2(arr,i,j):
    shape=i,arr.shape[0]//i,j,-1
    return arr.reshape(shape).sum(axis=3).sum(1)
def rebin1(arr,i):
    return arr.reshape(i,arr.shape[0]//i).sum(1)

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
        xvals=numpy.linspace(xmin,xmax,xbins,endpoint=False)
        yvals=numpy.linspace(ymin,ymax,ybins,endpoint=False)
        return xvals,yvals,arr

        #coomat=scipy.sparse.coo_matrix(arr)
        #x=coomat.row
        #y=coomat.col
        #dat=coomat.data















def chargedistr(name,inroot,ax):
    hist=inroot.FindObjectAny(name)
    xarr,arr=hist2arr(hist)
    arr=arr/arr.max()
    ax.step(xarr,arr,where='post',label='data')
    ax.set_xlabel('Charge[PhE]')
    #ax.set_yscale('log')
    return xarr,arr



def chargedistr_ch16(inroot):
    from scipy.optimize import curve_fit
    from scipy.stats import norm
    import math
    def errrf(x,a,x0,w):
        return a/2*(1+math.erf((x-x0)/w/numpy.sqrt(2)))*numpy.sqrt(2*numpy.pi)*w
    def errrf_right(x,a,x0,w):
        return a/2*(1-math.erf((x-x0)/w/numpy.sqrt(2)))*numpy.sqrt(2*numpy.pi)*w
    def sumgaus(x,*p):
        return (
                p[ 0]*numpy.exp(-(x-p[ 1])**2/2/p[ 2]**2)+
                p[ 3]*numpy.exp(-(x-p[ 4])**2/2/p[ 5]**2)+
                p[ 6]*numpy.exp(-(x-p[ 7])**2/2/p[ 8]**2)+
                p[ 9]*numpy.exp(-(x-p[10])**2/2/p[11]**2)+
                p[12]*numpy.exp(-(x-p[13])**2/2/p[14]**2)+
                p[15]*numpy.exp(-(x-p[16])**2/2/p[17]**2)+
                p[18]*numpy.exp(-(x-p[19])**2/2/p[20]**2)+
                #p[21]*numpy.exp(-(x-p[22])**2/2/p[23]**2)+
                #p[24]*numpy.exp(-(x-p[25])**2/2/p[26]**2)
                0
                )

    name='PhElectrAbs_ch_16'
    with PlotFile(name) as plot:
        #plot.axis.plot([1,2,3],[40,50,60])
        plot.axis.set_title('Charge distribution DAQ 16 (BTF Calo) run 618')
        #plot.axis.set_ylim(1e-2,1)
        plot.axis.set_yscale('log')
        plot.axis.set_ylim(.0001,2)
        plot.axis.set_xlim(-30,1430)
        xarr,arr=chargedistr(name,inroot,plot.axis)
        p0=[
                1     ,12 ,1.4  ,
                2e-2  ,220,27.7  ,
                2e-2  ,440,41   ,
                2e-2  ,664,43   ,
                2e-2  ,888,44   ,
                1e-2  ,1115,46.4 ,
                .005 ,1361,47.68,
                #0.026,335,13.35,
                #.034 ,373,18.8 ,
                ]
        popt=p0
        popt,covt=curve_fit(sumgaus,xarr,arr,p0=p0,bounds=([0,2,0.005]*7,[1.1,2000,60]*7))
        fitx=xarr
        fity=[sumgaus(xx,*popt) for xx in fitx]
        plot.axis.plot(fitx,fity,label=r'$\sum_{i=0}^7\, A_i\,exp\left(-\frac{(x-x0_i)^2}{2\,w^2}\right)$')
        #fity=[sumgaus(xx,*p0) for xx in fitx]
        #plot.axis.plot(fitx,fity)


        popt=numpy.array(popt).reshape(-1,3)
        for par in popt[:7]:
            #fity=[par[0]*numpy.exp(-(xx-par[1])**2/2/par[2]**2) for xx in fitx]
            fity=par[0]*numpy.exp(-(fitx-par[1])**2/2/par[2]**2)
            plot.axis.plot(fitx,fity)

        edge=(80,290)

        p1=popt[1]
        integral=errrf(edge[1],p1[0],p1[1],p1[2])-errrf(edge[0],p1[0],p1[1],p1[2])
        print('integral',integral,errrf(numpy.inf,p1[0],p1[1],p1[2]),integral/errrf(numpy.inf,p1[0],p1[1],p1[2]))


        multiple=0
        for gaus_i in range(2,7):
            multiple+=errrf(edge[1],popt[gaus_i][0],popt[gaus_i][1],popt[gaus_i][2])
            multiple-=errrf(edge[0],popt[gaus_i][0],popt[gaus_i][1],popt[gaus_i][2])
            print(gaus_i,multiple/integral*100,'%')

        zeropart=errrf_right(edge[0],popt[0][0],popt[0][1],popt[0][2])
        zeropart-=errrf_right(edge[1],popt[0][0],popt[0][1],popt[0][2])
        print(0, zeropart)
        primesi=zeropart+multiple
        print('primesi',primesi, primesi/integral*100 ,'%')

        gausX0s=popt[:,1]
        gausX0sig=numpy.diag(covt).reshape(-1,3)[:,1]
        gausX0s  =gausX0s  [:-1]
        gausX0sig=gausX0sig[:-1]

        zz=zip(xarr,arr)
        zz=filter(lambda x:edge[0]<=x[0]<=edge[1],zz)
        xhatch,yhatch=zip(*zz)  #,step='post'
        xhatch=[edge[0]]+list(xhatch)+[edge[1]]
        yhatch=[0]+list(yhatch)+[0]
        plot.axis.fill(xhatch,yhatch,label='Single particle beam', fill=False, hatch="//")
        plot.axis.legend()
        #plot.axis.legend(loc='lower right')
    ###with PlotFile('cal-linearity') as plot:
    ###    plot.axis.errorbar(list(range(len(gausX0s))),gausX0s, yerr=gausX0sig)



def osc_cum(name,inroot,ax):
    hist=inroot.FindObjectAny(name)
    xarr,yarr,arr=hist2arr(hist)
    coomat=scipy.sparse.coo_matrix(arr)
    datx=[ xarr[i] for i in coomat.col]
    daty=[ yarr[i] for i in coomat.row]
    dat=coomat.data
    ax.scatter(datx,daty,marker='.',s=2,c=numpy.log(dat)*dat**(-.1),cmap='rainbow')
    ax.set_xlabel('Time[ns]')
    ax.set_ylabel('Amplitude[V]')
    ticks=numpy.linspace(0,1000,11)
    ax.set_xticks(ticks)
    ax.set_xticklabels((ticks/5).astype(int))

def osc_trigNoT0(inroot):
    name='TriggerCumulativeOscillogram_ch_0'
    with PlotFile(name,filetype='png') as plot:
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_ylim(-100,2600)
        plot.axis.set_ylabel('Amplitude[ADU]')
        plot.axis.set_title('Cumulative oscillogram Trigger; no T0')
        plot.axis.set_xlabel('Time[samples]')
        plot.axis.set_xticklabels(map(int,plot.axis.get_xticks()))

def osc_trigT0(inroot):
    name='TriggerCumulativeOscillogramT0Fixed_ch_0'
    with PlotFile(name,filetype='png') as plot:
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_ylim(-100,2600)
        plot.axis.set_ylabel('Amplitude[ADU]')
        plot.axis.set_title('Cumulative oscillogram Trigger; T0 applied')
        plot.axis.set_xlabel('Time[samples]')
        plot.axis.set_xticklabels(map(int,plot.axis.get_xticks()))

def osc_cumCaloT0(inroot):
    name='CumulativeOscillogramT0Fixed_ch_16'
    with PlotFile(name,filetype='png') as plot:
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_title('Cumulative oscillogram DAQ 16 (BTF Calo) run 618')
        ranges={
                'Ped\nreg'        :(30,100),
                'Noise\nregion'   :(100,360),
                'Signal\nregion'  :(500,660),
                }
        for lab,ran in ranges.items():
            plot.axis.axvline(ran[0])
            plot.axis.axvline(ran[1])
            plot.axis.text((ran[0]+ran[1])/2,0.03,lab,horizontalalignment='center',verticalalignment='center')

def osc_cumSiPM(inroot):
    name='CumulativeOscillogramT0Fixed_ch_7'
    with PlotFile(name,filetype='png') as plot:
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_title('Cumulative oscillogram DAQ 7 (SiPM) run 618')
        ranges={
                'Ped\nreg'        :(30,100),
                'Noise\nregion'   :(100,450),
                'Signal\nregion'  :(450,800),
                }
        for lab,ran in ranges.items():
            plot.axis.axvline(ran[0])
            plot.axis.axvline(ran[1])
            plot.axis.text((ran[0]+ran[1])/2,0.025,lab,horizontalalignment='center',verticalalignment='center')





def plotTH1(name,inroot,ax):
    hist=inroot.FindObjectAny(name)
    x,y,arr=hist2arr(hist)
    #ax.step(x,arr,where='mid')
    ax.step(x,arr,where='post')
    #ax.scatter(x,arr)
    #ax.set_ylim(.5,2000)
    #ax.set_yscale('log')


def plot_signals_from_study(inroot):
    name='SignalStudy_ch_2'
    hist=inroot.FindObjectAny(name)
    x,y,arr=hist2arr(hist)
    with PlotFile('signal_study') as plot:
        #ax.step(x,arr,where='mid')
        for i in [75,14]: # chan 2 19,22
            plot.axis.plot(x,-arr[i])
        #ax.scatter(x,arr)
        #ax.set_ylim(.5,2000)
        #ax.set_yscale('log')
        ticks=numpy.linspace(0,1000,21)
        plot.axis.set_title('Sample signals DAQ 2 (H9500 D6)')
        plot.axis.set_xticks(ticks)
        plot.axis.set_xticklabels((ticks/5).astype(int))
        plot.axis.set_xlim(250,600)
        plot.axis.set_xlabel('Time[ns]')
        plot.axis.set_ylabel('Amplitude[V]')






def effinef_plt_config(ax):
    ax.set_xlim(1,100)
    ax.set_ylim(.001,1)
    ax.set_yscale('log')
    #ax.legend(loc='lower left')
    ax.legend()

    ticks=numpy.geomspace(1e-4,1e-1,4)
    ax.set_yticks(ticks)
    ax.set_yticklabels(map(lambda x:'%g'%(x*100), ticks))
    ax.set_xlabel('Charge[PhE]')
    ax.set_ylabel('Noise / Inefficiency[%]')
    ax.grid(b=True,which='minor', linewidth=.2,color='gray', linestyle='--')
    ax.grid(b=True,which='major', linewidth=.5,color='gray', linestyle='--')



def effinef():
    chansdic = {
            8 :'Scintillator with fiber\nScintillator only readout',
            9 :'Aluminized scintillator with fiber\nScintillator and fiber readout',
            10:'Scintillator without fiber\nScintillator only readout',
            11:'Scintillator with fiber\nScintillator and fiber readout',
            }
    rootfile=root.TFile('run_618.lst.root')


    ### 4 channel efficincy/noise CUMULATIVES
    with PlotFile('effinef') as plot:
        for chan_i,chan in enumerate(chansdic):
            eff,noi=f'PhElectrEffAbs_ch_{chan}', f'PhElectrNoiseAbs_ch_{chan}'
            print(eff,noi)
            eff_hist=rootfile.FindObjectAny(eff)
            noi_hist=rootfile.FindObjectAny(noi)
            print(eff_hist)
            print(noi_hist)
            eff_x,eff_arr=hist2arr(eff_hist)
            noi_x,noi_arr=hist2arr(noi_hist)
            eff_cum=numpy.cumsum(eff_arr)
            noi_cum=numpy.cumsum(noi_arr)
            eff_cum=eff_cum/eff_cum.max()
            noi_cum=noi_cum/noi_cum.max()

            def lines_crossing_poing(l1_x,l1_y,l2_x,l2_y):
                # noise inef cross
                for i in range(len(l1_x)):
                    ex_2=l1_x[i]
                    ey_2=l1_y[i]
                    nx_2=l2_x[i]
                    ny_2=l2_y[i]
                    if ey_2 == ny_2:
                        return ex_2,ey_2
                    if ey_2 > ny_2:
                        r_noi=(ny_2-ny_1)/(nx_2-nx_1)
                        r_eff=(ey_2-ey_1)/(ex_2-ex_1)
                        crosx=(r_noi*nx_1-ny_1 - r_eff*ex_1+ey_1)/(r_noi-r_eff)
                        if r_noi == 0:
                            crosy=ny_2
                        elif r_eff==0:
                            crosy=ey_2
                        else:
                            crosy=(-nx_1 + ny_1/r_noi + ex_1 - ey_1/r_eff )/(1/r_noi-1/r_eff)
                        return crosx,crosy
                    ex_1=l1_x[i]
                    ey_1=l1_y[i]
                    nx_1=l2_x[i]
                    ny_1=l2_y[i]


            crosx,crosy=lines_crossing_poing(eff_x,eff_cum,noi_x,1-noi_cum)


            plot.axis.plot(eff_x,eff_cum  ,'-' ,label=f'Ch.{chan} Ineff',color=vibrant_colors[chan_i+1])
            plot.axis.plot(noi_x,(1-noi_cum),'--',label=f'Ch.{chan} Noise',color=vibrant_colors[chan_i+1])
            plot.axis.plot([crosx],[crosy],'o',color=vibrant_colors[chan_i+1])

        plot.axis.set_title("Efficiency plot\nbeam at 90mm (centered along the bar)")
        effinef_plt_config(plot.axis)

    ### 4 channel efficincy/noise vs BEAM POSITION
    runs = {
            170: 613, #'run_613.lst.root',
            150: 614, #'run_614.lst.root',
            130: 616, #'run_616.lst.root',
            110: 617, #'run_617.lst.root',
            90:  618, #'run_618.lst.root',
            70:  619, #'run_619.lst.root',
            50:  621, #'run_621.lst.root',
            30:  622, #'run_622.lst.root',
            10:  623, #'run_623.lst.root',
            }
    res={}
    for chan_i,chan in enumerate(chansdic):
        res[chan]={
                'x':[],
                'eff_y':[],
                'noi_y':[],
                }


    for pos,run_i in runs.items():
        rootfile=root.TFile(f'run_{run_i}.lst.root')
        for chan_i,chan in enumerate(chansdic):


            eff,noi=f'PhElectrEffAbs_ch_{chan}', f'PhElectrNoiseAbs_ch_{chan}'
            print(eff,noi)
            eff_hist=rootfile.FindObjectAny(eff)
            noi_hist=rootfile.FindObjectAny(noi)
            print(eff_hist)
            print(noi_hist)
            eff_x,eff_arr=hist2arr(eff_hist)
            noi_x,noi_arr=hist2arr(noi_hist)
            eff_cum=numpy.cumsum(eff_arr)
            noi_cum=numpy.cumsum(noi_arr)
            eff_cum=eff_cum/eff_cum.max()
            noi_cum=noi_cum/noi_cum.max()



            threshold=20
            for i,x in enumerate(eff_x):
                if x>threshold:
                    eff=eff_cum[i]
                    break

            for i,x in enumerate(noi_x):
                if x>threshold:
                    noi=1-noi_cum[i]
                    break

            res[chan]['x'].append(pos)
            res[chan]['eff_y'].append(eff)
            res[chan]['noi_y'].append(noi)

    print(res)
    with PlotFile('inefficiency_vs_beam_position') as plot:
        for chan_i,(chan,dat) in enumerate(res.items()):
            plot.axis.plot(dat['x'],dat['eff_y'],marker=markers[chan_i],color=vibrant_colors[chan_i+1],label=f'Ch.{chan}')
        plot.axis.set_title(f'Inefficiency at threshold={threshold} PhE')
        plot.axis.set_yscale('log')
        plot.axis.set_ylabel('Inefficiency[%]')

        ticks=numpy.geomspace(1e-4,1e-1,4)
        plot.axis.set_yticks(ticks)
        plot.axis.set_yticklabels(map(lambda x:'%g'%(x*100), ticks))
        plot.axis.set_xlabel('Beam position starting from SiPM [mm]')
        plot.axis.set_ylim(.001,1)
        plot.axis.legend()

    with PlotFile('noise_vs_beam_position') as plot:
        for chan_i,(chan,dat) in enumerate(res.items()):
            plot.axis.plot(dat['x'],dat['noi_y'],marker=markers[chan_i],color=vibrant_colors[chan_i+1],label=f'Ch.{chan}')
        plot.axis.set_title(f'Noise at threshold={threshold} PhE')
        plot.axis.set_yscale('log')
        plot.axis.set_ylabel('Noise [%]')
        ticks=numpy.geomspace(1e-4,1e-1,4)
        plot.axis.set_yticks(ticks)
        plot.axis.set_yticklabels(map(lambda x:'%g'%(x*100), ticks))
        plot.axis.set_ylim(.004,.15)
        plot.axis.set_xlabel('Beam position starting from SiPM [mm]')
        plot.axis.legend()










def timediff():
    from scipy.optimize import curve_fit
    def gaus(x,*p):
        return p[ 0]/numpy.sqrt(2*numpy.pi)/p[2]*numpy.exp(-(x-p[ 1])**2/2/p[ 2]**2)
    gausvec=numpy.vectorize(gaus)

    chansdic = {
            (4,8):'Scintillator with fiber\nScintillator only readout',
            (5,9):'Aluminized scintillator with fiber\nScintillator and fiber readout',
            (6,10):'Scintillator without fiber\nScintillator only readout',
            (7,11):'Scintillator with fiber\nScintillator and fiber readout',
            }
    runs = {
            170: 613, #'run_613.lst.root',
            150: 614, #'run_614.lst.root',
            130: 616, #'run_616.lst.root',
            110: 617, #'run_617.lst.root',
            90:  618, #'run_618.lst.root',
            70:  619, #'run_619.lst.root',
            50:  621, #'run_621.lst.root',
            30:  622, #'run_622.lst.root',
            10:  623, #'run_623.lst.root',
            }

    methods=[
            "MeanTime",
            "MeanTime2",
            "MeanTimeAbs",
            "2080LeadTrailCros",
            "2080LeadZeroCros",
            "2080Lead50",
            "HalfMaxValue",
            "MaxValue",
            "01MaxValue",
            "02MaxValue",
            "Integral",
            ]

    try:
        #raise FileNotFoundError
        res=pickle.load(open('/tmp/time-characteristics.temp','rb'))
        print('warning /tmp/time-characteristics.temp used')
    except FileNotFoundError:
        res={}
        for dif_ch,lab in chansdic.items():
            res[(dif_ch[0],dif_ch[1])]={}
            for met in methods:
                res[(dif_ch[0],dif_ch[1])][met]={'x':[],'y':[],'yerr':[]}

        for pos,run in runs.items():
            rootname=f'run_{run}.lst.root'
            inroot=root.TFile(rootname)
            for dif_ch,lab in chansdic.items():
                for met in methods:
                    histname=f'TimeDiff{met}_{dif_ch[0]}_{dif_ch[1]}'
                    print(histname)

                    hist=inroot.FindObjectAny(histname)
                    x,y,dat=hist2arr(hist)
                    if dat.sum()<800:
                        continue

                    dat=dat.sum(axis=0)
                    popt,covt=curve_fit(gaus,x,dat,p0=[dat.max(),0,2])
                    w=popt[2]/numpy.sqrt(2)
                    w_err=numpy.sqrt(covt[2][2])/numpy.sqrt(2)
                    res[(dif_ch[0],dif_ch[1])][met]['x'].append(pos)
                    res[(dif_ch[0],dif_ch[1])][met]['y'].append(w)
                    residuals=dat-gaus(x,*popt)
                    ss_res = numpy.sum(residuals**2)
                    ss_tot = numpy.sum((dat-numpy.mean(dat))**2)
                    r_squared = 1 - (ss_res / ss_tot)



                    res[(dif_ch[0],dif_ch[1])][met]['yerr'].append(r_squared)
        pickle.dump(res,open('/tmp/time-characteristics.temp','bw'))

    res[(6,10)]['01MaxValue']['y'][0]=None
    res[(6,10)]['01MaxValue']['y'][1]=None
    res[(6,10)]['02MaxValue']['y'][0]=None
    #res[(6,10)]['01MaxValue']['x'].pop()
    #res[(6,10)]['01MaxValue']['yerr'].pop()
    #res[(6,10)]['01MaxValue']['yerr'].pop()

    for pair,title in chansdic.items():
        pp=res[pair]
        with PlotFile('time_resolution_%d-%d'%(pair)) as plot:
            plot.axis.set_title(title)
            for i,met in enumerate(pp):
                #plot.axis.errorbar(pp[met]['x'],pp[met]['y'],yerr=pp[met]['yerr'],color=safecolors[i],marker=markers[i],label=met)
                plot.axis.errorbar(pp[met]['x'],pp[met]['y'],color=safecolors[i],marker=markers[i],label=met)
            #plot.axis.legend(numpy.sqrt(numpy.diag(covt)))
            plot.axis.legend(ncol=2,loc='upper left')
            plot.axis.set_ylabel(r'$\sigma\left(\frac{t_{ch.%d}-t_{ch.%d}}{\sqrt {2}}\right)$ [ns]'%(pair))
            plot.axis.set_xlabel('Beam position starting from SiPM [mm]')
            plot.axis.set_xlim(0,180)

    with PlotFile('time_resolution_method_compare') as plot:
        met="HalfMaxValue"

        plot.axis.set_title('Performance of different scintillator types\n%s used for time estimate'%met)
        for i,pair in enumerate(chansdic):
            plot.axis.errorbar(res[pair][met]['x'],res[pair][met]['y'],color=vibrant_colors[i+1],marker=markers[i],label='Ch.%d-Ch.%d'%(pair))
        plot.axis.legend()
        #plot.axis.legend(ncol=3,loc='upper center')
        plot.axis.set_ylabel(r'$\sigma\left(\frac{t_{ch.i}-t_{ch.j}}{\sqrt {2}}\right)$ [ns]')
        plot.axis.set_xlabel('Beam position starting from SiPM [mm]')
        plot.axis.set_xlim(0,180)
        plot.axis.set_ylim(0.4,1)




def pedestal_distr(inroot):
    name='Pedestals_ch_5'
    hist=inroot.FindObjectAny(name)
    xarr,arr=hist2arr(hist)
    with PlotFile('pedestal_ch_5') as plot:
    #with PlotFile('') as plot:
        plot.axis.step(xarr,arr)
        plot.axis.set_xlabel('Amplitude[ADU]')
        plot.axis.set_title('Pedestal D4 H9500 (DAQ 5)')
        plot.axis.set_xlim(3750,3780)
        plot.axis.set_yscale('log')
        #plot.axis.set_ylabel('Amplitude[V]')

def charge_distr(inroot):
    name='PhElectrAbs_ch_5'
    hist=inroot.FindObjectAny(name)
    xarr,arr=hist2arr(hist)
    with PlotFile('ph_electr_abs_ch_5') as plot:
    #with PlotFile('') as plot:
        plot.axis.step(xarr,arr)
        plot.axis.set_xlabel('Amplitude[PhE]')
        plot.axis.set_title('Charge distribution (abs) D4 H9500 (DAQ 5)')
        plot.axis.set_xlim(-40,400)
        #plot.axis.set_yscale('log')
        #plot.axis.set_ylabel('Amplitude[PhE]')


def FFT():
    def gaus(x,*p):
        return p[ 0]/numpy.sqrt(2*numpy.pi)/p[2]*numpy.exp(-(x-p[ 1])**2/2/p[ 2]**2)
    def n2freq(cut):
        '''convert nfreq to MHz'''
        return (5000.*(512-cut)/1024)
    def plot_signals(indic,ax,channel=5,event=5,static=[]):
        for _,inpar in sorted(indic.items()):
            inroot=root.TFile(inpar['fn'])
            histname=f'SignalStudyLowPass_ch_{channel}'
            if not static:
                static.append(1)
                histname=f'SignalStudy_ch_{channel}'
                hist=inroot.FindObjectAny(histname)
                x,y,arr=hist2arr(hist)
                ax.plot(x,-arr[event],label=f'No FFT')
            hist=inroot.FindObjectAny(histname)
            x,y,arr=hist2arr(hist)
            ax.plot(x,-arr[event],label=f'{inpar["mhz"]:6.0f} MHz')
            ticks=numpy.linspace(0,1000,11)
            ax.set_xticks(ticks)
            ax.set_xticklabels((ticks/5).astype(int))
            ax.set_xlabel('Time[ns]')
            ax.set_ylabel('Amplitude[V]')
            ax.set_title('FFT low-pass filtered signals')

    def plot_times(indic,ax):
        #indic  nfreq:{'fn':'name.root','mhz':2131}
        thres=25
        timemethod='TimeDiffMeanTimeAbs'
        timemethodFFT='TimeDiffMeanTimeFFTAbs'

        channels=[
                {'pair':( 8,10),'normtime':None,'freq':[],'FFTtime':[],'FFTtime_err':[], 'title':'$t_{D3}-t_{D7}$ H9500',},
                {'pair':( 2, 5),'normtime':None,'freq':[],'FFTtime':[],'FFTtime_err':[], 'title':'$t_{D4}-t_{D6}$ H9500',},
                {'pair':(21,22),'normtime':None,'freq':[],'FFTtime':[],'FFTtime_err':[], 'title':'$t_{D4}-t_{D6}$ R6427',},
                ]
        for _,inpar in sorted(indic.items()):
            inroot=root.TFile(inpar['fn'])

            for chandic in channels:
                if chandic['normtime'] is None:
                    histname=timemethod+f'_{chandic["pair"][0]}_{chandic["pair"][1]}'
                    print(histname)
                    hist=inroot.FindObjectAny(histname)
                    x,y,arr=hist2arr(hist)
                    arr=arr[int(numpy.where(y>thres)[0][0]):]
                    y=y[int(numpy.where(y>thres)[0][0]):]
                    arr=arr.sum(axis=0)
                    popt,covt=curve_fit(gaus,x,arr,p0=[arr.max(),0,2])
                    w=popt[2]/numpy.sqrt(2)
                    w_err=numpy.sqrt(covt[2][2])/numpy.sqrt(2)
                    chandic['normtime']=w
                    chandic['normtime_err']=w_err

                chandic['freq'].append(inpar['mhz'])
                histname=timemethodFFT+f'_{chandic["pair"][0]}_{chandic["pair"][1]}'
                print(histname)
                hist=inroot.FindObjectAny(histname)
                x,y,arr=hist2arr(hist)
                arr=arr[int(numpy.where(y>thres)[0][0]):]
                y=y[int(numpy.where(y>thres)[0][0]):]
                arr=arr.sum(axis=0)
                popt,covt=curve_fit(gaus,x,arr,p0=[arr.max(),0,2])
                w=popt[2]/numpy.sqrt(2)
                w_err=numpy.sqrt(covt[2][2])/numpy.sqrt(2)
                chandic['FFTtime'].append(w)
                chandic['FFTtime_err'].append(w_err)
        for pl_i,chandic in enumerate(channels):
            norm=chandic['normtime']
            norm_err=chandic['normtime_err']
            freq=numpy.array(chandic['freq'])
            fft    =numpy.array(chandic['FFTtime'])
            fft_err=numpy.array(chandic['FFTtime_err'])
            #fft_err=(fft_err*norm+norm_err*fft)/norm/fft
            #fft=fft/norm
            ax.errorbar(freq/1000,fft,yerr=fft_err,label=chandic['title'],color=safecolors[pl_i+3])
            ax.axhspan(norm-norm_err,norm+norm_err,alpha=.2,label='$\pm 1\sigma_t$ no filter', color=safecolors[pl_i+3],)
            ax.axhline(norm, color=safecolors[pl_i+3],alpha=.8,linewidth=1)


    files=glob.glob('579-FFT*.root')
    indata={}
    for f in files:
        m=re.match(r'.*FFT([0-9]+)\.root',f)
        ncancel=int(m[1])
        indata[ncancel]={'fn':f,'mhz':n2freq(ncancel)}
    with PlotFile('fft-lowpass-signals') as plot:
        plot_signals(indata,plot.axis)
        plot.axis.legend(ncol=3)
        plot.figure.tight_layout()
    with PlotFile('fft-lowpass-sigmas') as plot:
        plot_times(indata,plot.axis)
        plot.axis.set_title('FFT low-pass filter performance')
        plot.axis.set_ylabel(r'$\sigma\left(\frac{\Delta T}{\sqrt{2}}\right)$ [ns]')
        plot.axis.set_xlabel('Low-pass cut-off frequency [GHz]')
        l,r=plot.axis.get_xlim()
        plot.axis.set_xlim(r,l)
        plot.axis.legend(ncol=2)
        plot.figure.tight_layout()


def D4_noise_eff_example(inroot):
    name='PhElectrAbsEff_ch_5'
    hist=inroot.FindObjectAny(name)
    xarr,arr=hist2arr(hist)
    arr=numpy.array(arr)
    cumul=numpy.cumsum(arr)
    cumul=cumul/cumul.max()
    with PlotFile('D4_eff_example') as plot:
        plot.axis.errorbar(xarr,arr/arr.max(),yerr=numpy.sqrt(arr)/arr.max(), fmt='.', label='Signal spectrum')
        plot.axis.plot(xarr,cumul,label='Cumulative')
        plot.axis.set_xlabel('Amplitude[PhE]')
        plot.axis.set_title('Signal charge distribution (abs) D4 H9500 (DAQ 5)')
        plot.axis.set_xlim(0,100)
        plot.axis.legend()
    name='PhElectrAbsNoise_ch_5'
    hist=inroot.FindObjectAny(name)
    xarr,arr=hist2arr(hist)
    arr=numpy.array(arr)
    cumul=numpy.cumsum(arr)
    cumul=cumul/cumul.max()
    with PlotFile('D4_noise_example') as plot:
        plot.axis.errorbar(xarr,arr/arr.max(),yerr=numpy.sqrt(arr)/arr.max(), fmt='.', label='Noise spectrum')
        plot.axis.plot(xarr,1-cumul,label='$1-$Cumulative')
        plot.axis.set_xlabel('Amplitude[PhE]')
        plot.axis.set_title('Noise charge distribution (abs) D4 H9500 (DAQ 5)')
        plot.axis.set_xlim(2,9)
        plot.axis.legend()



def main():
    rootfile=root.TFile('run_618.lst.root')
    #osc_cumCalo(rootfile)
    #osc_cum7T0(rootfile)

    #pedestal_distr(rootfile)
    ###charge_distr(rootfile)
    #D4_noise_eff_example(rootfile)

    chargedistr_ch16(rootfile)
    #osc_cumSiPM(rootfile)
    #osc_cumCaloT0(rootfile)
    #effinef()
    #timediff()




    #FFT()




if __name__ == '__main__':
    main()
