#!/usr/bin/env python3

import ROOT as root
import json
import numpy
import matplotlib.pyplot as plt
import scipy.sparse
import glob
import re
from scipy.optimize import curve_fit

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
markers='pP*Xdv^<>o'

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
        if self.filename:
            self.figure.tight_layout()
            self.figure.savefig(self.filename+'.'+self.filetype)
            plt.close(self.figure)
        else:
            plt.show()

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



def chargedistr_ch24(inroot):
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
                p[21]*numpy.exp(-(x-p[22])**2/2/p[23]**2)+
                p[24]*numpy.exp(-(x-p[25])**2/2/p[26]**2)
                )

    name='PhElectrAbs_ch_24'
    with PlotFile(name) as plot:
        #plot.axis.plot([1,2,3],[40,50,60])
        plot.axis.set_title('Charge distribution DAQ 24 (BTF Calo)')
        #plot.axis.set_ylim(1e-2,1)
        plot.axis.set_xlim(0,200)
        xarr,arr=chargedistr(name,inroot,plot.axis)
        p0=[1,5,1.4,.2,50,7.7,.24,97,11,.22,145,13,0.17,193,14,.11,242,16.4,0.065,290,17.68,0.026,335,13.35,.034,373,18.8]
        p0=[0.9999999999999999, 4.693799592374983, 1.2925841141552925, 0.6052285259508877, 48.902168068913184, 7.644904369423252, 0.7899896240786244, 96.21149322261765, 10.951597760644095, 0.8064693672629965, 143.68876598493816, 13.131527625387562, 0.6647847853792478, 191.23051043646174, 14.31772053154287, 0.4422289173798241, 239.0797752337072, 16.45913001757027, 0.17223739781957292, 284.7781211448898, 13.471152358853413, 0.1446444900338951, 318.9598496971182, 39.99999999999999, 0.0327257233768351, 414.9661675194721, 39.99999999932987]
        popt,covt=curve_fit(sumgaus,xarr,arr,p0=p0,bounds=([0,2,0.005]*9,[1,500,40]*9))
        fitx=numpy.arange(0,400)
        fity=[sumgaus(xx,*popt) for xx in fitx]
        plot.axis.plot(fitx,fity,label=r'$\sum_{i=0}^8\, A_i\,exp\left(-\frac{(x-x0_i)^2}{2\,w^2}\right)$')
        #fity=[sumgaus(xx,*p0) for xx in fitx]
        #plot.axis.plot(fitx,fity)

        popt=numpy.array(popt).reshape(-1,3)
        gausX0s=popt[:,1]
        gausX0sig=numpy.diag(covt).reshape(-1,3)[:,1]
        gausX0s  =gausX0s  [:-1]
        gausX0sig=gausX0sig[:-1]

        for par in popt[:7]:
            fity=[par[0]*numpy.exp(-(xx-par[1])**2/2/par[2]**2) for xx in fitx]
            plot.axis.plot(fitx,fity)

        p1=popt[1]
        integral=errrf(58,p1[0],p1[1],p1[2])-errrf(35,p1[0],p1[1],p1[2])
        print('integral',integral,errrf(numpy.inf,p1[0],p1[1],p1[2]),integral/errrf(numpy.inf,p1[0],p1[1],p1[2]))


        multiple=0
        for gaus_i in range(2,8):
            multiple+=errrf(58,popt[gaus_i][0],popt[gaus_i][1],popt[gaus_i][2])
            multiple-=errrf(35,popt[gaus_i][0],popt[gaus_i][1],popt[gaus_i][2])
            print(gaus_i,multiple/integral*100,'%')

        zeropart=errrf_right(35,popt[0][0],popt[0][1],popt[0][2])
        zeropart-=errrf_right(58,popt[0][0],popt[0][1],popt[0][2])
        print(zeropart)
        print('primesi ot zeropart <', 2.44/errrf(35,popt[0][0],popt[0][1],popt[0][2]))
        primesi=zeropart+multiple
        print('primesi',primesi, primesi/integral*100 ,'%')


        zz=zip(xarr,arr)
        zz=filter(lambda x:35<=x[0]<=58,zz)
        xhatch,yhatch=zip(*zz)  #,step='post'
        xhatch=[35]+list(xhatch)+[58]
        yhatch=[0]+list(yhatch)+[0]
        plot.axis.fill(xhatch,yhatch,label='Single particle beam', fill=False, hatch="//")
        plot.axis.legend(loc='lower right')
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
    name='CumulativeOscillogramT0Fixed_ch_24'
    with PlotFile(name,filetype='png') as plot:
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_title('Cumulative oscillogram DAQ 24 (BTF Calo)')
        ranges={
                'Ped\nreg':(30,100),
                'Noise\nregion'   :(200,370),
                'Signal\nregion'  :(420,580),
                }
        for lab,ran in ranges.items():
            plot.axis.axvline(ran[0])
            plot.axis.axvline(ran[1])
            plot.axis.text((ran[0]+ran[1])/2,0.01,lab,horizontalalignment='center',verticalalignment='center')

