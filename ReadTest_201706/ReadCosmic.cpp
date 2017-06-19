#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

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
//if true: the mean of the first NAvg will be subtracted for the charge evaluation
//if false: PedCh[] will be subtracted for the chrge evluation
const Bool_t UseMean100 = false;
// number of cristals in a column
const Int_t nChCol = 4;


struct Eve{
  Int_t NTNevent;
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
  //  PedCh[ 0] =-12.5; PedCh[ 1] =-18.5; PedCh[ 2] = -16.5; PedCh[ 3] = -18.5; PedCh[ 4] = -16.5;
  //  PedCh[ 5] =-17.5; PedCh[ 6] =-9.5;  PedCh[ 7] = -17.5; PedCh[ 8] = -14.5; PedCh[ 9] = -14.5;
  //  PedCh[10] =-12.5; PedCh[11] =-14.5; PedCh[12] = -11.5; PedCh[13] =  -5.5; PedCh[14] = -9.5;
  //  PedCh[15] =-11.5; PedCh[16] =-5.5;  PedCh[17] = -12.5; PedCh[18] = -13.5; PedCh[19] = -13.5;
  //  PedCh[20] =-12.5; PedCh[21] =-3.5;  PedCh[22] = -13.5; PedCh[23] = -12.5; PedCh[24] = -1.5;
  /*
  PedCh[ 0] =-9.5;  PedCh[ 1] =-16.; PedCh[ 2] = -14.0; PedCh[ 3] = -6.0; PedCh[ 4] = -14.;
  PedCh[ 5] =-15.;  PedCh[ 6] =-7.;  PedCh[ 7] = -15.; PedCh[ 8] = -12.; PedCh[ 9] = -12.;
  PedCh[10] =-10.; PedCh[11] =-13.; PedCh[12] = -11.; PedCh[13] =  -3.; PedCh[14] = -7.;
  PedCh[15] =-9.; PedCh[16] =-3.;  PedCh[17] = -11.; PedCh[18] = -11.; PedCh[19] = -11.;
  PedCh[20] =-10.; PedCh[21] =-2.;  PedCh[22] = -11.; PedCh[23] = -10; PedCh[24] = -1.;
  */
  
