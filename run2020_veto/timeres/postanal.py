#!/usr/bin/env python

import argparse
import ROOT as root
import matplotlib.pyplot as plt
import numpy as np



#parser = argparse.ArgumentParser()
#parser.add_argument('-i',"--input", type=str)
#parser.add_argument('-o',"--output", type=str)
#args = parser.parse_args()

for filename in [ #f'test-{i:02d}.root' for i in range(60)
        "xxx.root"
        #"test0.root",
        #"test1.root",
        #"test2.root",
        #"test3.root",
        #"test4.root",
        #"test5.root",
        #"test6.root",
        #"test7.root",
        #"test8.root",
        #"test9.root",
        #"testmix.root",
        ]:
    if '23' in filename: continue
    if '30' in filename: continue
    print(filename)
    ifile = root.TFile(filename)
    ofile = root.TFile('postanal'+'_'+filename, "recreate")

    #plt.xkcd()

    fig, ax = plt.subplots(ncols = 1, figsize=(9,5))

    for detector in ["PVeto"]:#, "EVeto"]:
        for method in [

                #"TimeDiff2080LeadTrailCros",
                #"TimeDiff2080LeadZeroCros",
                #"TimeDiffHalfMaxValue",
                #"TimeDiffMaxValue",

                "TimeDiffMeanTime",
                "TimeDiffMeanTime2",
                #"TimeDiffMeanTimeAbs",
                "TimeDiff2080Lead50",

                #"TimeDiff01MaxValue",
                #"TimeDiff02MaxValue",
                "TimeDiffIntegral",

                #"TimeDiffTSpectrum",
                ]:
            ofile.cd()
            ofile.mkdir(f"{detector}_{method}", "", True).cd()
            mean_L=[]
            mean_Ld=[]
            sig=[]
            sigd=[]
            for channel in range(70):
                try:
                    histname = f'{detector}_{method}_ch{channel+1}_ch{channel}'
                    h = ifile.FindObjectAny(histname)
                    k = h.ProjectionX()
                    if k.GetEntries() < 20: continue
                    max_x = k.GetXaxis().GetBinCenter(k.GetMaximumBin())
                    f1 = root.TF1("f1", "gaus",max_x-10,max_x+10)
                    f1.SetParameters(
                            k.GetMaximum(),
                            max_x, .1)
                    f1.SetParLimits(0, .1*k.GetMaximum(), 10*k.GetMaximum())
                    f1.SetParLimits(1,max_x-5,max_x+5)
                    f1.SetParLimits(2,.001, 5)
                    #fitres = k.Fit(f1,"B M Q R S WW","")
                    fitres = k.Fit(f1,"B M Q R S","")
                    #covar = fitres.GetCovarianceMatrix()
                    mean = fitres.Parameter(1)
                    meand = fitres.ParError(1)
                    sigma = fitres.Parameter(2)
                    sigmad = fitres.ParError(2)
                    mean_L  .append(mean)
                    mean_Ld .append(meand)
                    sig.append(sigma)
                    sigd.append(sigmad)
                    print(histname, f'{mean:8.3}± {meand:8.3} {sigma:8.3}±{sigmad:8.3}')
                except Exception as e:
                    print(histname)
                    print(e)
                    raise e
            print(sig)
            print(sigd)
            sig = np.array(sig) /np.sqrt(2)
            ax.plot(sig, label=(method if method != 'TimeDiffIntegral' else "TimeDIffCumulative")) #,yerr=sigd)
            #ax[1].plot(np.cumsum(mean_L, dtype=float)) #,yerr=sigd)

            #ax[1].plot(mean_L, label=method) #,yerr=sigd)
    ax.grid(True)
    ax.set_xlabel("channel")
    ax.set_ylabel("$\Delta T/\sqrt{2}$ [ns]")
    #ax[1].set_xlabel("channel")
    #ax[1].grid(True)
    #ax[1].set_ylabel("cumulative T[ns]")

    fig.tight_layout()
    fig.subplots_adjust(top=.9)
    plt.figlegend(bbox_to_anchor=(0.5,1), ncol=5, loc='upper center')
#k.Write()
    ofile.Write()
    ofile.Close()
    ifile.Close()


    fig.savefig("all"+"_"+filename+".pdf")
    plt.close(fig)
