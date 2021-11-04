#include"a.hh"
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


int GExpStep(int i){
  return (2<<(i/2)|(1<<(i/2))*(i%2))-2; // ~ (√2)^(i-2)-1
}







class Signal{
  public:
    Signal(){
      fSampl.resize(102900);
    }
    void Print(){
      for(int i=0;i<fSampl.size();++i){
        double t=i/100.;
        std::cout<<t<<"   "<<fSampl[i]<<std::endl;
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

    void Zerofy(){
      for(int i=0;i<fSampl.size();++i){
        fSampl[i]=0;
      }
    }
    void Square(int step=1200/*samples*/){
      double x1=150-step/200. , x2=150+step/200.;
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
    double Sine(double tc=1,double ampl=100){
      double phy=rand()/RAND_MAX; //[0;1)
      for(int i=0;i<fSampl.size();++i){
        double t=i/100.;
        fSampl[i]+=sin(2*acos(-1)*(t/tc+phy))*ampl;
      }
      return phy;
    }
  private:
    std::vector<double> fSampl;
};

class Channel{
  public:
    Channel(Signal& s):fDat(s.GetSamples()){
      fShift=int(500.*rand()/RAND_MAX);
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
      --t;
      int count=0;
      do{
        double sig=1;
        double invssig=1./sig/sig;
        s  +=invssig;
        sx +=t*invssig;
        sxx+=t*t*invssig;
        sxy+=t*fSamples[t]*invssig;
        sy +=fSamples[t]*invssig;
        ++count;
        ++t;
      } while(fSamples[t]>250||count<2);
      double delta=s*sxx-sx*sx;
      double a=(sxx*sy-sx*sxy)/delta;
      double b=(s*sxy-sx*sy)/delta;
      fT0=(500-a)/b;
    }
    const auto& GetSamples(){return fSamples;}
    double CalcT0Sine(double tau){
      double re=0,im=0;
      int nDat=fSamples.size();
      const double df=-2*acos(-1.)/nDat;
      for(unsigned t=0;t<nDat;++t){
        re+=fSamples[t]*cos(df*t/tau);
        im+=fSamples[t]*sin(df*t/tau);
      }
      double phy=atan2(im,re)/2./acos(-1);
      double rho=sqrt(re*re+im*im);
      //double phy=atan(re/im);
      fT0=tau*phy;
    }
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
};

void CalcSQN(Histos& hists){
  Signal sig;

  std::fstream sqnIntrThres("sqnIntrThres",std::fstream::out);
  std::fstream sqnDiffThres("sqnDiffThres",std::fstream::out);
  std::fstream sqnIntrSlope("sqnIntrSlope",std::fstream::out);
  std::fstream sqnDiffSlope("sqnDiffSlope",std::fstream::out);

  for(int slope_i=0;slope_i<gSqNoiseSlopes;++slope_i){
    for(int noise_i=0;noise_i<gSqNoiseNoises;++noise_i){
      std::cerr
        <<"slope "<<slope_i<<"/"<<gSqNoiseSlopes
        <<"   "
        <<"noise "<<noise_i<<"/"<<gSqNoiseNoises
        <<std::endl;
      sig.Square(GExpStep(slope_i));
      sig.Noise (GExpStep(noise_i));
      for(int i=0;i<5000;++i){
        Channel ch1(sig),ch2(sig);
        ch1.CalcT0Thres(); ch2.CalcT0Thres();
        hists.hist1f_SqNoiseIntrThres[slope_i][noise_i]->Fill(ch1.GetT0()+ch1.GetShift()/100.);
        hists.hist1f_SqNoiseDiffThres[slope_i][noise_i]->Fill((ch1.GetT0()-ch2.GetT0())/sqrt(2.));
        ch1.CalcT0Slope(); ch2.CalcT0Slope();
        hists.hist1f_SqNoiseIntrSlope[slope_i][noise_i]->Fill(ch1.GetT0()+ch1.GetShift()/100.);
        hists.hist1f_SqNoiseDiffSlope[slope_i][noise_i]->Fill((ch1.GetT0()-ch2.GetT0())/sqrt(2.));
        if(i==0){
          const auto&chref=ch1.GetSamples();
          for(int t=0;t<chref.size();++t){
            hists.hist2f_SqNoiseOsc[slope_i][noise_i]->SetPoint(t,t,chref[t]);
          }
        }
      }

      if(hists.hist1f_SqNoiseIntrThres[slope_i][noise_i]->Integral()>hists.hist1f_SqNoiseIntrThres[slope_i][noise_i]->GetEntries()*.85)sqnIntrThres<<GExpStep(slope_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseIntrThres[slope_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseIntrThres[slope_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SqNoiseDiffThres[slope_i][noise_i]->Integral()>hists.hist1f_SqNoiseDiffThres[slope_i][noise_i]->GetEntries()*.85)sqnDiffThres<<GExpStep(slope_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseDiffThres[slope_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseDiffThres[slope_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SqNoiseIntrSlope[slope_i][noise_i]->Integral()>hists.hist1f_SqNoiseIntrSlope[slope_i][noise_i]->GetEntries()*.85)sqnIntrSlope<<GExpStep(slope_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseIntrSlope[slope_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseIntrSlope[slope_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SqNoiseDiffSlope[slope_i][noise_i]->Integral()>hists.hist1f_SqNoiseDiffSlope[slope_i][noise_i]->GetEntries()*.85)sqnDiffSlope<<GExpStep(slope_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseDiffSlope[slope_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseDiffSlope[slope_i][noise_i]->GetStdDevError()<<std::endl;

    }
    sqnIntrThres<<std::endl;
    sqnDiffThres<<std::endl;
    sqnIntrSlope<<std::endl;
    sqnDiffSlope<<std::endl;
  }
  sqnIntrThres.close();
  sqnDiffThres.close();
  sqnIntrSlope.close();
  sqnDiffSlope.close();
}
void CalcSin(Histos& hists){
  Signal sig;

  std::fstream sinIntrThres("sinIntrThres",std::fstream::out);
  std::fstream sinDiffThres("sinDiffThres",std::fstream::out);
  std::fstream sinIntrSlope("sinIntrSlope",std::fstream::out);
  std::fstream sinDiffSlope("sinDiffSlope",std::fstream::out);
  std::fstream sinIntrSine("sinIntrSine",std::fstream::out);
  std::fstream sinDiffSine("sinDiffSine",std::fstream::out);

  for(int sine_i=0;sine_i<gNSines;++sine_i){
    for(int noise_i=0;noise_i<gSqNoiseNoises;++noise_i){
      std::cerr
        <<"sine"<<sine_i<<"/"<<gNSines
        <<"   "
        <<"noise "<<noise_i<<"/"<<gSqNoiseNoises
        <<std::endl;
      sig.Square(GExpStep(300));
      double const tau=(GExpStep(sine_i)+1)/3.;
      double phy0=sig.Sine(tau,100);
      sig.Noise (GExpStep(noise_i));
      for(int i=0;i<500;++i){
        Channel ch1(sig),ch2(sig);
        ch1.CalcT0Thres(); ch2.CalcT0Thres();
        hists.hist1f_SineIntrThres[sine_i][noise_i]->Fill(ch1.GetShift()/100.+ch1.GetT0());
        hists.hist1f_SineDiffThres[sine_i][noise_i]->Fill((ch1.GetT0()-ch2.GetT0())/sqrt(2.));
        ch1.CalcT0Slope(); ch2.CalcT0Slope();
        hists.hist1f_SineIntrSlope[sine_i][noise_i]->Fill(ch1.GetShift()/100.+ch1.GetT0());
        hists.hist1f_SineDiffSlope[sine_i][noise_i]->Fill((ch1.GetT0()-ch2.GetT0())/sqrt(2.));
        ch1.CalcT0Sine(tau); ch2.CalcT0Sine(tau);
        hists.hist1f_SineIntrFFTPhase[sine_i][noise_i]->Fill(ch1.GetT0()+phy0*tau);
        //std::cout<<ch1.GetShift()/100.+ch1.GetT0()<<std::endl;
        hists.hist2f_SineDiffFFTPhase[sine_i][noise_i]->Fill((ch1.GetT0()-ch2.GetT0())/sqrt(2.),ch1.GetShift()/100.-ch2.GetShift()/100.);
        if(i==0){
          const auto&chref=ch1.GetSamples();
          for(int t=0;t<chref.size();++t){
            hists.hist2f_SineOsc[sine_i][noise_i]->SetPoint(t,t,chref[t]);
          }
        }
      }

      if(hists.hist1f_SqNoiseIntrThres[sine_i][noise_i]->Integral()>hists.hist1f_SqNoiseIntrThres[sine_i][noise_i]->GetEntries()*.85)sinIntrThres<<GExpStep(sine_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseIntrThres[sine_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseIntrThres[sine_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SqNoiseDiffThres[sine_i][noise_i]->Integral()>hists.hist1f_SqNoiseDiffThres[sine_i][noise_i]->GetEntries()*.85)sinDiffThres<<GExpStep(sine_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseDiffThres[sine_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseDiffThres[sine_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SqNoiseIntrSlope[sine_i][noise_i]->Integral()>hists.hist1f_SqNoiseIntrSlope[sine_i][noise_i]->GetEntries()*.85)sinIntrSlope<<GExpStep(sine_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseIntrSlope[sine_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseIntrSlope[sine_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SqNoiseDiffSlope[sine_i][noise_i]->Integral()>hists.hist1f_SqNoiseDiffSlope[sine_i][noise_i]->GetEntries()*.85)sinDiffSlope<<GExpStep(sine_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SqNoiseDiffSlope[sine_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SqNoiseDiffSlope[sine_i][noise_i]->GetStdDevError()<<std::endl;
      if(hists.hist1f_SineIntrFFTPhase[sine_i][noise_i]->Integral()>hists.hist1f_SineIntrFFTPhase[sine_i][noise_i]->GetEntries()*.85)sinIntrSlope<<GExpStep(sine_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SineIntrFFTPhase[sine_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SineIntrFFTPhase[sine_i][noise_i]->GetStdDevError()<<std::endl;
      //if(hists.hist1f_SineDiffFFTPhase[sine_i][noise_i]->Integral()>hists.hist1f_SineDiffFFTPhase[sine_i][noise_i]->GetEntries()*.85)sinDiffSlope<<GExpStep(sine_i)<<"  "<<GExpStep(noise_i)<<"   "<<hists.hist1f_SineDiffFFTPhase[sine_i][noise_i]->GetStdDev()<<"   "<<hists.hist1f_SineDiffFFTPhase[sine_i][noise_i]->GetStdDevError()<<std::endl;

    }
    sinIntrThres<<std::endl;
    sinDiffThres<<std::endl;
    sinIntrSlope<<std::endl;
    sinDiffSlope<<std::endl;
    sinIntrSine <<std::endl;
    sinDiffSine <<std::endl;
  }
  sinIntrThres.close();
  sinDiffThres.close();
  sinIntrSlope.close();
  sinDiffSlope.close();
  sinIntrSine.close();
  sinDiffSine.close();
}

int main(){
  srand(time(NULL));
  Histos hists("h.root");
  //CalcSQN(hists);
  CalcSin(hists);

  return 0;
}
