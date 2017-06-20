#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom3.h"
#include "TApplication.h"
#include "TMath.h"
#include "TRawEvent.hh"
#include "Histo.hh"
#include "TObjArray.h"
#include "TChain.h"

Double_t Xcry[TADCBOARD_NCHANNELS];
Double_t Ycry[TADCBOARD_NCHANNELS];
Double_t PedCh[TADCBOARD_NCHANNELS];
Double_t Cij[TADCBOARD_NCHANNELS];

const int nSamples = 1024;
const Int_t NAvg=80;
// if Use_mean100=true the mean of the first NAvg samples 
// will be used to evaluate the charge
const Bool_t Use_mean100 = true;
const Double_t QZSCut=5.;
const Int_t IsRandCal=0.;
const Bool_t OnlyCentrals=false;
const Bool_t IsCalibrated=true;
const Double_t IsSaturatedValue = 30.;

struct Eve{
  Int_t NTNevent;
  Int_t RunNumber;
  Int_t NTNCry;
  Double_t NTQCh[25];
  Double_t NTQtot;
  Double_t NTQtotCal;
  Double_t NTPedCh[25];
  Double_t NTMeanCh[25];
  Double_t NTRMSCh[25];
  Double_t NTRMS100Ch[25];
  Double_t Xcluster;
  Double_t Ycluster;
  Bool_t IsPositron;
  Bool_t IsElectron;
  Bool_t IsSaturated;
};

int IsEveGood(Double_t * QCh){
  for(int i=0;i<25;i++){
    if(QCh[i]<-500.) return -1;
  }
  return 1;
}