def osc_cum5T0(inroot):
    name='CumulativeOscillogramT0Fixed_ch_5'
    with PlotFile(name,filetype='png') as plot:
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_title('Cumulative oscillogram DAQ 5 (H9500 D4)')
        ranges={
                'Ped\nreg':(30,100),
                'Noise\nregion'   :(120,270),
                'Signal\nregion'  :(320,470),
                }
        for lab,ran in ranges.items():
            plot.axis.axvline(ran[0])
            plot.axis.axvline(ran[1])
            plot.axis.text((ran[0]+ran[1])/2,0.017,lab,horizontalalignment='center',verticalalignment='center')

def osc_cum22T0(inroot):
    name='CumulativeOscillogramT0Fixed_ch_22'
    with PlotFile(name,filetype='png') as plot:
        plot.axis.set_title('Cumulative oscillogram DAQ 22 (R6427 D4)')
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_ylim(bottom=-.1)
        ranges={
                'Ped\nreg':(30,100),
                'Noise\nregion'   :(200,350),
                'Signal\nregion'  :(400,550),
                }
        for lab,ran in ranges.items():
            plot.axis.axvline(ran[0])
            plot.axis.axvline(ran[1])
            plot.axis.text((ran[0]+ran[1])/2,0.016,lab,horizontalalignment='center',verticalalignment='center')

def osc_cumCalo(inroot):
    name='CumulativeOscillogram_ch_24'
    with PlotFile(name,filetype='png') as plot:
        plot.axis.set_title('Cumulative oscillogram DAQ 24 (BTF Calo); raw data')
        osc_cum(name,inroot,plot.axis)
        plot.axis.set_ylabel('Amplitude[ADU]')
        plot.axis.set_xlabel('Time[samples]')
        ticks=numpy.linspace(0,1000,11)
        plot.axis.set_xticks(ticks)
        plot.axis.set_xticklabels((ticks).astype(int))



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
    ax.set_xlim(1,15)
    ax.set_ylim(.0001,.1)
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

def effinef_abs(ch_dic,inroot,ax):
    colors=[ "#88CCEE", "#CC6677", "#DDCC77", "#117733", "#332288", "#AA4499", "#44AA99", "#999933", "#882255", "#661100", "#6699CC", "#888888" ]

    for color_i,chan_i in enumerate(ch_dic):
        eff,noi=f'PhElectrAbsEff_ch_{chan_i}', f'PhElectrAbsNoise_ch_{chan_i}'
        #eff,noi=f'PhElectrEff_ch_{chan_i}', f'PhElectrNoise_ch_{chan_i}'
        eff_hist=inroot.FindObjectAny(eff)
        noi_hist=inroot.FindObjectAny(noi)
        eff_x,eff_arr=hist2arr(eff_hist)
        noi_x,noi_arr=hist2arr(noi_hist)
        eff_cum=numpy.cumsum(eff_arr)
        noi_cum=numpy.cumsum(noi_arr)
        eff_cum=eff_cum/eff_cum.max()
        noi_cum=noi_cum/noi_cum.max()

        ax.plot(eff_x,eff_cum  ,linestyle='-' ,label=ch_dic[chan_i]+' Ineff',color=colors[color_i])
        ax.plot(noi_x,1-noi_cum,linestyle='--',label=ch_dic[chan_i]+' Noise',color=colors[color_i])

        crosx,crosy=lines_crossing_poing(eff_x,eff_cum,noi_x,1-noi_cum)
        ax.plot([crosx],[crosy],'o',color=colors[color_i])

        effinef_plt_config(ax)
        #ax.set_xlim(2,10)

def effinef_abs_norm_cmp(ch_dic,inroot,ax):
    colors=[ "#88CCEE", "#CC6677", "#DDCC77", "#117733", "#332288", "#AA4499", "#44AA99", "#999933", "#882255", "#661100", "#6699CC", "#888888" ]

    for color_i,((chan_i,abs_i),chan_lab) in enumerate(ch_dic.items()):
        eff,noi=f'PhElectr{abs_i}Eff_ch_{chan_i}', f'PhElectr{abs_i}Noise_ch_{chan_i}'
        eff_hist=inroot.FindObjectAny(eff)
        noi_hist=inroot.FindObjectAny(noi)
        eff_x,eff_arr=hist2arr(eff_hist)
        noi_x,noi_arr=hist2arr(noi_hist)
        eff_cum=numpy.cumsum(eff_arr)
        noi_cum=numpy.cumsum(noi_arr)
        eff_cum=eff_cum/eff_cum.max()
        noi_cum=noi_cum/noi_cum.max()

        ax.plot(eff_x,eff_cum  ,linestyle='-' ,label=chan_lab+' Ineff',color=colors[color_i])
        ax.plot(noi_x,1-noi_cum,linestyle='--',label=chan_lab+' Noise',color=colors[color_i])

        crosx,crosy=lines_crossing_poing(eff_x,eff_cum,noi_x,1-noi_cum)
        ax.plot([crosx],[crosy],'o',color=colors[color_i])

        effinef_plt_config(ax)


