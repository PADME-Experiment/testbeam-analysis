#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom3.h"
#include "TApplication.h"
#include "TProfile.h"
#include "TMath.h"
#include "TSpectrum.h"
#include "TNamed.h"
#include "TCanvas.h"
#include "TVirtualFitter.h"

#include "TRawEvent.hh"
#include "Histos.hh"

Double_t Xcry[TADCBOARD_NCHANNELS];
Double_t Ycry[TADCBOARD_NCHANNELS];
Double_t PedCh[TADCBOARD_NCHANNELS];
Double_t Cij[TADCBOARD_NCHANNELS];

const Int_t    NAvg  = 1000;
const Int_t FitCharge = 1;
Double_t min_peak_V = 20.; //minimum peak height allowed. 

struct Eve{
  Int_t NTNevent;
  Double_t NTQCh[32];
  Double_t NTQtot;
  Double_t NTPedCh[32];
  Double_t NTZSupp[32];
  Double_t NTZSupp1[32];
  Double_t NTZSupp2[32];
  Double_t NTCh[32];
};

void FillHisto(std::string name,std::string outname, int nevents){
  Double_t PedChA[32];
  PedChA[0] = 3812.9;
  PedChA[1] = 3779.4;
  PedChA[2] = 3788.7;
  PedChA[3] = 3782.7;
  PedChA[4] = 3802.4;
  PedChA[5] = 3789.3;
  PedChA[6] = 3750.8;
  PedChA[7] = 3771.0;
  PedChA[8] = 3792.3;
  PedChA[9] = 3763.2;
  PedChA[10]= 3804.9;
  PedChA[11]= 3765.5;
  PedChA[12]= 3758.5;
  PedChA[13]= 3795.3;
  PedChA[14]= 3760.8;
  PedChA[15]= 3763.3;
  PedChA[16]= 3819.7;
  PedChA[17]= 3807.9;
  PedChA[18]= 3818.3;
  PedChA[19]= 3807.5;
  PedChA[20]= 3790.5;
  PedChA[21]= 3840.6;
  PedChA[22]= 3822.1;
  PedChA[23]= 3780.9;
  PedChA[24]= 3834.1;
  PedChA[25]= 3810.3;
  PedChA[26]= 3868.1;
  PedChA[27]= 3838.1;
  PedChA[28]= 3803.4;
  PedChA[29]= 3796.0;
  PedChA[30]= 3835.2;
  PedChA[31]= 3824.0;

  Eve Event; 
  printf("GetInstance %s\n",outname.c_str());
  Histo* his = Histo::GetInstance(outname);
  printf("new TFile\n");
  TFile *fileNTU  = new TFile("ntu.root", "RECREATE");
  printf("new TTree\n");
  TTree *tree     = new TTree("NTU","Event3");
  tree->Branch("Nevent",&(Event.NTNevent),"Nevent/I");
  tree->Branch("Qtot",&(Event.NTQtot),"Qtot/D");
  tree->Branch("Ch",Event.NTCh,"Ch[32]/D");
  tree->Branch("QCh",Event.NTQCh,"QCh[32]/D");
  tree->Branch("PedCh",Event.NTPedCh,"PedCh[32]/D");
  printf("new TFile\n");

  TFile* fhisto = new TFile("histo.root","RECREATE");
  TFile* fRawEv = new TFile(name.c_str());
  printf("Get\n");
  TTree* tRawEv = (TTree*)fRawEv->Get("RawEvents");
  printf("GetBranch\n");
  TBranch* bRawEv = tRawEv->GetBranch("RawEvent");
  printf("TRawEvent\n");
  TRawEvent* rawEv = new TRawEvent();
  //  TRandom 
  printf("SetAddress\n");
  bRawEv->SetAddress(&rawEv);
  Int_t NMaxSamp = 1024;
  Double_t SampInd[1024];
  for(int ll=0;ll<NMaxSamp;ll++) SampInd[ll]=ll*1.;
  UInt_t nevt = tRawEv->GetEntries();
  printf("TTree RawEvents contains %d events\n",nevt);
  // Set number of events to read
  UInt_t ntoread = nevt;
  Double_t Sam[1024];
  Double_t SamRec[1024];
  Double_t AbsSamRec[1024];
  if (nevents && nevents<nevt) ntoread = nevents;
  printf("Reading the first %d events\n",ntoread);

  // Define counters for bad rms events
  Int_t NTotEvents = 0;
  Int_t NGoodEvents = 0;
  const Int_t NHistos = 5000;

  //  TH1D* hNIDiff= new TH1D("hNIDif","hNIDis",32,-0.5,31.5);
  TH1D** hSCh = new TH1D*[5000];
  TH1D* H1 = new TH1D("h1","h1",1000,0.,1000.);
  //  TH1D* H2 = new TH1D("h2","h2",1024,0.,1024.);
  TH1D* H3 = new TH1D("h3","h3",100,0.,1000.);
  for(int kk=0;kk<NHistos;kk++) {
    hSCh[kk] = new TH1D(Form("hSCh%d",kk),Form("hSCh%d",kk),1023,-0.5,1022.5);
  }


  // TH1D *hQCh = new TH1D("hQCh","hQCh",200,0.,100.);
  std::vector <TH1D*> vQCh;
  for(int ii=0;ii<25;ii++){
    TH1D* h = new TH1D(Form("hQCh%d",ii),Form("hQCh%d",ii),200,0.,100.);
    vQCh.push_back(h);
  }

  Double_t mean1000[32]= {0.};
  Double_t rms1000[32] = {0.};
  Double_t QCh[32]     = {0.};
  Double_t w = 1900; //1400
  Double_t h = 2000; //800
  TCanvas *c1 = new TCanvas("c1","Target Analog",0,0,w,h);
  c1->Divide(4,8);
  Double_t w2 = 1900; //1400
  Double_t h2 = 2000; //800
  TCanvas *c2 = new TCanvas("c2","analog",2000,0,w2,h2);
  c2->Divide(4,8);

  //*************************
  //START MAIN LOOP ON EVENTS
  //*************************
  Int_t kk = 0;
  //  Double_t NIDif[33]={0};
  for(Int_t iev=0;iev<ntoread;iev++){
    Int_t GoodEvent = 0;
    // Read event
    Event.NTNevent=iev;
    if(iev%1000==0) printf("Reading event %d\n",iev);
    bRawEv->GetEntry(iev);
    // Show event header
    UChar_t nBoards = rawEv->GetNADCBoards();
    // Loop over boards
    for(UChar_t b=0;b<nBoards;b++){
      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      UChar_t nTrg    = adcB->GetNADCTriggers();
      UChar_t nChn    = adcB->GetNADCChannels();
      UChar_t BDID    = adcB->GetBoardId();
      if(
          //BDID!=10&&  //pveto
          //BDID!=11&&  //pveto
          //BDID!=12&&  //pveto
          //BDID!=24&&  //eveto
          //BDID!=25&&  //eveto
          BDID!=26    //eveto
        ) continue;
      if(iev==1) printf("Ntrg Nchn NBoards %d %d %d \n",nTrg,nChn,nBoards);
      Int_t PedIsGood=1;
      for(UChar_t c=0;c<nChn;c++){       // Loop over channels
        TADCChannel* chn = adcB->ADCChannel(c);
        UChar_t ch = chn->GetChannelNumber();
        //	printf("\t\tChan %u Chn# %u\n",c,chn->GetChannelNumber());
        for(UShort_t s=0;s<NAvg;s++){
          Sam[s] = (Double_t) chn->GetSample(s);
        }
        rms1000[ch]  = TMath::RMS(NAvg,&Sam[0]);
        //update pedestal otherwise keep the last
        if(rms1000[ch]<5.)  mean1000[ch] = TMath::Mean(NAvg,&Sam[0]); 
        if(rms1000[ch]>5.)  {
          PedIsGood=-1;
          //	  std::cout<<(Int_t)ch<<" rms Ped "<<rms1000[ch]<<std::endl;
        }	

        for(UShort_t s=0;s<NAvg;s++){
          Sam[s]    = (Double_t) chn->GetSample(s);          
          SamRec[s] = (Double_t) (chn->GetSample(s)-PedChA[ch])/4096*1.; //in V
          AbsSamRec[s] = (Double_t) (-1.*chn->GetSample(s)+PedChA[ch])/4096*1000.; //Abs V in mV
        }

        Event.NTPedCh[ch] = mean1000[ch];

        if(rms1000[ch]<4.5){ 
          //	  ZSupp[ch]=1.;
          Event.NTCh[ch]=0;
        }else{
          //	  ZSupp[ch]=0.;
          Event.NTCh[ch]=1;
        }	
        fhisto->cd();
        char hisname[50];
        char hisnameQX[50];
        char hisnameQY[50];

        sprintf(hisname,Form("hSCh%d",kk));
        //	TH1D* H1 = new TH1D("h1","h1",1024,0.,1024.);
        H1->SetContent(AbsSamRec);
        sprintf(hisname,Form("hAn%d",ch));
        his->Set1D(hisname,AbsSamRec);

        Int_t npeaks=20;
        Int_t PlotPos =	(Int_t)ch;
        Double_t VMax = H1->GetMaximum();
        Double_t Charge = 0;
        Int_t bin=0;
        //	std::cout<<"Vmax "<<VMax<<std::endl;
        //	if(rms1000[ch]>6. && VMax>min_peak_V){   //zero suppression cut
        if(rms1000[ch]>3.){   //zero suppression cut
          for (Int_t ii=0;ii<300;ii++) {
            Charge += H1->GetBinContent(ii)*1e-3/50*1E-9/1E-12; //1E-9 da cambiare con la frequenza di integrazione.
          }
          QCh[ch]=Charge;
          if(ch<16){
            sprintf(hisnameQY,Form("hYQCh%d",ch));
            his->Fill1D(hisnameQY,QCh[ch]);
          }else{
            sprintf(hisnameQX,Form("hXQCh%d",ch));
            his->Fill1D(hisnameQX,QCh[ch]);
          }
        }  //end of good event 
        Event.NTQCh[ch] = QCh[ch];
        // Qui fai la parte di visualizzaione online 
        //	std::cout<<"iev "<<iev<<" "<< ch<< (Int_t)ch<<" plot pos "<< PlotPos <<std::endl;

        if(iev%100==0 && iev!=0){  // && PlotPos==31){
          c1->cd(ch+1); 
          his->Draw1D(hisname);
          //	  H1->GetYaxis()->SetRangeUser(0.,VMax);
          if(ch==31){ 
            c1->Update();
            //	    getchar();
          }
        }

        if(iev%100==0 && iev!=0){ 
          c2->cd(ch+1);
          if(ch<16){
            sprintf(hisnameQY,Form("hYQCh%d",ch));
            //	    his->Draw1DR(hisnameQY,500.);
            his->Draw1D(hisnameQY);
          }else{
            sprintf(hisnameQX,Form("hXQCh%d",ch));
            //	    his->Draw1DR(hisnameQX,500.);
            his->Draw1D(hisnameQX);
          }
          if(ch==31){ 
            c2->Update();
            //	    getchar();
          }
        }
        H1->Reset();
        kk++;
        }//end of loop on channels 
        // c1->Update();
        //      Event.NTQtot= Qtot[b];      
      }//end of loop on boards
      tree->Fill();    
      }//end of loop on events

      //  his->Dump1DHisto("H1","TARGET_Qtot");
      //  his->Dump1DHisto("H1","TARGET_QXCh%d");
      //  his->Dump1DHisto("H1","TARGET_QYCh%d");

      //  his->Dump1DHisto("H1","TARGET_ProfX%d");
      //  his->Dump1DHisto("H1","TARGET_ProfY%d");

      // Count events with at least 1 channel with bad RMS
      NTotEvents++;
      std::cout<<"Ntot events "<<NTotEvents<<std::endl;
      //  getchar();
      // kiLL ALL graphs    
      // Clear event
      //  rawEv->Clear("C");

      fhisto->cd();
      fhisto->Close();  
      fileNTU->cd();
      tree->Print();
      tree->Write();
      fileNTU->Close();
      //  delete rawEv;
      //  delete bRawEv;
      //  delete tRawEv;
      //  fRawEv->Close();
      //  delete fRawEv;
    }


