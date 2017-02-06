#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include<Histos.hh>

#include<gsl/gsl_fft_halfcomplex_float.h>
#include<gsl/gsl_fft_real_float.h>
#include<gsl/gsl_fft_halfcomplex.h>
#include<gsl/gsl_fft_real.h>

class Signal{
  public:
    Signal(){
      fSampl.resize(102800);
    }
    void Refill(){
      Square();
      //Zeroes();
      Noise();
    }
    void Print(){
      for(int i=0;i<fSampl.size();++i){
        double t=i/100.;
        std::cout<<t<<"   "<<fSampl[i]<<std::endl;
      }
    }
    void Sine(double freq=1){
      double phy0=2*acos(-1)*rand()/RAND_MAX;
      for(int i=0;i<fSampl.size();++i){
        double t=i/100.;
        fSampl[i]+=sin(t*freq/2./acos(-1)+phy0)*100;
      }
    }
    void SigDump(){
      std::fstream f("sig.dat",std::fstream::out);
      for(int i=0;i<fSampl.size();++i){
        f<<fSampl[i]<<std::endl;
      }
    }
    void FFTDump(){
      std::vector<double> fft=fSampl;
      fft.resize(131072,0);
      gsl_fft_real_radix2_transform(&fft[0],1,fft.size());
      std::fstream f("fft.dat",std::fstream::out);
      f<<fft[0]<<"  "<<0<<std::endl;
      for(int i=1;i<fft.size()/2;++i){
        f
          <<sqrt(fft[i]*fft[i]+fft[fft.size()-i]*fft[fft.size()-i])
          <<"  "
          <<atan2(fft[fft.size()-i],fft[i])
          <<std::endl;
      }
      f<<*fft.rbegin()<<"  "<<0<<std::endl;
    }
    std::vector<double>& GetSamples(){return fSampl;}
  private:
    void Zeroes(){
      for(int i=0;i<fSampl.size();++i){
        fSampl[i]=0;
      }
    }
    void Square(int step=12/*samples*/){
      double x1=100 , x2=x1+step;
      double y1=1000, y2=0;
      for(int i=0;i<fSampl.size();++i){
        double t=i/100.;
        if(t<x1)
          fSampl[i]=y1;
        else if(t<x2)
          fSampl[i]=y1-(y1-y2)/(x1-x2)*(x1-t);
        else if(t<1024-x2)
          fSampl[i]=y2;
        else if(t<1024-x1)
          fSampl[i]=y1-(y1-y2)/(x1-x2)*(x1+t-1024);
        else fSampl[i]=y1;
      }
    }
    void Noise(double ampl=10){
      for(auto it=fSampl.begin();it!=fSampl.end();++it){
        if(rand()>RAND_MAX/2)
          *it+=-log(1.*rand()/RAND_MAX)*ampl;
        else
          *it-=-log(1.*rand()/RAND_MAX)*ampl;
      }
    }
    std::vector<double> fSampl;
};