def effinef(inroot):
    ch_dic={
            'H9500_X_noAl':{
                0 :"D2",
                2 :"D6",
                5 :"D4",
                7 :"D8",
                },
            'H9500_Y_Al':{
                8 :"D7Al",
                10:"D3Al",
                13:"D5Al",
                15:"D1Al",
                },
            'R6427_noAl':{
                19:"D2",
                21:"D6",
                22:"D4",
                23:"D8",
                }
            }
    titles={
            'H9500_X_noAl':'Efficiency plot for H9500 no Al; run 579',
            'H9500_Y_Al':  'Efficiency plot for H9500 with Al; run 579',
            'R6427_noAl':  'Efficiency plot for R6427 no Al; run 579',
            }
    for name,dic in ch_dic.items():
        with PlotFile(name) as plot:
            plot.axis.set_title(titles[name])
            effinef_abs(dic,inroot,plot.axis)
    ch_dic={
            (7,''    ) :"H9500 A",
            (23,''   ) :"R6427 A",
            (7,'Abs' ) :"H9500 |A|",
            (23,'Abs') :"R6427 |A|",
            }
    with PlotFile('Abs_norm_cmp') as plot:
        effinef_abs_norm_cmp(ch_dic,inroot,plot.axis)
        plot.axis.set_title('Charge vs charge by absolute value for D8; run 579')


def timediff(inroot):
    from scipy.optimize import curve_fit
    def gaus(x,*p):
        return p[ 0]/numpy.sqrt(2*numpy.pi)/p[2]*numpy.exp(-(x-p[ 1])**2/2/p[ 2]**2)
    diffs={5:[0,2,7],10:[8,15],22:[19,21,23]}
    xtics=[0,  2,3,     5,  8,     10,   12,13]

    xticklabels=[
            'D2(00)', 'D4(05)', 'D6(02)', 'D8(07)', '',
            'D1(15)', 'D3(10)', 'D5(12)', 'D7(08)', '',
            'D2(19)', 'D4(22)', 'D6(21)', 'D8(23)']
    thres=25
    methods=[
            "MeanTime",
            "MeanTime2",
            "MeanTimeAbs",
            "2080LeadTrailCros",
            "2080LeadZeroCros",
            "2080Lead50",
            "HalfMaxValue",
            "MaxValue",
            ]
    timeres={}
    for m in methods:
        timeres[m]={'x':[],'y':[],'yerr':[]}

    for met in methods:
        for base_ch in diffs:
            for dif_ch in diffs[base_ch]:
                histname=f'TimeDiff{met}_{min(base_ch,dif_ch)}_{max(base_ch,dif_ch)}'
                hist=inroot.FindObjectAny(histname)
                x,y,dat=hist2arr(hist)

                dat=dat[int(numpy.where(y>thres)[0][0]):]
                y=y[int(numpy.where(y>thres)[0][0]):]
                dat=dat.sum(axis=0)
                popt,covt=curve_fit(gaus,x,dat,p0=[dat.max(),0,2])
                w=popt[2]/numpy.sqrt(2)
                w_err=numpy.sqrt(covt[2][2])/numpy.sqrt(2)
                timeres[met]['x'].append(dif_ch)
                timeres[met]['y'].append(w)
                timeres[met]['yerr'].append(w_err)

    markers='pP*Xdv^<>o'
    with PlotFile('time_resolution_allmethods') as plot:
        for i,met in enumerate(methods):
            plot.axis.errorbar(xtics,timeres[met]['y'],yerr=timeres[met]['yerr'],label=met,fmt=markers[i],color=safecolors[i])
        plot.axis.set_xticks(range(len(xticklabels)))
        plot.axis.set_xticklabels(xticklabels,rotation='vertical')
        plot.axis.text(1.5 ,2.6,'H9500 noAL',color='darkblue',horizontalalignment='center',verticalalignment='center')
        plot.axis.text(6.5 ,2.6,'H9500 AL'  ,color='darkblue',horizontalalignment='center',verticalalignment='center')
        plot.axis.text(11.5,2.6,'R6427 noAL',color='darkblue',horizontalalignment='center',verticalalignment='center')

        plot.axis.text(1, 1.7,'Referent channel' ,color='darkblue',horizontalalignment='center',verticalalignment='center',rotation='vertical')
        plot.axis.text(6, 1.7,'Referent channel' ,color='darkblue',horizontalalignment='center',verticalalignment='center',rotation='vertical')
        plot.axis.text(7, 1.7,'No data',color='darkred',horizontalalignment='center',verticalalignment='center',rotation='vertical')
        plot.axis.text(11,1.7,'Referent channel',color='darkblue',horizontalalignment='center',verticalalignment='center',rotation='vertical')
        plot.axis.axvline(4)
        plot.axis.axvline(9)
        plot.axis.set_title('Time resolution')
        plot.axis.set_ylabel(r'$\sigma\left(\frac{t-t_{ref}}{\sqrt {2}}\right)$ [ns]')

        plot.axis.set_ylim(top=3.3)
        plot.axis.legend(ncol=3,loc='upper center')
        plot.figure.tight_layout()

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
                #ax.plot(x,-arr[event],label=f'No FFT')
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


    files = [
            #'579-FFT100.root',
            #'579-FFT160.root',
            #'579-FFT240.root',
            #'579-FFT300.root',
            #'579-FFT400.root',
            '579-FFT450.root',
            #'579-FFT200.root',
            '579-FFT375.root',
            '579-FFT50.root',
            #'579-FFT60.root',
            #'579-FFT90.root',
            ]
    indata={}
    for f in files:
        m=re.match(r'.*FFT([0-9]+)\.root',f)
        ncancel=int(m[1])
        indata[ncancel]={'fn':f,'mhz':n2freq(ncancel)}
    with PlotFile('fft-lowpass-signals') as plot:
        plot_signals(indata,plot.axis)
        plot.axis.legend(ncol=3)
        plot.figure.tight_layout()


    files=glob.glob('579-FFT*.root')
    indata={}
    for f in files:
        m=re.match(r'.*FFT([0-9]+)\.root',f)
        ncancel=int(m[1])
        indata[ncancel]={'fn':f,'mhz':n2freq(ncancel)}
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


