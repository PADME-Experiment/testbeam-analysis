//#include<TH1F.h>
//#include<TH1D.h>
#include<TH2F.h>
#include<TF1.h>
#include<TStyle.h>
//#include<TArrayD.h>
#include<TFile.h>
#include<TCanvas.h>


#include<valarray>
#include<vector>
#include<numeric>
#include<iostream>
#include<fstream>
#include<math.h>

void GainCalib(const TFile& f){
  std::vector<double> vect;
  for(int chan_i=8;chan_i<16;++chan_i){
    TCanvas * c =new TCanvas(Form("%d",chan_i),Form("%d",chan_i));
    c->SetLogy();
    c->SetGridy();
    c->SetGridx();
    TH1F* h=(TH1F*)f.FindObjectAny(Form("PhElectrEff_ch_%d",chan_i));
    //std::cout<<h->GetEntries();
    TF1 *func = new TF1("func","[0]*exp(-x*[1])",h->GetBinCenter(h->GetMaximumBin())+h->GetRMS()/2.,h->GetBinCenter(h->GetNbinsX()));
    h->Fit(func,"LRQ","");
    vect.push_back(log(func->GetParameter(0))/func->GetParameter(1));
    std::cout
      <<chan_i<<"  "
      <<log(func->GetParameter(0))/func->GetParameter(1)
      <<std::endl;
    h->Draw();
  }
  double avg=std::accumulate(vect.begin(),vect.end(),0)/vect.size();
  std::cout <<"avg  "<<avg <<std::endl;
  int i=8;
  std::cout.precision(10);
  for(std::vector<double>::iterator v_it=vect.begin();v_it!=vect.end();++v_it){
    double val=*v_it;
    std::cout<<"ch "<<i++<<"   "<<val/avg<<std::endl;
  }


}

void PedestalCalc(TFile& f){
  TH2F* h2=(TH2F*)f.FindObjectAny("PedestalsStudy_ch_10");
  for(int bin_i=0;bin_i<20;++bin_i){
    TH1D* proj=(TH1D*)h2->ProjectionX("_px",bin_i,bin_i,"");
    double mode=proj->GetMean()-proj->GetSkewness()*proj->GetRMS()/4;
    std::cout
      <<proj->GetBinCenter(proj->GetMaximumBin())<<"  "
      <<mode<<"  "
      <<proj->GetMean()<<"  "
      <<std::endl;
  }

  //proj->Draw();
}

void Eff_Ineff(const TFile&f, const std::string& outf){
  std::ofstream out(outf);
  for(int ch_i=8;ch_i<12;++ch_i) {
    TH1F* sigh  =(TH1F*)f.FindObjectAny(Form("PhElectrEff_ch_%d",ch_i));
    TH1F* noiseh=(TH1F*)f.FindObjectAny(Form("PhElectrNoise_ch_%d",ch_i));
    int nbins=sigh->GetNbinsX();
    for(int bin_i=1;bin_i<=nbins;++bin_i){
      const double nevt=sigh->GetEntries();
      const double noise=100-noiseh->Integral(0,bin_i)/nevt*100;
      const double inef =sigh  ->Integral(0,bin_i)/nevt*100;
      out
        <<ch_i<<"  "
        <<sigh->GetBinCenter(bin_i)<<"   "
        <<inef<<"   "
        <<noise<<"   "
        <<nevt<<"   "
        <<std::endl;
    }
    out<<std::endl;
    out<<std::endl;
  }
}

void Eff_IneffAbs(const TFile&f, const std::string& outf){
  std::ofstream out(outf);
  for(int ch_i=0;ch_i<32;++ch_i) {
    TH1F* sigh  =dynamic_cast<TH1F*>(f.FindObjectAny(Form("PhElectrAbsEff_ch_%d",ch_i)) );
    TH1F* noiseh=dynamic_cast<TH1F*>(f.FindObjectAny(Form("PhElectrAbsNoise_ch_%d",ch_i)));
    if(sigh==nullptr||noiseh==nullptr)continue;
    int nbins=sigh->GetNbinsX();
    for(int bin_i=1;bin_i<=nbins;++bin_i){
      const double nevt=sigh->GetEntries();
      const double noise=100-noiseh->Integral(0,bin_i)/nevt*100;
      const double inef =sigh  ->Integral(0,bin_i)/nevt*100;
      out
        <<ch_i<<"  "
        <<sigh->GetBinCenter(bin_i)<<"   "
        <<inef<<"   "
        <<noise<<"   "
        <<std::endl;
    }
    out<<std::endl;
    out<<std::endl;
  }
}