class Channel{
  public:
    Channel(Signal& s):fDat(s.GetSamples()){
      fShift=int(350.*rand()/RAND_MAX);
      fSamples.resize(1024);
      for(int s=0;s<1024;++s){
        fSamples[s]=fDat[s*100+fShift];
      }
    }
    void CalcT0Thres(){
      for(int s=0;s<1024;++s){
        if(fSamples[s]<500){
          fT0=s;
          break;
        }
      }
    }
    double GetT0(){return fT0;}
    double GetShift(){return fShift;}
    void CalcT0Slope(){
      double s=0;
      double sx=0;
      double sxx=0;
      double sxy=0;
      double sy=0;
      int t=0;
      while(fSamples[t]>750)++t;
      while(fSamples[t]>250){
        double sig=1;
        double invssig=1./sig/sig;
        s  +=invssig;
        sx +=t*invssig;
        sxx+=t*t*invssig;
        sxy+=t*fSamples[t]*invssig;
        sy +=fSamples[t]*invssig;
        ++t;
      }
      double delta=s*sxx-sx*sx;
      double a=(sxx*sy-sx*sxy)/delta;
      double b=(s*sxy-sx*sy)/delta;
      fT0=(500-a)/b;
    }
    const auto& GetSamples(){return fSamples;}
    void CalcT0Sine(int f=26){
      double re=0,im=0;
      int nDat=fSamples.size();
      const double df=-2*acos(-1.)/nDat;
      for(unsigned t=0;t<nDat;++t){
        re+=fSamples[t]*cos(df*t*f);
        im+=fSamples[t]*sin(df*t*f);
      }
      fPhy=atan2(im,re);
      //fPhy=atan(re/im);
    }
    double GetPhy(){return fPhy;}
    void FFTDump(const std::string& fn){
      std::vector<double> fft=fSamples;
      //fft.resize(131072,0);
      gsl_fft_real_radix2_transform(&fft[0],1,fft.size());
      std::fstream f(fn,std::fstream::out);
      f<<fft[0]<<"  "<<0<<std::endl;
      for(int i=1;i<fft.size()/2;++i){
        //double phy=atan2(fft[fft.size()-i],fft[i]);
        double phy=atan(fft[i]/fft[fft.size()-i]);
        f
          //<<fft[i]<<"   "<< fft[fft.size()-i]
          <<sqrt(fft[i]*fft[i]+fft[fft.size()-i]*fft[fft.size()-i])
          <<"  "
          <<(phy<0?2*acos(-1)+phy:phy)
          <<std::endl;
      }
      f<<fft[fft.size()/2]<<"  "<<0<<std::endl;
    }
    void SigDump(const std::string& fn){
      std::fstream f(fn,std::fstream::out);
      for(int i=0;i<fSamples.size();++i){
        f<<fSamples[i]<<std::endl;
      }
    }
  private:
    std::vector<double>&fDat;
    std::vector<double>fSamples;
    int fShift;
    double fT0;
    double fPhy;
};

int main(){
  srand(time(NULL));
  Signal sig;
  Histos hists("h.root");
  sig.Refill();
  sig.Sine();
  sig.SigDump();
  sig.FFTDump();
  Channel c1(sig);
  Channel c2(sig);
  c1.FFTDump("ch1_fft.dat");
  c1.SigDump("ch1_sig.dat");
  c2.FFTDump("ch2_fft.dat");
  c2.SigDump("ch2_sig.dat");

  for(int i=0;i<10000;++i){
    sig.Refill();
    Channel ch1(sig);
    Channel ch2(sig);
    ch1.CalcT0Thres();
    ch2.CalcT0Thres();
    hists.hist1f_TrigIntrThres[0]->Fill(ch1.GetShift()/100.+ch1.GetT0());
    hists.hist1f_TrigDiffThres->Fill(ch1.GetT0()-ch2.GetT0());
    ch1.CalcT0Slope();
    ch2.CalcT0Slope();
    hists.hist1f_TrigIntrSlope[0]->Fill(ch1.GetShift()/100.+ch1.GetT0());
    hists.hist1f_TrigDiffSlope->Fill(ch1.GetT0()-ch2.GetT0());
    sig.Sine(1);
    Channel chSine1(sig);
    Channel chSine2(sig);
    chSine1.CalcT0Sine();
    chSine2.CalcT0Sine();

    hists.hist2f_phy_dif->Fill(chSine1.GetShift()-chSine2.GetShift(),fmod(chSine1.GetPhy()-chSine2.GetPhy()+2*acos(-1),2*acos(-1)));

    if(i==0){
      const auto&sineref=chSine1.GetSamples();
      for(int t=0;t<sineref.size();++t){
        hists.hist2f_TrigCum[0]->Fill(t,sineref[t]);
      }
    }
  }
  return 0;
}