  // May 2017 Cosmic Rays
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
  }
  Eve Event; 
  printf("GetInstance\n");
  Histo* his = Histo::GetInstance();
  printf("new TFile\n");
  TFile *fileNTU  = new TFile("ntuCosmic.root", "RECREATE");
  printf("new TTree\n");
  TTree *tree     = new TTree("NTU","Event3");
  tree->Branch("Nevent",&(Event.NTNevent),"Nevent/I");
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

  Double_t mean100[32]={0.};
  Double_t rms100[32]={0.};

  Int_t NCol1 = 0;
  Int_t NCol2 = 0;
  Int_t NCol3 = 0;

  // loop on events //
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
      if(iev==0) printf("Ntrg Nchn %d %d\n",nTrg,nChn);
      // Loop over triggers
      Double_t SamDiffTr[1024];
      for(UChar_t t=0;t<nTrg;t++){
	Int_t     MinInd=-1;
	TADCTrigger* trg = adcB->ADCTrigger(t);
	for(Int_t tt=0;tt<trg->GetNSamples();tt++){
	  Sam[tt] = (Double_t) trg->GetSample(tt);
	  if(tt<1000 && tt>10) SamDiffTr[tt]=Sam[tt]-Sam[tt-3];//+mean100[ch];
	  //	  std::cout<<(float)tt<<" sam "<<SamDiffTr[tt]<<" "<<std::endl;
	  if(SamDiffTr[tt]<-50. && MinInd==-1) MinInd=tt;
	  //	  if(tt<MinInd+4) std::cout<<(float)tt<<" " <<Sam[tt]<<" "<<SamDiffTr[tt]<<std::endl;
	}

//	Int_t     MinInd  =TMath::LocMin(800,&SamDiffTr[0]);
//	Double_t  MinDiff =TMath::MinElement(800,&SamDiffTr[0]); 
//	Double_t  MaxInd =TMath::LocMax(800,&SamDiffTr[0]); 
	TTrig[t]=float(MinInd);
	//	double TWdt=MaxInd-MinInd;
	//	std::cout<<(float)t<<" TTrig "<<TTrig[t]<<" "<<MinInd<<std::endl;//" wdt "<<TWdt<<std::endl;
	//	if(b==0) his->FillGraph("CaloTrig",t,trg->GetNSamples(),SampInd,Sam);
	if(b==0) his->Fill1D(Form("hTTrig%d",t),TTrig[t]);
      }
      if(b==0) his->Fill1D("hTT0_TT1",TTrig[0]-TTrig[1]);
      if(b==0) his->Fill1D("hTT2_TT3",TTrig[2]-TTrig[3]);
	
      // Loop over channels
      Double_t Qtot[2]={0};
      Double_t QtotZS[2]={0};
      Double_t TTot[2]={0};
      Double_t TEv[2]={0};
      Double_t XcryTot = 0.;
      Double_t YcryTot = 0.;
      Double_t EleX = 0.;
      Double_t EleY = 0.;
      Double_t XcryTotZS = 0.;
      Double_t YcryTotZS = 0.;

      Int_t NCry=0.;
      Int_t NTCry=0.;
      Int_t PedIsGood=1;
      Double_t QCh[32]={0.};
      Double_t TCh[32]={0.};
      Double_t SamDiffCh[1023]={0.};

      Bool_t IsSigCh[32]={false};
      Bool_t IsSig2Ch[32]={false};
      Int_t Is3max[32] = {0};
      Int_t NSig = 0;
      Int_t NSig2 = 0;
      Int_t NQCh[5]={0};
	
      for(UChar_t c=0;c<nChn;c++){
	TADCChannel* chn = adcB->ADCChannel(c);
	Int_t ch = chn->GetChannelNumber();
	//	printf("\t\tChan %u Chn# %u\n",c,chn->GetChannelNumber());
	//	Double_t SumSam=0.;

       	for(UShort_t s=0;s<NAvg;s++){
	  Sam[s] = (Double_t) chn->GetSample(s);
	}
	rms100[ch]  = TMath::RMS(NAvg,&Sam[0]);

	//update pedestal otherwise keep the last
	if(rms100[ch]<7.)  mean100[ch] = TMath::Mean(NAvg,&Sam[0]); 
	if(rms100[ch]>7.)  {
	  PedIsGood=-1;
	  //	  std::cout<<(Int_t)ch<<" rms Ped "<<rms100[ch]<<std::endl;
	}	
	
       	for(UShort_t s=0;s<chn->GetNSamples();s++){
	  Sam[s]    = (Double_t) chn->GetSample(s);
	  if(UseMean100) SamRec[s] = (Double_t) (chn->GetSample(s)-mean100[ch])/4096*1.; //in V
	  else SamRec[s] = (Double_t) (chn->GetSample(s)-PedCh[ch])/4096*1.; //in V
	  if(s>NAvg){
	    QCh[ch]+=-SamRec[s]/50*1E-9/1E-12; //in p coulomb
	    if(s<1000) SamDiffCh[s]=Sam[s]-Sam[s-6];//+mean100[ch];

	    if(fabs(Sam[s]-mean100[ch])/rms100[ch] > 5.
	       && fabs(Sam[s-1]-mean100[ch])/rms100[ch] > 5.
	       && fabs(Sam[s-2]-mean100[ch])/rms100[ch] > 5.
	       && fabs(Sam[s-3]-mean100[ch])/rms100[ch] > 5.
	       && fabs(Sam[s-4]-mean100[ch])/rms100[ch] > 5.){

		IsSigCh[ch]=true;
	    }

	    if(fabs(Sam[s]-mean100[ch])/rms100[ch] > 10.
	       && fabs(Sam[s-1]-mean100[ch])/rms100[ch] > 10.
	       && fabs(Sam[s-2]-mean100[ch])/rms100[ch] > 10.
	       && fabs(Sam[s-3]-mean100[ch])/rms100[ch] > 10.
	       && fabs(Sam[s-4]-mean100[ch])/rms100[ch] > 10.
	       && fabs(Sam[s-5]-mean100[ch])/rms100[ch] > 10.
	       && fabs(Sam[s-6]-mean100[ch])/rms100[ch] > 10.){

		IsSig2Ch[ch]=true;
	    }

	  }
	}
	if(IsSigCh[ch]) NSig++;
	if(IsSig2Ch[ch]) NSig2++;
	//std::cout<<"IsSigCh["<<ch<<"]="<<IsSigCh[ch]<<", NSig "<<NSig<<std::endl;

	//	if(PedIsGood==-1) std::cout<<(Int_t)ch<<" QCh "<<QCh[ch]<<std::endl;
	Double_t  mean    = TMath::Mean(nSamples,&Sam[0]);
	Double_t  rms     = TMath::RMS(nSamples,&Sam[0]);
	Double_t  meanDif = TMath::Mean(800,&SamDiffCh[100]);
	Double_t  RMSDif  = TMath::RMS(800,&SamDiffCh[100]);
	Int_t     MinInd  = TMath::LocMin(300,&SamDiffCh[100]);
	Double_t  MinDiff = TMath::MinElement(300,&SamDiffCh[100]); 
	TCh[ch]=MinInd;
	//	QCh[ch]-=PedCh[ch];
	Event.NTQCh[ch]   = QCh[ch];
	Event.NTPedCh[ch] = mean100[ch];

	Int_t MyInd=ch%5;
	if(QCh[ch]>150.) NQCh[MyInd]++; 
	//	std::cout<<"Ch"<< ch <<" Q "<<QCh[ch]<<" "<<NQCh[MyInd]<<" "<<MyInd<<std::endl;

	if (ch==25) his->Fill1D(Form("hQCh%d",24),QCh[ch]);
	if (ch<25) {
	  if(b==0 && PedIsGood==1) his->Fill1D(Form("hPedCalo%d",ch),mean100[ch]);
	  if(b==0) his->Fill1D(Form("hQCh%d",ch),QCh[ch]);
	  if(b==0 && QCh[ch]>500.) his->Fill1D(Form("hTCh%d",ch),TCh[ch]);
	  if(b==0 && QCh[ch]>500.) his->Fill1D("hTevRes",TCh[ch]-TTrig[1]);
	  if(b==0) his->Fill1D(Form("hRMS100%d",ch),rms100[ch]);
	}

	//	if(b==0) his->FillGraph("Calo",ch,chn->GetNSamples(),SampInd,Sam);
	//	if(b==0) his->FillGraph("CaloReco",ch,chn->GetNSamples(),SampInd,SamRec);
	
	//	if(ch!=10) Qtot[b]+=QCh[ch];//*Cij[ch];
	Qtot[b]+=QCh[ch];//*Cij[ch];
	//	if(QCh[ch]>QZSCut && ch!=10) { //perform zero suppression

	if(QCh[ch]>QZSCut) { //perform zero suppression
	  QtotZS[b]+=QCh[ch];
	  NCry++;
	}
	//	if(QCh[ch]>300 && ch!=10) { //perform zero suppression
	if(QCh[ch]>300) { //perform zero suppression
	  TTot[b]+=TCh[ch];
	  NTCry++;
	}
	XcryTot += Xcry[ch]*QCh[ch]*2;
	YcryTot += Ycry[ch]*QCh[ch]*2;
	if(QCh[ch]>QZSCut)  XcryTotZS += Xcry[ch]*QCh[ch]*2;
	if(QCh[ch]>QZSCut)  YcryTotZS += Ycry[ch]*QCh[ch]*2;
      }//end of loop on channels
      
      //      if(Qtot[b]>200.){
      //      his->DrawChannels(1,25);
      //      getchar();
	//      }
      Event.NTQtot= Qtot[b];
      TEv[b]=TTot[b]/NTCry;
      //      std::cout<<""<<std::endl;
      EleX=XcryTot/Qtot[b];
      EleY=YcryTot/Qtot[b];

      //      if(QCh[12]<0.){
      for(Int_t c=0;c<25;c++){
	his->Fill1D(Form("hQPedCalo%d",c),QCh[c]);
	//	  if(b==0) his->Fill1D(Form("hQPedCaloProf%d",ch),iev,Qtot[b]);
	//	if(NQCh[c%5]>1) his->Fill1D(Form("hQCh%d",c),QCh[c]);
	//	his->Fill1D(Form("hQCh%d",c),QCh[c]);
	if(NQCh[c%5]>0)	his->Fill2D("hNCol",c%5,NQCh[c%5]);
      }
      his->Fill2D("hECALPos",EleX,EleY);         
      his->Fill2D("hECALPosZS",XcryTotZS/QtotZS[b],YcryTotZS/QtotZS[b]);
      if(NCry<10) his->Fill2D("hECALPosZS1e",EleX,EleY);
      //      his->Fill1D("hNCry",NCry);
      his->Fill1D("hNCry",NSig);
      //his->Fill1D("hNTCry",NTCry);
      his->Fill1D("hNTCry",NSig2);
      // && sqrt(EleX*EleX+EleY*EleY)<0.4
      if(b==0) his->Fill1D("hQTotNoCut",Qtot[b]);
      if(b==0 && Qtot[b]>-200.&& NCry<4) his->Fill1D("hQTot2cry",Qtot[b]);
      if(b==0 && Qtot[b]>-200.&& NCry>10 && sqrt(EleX*EleX+EleY*EleY)<0.5 && PedIsGood>0) his->Fill1D("hQTot",Qtot[b]);
      if(b==0 && QtotZS[b]>0. && NCry>10 && sqrt(EleX*EleX+EleY*EleY)<0.5 && PedIsGood>0) his->Fill1D("hQTotZS",QtotZS[b]);
      if(b==0 && PedIsGood<0) his->Fill1D("hQTotWP",Qtot[b]);


      // identifying the nChCol  channels with the largest charge
      std::map<Int_t,Double_t> Ch_Q;
      for(Int_t nch=0;nch<nChn;nch++){
	
	TADCChannel* Chn = adcB->ADCChannel(nch);
	Int_t Ch = Chn->GetChannelNumber();
	Ch_Q[Ch] = QCh[Ch];
	//printf("ch %d, Q %f \n",Ch,QCh[Ch]);
      }
      
      for(Int_t ij=0;ij<nChCol;ij++){
	Int_t Ch_Qmax = -1;
	Double_t Qmax = 0.;

	std::map<Int_t,Double_t>::iterator ChQ_it;
	for(ChQ_it=Ch_Q.begin();ChQ_it!=Ch_Q.end();ChQ_it++){
	  if(ChQ_it->second > Qmax){
	    Ch_Qmax = ChQ_it->first;
	    Qmax = ChQ_it->second; 
	  }
	}
	if(Qmax>0){Is3max[Ch_Qmax]=1; Ch_Q.erase(Ch_Qmax);}
      }
      //for(Int_t jk=0;jk<32;jk++) printf("Ch %d, Is3max %d \n",jk,Is3max[jk]);
      // end of channels identification

      Int_t IsVert = 0;

      //Only (non simultaneous) vertical cosmic rays are considered
      if(NSig>=4){// 4 = 3 crystals + 1 pad
	//std::cout<<"3 crystals"<<std::endl;
	//third column
	if(IsSigCh[11]&&IsSigCh[8]&&IsSigCh[5]&&IsSigCh[2]
	   &&(Is3max[11]+Is3max[8]+Is3max[5]+Is3max[2])==4){
	  his->Fill1D("hQVertCh11",QCh[11]);
	  his->Fill1D("hQVertCh8",QCh[8]);
	  his->Fill1D("hQVertCh5",QCh[5]);
	  his->Fill1D("hQVertCh2",QCh[2]);

	  IsVert = 1;
	}
	//second column
	if(IsSigCh[10]&&IsSigCh[7]&&IsSigCh[4]&&IsSigCh[1]
	   &&(Is3max[10]+Is3max[7]+Is3max[4]+Is3max[1])==4){
	  his->Fill1D("hQVertCh10",QCh[10]);
	  his->Fill1D("hQVertCh7",QCh[7]);
	  his->Fill1D("hQVertCh4",QCh[4]);
	  his->Fill1D("hQVertCh1",QCh[1]);

	  IsVert = 1;
	}
	//first column
	if(IsSigCh[9]&&IsSigCh[6]&&IsSigCh[3]&&IsSigCh[0]
	   &&(Is3max[9]+Is3max[6]+Is3max[3]+Is3max[0])==4){
	  his->Fill1D("hQVertCh9",QCh[9]);
	  his->Fill1D("hQVertCh6",QCh[6]);
	  his->Fill1D("hQVertCh3",QCh[3]);
	  his->Fill1D("hQVertCh0",QCh[0]);

	  IsVert = 1;
	}
      }

      if(IsVert){
	for(int ivv=0;ivv<nChn;ivv++){
	  his->Fill1D(Form("hQAllVertCh%d",ivv),QCh[ivv]);
	}
      }


      //Only (non simultaneous) vertical cosmic rays are considered
      if(NSig2>=4){// 4 = 3 crystals + 1 pad
	//std::cout<<"3 crystals"<<std::endl;
	//third column
	if(IsSig2Ch[11]&&IsSig2Ch[8]&&IsSig2Ch[5]&&IsSig2Ch[2]
	   &&(Is3max[11]+Is3max[8]+Is3max[5]+Is3max[2])==4){
	  his->Fill1D("hQVert2Ch11",QCh[11]);
	  his->Fill1D("hQVert2Ch8",QCh[8]);
	  his->Fill1D("hQVert2Ch5",QCh[5]);
	  his->Fill1D("hQVert2Ch2",QCh[2]);

	  NCol3++;
	  //std::cout<<"col3"<<std::endl;
	}
	//second column
	if(IsSig2Ch[10]&&IsSig2Ch[7]&&IsSig2Ch[4]&&IsSig2Ch[1]
	   &&(Is3max[10]+Is3max[7]+Is3max[4]+Is3max[1])==4){
	  his->Fill1D("hQVert2Ch10",QCh[10]);
	  his->Fill1D("hQVert2Ch7",QCh[7]);
	  his->Fill1D("hQVert2Ch4",QCh[4]);
	  his->Fill1D("hQVert2Ch1",QCh[1]);

	  NCol2++;
	  //std::cout<<"col2"<<std::endl;
	}
	//first column
	if(IsSig2Ch[9]&&IsSig2Ch[6]&&IsSig2Ch[3]&&IsSig2Ch[0]
	   &&(Is3max[9]+Is3max[6]+Is3max[3]+Is3max[0])==4){
	  his->Fill1D("hQVert2Ch9",QCh[9]);
	  his->Fill1D("hQVert2Ch6",QCh[6]);
	  his->Fill1D("hQVert2Ch3",QCh[3]);
	  his->Fill1D("hQVert2Ch0",QCh[0]);

	  NCol1++;
	  //std::cout<<"col1"<<std::endl;
	}

      }

      if((Is3max[11]+Is3max[8]+Is3max[5]+Is3max[2])==4){
	his->Fill1D("hQ3maxCh11",QCh[11]);
	his->Fill1D("hQ3maxCh8",QCh[8]);
	his->Fill1D("hQ3maxCh5",QCh[5]);
	his->Fill1D("hQ3maxCh2",QCh[2]);
      }
      //second column
      if((Is3max[10]+Is3max[7]+Is3max[4]+Is3max[1])==4){
	his->Fill1D("hQ3maxCh10",QCh[10]);
	his->Fill1D("hQ3maxCh7",QCh[7]);
	his->Fill1D("hQ3maxCh4",QCh[4]);
	his->Fill1D("hQ3maxCh1",QCh[1]);
      }
      //first column
      if((Is3max[9]+Is3max[6]+Is3max[3]+Is3max[0])==4){
	his->Fill1D("hQ3maxCh9",QCh[9]);
	his->Fill1D("hQ3maxCh6",QCh[6]);
	his->Fill1D("hQ3maxCh3",QCh[3]);
	his->Fill1D("hQ3maxCh0",QCh[0]);
      }
      
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
  // end of loop on events //

  printf("NCol1=%d, NCol2=%d, NCol3=%d\n",NCol1,NCol2,NCol3);

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
  printf("FillHisto\n");
  FillHisto(infile.c_str(),outfile.c_str(),nevents);
  // his->InitMonitor();
  // his->DrawChannels(1,25);
  // his->DrawCalo(1,25);
  his->WriteHisto();
  //sleep(10);
  //theApp.Run();
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
