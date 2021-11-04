#!/usr/bin/env python

import argparse
import ROOT as root
import matplotlib.pyplot as plt
import numpy as np
import json
from collections import defaultdict
from matplotlib.collections import LineCollection
from ggf import pyplot as ggfplt
import matplotlib.colors as mpcolors



def fitdata(filename, nocal=False):
    fname_nodir = filename.split('/')[-1]
    json_tmp = f'anl-{fname_nodir}-tmp.json'
    root_out = f'anl-{fname_nodir}-fit.root'
    try:
        hist_res = json.load(open(json_tmp, 'r'))
    except Exception as e:
        print(e)
        hist_res = defaultdict(list)

        try:
            ifile = root.TFile(filename)
        except:
            return []
        ofile = root.TFile(root_out, "recreate")
        nofix_res = []
        fixed_res = []
        for board_it, board in enumerate(range(28)):
        #for board_it, board in enumerate([3, 28]):
            ofile.cd()
            ofile.mkdir(f"b{board}", "", True).cd()
            for channel in range(32):
                try:
                    histname = f'b{board}_Pedestal_cal_time_ch{channel}'
                    hist = ifile.FindObjectAny(histname)
                    hist_1d = hist.ProjectionY()
                    hist_maxx = hist_1d.GetXaxis().GetBinCenter(hist_1d.GetMaximumBin())
                    hist_fun = root.TF1("hist_fun", "gaus", hist_maxx-50,hist_maxx+50)
                    hist_fun.SetParameters(hist_1d.GetMaximum(), hist_maxx, 4)
                    hist_fun.SetParLimits(1, hist_maxx-50, hist_maxx+50);
                    hist_fun.SetParLimits(2, 1e-3, 10);
                    hist_fitres = hist_1d.Fit(hist_fun, "WQRSB","")

                    hist_res[f'{board}'].append(hist_fitres.Get().Parameter(2))
                except Exception as e:
                    #hist_res[f'{board}'].append(float("nan"))
                    print(e)
        ofile.Write()
        ofile.Close()
        ifile.Close()

        print(board_it)

    if hist_res:
        json.dump(hist_res, open(json_tmp, 'w'))
    #hist_res['27'][16:24] = [float('nan')]*(24-16)
    hist_res['27'][16:24] = []
    return [i for k in hist_res.values() for i in k]



def drawfig():
    dat = {
            'cosmic':{
                'Firmware': fitdata('../cosmicrun-NOCAL.root'),
                'Mode':      fitdata('../cosmicrun-CALcosmic-mpv.root'),
                #'Mean':     fitdata('../cosmicrun-CALcosmic-mean.root'),
                'Poly1':    fitdata('../cosmicrun-CALcosmic-poly1.root'),
                'Poly2':    fitdata('../cosmicrun-CALcosmic-poly2.root'),
                'Poly3':    fitdata('../cosmicrun-CALcosmic-poly3.root'),
                'Poly4':    fitdata('../cosmicrun-CALcosmic-poly4.root'),
                'Poly5':    fitdata('../cosmicrun-CALcosmic-poly5.root'),
                },
            'daqcosmic':{
                'Firmware': fitdata('../DAQrun-NOCAL.root'),
                'Mode':      fitdata('../DAQrun-CALcosmic-mpv.root'),
                #'Mean':     fitdata('../DAQrun-CALcosmic-mean.root'),
                'Poly1':    fitdata('../DAQrun-CALcosmic-poly1.root'),
                'Poly2':    fitdata('../DAQrun-CALcosmic-poly2.root'),
                'Poly3':    fitdata('../DAQrun-CALcosmic-poly3.root'),
                'Poly4':    fitdata('../DAQrun-CALcosmic-poly4.root'),
                'Poly5':    fitdata('../DAQrun-CALcosmic-poly5.root'),
                },
            'daqdaq':{
                'Firmware': fitdata('../DAQrun-NOCAL.root'),
                'Mode':      fitdata('../DAQrun-CALdaq-mpv.root'),
                #'Mean':     fitdata('../DAQrun-CALdaq-mean.root'),
                #'Poly1':    fitdata('../DAQrun-CALdaq-poly1.root'),
                #'Poly2':    fitdata('../DAQrun-CALdaq-poly2.root'),
                #'Poly3':    fitdata('../DAQrun-CALdaq-poly3.root'),
                #'Poly4':    fitdata('../DAQrun-CALdaq-poly4.root'),
                #'Poly5':    fitdata('../DAQrun-CALdaq-poly5.root'),
                }
            }
    #for dat in list(dat['daqdaq'].values()):
    #    plt.plot(dat)
    #plt.show()

    fig, ax = plt.subplots(figsize=(6.5,4.0))
    colorset = ggfplt.muted[5:]
    ax.set_prop_cycle(color=colorset)
    hwfm = ax.secondary_yaxis('right', functions=(lambda x:2.355*x/4.096, lambda x:x*4.096/2.355))
    hwfm.set_ylabel('FWHM[mV]')
    #ax.grid(axis='y', color='gray', linestyle=':', linewidth=1)
    ax.set_ylabel('$\sigma$ [ADU]')
    ax.set_xticks(list(range(1, 1+len(list(dat['cosmic'].values())))))
    ax.set_xticklabels(list(dat['cosmic'].keys()))
    viols = {}
    viols['cosmic'   ] = ax.violinplot(list(dat['cosmic'   ].values()), points=1000, widths=.8, showmedians=True, showmeans=False)
    viols['daqcosmic'] = ax.violinplot(list(dat['daqcosmic'].values()), points=1000, widths=.8, showmedians=True, showmeans=False)
    #viols['daqdaq'   ] = ax.violinplot(list(dat['daqdaq'   ].values()), points=1000, widths=.8, showmedians=True, showmeans=False)
    for hatch,kk,color in zip(['//', '\\\\', '--'],viols , colorset):
        viols[kk]['cbars'].set_linewidth(0)
        viols[kk]['cmedians'].set_linestyle(':')
        for viol in viols[kk]['bodies']:
            viol.set_edgecolor(mpcolors.to_rgba(color, 1))
            #viol.set_linewidth(2)
            viol.set_hatch(hatch)
            viol.set_facecolor(mpcolors.to_rgba(color,.1))
    ax.legend([
        LineCollection([], linestyle=':', colors='k'),
        LineCollection([], linestyle='-', colors='k'),
        viols['cosmic'   ]['bodies'][0],
        viols['daqcosmic']['bodies'][0],
        #viols['daqdaq'   ]['bodies'][0],
        ], [
            'Medians',
            'Extrema',
            "Random data Random calibration",
            "Physics data Random calibration",
            #"DAQ run DAQ cal",
            ],loc='best', ncol=2 )

    fig.tight_layout()
    fig.savefig("method-comparison.png")
    plt.show()
    exit()

    hist_res = np.array(hist_res)
    fig, ax = plt.subplots(ncols = 2, figsize=(5.5,3.5), gridspec_kw={'width_ratios': [3, 1]})


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




drawfig()
