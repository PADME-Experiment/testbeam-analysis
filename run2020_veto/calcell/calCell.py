#!/usr/bin/env python

import argparse
import ROOT as root
import matplotlib.pyplot as plt
import numpy as np
import json



def caljson():
    filename = 'test.root'
    ifile = root.TFile(filename)
    res = {}
#for board in [10, 11, 12, 13, 24, 25, 26]:
    for board in [25]:
        chanlist = []
        for channel in range(32):
            histname = f'b{board}_PedestalCell_ch{channel}'
            h = ifile.FindObjectAny(histname)
            celllist =[]
            #h.Draw()
            #input()
            for cell in range(1024):
                k = h.ProjectionY("", cell+1, cell+1)
                #k.Draw()
                #input()
                #celllist.append(k.GetMean())
                celllist.append(k.GetBinLowEdge(k.GetMaximumBin()))
            celllist = np.array(celllist)
            celllist -= celllist.mean()
            celllist = celllist.round().astype(int)
            chanlist.append(celllist.tolist())
        res[board] = chanlist
    json.dump(res, open("aa.json", 'w'), indent=2)





def fitdata():
    try:
        a = json.load(open('tmp.dat', 'r'))
        nofix_res=a['nofix_res']
        fixed_res=a['fixed_res']
        board_it =a['board_it']
    except Exception as e:
        print(e)

        filename = 'test11.root'
        ifile = root.TFile(filename)
        ofile = root.TFile('calcell'+'_'+filename, "recreate")
        nofix_res = []
        fixed_res = []
        for board_it, board in enumerate(range(28)):
        #for board_it, board in enumerate([3, 28]):
            ofile.cd()
            ofile.mkdir(f"b{board}", "", True).cd()
            for channel in range(32):
                try:
                    nofix_name = f'b{board}_PedestalNoCellPedCor_ch{channel}'
                    fixed_name = f'b{board}_Pedestal_ch{channel}'
                    nofix = ifile.FindObjectAny(nofix_name)
                    fixed = ifile.FindObjectAny(fixed_name)
                    nofix_1d = nofix.ProjectionY()
                    fixed_1d = fixed.ProjectionY()

                    nofix_maxx = nofix_1d.GetXaxis().GetBinCenter(nofix_1d.GetMaximumBin())
                    fixed_maxx = fixed_1d.GetXaxis().GetBinCenter(fixed_1d.GetMaximumBin())

                    nofix_fun = root.TF1("nofix_fun", "gaus", nofix_maxx-50,nofix_maxx+50)
                    fixed_fun = root.TF1("fixed_fun", "gaus", fixed_maxx-50,fixed_maxx+50)

                    nofix_fun.SetParameters(nofix_1d.GetMaximum(), nofix_maxx, 4)
                    fixed_fun.SetParameters(fixed_1d.GetMaximum(), fixed_maxx, 4)

                    nofix_fun.SetParLimits(1, nofix_maxx-50,nofix_maxx+50);
                    fixed_fun.SetParLimits(1, fixed_maxx-50,fixed_maxx+50);

                    nofix_fun.SetParLimits(2, 1e-3, 10);
                    fixed_fun.SetParLimits(2, 1e-3, 10);

                    nofix_fitres = nofix_1d.Fit(nofix_fun, "WQRSB","")
                    fixed_fitres = fixed_1d.Fit(fixed_fun, "WQRSB","")

                    #nofix_1d.Draw()
                    #input()
                    #fixed_1d.Draw()
                    #input()

                    nofix_res.append(nofix_fitres.Get().Parameter(2))
                    fixed_res.append(fixed_fitres.Get().Parameter(2))
                except Exception as e:
                    nofix_res.append(float("nan"))
                    fixed_res.append(float("nan"))
                    print(e)

            #plt.axvline(board_it*32)
        ofile.Write()
        ofile.Close()
        ifile.Close()

        print(board_it)

        #end exeption

    json.dump(dict(board_it=board_it, nofix_res=nofix_res, fixed_res=fixed_res), open('tmp.dat', 'w'))


    nofix_res = np.array(nofix_res)
    fixed_res = np.array(fixed_res)
    fig, ax = plt.subplots(ncols = 2, figsize=(8.5,5), gridspec_kw={'width_ratios': [3, 1]})


    #plt.plot(nofix_res/fixed_res)
    ax[0].plot(nofix_res ) #, label="native"  )
    ax[0].plot(fixed_res ) #, label="improved")
    #ax02 = ax[0].twinx()
    #ax02.plot(nofix_res/fixed_res, 'g')

    #ax[0].set_title("V1742 cell calibration")
    ax[0].set_xlabel("ADC boards, 32 channels each")
    ax[0].set_ylabel("$\sigma(Noise)$ [ADU]")


    ax[0].set_xticks([i*32 for i in range(board_it+2) ])
    ax[0].set_xticklabels([f'' for i in range(board_it+2) ])

    ax[0].set_xticks([b*32+16 for b in range(board_it+1)], minor=True)
    ax[0].set_xticklabels([f"b {b:02d}" for b in range(board_it+1)], minor=True, rotation='vertical')
    ax[0].grid(True, which="major", axis="both")


    ax[1].hist(nofix_res, bins=50, range=(.9, 6), histtype="step", label="native"  )
    ax[1].hist(fixed_res, bins=50, range=(.9, 6), histtype="step", label="improved")
    ax[1].hist(nofix_res/fixed_res, bins=50, range=(.9, 6), histtype="step" , label=r"$\frac{\sigma_{native}}{\sigma_{improved}}$")
    fig.suptitle("V1742 cell calibration"+' '*49)
    ax[1].set_xlabel("\n$\sigma(Noise)$ [ADU]")
    ax[1].set_ylabel(" ")
    ax[1].set_yscale('log')
    ax[1].grid()
    ax[1].grid(True, 'minor', 'y', linestyle=':')

    fig.tight_layout()
    fig.subplots_adjust(top=.9)
    plt.figlegend(bbox_to_anchor=(0.75,1), ncol=5, loc='upper center')
    fig.savefig("calCell.pdf")
    plt.close(fig)




fitdata()