void sigma(){
  gStyle->SetOptStat(  1112110); gStyle->SetOptTitle(kTRUE);
  gStyle->SetOptFit(11);       gStyle->SetStatStyle(1001);
  gStyle->SetStatFormat("6.4g"); gStyle->SetStripDecimals(kFALSE);
  gStyle->SetFitFormat("5.4g");
  TFile f("a.root");
  TH2F* hist=(TH2F*)f.FindObjectAny("TimeDiffMeanTime_13_14_nphe");
  std::cout<<hist<<std::endl;
  TCanvas a;
  a.SetLogy();
  for(int i=1;i<60;++i){
    TH1D* hproj=hist->ProjectionX("_px",i,i,"");
    hproj->SetTitle( Form("%3.2f+- %2.0f phe;T(13)-T(14)[ns];#",((TAxis*) hist->GetYaxis())->GetBinCenter(i),
          (((TAxis*) hist->GetYaxis())->GetBinUpEdge(i)-((TAxis*) hist->GetYaxis())->GetBinLowEdge(i))/2.));
    hproj->Fit("gaus","Lq");
    hproj->SetAxisRange(-50,50.,"X");
    hproj->Draw();
    getchar();
    a.SaveAs(Form("a-%d.png",i));
    std::cout
      <<i<<"  "
      <<((TAxis*) hist->GetYaxis())->GetBinCenter(i)
      <<"  "
      << hproj->GetRMS()
      <<"  "
      << hproj->GetRMSError()
      <<std::endl;
  }
}

