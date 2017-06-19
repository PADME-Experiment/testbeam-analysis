#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom3.h"
#include "TApplication.h"
#include "TMath.h"
#include "TRawEvent.hh"
#include "Histo.hh"

Double_t Xcry[TADCBOARD_NCHANNELS];
Double_t Ycry[TADCBOARD_NCHANNELS];
Double_t PedCh[TADCBOARD_NCHANNELS];
Double_t Cij[TADCBOARD_NCHANNELS];

const int nSamples = 1024;
const Int_t NAvg=80;
const Double_t QZSCut=10.;
const Int_t IsRandCal=0.;
const Bool_t OnlyCentrals=false;
const Bool_t IsCalibrated=true;
const Double_t IsSaturatedValue = 30.;

struct Eve{
  Int_t NTNevent;
  Int_t NTNCry;
  Double_t NTQCh[25];
  Double_t NTQtot;
  Double_t NTPedCh[25];
};

int IsEveGood(Double_t * QCh){
  for(int i=0;i<25;i++){
    if(QCh[i]<-500.) return -1;
  }
  return 1;
}

void FillHisto(std::string name,std::string outname, int nevents){
  Xcry[ 0]=-2.; Xcry[ 1]=-1.; Xcry[ 2]= 0.; Xcry[ 3]= 1.; Xcry[ 4]= 2.;
  Ycry[ 0]=-2.; Ycry[ 1]=-2.; Ycry[ 2]=-2.; Ycry[ 3]=-2.; Ycry[ 4]=-2.;
  Xcry[ 5]=-2.; Xcry[ 6]=-1.; Xcry[ 7]= 0.; Xcry[ 8]= 1.; Xcry[ 9]= 2.;
  Ycry[ 5]=-1.; Ycry[ 6]=-1.; Ycry[ 7]=-1.; Ycry[ 8]=-1.; Ycry[ 9]=-1.;
  Xcry[10]=-2.; Xcry[11]=-1.; Xcry[12]= 0.; Xcry[13]= 1.; Xcry[14]= 2.;
  Ycry[10]= 0.; Ycry[11]= 0.; Ycry[12]= 0.; Ycry[13]= 0.; Ycry[14]= 0.;
  Xcry[15]=-2.; Xcry[16]=-1.; Xcry[17]= 0.; Xcry[18]= 1.; Xcry[19]= 2.;
  Ycry[15]= 1.; Ycry[16]= 1.; Ycry[17]= 1.; Ycry[18]= 1.; Ycry[19]= 1.; 
  Xcry[20]=-2.; Xcry[21]=-1.; Xcry[22]= 0.; Xcry[23]= 1.; Xcry[24]= 2.;
  Ycry[20]= 2.; Ycry[21]= 2.; Ycry[22]= 2.; Ycry[23]= 2.; Ycry[24]= 2.;
// July values
  PedCh[ 0] =-12.5; PedCh[ 1] =-18.5; PedCh[ 2] = -16.5; PedCh[ 3] = -18.5; PedCh[ 4] = -16.5;
  PedCh[ 5] =-17.5; PedCh[ 6] =-9.5;  PedCh[ 7] = -17.5; PedCh[ 8] = -14.5; PedCh[ 9] = -14.5;
  PedCh[10] =-12.5; PedCh[11] =-14.5; PedCh[12] = -11.5; PedCh[13] =  -5.5; PedCh[14] = -9.5;
  PedCh[15] =-11.5; PedCh[16] =-5.5;  PedCh[17] = -12.5; PedCh[18] = -13.5; PedCh[19] = -13.5;
  PedCh[20] =-12.5; PedCh[21] =-3.5;  PedCh[22] = -13.5; PedCh[23] = -12.5; PedCh[24] = -1.5;
//Novembre
//  PedCh[ 0] =-9.5;  PedCh[ 1] =-16.; PedCh[ 2] = -14.0; PedCh[ 3] = -6.0; PedCh[ 4] = -14.;
//  PedCh[ 5] =-15.;  PedCh[ 6] =-7.;  PedCh[ 7] = -15.; PedCh[ 8] = -12.; PedCh[ 9] = -12.;
//  PedCh[10] =-10.; PedCh[11] =-13.; PedCh[12] = -11.; PedCh[13] =  -3.; PedCh[14] = -7.;
//  PedCh[15] =-9.; PedCh[16] =-3.;  PedCh[17] = -11.; PedCh[18] = -11.; PedCh[19] = -11.;
//  PedCh[20] =-10.; PedCh[21] =-2.;  PedCh[22] = -11.; PedCh[23] = -10; PedCh[24] = -1.;
  
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
    //printf("\n\n === In the total charge histogram ONLY the 9 central crystals are considered === \n\n");
    for(int kk=0;kk<32;kk++) Cij[kk]=1.;
    Cij[6]=1.0274;
    Cij[7]=1.0307;
    Cij[8]=1.16;
    Cij[11]=1.0015;
    Cij[12]=1;
    Cij[13]=0.817;
    Cij[16]=1.096;
    Cij[17]=1.618;
    Cij[18]=1.0896;
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
  TTree *tree     = new TTree("NTU","Event3");
  tree->Branch("Nevent",&(Event.NTNevent),"Nevent/I");
  tree->Branch("NCry",&(Event.NTNCry),"NCry/I");
  tree->Branch("Qtot",&(Event.NTQtot),"Qtot/D");
  tree->Branch("QCh",Event.NTQCh,"QCh[25]/D");
  tree->Branch("PedCh",Event.NTPedCh,"PedCh[25]/D");

  printf("new TFile\n");
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
  Int_t GoToEnd=0;
  Int_t NMaxSamp = 1024;
  Double_t SampInd[1024];
  for(int ll=0;ll<NMaxSamp;ll++) SampInd[ll]=ll*1.;

  UInt_t nevt = tRawEv->GetEntries();
  printf("TTree RawEvents contains %d events\n",nevt);
  // Set number of events to read
  UInt_t ntoread = nevt;
  Double_t Sam[1024];
  Double_t SamRec[1024];
  Double_t TTrig[4];
  if (nevents && nevents<nevt) ntoread = nevents;

  printf("Reading the first %d events\n",ntoread);

  //  ntoread = 1500.;
  Double_t mean100[32]={0.};
  Double_t rms100[32]={0.};

  for(Int_t iev=0;iev<ntoread;iev++){
    // Read event
    Event.NTNevent=iev;
    // B1->Fill();

    if(iev%1000==0) printf("Reading event %d\n",iev);
    bRawEv->GetEntry(iev);
    // Show event header
    UChar_t nBoards = rawEv->GetNADCBoards();
    // Loop over boards
    for(UChar_t b=0;b<nBoards;b++){
      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      UChar_t nTrg = adcB->GetNADCTriggers();
      UChar_t nChn = adcB->GetNADCChannels();
      if(iev==1) printf("Ntrg Nchn %d %d\n",nTrg,nChn);
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
	Double_t  TrigLowThr= MinTrig*0.1;
	Double_t  TriHighThr= MinTrig*0.9;
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

	Int_t npt=2;
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
	//	Double_t SumSam=0.;

       	for(UShort_t s=0;s<NAvg;s++){
	  Sam[s] = (Double_t) chn->GetSample(s);
	}
	rms100[ch]  = TMath::RMS(NAvg,&Sam[0]);
	//std::cout<<"rms["<<(int)ch<<"]="<<rms100[ch]<<std::endl;

	//update pedestal otherwise keep the last
	if(rms100[ch]<7. || iev==0)  mean100[ch] = TMath::Mean(NAvg,&Sam[0]); 
	if(rms100[ch]>7.)  {
	  PedIsGood=-1;
	  //	  std::cout<<(Int_t)ch<<" rms Ped "<<rms100[ch]<<std::endl;
	}	
	
       	for(UShort_t s=0;s<chn->GetNSamples();s++){
	  Sam[s]    = (Double_t) chn->GetSample(s);
	  SamRec[s] = (Double_t) (chn->GetSample(s)-mean100[ch])/4096*1.; //in V

 	  //printf("%f ",Sam[s]);
	  // Troppo stringente basta un punto sotto 30 ne servirebbero forse 10 per cambiare l'integrale
	  if(Sam[s]<IsSaturatedValue) {
	    IsSaturated=true;
	    //printf("Saturated ch %d: ev=%d x=%d, y=%f\n",(int)ch,iev,s,Sam[s]);
	  }
	  if(s>NAvg && s<1000.){
	    QCh[ch]+=-SamRec[s]/50*1E-9/1E-12; //in p coulomb
	    if(s<1000) SamDiffCh[s]=Sam[s]-Sam[s-6];//+mean100[ch];
	  }
	}
	//	if(PedIsGood==-1) std::cout<<(Int_t)ch<<" QCh "<<QCh[ch]<<std::endl;
	Double_t  mean    = TMath::Mean(nSamples,&Sam[0]);
	Double_t  rms     = TMath::RMS(nSamples,&Sam[0]);
	Double_t  meanDif = TMath::Mean(800,&SamDiffCh[100]);
	Double_t  RMSDif  = TMath::RMS(800,&SamDiffCh[100]);
	Int_t     MinInd  = TMath::LocMin(300,&SamDiffCh[100]);
	Double_t  MinDiff = TMath::MinElement(300,&SamDiffCh[100]); 
	TCh[ch] = MinInd;
	QCh[ch]-= PedCh[ch];
	Event.NTQCh[ch]   = QCh[ch];
	Event.NTPedCh[ch] = mean100[ch];

	if (ch<25) {
	  if(b==0 && PedIsGood==1) his->Fill1D(Form("hPedCalo%d",ch),mean100[ch]);
	  if(b==0 && PedIsGood==1) his->Fill1D(Form("hQCh%d",ch),QCh[ch]);
	  if(b==0 && QCh[ch]>50.)  his->Fill1D(Form("hTCh%d",ch),TCh[ch]);
	  if(b==0 && QCh[12]>500.) his->Fill1D("hTevRes",TCh[12]-TTrig[1]);
	  if(b==0) his->Fill1D(Form("hRMS100%d",ch),rms100[ch]);
	}

	//	if(b==0) his->FillGraph("Calo",ch,chn->GetNSamples(),SampInd,Sam);
//	if(b==0) his->FillGraph("CaloReco",ch,chn->GetNSamples(),SampInd,SamRec);

	if(ch!=10 && QCh[ch]>0.) Qtot[b]   += QCh[ch];//
	if(ch!=10 && QCh[ch]>0.){ 
	  QtotCal[b]+= QCh[ch]/Cij[ch];
	  //	if(QCh[ch]>QZSCut && ch!=10) { //perform zero suppression
	  if(QCh[ch]>QZSCut) { //perform zero suppression
	    QtotZS[b]+=QCh[ch]/Cij[ch];
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
      //      if(iev%1000==0) his->DrawChannels(1,25);
      Event.NTQtot= Qtot[b];
      Event.NTNCry= NCry;
      TEv[b]=TTot[b]/NTCry;
      //      std::cout<<""<<std::endl;
      EleX=XcryTot/Qtot[b]*2;
      EleY=YcryTot/Qtot[b]*2;
      //      if(QCh[12]<0.){
      for(UChar_t c=0;c<25;c++) his->Fill1D(Form("hQPedCalo%d",c),QCh[c]);
      //	  if(b==0) his->Fill1D(Form("hQPedCaloProf%d",ch),iev,Qtot[b]);
      //      }
      his->Fill2D("hECALPos",EleX,EleY);         
      his->Fill2D("hECALPosZS",XcryTotZS/QtotZS[b]*2,YcryTotZS/QtotZS[b]*2);
      if(NCry<10) his->Fill2D("hECALPosZS1e",EleX,EleY);
      his->Fill1D("hNCry",NCry);
      his->Fill1D("hNTCry",NTCry);
      // && sqrt(EleX*EleX+EleY*EleY)<0.4

      // FILLING FINAL HISTOGRAMS
      IsSaturated=0; //M Raggi temporary
      if(b==0) his->Fill1D("hQTotNoCut",Qtot[b]);
      if(b==0 && Qtot[b]>-200. && NCry<4) his->Fill1D("hQTot2cry",Qtot[b]);
      if(b==0 && Qtot[b]>-200. && sqrt(EleX*EleX+EleY*EleY)<0.7 && PedIsGood>0 && (!IsSaturated)) his->Fill1D("hQTot",Qtot[b]);
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
  }
  fileNTU->cd();
  tree->Print();
  tree->Write();
  fileNTU->Close();
  delete rawEv;
  delete bRawEv;
  delete tRawEv;
  fRawEv->Close();
  delete fRawEv;
}

int main(int argc, char* argv[])
{
  int nevents=0;
  int c;
  std::string infile = "rawdata.root";
  std::string outfile = "out.root";
  int verbose = 0;
  Histo* his = Histo::GetInstance();
  // Parse options
  while ((c = getopt (argc, argv, "i:o:n:v:h")) != -1) {
    switch (c)
      {
      case 'i':
        infile = optarg;
        fprintf(stdout,"Set input data file to '%s'\n",infile.c_str());
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

  //  TApplication theApp("App",&argc,argv);
  //  printf("FillHisto\n");
  FillHisto(infile.c_str(),outfile.c_str(),nevents);
  // his->InitMonitor();
  // his->DrawCalo(1,25);
  his->WriteHisto();
  //sleep(10);
  //  theApp.Run();
  exit(0);
}


//void ECALAnal::AnalyzePosition()
//{
//
//  // Map of crystal positions
//  Double_t Xcry[TADCBOARD_NCHANNELS];
//  Double_t Ycry[TADCBOARD_NCHANNELS];
//  Xcry[ 5]= 4.; Xcry[ 6]= 2.; Xcry[ 7]= 0.; Xcry[ 8]=-2.;
//  Ycry[ 5]=-2.; Ycry[ 6]=-2.; Ycry[ 7]=-2.; Ycry[ 8]=-2.;
//  Xcry[10]= 4.; Xcry[11]= 2.; Xcry[12]= 0.; Xcry[13]=-2.;
//  Ycry[10]= 0.; Ycry[11]= 0.; Ycry[12]= 0.; Ycry[13]= 0.;
//  Xcry[15]= 4.; Xcry[16]= 2.; Xcry[17]= 0.; Xcry[18]=-2.;
//  Ycry[15]= 2.; Ycry[16]= 2.; Ycry[17]= 2.; Ycry[18]= 2.;
//
//  // Loop over boards
//  UChar_t nBoards = fRawEvent->GetNADCBoards();
//  for(UChar_t b=0;b<nBoards;b++){
//
//    // Check if we are looking at the ECAL ADC board (board id 0) and we have some signal
//    TADCBoard* adcB = fRawEvent->ADCBoard(b);
//    UChar_t bid = adcB->GetBoardId();
//    if (bid != 0 || fQTotal1[bid] <= 0.) continue;
//
//    //    printf("AnalPos - Board %d Charge %f\n",bid,fQTotal1[bid]);
//
//    // Get number of active channels in this board
//    UChar_t nChn = adcB->GetNADCChannels();
//
//    Double_t XcryTot = 0.;
//    Double_t YcryTot = 0.;
//    for(Int_t c=0;c<nChn;c++){
//      UChar_t cnr = adcB->ADCChannel(c)->GetChannelNumber();
//      XcryTot += Xcry[cnr]*fQChannel[bid][cnr];
//      YcryTot += Ycry[cnr]*fQChannel[bid][cnr];
//    }
//    fECALHisto->Fill2DHisto("ECALPos",XcryTot/fQTotal1[bid],YcryTot/fQTotal1[bid]);
//  }
//}