//void FillHisto(std::string name,std::string outname, int nevents){
void FillHisto(TChain* Chain, std::string outname, Long64_t nevents){
  //Fill Crystals position MAP
  // 3 crystals per row
  //for(Int_t xx=0;xx<25;xx++) Xcry[xx]= 2.-(xx%3)*2.;
  //for(Int_t yy=0;yy<25;yy++) Ycry[yy]=-4.+(yy/3)*2.;
  // 5x5 matrix
  for(Int_t xx=0;xx<25;xx++) Xcry[xx]= 4.-(xx%5)*2.;
  for(Int_t yy=0;yy<25;yy++) Ycry[yy]=-4.+(yy/5)*2.;

  for(Int_t yy=0;yy<25;yy++) std::cout<<"Channel "<<yy<<" XCry "<<Xcry[yy]<<" YCry "<<Ycry[yy]<<std::endl;
// July values
//  PedCh[ 0] = 3770; PedCh[ 1] =3835; PedCh[2]=3792; PedCh[3] = 3793; PedCh[ 4] = 3764;
//  PedCh[ 5] = 3801; PedCh[ 6] =3791; PedCh[7]=3766; PedCh[8] = 3780; PedCh[ 9] = 3770;
//  PedCh[10] = 3810; PedCh[11] =3809; 
// Double values
  PedCh[ 0] = 3769.59; PedCh[ 1] =3834.69; PedCh[2]=3791.53; PedCh[3] = 3792.51; PedCh[ 4] = 3764.45;
  PedCh[ 5] = 3801.51; PedCh[ 6] =3790.81; PedCh[7]=3766.48; PedCh[8] = 3779.93; PedCh[ 9] = 3770.16;
  PedCh[10] = 3809.6; PedCh[11]  =3808.6; 

  
  if(IsRandCal==1){
    TRandom *rand       = new TRandom();
    for(int kk=0;kk<25;kk++){
      Cij[kk] = rand->Gaus(1.,0.1);     
      Cij[12]=1.;
      std::cout<<"Cost "<<kk<<" "<<Cij[kk]<<std::endl;
    }
  } else if(OnlyCentrals){  //Consider only the 9 central crystals
    printf("\n\n === In the total charge histogram ONLY the 9 central crystals are considered === \n\n");
    for(int kk=0;kk<32;kk++) Cij[kk]=0.;
    Cij[6]=1;
    Cij[7]=1;
    Cij[8]=1;
    Cij[11]=1;
    Cij[12]=1;
    Cij[13]=1;
    Cij[16]=1;
    Cij[17]=1;
    Cij[18]=1;
  }
  else if(IsCalibrated){  //Include Cosmic ray calibration constants for the central 9.
    
    for(int kk=0;kk<32;kk++) Cij[kk]=1.;
    /*
    Cij[0] = 1.341;
    Cij[1] = 1.135;
    Cij[2] = 1.274;
    Cij[3] = 1.0031;
    Cij[4] = 1;
    Cij[5] = 1.324;
    Cij[6] = 1.444;
    Cij[7] = 0.911;
    Cij[8] = 0.962;
    Cij[9] = 1.740;
    Cij[10] = 0.650;
    Cij[11] = 0.823;
    */
    Cij[14] = 1.341;
    Cij[16] = 1.135;
    Cij[11] = 1.274;
    Cij[18] = 1.0031;
    Cij[3] = 1;
    Cij[17] = 1.324;
    Cij[8] = 1.444;
    Cij[13] = 0.911;
    Cij[7] = 0.962;
    Cij[12] = 1.740;
    Cij[6] = 0.650;
    Cij[2] = 0.823;


    printf("\n\n === Using crystal by Crystal calibration constants === \n\n");
  }
  else{
    for(Int_t ij=0;ij<32;ij++) Cij[ij]=1.;
  }

  Eve Event; 
  printf("GetInstance\n");
  Histo* his = Histo::GetInstance();
  printf("new TFile\n");
  TFile *fileNTU  = new TFile("ntu.root", "RECREATE");
  printf("new TTree\n");
  TTree *tree = new TTree("NTU","Event3");
  tree->Branch("QCh",Event.NTQCh,"QCh[25]/D");
  tree->Branch("PedCh",Event.NTPedCh,"PedCh[25]/D");
  tree->Branch("RMS100Ch",Event.NTRMS100Ch,"RMS100Ch[25]/D");
  tree->Branch("MeanCh",Event.NTMeanCh,"MeanCh[25]/D");
  tree->Branch("RMSCh",Event.NTRMSCh,"RMSCh[25]/D");
  tree->Branch("Qtot",&(Event.NTQtot),"Qtot/D");
  tree->Branch("QtotCal",&(Event.NTQtotCal),"QtotCal/D");
  tree->Branch("Xcluster",&(Event.Xcluster),"Xcluster/D");
  tree->Branch("Ycluster",&(Event.Ycluster),"Ycluster/D");
  tree->Branch("Run",&(Event.RunNumber),"Run/I");
  tree->Branch("Nevent",&(Event.NTNevent),"Nevent/I");
  tree->Branch("NCry",&(Event.NTNCry),"NCry/I");
  tree->Branch("IsPositron",&Event.IsPositron,"IsPositron/O");
  tree->Branch("IsElectron",&Event.IsElectron,"IsElectron/O");
  tree->Branch("IsSaturated",&(Event.IsSaturated),"ISSaturated/O");
  printf("new TFile\n");

  //TFile* fRawEv = new TFile(name.c_str());//
  printf("Get\n");
  //TTree* tRawEv = (TTree*)fRawEv->Get("RawEvents");//
  printf("GetBranch\n");
  //TBranch* bRawEv = tRawEv->GetBranch("RawEvent");//
  //TBranch* bRawEv = Chain->GetBranch("RawEvent");//
  printf("TRawEvent\n");
  TRawEvent* rawEv = new TRawEvent();
  //  TRandom 
  printf("SetAddress\n");
  //bRawEv->SetAddress(&rawEv);
  Chain->SetBranchAddress("RawEvent",&rawEv);

  //Int_t GoToEnd  = 0;
  Int_t NMaxSamp = 1024;
  Double_t SampInd[1024];
  for(int ll=0;ll<NMaxSamp;ll++) SampInd[ll]=ll*1.;

  // Set number of events to read
  //UInt_t nevt = tRawEv->GetEntries();//
  Long64_t nevt = Chain->GetEntries();//
  Chain->SetEstimate(nevt);
  std::cout<<"TTree RawEvents contains "<<nevt<<" events\n";
  UInt_t ntoread = nevt;
  Double_t Sam[1024];
  Double_t SamRec[1024];
  Double_t TTrig[4];
  if (nevents && nevents<nevt) ntoread = nevents;
  std::cout<<"Reading the first "<<ntoread<<" events\n";

  Double_t mean100[32]={0.};
  Double_t rms100[32]={0.};

  // loop over events
  for(Long64_t iev=0;iev<ntoread;iev++){
    // Read event
    Event.NTNevent=iev;
    if(iev%1000==0) std::cout<<"Reading event "<<iev<<std::endl;
    //bRawEv->GetEntry(iev);
    Chain->GetEntry(iev);

    UChar_t nBoards = rawEv->GetNADCBoards();
    if(iev==0) printf("Number of boards: %d\n",(int)nBoards);

    UInt_t runnumber = rawEv->GetRunNumber();
    Event.RunNumber = (int)runnumber;

    // Loop over boards
    for(UChar_t b=0;b<nBoards;b++){

      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      UChar_t nTrg = adcB->GetNADCTriggers();
      UChar_t nChn = adcB->GetNADCChannels();
      if(iev==0) printf("connected Ntrg %d Nchn %d\n",nTrg,nChn);

      // Loop over triggers
      Int_t     MinInd;
      Double_t SamDiffTr[1024];
      for(UChar_t t=0;t<nTrg;t++){
	MinInd=-1;
	TADCTrigger* trg = adcB->ADCTrigger(t);

	for(Int_t tt=0;tt<trg->GetNSamples();tt++){
	  Sam[tt] = (Double_t) trg->GetSample(tt);

	  if(tt<1000 && tt>10) SamDiffTr[tt]=Sam[tt]-Sam[tt-3];//+mean100[ch];
	  //	  std::cout<<(float)tt<<" sam "<<SamDiffTr[tt]<<" "<<std::endl;
	  if(SamDiffTr[tt]<-50. && MinInd==-1) MinInd=tt;
	  //	  if(tt<MinInd+4) std::cout<<(float)tt<<" " <<Sam[tt]<<" "<<SamDiffTr[tt]<<std::endl;
	}
	Double_t  meantr100 = TMath::Mean(100.,&Sam[0]);
	for(Int_t tt=0;tt<trg->GetNSamples();tt++){
	  SamRec[tt] = (Double_t) (trg->GetSample(tt)-meantr100)/4096*1.; //in
	}

//	Int_t     MinInd  =TMath::LocMin(800,&SamDiffTr[0]);
	Double_t  MinTrig =TMath::MinElement(400,&SamRec[0]);
	//Double_t  TrigLowThr= MinTrig*0.1;
	//Double_t  TriHighThr= MinTrig*0.9;
	Double_t  Trig05    = MinTrig*0.5;
	Double_t  Ind05     = 0;
	// std::cout<<"Trig05 "<<Trig05<<"Min Trig "<<MinTrig<<std::endl;

	for(Int_t tt=0;tt<trg->GetNSamples();tt++){
	  if(SamRec[tt]<Trig05) {
	    Ind05 = tt;
	    break;
	  }
	}
	//	std::cout<<"Ind05 "<<Ind05<<std::endl;
	  
//	Double_t  MaxInd =TMath::LocMax(800,&SamDiffTr[0]); 
//	TTrig[t]=float(MinInd);

	Double_t sumx=0.;  
	Double_t sumxsq=0.;
	Double_t sumy=0.;
	Double_t sumxy=0.;
	Double_t sumw2=0.;
	Double_t denom=0.;
	Double_t * y = Sam;
	Double_t x[10];
	//	Double_t y[10]={0,1};
	Double_t w[10];

	//Int_t npt=2;
	for(int i=Ind05-2;i<=Ind05+2;i++){
	  w[i]=y[i]-Trig05;
	  w[i]=1/sqrt(w[i]*w[i]*w[i]);
	  x[i]=i;
	  //	  std::cout<<" "<<x[i]<<" "<<y[i]<<" "<<w[i]<<std::endl;
	  Double_t w2=w[i]*w[i];	
          sumw2  += 1/w2;
	  sumx   += x[i]/w2;
	  sumxsq += x[i]*x[i]/w2;
	  sumy   += y[i]/w2;
	  sumxy  += x[i]*y[i]/w2; 
	}
	denom = sumw2*sumxsq-sumx*sumx;
	Double_t a0 = (sumy * sumxsq- sumx * sumxy) / denom; //intercept
	Double_t a1 = (sumw2 * sumxy - sumx * sumy) / denom; //slope
	//	std::cout<<" "<<a0<<" "<<a1<<" pos "<<-a0/a1<<std::endl;
	TTrig[t]=-a0/a1;
	//	double TWdt=MaxInd-MinInd;
	//	std::cout<<(float)t<<" TTrig "<<TTrig[t]<<" "<<MinInd<<std::endl;//" wdt "<<TWdt<<std::endl;
	//	if(b==0) his->FillGraph("CaloTrig",t,trg->GetNSamples(),SampInd,Sam);
	if(b==0) his->Fill1D(Form("hTTrig%d",t),TTrig[t]);
      } //end of loop on triggers

      if(b==0) his->Fill1D("hTT0_TT1",TTrig[0]-TTrig[1]);
      if(b==0) his->Fill1D("hTT2_TT3",TTrig[2]-TTrig[3]);
	
      // Loop over channels
      Double_t Qtot[2]={0};
      Double_t QtotCal[2]={0};
      Double_t QtotZS[2]={0};
      Double_t TTot[2]={0};
      Double_t TEv[2]={0};
      Double_t XcryTot = 0.;
      Double_t YcryTot = 0.;
      Double_t EleX = 0.;
      Double_t EleY = 0.;
      Double_t XcryTotZS = 0.;
      Double_t YcryTotZS = 0.;
      Bool_t IsSaturated=false;

      Int_t NCry=0.;
      Int_t NTCry=0.;
      Int_t PedIsGood=1;
      Double_t QCh[32]={0.};
      Double_t TCh[32]={0.};
      Double_t SamDiffCh[1023]={0.};

      for(UChar_t c=0;c<nChn;c++){
	TADCChannel* chn = adcB->ADCChannel(c);
	UChar_t ch = chn->GetChannelNumber();
	//	printf("\t\tChan %u Chn# %u\n",c,chn->GetChannelNumber());
       	for(UShort_t s=0;s<chn->GetNSamples();s++){
	  Sam[s] = (Double_t) chn->GetSample(s);
	}

	if(ch >= 25){

	  // ch 29: positron NIM
	  if(ch == 29){
	    if(TMath::Mean(50,&Sam[930]) < 2048){
	      Event.IsPositron = true;
	    } else {
	      Event.IsPositron = false;
	    }
	}
	  // ch 30: electron NIM
	  if(ch == 30){
	    if(TMath::Mean(50,&Sam[930]) < 2048){
	      Event.IsElectron = true;
	    } else {
	      Event.IsElectron = false;
	    }
	  }

	  //if(!Event.IsElectron) printf("IsPositron %d, IsElectron %d\n",(int)Event.IsPositron,(int)Event.IsElectron);
	  continue;
	}


	mean100[ch] = TMath::Mean(NAvg,&Sam[0]); 
	rms100[ch]  = TMath::RMS(NAvg,&Sam[0]);
	//std::cout<<"rms["<<(int)ch<<"]="<<rms100[ch]<<std::endl;
	//	if(PedIsGood==-1) std::cout<<(Int_t)ch<<" QCh "<<QCh[ch]<<std::endl;
	Double_t  mean    = TMath::Mean(nSamples,&Sam[0]);
	Double_t  rms     = TMath::RMS(nSamples,&Sam[0]);
	//Double_t  meanDif = TMath::Mean(800,&SamDiffCh[100]);
	//Double_t  RMSDif  = TMath::RMS(800,&SamDiffCh[100]);
	Int_t     MinInd  = TMath::LocMin(300,&SamDiffCh[100]);
	//Double_t  MinDiff = TMath::MinElement(300,&SamDiffCh[100]); 
	//update pedestal otherwise keep the last
	//	if(rms100[ch]<7. || iev==0)  mean100[ch] = TMath::Mean(NAvg,&Sam[0]); 
	//	if( abs(mean-mean100[ch]) <3. )  mean100[ch] = mean;
	//	std::cout<<(Int_t)ch<<" rms Ped "<<rms100[ch]<<" "<<rms100[ch]-rms<<std::endl;
	if(rms100[ch]>7.)  {
	  PedIsGood=-1;
	}	
	//	mean100[ch]=3766;
       	for(UShort_t s=0;s<chn->GetNSamples();s++){
	  //	  Sam[s]    = (Double_t) chn->GetSample(s);
	  if(Use_mean100){
	    SamRec[s] = (Double_t) (chn->GetSample(s)-mean100[ch])/4096*1.; //in V
	  } else {
	    SamRec[s] = (Double_t) (chn->GetSample(s)-PedCh[ch])/4096*1.; //in V
	  }

	  if((iev%10==0) && iev<4000){
	    
	    TH2D* histo2d = his->Get2DHisto(Form("SigCh%d",ch));
	    histo2d->SetBinContent(s,iev/10,SamRec[s]);
	  }

 	  //printf("%f ",Sam[s]);
	  // Troppo stringente basta un punto sotto 30 ne servirebbero forse 10 per cambiare l'integrale
	  if(Sam[s]<IsSaturatedValue
	     && Sam[s+1]<IsSaturatedValue
	     && Sam[s+2]<IsSaturatedValue
	     && Sam[s+3]<IsSaturatedValue) {
	    IsSaturated=true;

	    //printf("Saturated ch %d: ev=%d x=%d, y=%f\n",(int)ch,iev,s,Sam[s]);
	  }
	  if(s>NAvg && s<1000.){
	    QCh[ch]+=-SamRec[s]/50*1E-9/1E-12; //in p coulomb
	    if(s<1000) SamDiffCh[s]=Sam[s]-Sam[s-6];//+mean100[ch];
	  }
	}

	TCh[ch] = MinInd;
	//	QCh[ch]-= PedCh[ch];
	Event.NTQCh[ch]    = QCh[ch];
	Event.NTPedCh[ch]  = mean100[ch];
	Event.NTMeanCh[ch] = mean;
	Event.NTRMSCh[ch]  = rms;	
	Event.NTRMS100Ch[ch]  = rms100[ch];
	Event.IsSaturated = IsSaturated;



	if (ch<nChn) {
	  if(b==0 && PedIsGood==1) his->Fill1D(Form("hPedCalo%d",ch),mean100[ch]);
	  if(b==0 && PedIsGood==1 && rms<4.5 && abs(rms-rms100[ch])<1.8) his->Fill1D(Form("hPedMean%d",ch),mean);
	  if(b==0 && PedIsGood==1) his->Fill1D(Form("hQCh%d",ch),QCh[ch]);
	  if(b==0 && QCh[ch]>50.)  his->Fill1D(Form("hTCh%d",ch),TCh[ch]);
	  if(b==0 && QCh[12]>500.) his->Fill1D("hTevRes",TCh[12]-TTrig[1]);
	  if(b==0) his->Fill1D(Form("hRMS100%d",ch),rms100[ch]);
	}

	//	if(b==0) his->FillGraph("Calo",ch,chn->GetNSamples(),SampInd,Sam);
//	if(b==0) his->FillGraph("CaloReco",ch,chn->GetNSamples(),SampInd,SamRec);

	if(1/*QCh[ch]>0.*/) Qtot[b]   += QCh[ch];//
	if(1/*QCh[ch]>0.*/){ 
	  //	if(QCh[ch]>QZSCut && ch!=10) { //perform zero suppression
	  if(QCh[ch]>QZSCut) { //perform zero suppression
	    //	    QtotZS[b]+=QCh[ch]/Cij[ch];
	    QtotZS[b]+=QCh[ch];
	    QtotCal[b]+= QCh[ch]/Cij[ch];
	    NCry++;
	  }
	  //	if(QCh[ch]>300 && ch!=10) { //perform zero suppression
	  if(QCh[ch]>300) { //perform zero suppression
	    TTot[b]+=TCh[ch];
	    NTCry++;
	  }
	  XcryTot += Xcry[ch]*QCh[ch];
	  YcryTot += Ycry[ch]*QCh[ch];
	  if(QCh[ch]>QZSCut)  XcryTotZS += Xcry[ch]*QCh[ch];
	  if(QCh[ch]>QZSCut)  YcryTotZS += Ycry[ch]*QCh[ch];
	}
      }//end of loop on channels



      Event.NTQtot= Qtot[b];
      Event.NTQtotCal= QtotCal[b];
      Event.NTNCry= NCry;
      TEv[b]=TTot[b]/NTCry;
      //      std::cout<<""<<std::endl;
      EleX=XcryTot/Qtot[b];
      EleY=YcryTot/Qtot[b];

      Event.Xcluster = EleX;
      Event.Ycluster = EleY;

      //      if(QCh[12]<0.){
      for(UChar_t c=0;c<nChn;c++) his->Fill1D(Form("hQPedCalo%d",c),QCh[c]);
      //	  if(b==0) his->Fill1D(Form("hQPedCaloProf%d",ch),iev,Qtot[b]);
      //      }
      if(Qtot[b]>300.) his->Fill2D("hECALPos",EleX,EleY);         
      if(Qtot[b]>300.) his->Fill2D("hECALPosZS",XcryTotZS/QtotZS[b],YcryTotZS/QtotZS[b]);
      if(NCry<10) his->Fill2D("hECALPosZS1e",EleX,EleY);
      his->Fill2D("hQtotVsNevt",iev,Qtot[b]);         
      his->Fill1D("hNCry",NCry);
      his->Fill1D("hNTCry",NTCry);
      // && sqrt(EleX*EleX+EleY*EleY)<0.4

      // FILLING FINAL HISTOGRAMS
      if(b==0) his->Fill1D("hQTotNoCut",Qtot[b]);
      if(b==0 && Qtot[b]>-200. && NCry<4) his->Fill1D("hQTot2cry",Qtot[b]);
      //      if(b==0 && Qtot[b]>-200. && sqrt(EleX*EleX+EleY*EleY)<0.7 && PedIsGood>0 && (!IsSaturated)) his->Fill1D("hQTot",Qtot[b]);
      if(b==0 && Qtot[b]>-200. && PedIsGood>0 && (!IsSaturated)) his->Fill1D("hQTot",Qtot[b]);
      if(b==0 && Qtot[b]>-200. && sqrt(EleX*EleX+EleY*EleY)<0.7 && PedIsGood>0 && (!IsSaturated)) his->Fill1D("hQTotCal",QtotCal[b]);
      //      if(b==0 && QtotZS[b]>0.  && NCry>10 && sqrt(EleX*EleX+EleY*EleY)<0.7 && PedIsGood>0 && (!IsSaturated)) his->Fill1D("hQTotZS",QtotZS[b]);
      if(b==0 && QtotZS[b]>0. && NCry>3  && sqrt(EleX*EleX+EleY*EleY)<0.7 && PedIsGood>0 && (!IsSaturated)) his->Fill1D("hQTotZS",QtotZS[b]);
      if(b==0 && PedIsGood<0) his->Fill1D("hQTotWP",Qtot[b]);

      //    if(iev%10==0. && !GoToEnd) {
      //      if(IsEveGood(QCh)<0.) std::cout<<"ma che cazzo "<<IsEveGood(QCh)<<" Qtot "<<QtotZS[b]<<std::endl;
//      if(IsEveGood(QCh)<0. && Qtot[b]>1000.){
//	std::cout<<iev<<" ma che cazzo "<<IsEveGood(QCh)<<" Qtot "<<QtotZS[b]<< " "<<std::endl;
//	for(int bb=0;bb<25;bb++) std::cout<<"ch "<<bb<<" QCh "<<QCh[bb]<<" TCh "<<TCh[bb]<<" "<<mean100[bb]<<std::endl;
//      }

//	Int_t resp = getchar();
//	if(resp!=10) GoToEnd=1;
////	//	printf("resp %d\n",resp);
//	his->KillGraph();
//      }
      //      printf("Bd %d Qtot %f\n",b,Qtot[b]);
    }
    // kiLL ALL graphs    
    // Clear event
    rawEv->Clear("C");
    tree->Fill();


  }// end of loop over events



  fileNTU->cd();
  tree->Print();
  tree->Write();
  fileNTU->Close();
  delete rawEv;
  //delete bRawEv;
  //delete tRawEv;//
  //fRawEv->Close();//
  //delete fRawEv;//
}
/*
TString CheckProtocols(TString OldStr){
  return OldStr;
  }*/