def timediff_fit_example(inroot):
    from scipy.optimize import curve_fit
    def gaus(x,*p):
        return p[ 0]/numpy.sqrt(2*numpy.pi)/p[2]*numpy.exp(-(x-p[ 1])**2/2/p[ 2]**2)
    thres=25
    histname='TimeDiffHalfMaxValue_2_5'
    hist=inroot.FindObjectAny(histname)
    x,y,dat=hist2arr(hist)

    dat=dat[int(numpy.where(y>thres)[0][0]):]
    y=y[int(numpy.where(y>thres)[0][0]):]
    dat=dat.sum(axis=0)
    popt,covt=curve_fit(gaus,x,dat,p0=[dat.max(),0,2])
    w=popt[2]/numpy.sqrt(2)
    w_err=numpy.sqrt(covt[2][2])/numpy.sqrt(2)
    with PlotFile('timediff-distribution-example') as plot:
        plot.axis.set_title('TimeDiffHalfMax D6(ch.02) - D4(ch.05)')
        plot.axis.set_xlabel('Time difference [ns]')
        #plot.axis.bar(x,dat,width=.5,linewidth=5)
        plot.axis.plot(x,dat,drawstyle='steps-mid',label='data')
        plot.axis.plot(x, gaus(x, *popt),label='\n'.join((
                r'$\frac{ A }{\sqrt{ 2*\pi }}*e^{-(\frac{x-x_0}{\sqrt{2}*\sigma})^2}$',
                r'$A=%5.3f\pm%5.3f$'%(popt[0],numpy.sqrt(covt[0][0])),
                r'$x_0=%5.3f\pm%5.3f$'%(popt[1],numpy.sqrt(covt[1][1])),
                r'$\sigma=%5.3f\pm%5.3f$'%(popt[2],numpy.sqrt(covt[2][2])),
                ))
            )
        plot.axis.set_xlim(-10,10)
        plot.axis.legend()

def main():
    rootfile=root.TFile('579-240k-osccum-adu.root')
    ###rootfile=root.TFile('579-240k.root')
    ###plot_signals_from_study(rootfile)
    #osc_cumCaloT0(rootfile)
    #osc_cumCalo(rootfile)
    #osc_cum5T0(rootfile)
    #osc_cum22T0(rootfile)

    #osc_trigNoT0(rootfile)
    #osc_trigT0(rootfile)

    #chargedistr_ch24(rootfile)
    #effinef(rootfile)
    #timediff(rootfile)
    #pedestal_distr(rootfile)
    ###charge_distr(rootfile)
    #D4_noise_eff_example(rootfile)
    #timediff_fit_example(rootfile)




    FFT()




if __name__ == '__main__':
    main()