void TimeRes(const TFile&f, const std::string& outf, const std::string& runN){
  static std::ofstream out(outf);
  out<<"TimeDiffMaxValue TimeDiffMaxValue_err TimeDiffHalfMaxValue TimeDiffHalfMaxValue_err TimeDiff2080LeadTrailCros TimeDiff2080LeadTrailCros_err TimeDiff2080LeadZeroCros TimeDiff2080LeadZeroCros_err TimeDiff2080Lead50 TimeDiff2080Lead50_err TimeDiffMeanTime TimeDiffMeanTime_err TimeDiffMeanTime2 TimeDiffMeanTime2_err TimeDiffMeanTimeAbs TimeDiffMeanTimeAbs_err TimeDiffIntegral TimeDiffIntegral_err TimeDiff01MaxValue TimeDiff01MaxValue_err TimeDiff02MaxValue TimeDiff02MaxValue_err "<<std::endl;;


  for(int ch_i=4;ch_i<8;++ch_i) {
    int ref=ch_i+4;
    //if(
    //    ch_i== 1||
    //    ch_i== 4||
    //    ch_i== 6||
    //    ch_i== 9||
    //    ch_i==11||
    //    ch_i==14||
    //    ch_i==18||
    //    ch_i==20)continue;
    if(ch_i==ref)continue;
    TH2F* hist2f_TimeDiffMaxValue         = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiffMaxValue_%d_%d"         ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiffHalfMaxValue     = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiffHalfMaxValue_%d_%d"     ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiff2080LeadTrailCros= dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiff2080LeadTrailCros_%d_%d",std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiff2080LeadZeroCros = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiff2080LeadZeroCros_%d_%d" ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiff2080Lead50       = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiff2080Lead50_%d_%d"       ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiffMeanTime         = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiffMeanTime_%d_%d"         ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiffMeanTime2        = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiffMeanTime2_%d_%d"        ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiffMeanTimeAbs      = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiffMeanTimeAbs_%d_%d"      ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiffIntegral         = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiffIntegral_%d_%d"         ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiff01MaxValue     = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiff01MaxValue_%d_%d"     ,std::min(ref,ch_i),std::max(ref,ch_i))));
    TH2F* hist2f_TimeDiff02MaxValue     = dynamic_cast<TH2F*>(f.FindObjectAny(Form("TimeDiff02MaxValue_%d_%d"     ,std::min(ref,ch_i),std::max(ref,ch_i))));
    if(
        hist2f_TimeDiffMaxValue         ==nullptr||
        hist2f_TimeDiffHalfMaxValue     ==nullptr||
        hist2f_TimeDiff2080LeadTrailCros==nullptr||
        hist2f_TimeDiff2080LeadZeroCros ==nullptr||
        hist2f_TimeDiff2080Lead50       ==nullptr||
        hist2f_TimeDiffMeanTime         ==nullptr||
        hist2f_TimeDiffMeanTime2        ==nullptr||
        hist2f_TimeDiffMeanTimeAbs      ==nullptr||
        hist2f_TimeDiffIntegral         ==nullptr||
        hist2f_TimeDiff01MaxValue     ==nullptr||
        hist2f_TimeDiff02MaxValue     ==nullptr||
        false)continue;
    TH1D*tmphist;
    out <<ch_i<<"  ";
    TF1* gausss=new TF1("gausss", "gaus");
    static int sHistTimeDiff=0;
    tmphist=hist2f_TimeDiffMaxValue         ->ProjectionX(Form("%s_%s",hist2f_TimeDiffMaxValue         ->GetName(),runN.c_str()),hist2f_TimeDiffMaxValue         ->GetYaxis()->FindBin(30),hist2f_TimeDiffMaxValue         ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiffHalfMaxValue     ->ProjectionX(Form("%s_%s",hist2f_TimeDiffHalfMaxValue     ->GetName(),runN.c_str()),hist2f_TimeDiffHalfMaxValue     ->GetYaxis()->FindBin(30),hist2f_TimeDiffHalfMaxValue     ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiff2080LeadTrailCros->ProjectionX(Form("%s_%s",hist2f_TimeDiff2080LeadTrailCros->GetName(),runN.c_str()),hist2f_TimeDiff2080LeadTrailCros->GetYaxis()->FindBin(30),hist2f_TimeDiff2080LeadTrailCros->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiff2080LeadZeroCros ->ProjectionX(Form("%s_%s",hist2f_TimeDiff2080LeadZeroCros ->GetName(),runN.c_str()),hist2f_TimeDiff2080LeadZeroCros ->GetYaxis()->FindBin(30),hist2f_TimeDiff2080LeadZeroCros ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiff2080Lead50       ->ProjectionX(Form("%s_%s",hist2f_TimeDiff2080Lead50       ->GetName(),runN.c_str()),hist2f_TimeDiff2080Lead50       ->GetYaxis()->FindBin(30),hist2f_TimeDiff2080Lead50       ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiffMeanTime         ->ProjectionX(Form("%s_%s",hist2f_TimeDiffMeanTime         ->GetName(),runN.c_str()),hist2f_TimeDiffMeanTime         ->GetYaxis()->FindBin(30),hist2f_TimeDiffMeanTime         ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiffMeanTime2        ->ProjectionX(Form("%s_%s",hist2f_TimeDiffMeanTime2        ->GetName(),runN.c_str()),hist2f_TimeDiffMeanTime2        ->GetYaxis()->FindBin(30),hist2f_TimeDiffMeanTime2        ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiffMeanTimeAbs      ->ProjectionX(Form("%s_%s",hist2f_TimeDiffMeanTimeAbs      ->GetName(),runN.c_str()),hist2f_TimeDiffMeanTimeAbs      ->GetYaxis()->FindBin(30),hist2f_TimeDiffMeanTimeAbs      ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiffIntegral         ->ProjectionX(Form("%s_%s",hist2f_TimeDiffIntegral         ->GetName(),runN.c_str()),hist2f_TimeDiffIntegral         ->GetYaxis()->FindBin(30),hist2f_TimeDiffIntegral         ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiff01MaxValue     ->ProjectionX(Form("%s_%s",hist2f_TimeDiff01MaxValue     ->GetName(),runN.c_str()),hist2f_TimeDiff01MaxValue     ->GetYaxis()->FindBin(30),hist2f_TimeDiff01MaxValue     ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    tmphist=hist2f_TimeDiff02MaxValue     ->ProjectionX(Form("%s_%s",hist2f_TimeDiff02MaxValue     ->GetName(),runN.c_str()),hist2f_TimeDiff02MaxValue     ->GetYaxis()->FindBin(30),hist2f_TimeDiff02MaxValue     ->GetYaxis()->FindBin(23000));tmphist->Fit("gausss",tmphist->GetEntries()<1000?"L":"");out<<gausss->GetParameter(2) <<"  "   <<gausss->GetParError(2) <<"  ";tmphist->Write();
    out<<runN;
    out<<std::endl;
  }
}


bool FFT(
    const std::vector<double>&fre,
    const std::vector<double>&fim,
    std::vector<double>&Fre,
    std::vector<double>&Fim
    ){
  const unsigned int N=fre.size();
  if(fim.size()!=0&&fim.size()!=N)return false;
  Fre.clear();Fre.resize(N,0);
  Fim.clear();Fim.resize(N,0);
  double df=-2*acos(-1.)/N;
  if(fim.size()==0){
    for(unsigned int i=0;i<N;++i){
      for(unsigned int f=0;f<N;++f){
        Fre[f]+=fre[i]*cos(df*i*f);
        Fim[f]+=fre[i]*sin(df*i*f);
      }
    }
  }else{
    for(unsigned int i=0;i<N;++i){
      for(unsigned int f=0;f<N;++f){
        Fre[f]+=fre[i]*cos(df*i*f)+fim[i]*sin(df*i*f);
        Fim[f]+=fre[i]*sin(df*i*f)+fim[i]*cos(df*i*f);
      }
    }
  }

  return true;
}
bool IFFTreal(
    const std::vector<double>&Fre,
    const std::vector<double>&Fim,
    std::vector<double>&fre,
    std::vector<double>&fim
    ){
  const unsigned int N=Fre.size();
  if(fim.size()!=0&&fim.size()!=N)return false;
  fre.clear();fre.resize(N,0);
  fim.clear();fim.resize(N,0);
  double df=-2*acos(-1.)/N;
  for(unsigned int p=0;p<N;++p){
    unsigned int i=p;//p>N/2?N-p:p;
    for(unsigned int k=1;k<N/2;++k){
      unsigned f=k;
      fre[i]+=2*Fre[f]*cos(df*i*f)+Fim[f]*sin(df*i*f)-Fim[f]*sin(df*i*(N-f));
      fim[i]+=2*Fre[f]*sin(df*i*f)+Fim[f]*cos(df*i*f)-Fim[f]*cos(df*i*(N-f));
    }
    unsigned f;
    f=0;
    fre[i]+=Fre[f]*cos(df*i*f)+Fim[f]*sin(df*i*f)-Fim[f]*sin(df*i*(N-f));
    fim[i]+=Fre[f]*sin(df*i*f)+Fim[f]*cos(df*i*f)-Fim[f]*cos(df*i*(N-f));
    f=N/2;
    fre[i]+=Fre[f]*cos(df*i*f)+Fim[f]*sin(df*i*f)-Fim[f]*sin(df*i*(N-f));
    fim[i]+=Fre[f]*sin(df*i*f)+Fim[f]*cos(df*i*f)-Fim[f]*cos(df*i*(N-f));
    fre[i]/=N;
    fim[i]/=N;
  }
  return true;
}

void FFTLowPass(std::vector<double>& re){
  const unsigned nDat=re.size();
  const unsigned nFreq=32;
  const double df=-2*acos(-1.)/nDat;
  std::vector<double> Re;Re.resize(nFreq);
  std::vector<double> Im;Im.resize(nFreq,0);
  re[1023]=
    re[1022]=
    re[1021]=
    re[1020]=
    re[1019];
  for(unsigned f=1;f<nFreq;++f){
    for(unsigned t=0;t<nDat;++t){
      Re[f]+=re[t]*cos(df*t*f);
      Im[f]+=re[t]*sin(df*t*f);
    }
    Re[0]-=Re[f]; //background subtraction
  }
  for(unsigned t=0;t<nDat;++t){
    re[t]=Re[0];
    for(unsigned f=1;f<nFreq;++f){
      re[t]+=2*(Re[f]*cos(df*t*f)+Im[f]*(sin(df*t*f)));
    }
    re[t]/=nDat;
  }
}

void FFTPlay(const TFile&f, const std::string& outf){
  std::ofstream out(outf);
  TH2F* h2d=((TH2F*)f.FindObjectAny("PedestalsStudy_ch_15"));
  for(int evt_i=1;evt_i<100;++evt_i){
    TH1D* oscilo=h2d->ProjectionX("_px",evt_i,evt_i,"");

    std::vector<double> r;
    std::vector<double> i;
    std::vector<double> rr,ii;
    std::vector<double> R;
    std::vector<double> I;

    for(int i=1;i<=oscilo->GetNbinsX();++i) r.push_back(oscilo->GetBinContent(i));
    //for(int i=250;i<=400;++i) r.push_back(oscilo->GetBinContent(i));
    //for(int i=400;i<=600;++i) r.push_back(oscilo->GetBinContent(i));
    //for(int i=400;i<=600;++i) r.push_back(oscilo->GetBinContent(i));
    //for(int i=400;i<=600;++i) r.push_back(oscilo->GetBinContent(i));



    FFT(r,i,R,I);

    std::vector<double> Z;Z.resize(R.size());
    std::vector<double> F;F.resize(R.size());
    for(int i=0;i<R.size();++i){
      Z[i]=sqrt(R[i]*R[i]+I[i]*I[i]);
      F[i]=atan2(I[i],R[i]);
    }

    unsigned x1=1;
    unsigned x2=26;
    double y1=log(Z[x1]);
    double y2=log(Z[x2]);
    for(int i=3;i<R.size();++i){
      //Z[i]=exp((y2-y1)/(x2-x1)*(i-x1)+y1);
    }
    for(int i=32;i<R.size();++i){
      Z[i]=0;
    }

    for(int i=0;i<R.size();++i){
      R[i]=abs(Z[i])*cos(F[i]);
      F[i]=abs(Z[i])*sin(F[i]);
    }



    //R[0]=0; I[0]=0;
    ////R[6]*=3;
    //I[4];
    //for(int i=12;i<R.size();++i){
    //  R[i]=0;
    //  I[i]=0;
    //}
    //for(int i=1;i<R.size();++i) R[0]-=R[i];
    //for(int i=1;i<R.size();++i) R[0]-=R[i];

    IFFTreal(R,I,rr,ii);

    std::vector<double>k=r;
    FFTLowPass(k);



    for(int i=0;i<r.size();++i){
      out
        <<r[i]<<"  "
        <<0   <<"  "
        <<R[i]<<"  "
        <<I[i]<<"  "
        <<rr[i]<<"  "
        <<ii[i]<<"  "
        <<Z[i]<<"  "
        <<F[i]<<"  "
        <<k[i]
        <<std::endl;
    }
    out
      <<std::endl
      <<std::endl
      <<std::endl;
    delete oscilo;

  }
}



void ch11phe_ypos(const TFile&f, const std::string& outf){
    TH1F* h=dynamic_cast<TH1F*>(f.FindObjectAny("PhElectrAbsSinglePartBeam_ch_11"));
    if(h==nullptr){std::cout<<outf<<std::endl;return;}
    std::cout<<outf<<"  "<<h->GetMean()<<"  "<<h->GetRMS()<<std::endl;
}


int PostAnalysis(){
  TFile *tfileo=new TFile("temp.root","recreate");
  for(int run_i=500;run_i<1000;++run_i){
    std::string filename=Form("run_%d.lst.root",run_i);
    TFile nonfft50(filename.c_str(), "READ");
    tfileo->cd();
    if(nonfft50.GetSize()<=0)continue;
    TimeRes  (nonfft50,"___timeres.dat",Form("%d",run_i));
    Eff_Ineff(nonfft50,Form("%d-effinef.dat",run_i));
    //ch11phe_ypos(nonfft50,Form("%d",run_i));
  }

  //PedestalCalc(f);
  //GainCalib(TFile ("nonfft-50.root", "READ"));

  //new TBrowser();
  //exit(0);
  tfileo->Write();
  tfileo->Close();
  return 0;
}

int main(){
  PostAnalysis();
  return 0;
}