int main(int argc, char* argv[])
{
  Int_t nevents=0;
  int c;
  TString OutputFileName("OutputFile.root");
  TString InputListFileName("InputListFile.txt");
  TString InputFileName("Inputfile.root");
  std::string infile = "rawdata.root";
  std::string outfile = "out.root";
  int iFile = 0, NFiles = 100000;
  struct stat filestat;
  int verbose = 0;
  Histo* his = Histo::GetInstance();

  // Parse options
  while ((c = getopt (argc, argv, "i:l:o:n:v:h")) != -1) {
    switch (c)
      {
      case 'i':
        infile = optarg;
        fprintf(stdout,"Set input data file to '%s'\n",infile.c_str());
	InputFileName = TString(optarg);
        break;
      case 'l':
	InputListFileName = TString(optarg);
	break;
      case 'o':
        outfile = optarg;
        fprintf(stdout,"Set output data file to '%s'\n",outfile.c_str());
        break;
      case 'n':
        if ( sscanf(optarg,"%d",&nevents) != 1 ) {
          fprintf (stderr, "Error while processing option '-n'. Wrong parameter '%s'.\n", optarg);
          exit(1);
        }
        if (nevents<0) {
          fprintf (stderr, "Error while processing option '-n'. Required %d events (must be >=0).\n", nevents);
          exit(1);
        }
	if (nevents) {
	  fprintf(stdout,"Will read first %d events in file\n",nevents);
	} else {
	  fprintf(stdout,"Will read all events in file\n");
	}
        break;
      case 'v':
        if ( sscanf(optarg,"%d",&verbose) != 1 ) {
          fprintf (stderr, "Error while processing option '-v'. Wrong parameter '%s'.\n", optarg);
          exit(1);
        }
        if (verbose<0) {
          fprintf (stderr, "Error while processing option '-v'. Verbose level set to %d (must be >=0).\n", verbose);
          exit(1);
        }
        fprintf(stdout,"Set verbose level to %d\n",verbose);
        break;
      case 'h':
        fprintf(stdout,"\nReadTest [-i input root file] [-v verbosity] [-h]\n\n");
        fprintf(stdout,"  -i: define an input file in root format\n");
	fprintf(stdout,"  -o: define an output file in root format\n");
        fprintf(stdout,"  -n: define number of events to read from input file (0: all events)\n");
        fprintf(stdout,"  -v: define verbose level\n");
        fprintf(stdout,"  -h: show this help message and exit\n\n");
        exit(0);
      case '?':
        if (optopt == 'v') {
          // verbose with no argument: just enable at minimal level
          verbose = 1;
          break;
        } else if (optopt == 'i' || optopt == 'l' || optopt == 'o')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        exit(1);
      default:
        abort();
      }
  }
  

  TChain* chain = new TChain("RawEvents");

  
  TObjArray InputFileNameList;
  if(stat(Form(InputListFileName.Data()), &filestat) == 0) { //-l option used
    std::ifstream InputList(InputListFileName.Data());
    while(InputFileName.ReadLine(InputList) && iFile < NFiles){
      if(stat(Form(InputFileName.Data()), &filestat) == 0)
	//InputFileNameList.Add(new TObjString(InputFileName.Data()));
      chain->Add(InputFileName.Data());      
      iFile++;
    }
  } else if(InputFileName.CompareTo("")) { //-i option used
    if(stat(Form(InputFileName.Data()), &filestat) == 0)
      //InputFileNameList.Add(new TObjString(InputFileName.Data()));
    chain->Add(InputFileName.Data());      
  }
  
  if(chain->GetEntries() == 0 /*InputFileNameList.GetEntries() == 0*/) {
    perror(Form("No Input File"));
    exit(1);
  }
  //TFile* OutputFile = TFile::Open(OutputFileName.Data(),"RECREATE");
  /*  
  for(Int_t jFile = 0; jFile < InputFileNameList.GetEntries(); jFile++){
    chain->Add((((TObjString*)InputFileNameList.At(jFile))->GetString()));
    //printf("adding %s",(((TObjString*)InputFileNameList.At(jFile))->GetString()));
  }
  */

  chain->SetEstimate(chain->GetEntries());
  /*  
  TBranch* bRawEv = chain->GetBranch("RawEvent");
  TRawEvent* rawEv = new TRawEvent();
  chain->SetBranchAddress("RawEvent",&rawEv);
  //bRawEv->SetAddress(&rawEv);
  //bRawEv->GetEntry(99999);
  //bRawEv->GetEntry(100002,1);
  chain->GetEntry(100004);
  UChar_t nBoards = rawEv->GetNADCBoards();
  printf("Number of boards %d\n",nBoards);
  */
  if((nevents == 0) || (nevents > chain->GetEntries())) nevents = chain->GetEntries();
  printf("nevents %d\n", nevents);
  
  FillHisto(chain,outfile.c_str(),nevents);
  his->WriteHisto();
  
  
  exit(0);
}
