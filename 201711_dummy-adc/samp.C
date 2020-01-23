#include"TFile.h"
#include"TH1F.h"
#include<map>
#include<string>
#include<iostream>
void samp(){
  TFile inf("all.root");
  TFile outf("samp.root","recreate");
  ::std::map<::std::string,TH1F*> mapp;

//  mapp["TrigSigPedMean_0126"  ]=nullptr;
//  mapp["TrigSigPedSig_0126"   ]=nullptr;
  mapp["ChanSigPedMean_0126"  ]=nullptr;
  mapp["ChanSigPedSig_0126"   ]=nullptr;
  mapp["ChanOscSigY_0126"     ]=nullptr;
//  mapp["TrigSigPedMean_0182"  ]=nullptr;
//  mapp["TrigSigPedSig_0182"   ]=nullptr;
  mapp["ChanSigPedMean_0182"  ]=nullptr;
  mapp["ChanSigPedSig_0182"   ]=nullptr;
  mapp["ChanOscSigY_0182"     ]=nullptr;
//  mapp["TrigSigPedMean_0183"  ]=nullptr;
//  mapp["TrigSigPedSig_0183"   ]=nullptr;
  mapp["ChanSigPedMean_0183"  ]=nullptr;
  mapp["ChanSigPedSig_0183"   ]=nullptr;
  mapp["ChanOscSigY_0183"     ]=nullptr;
//  mapp["TrigSigPedMean_0184"  ]=nullptr;
//  mapp["TrigSigPedSig_0184"   ]=nullptr;
  mapp["ChanSigPedMean_0184"  ]=nullptr;
  mapp["ChanSigPedSig_0184"   ]=nullptr;
  mapp["ChanOscSigY_0184"     ]=nullptr;
//  mapp["TrigSigPedMean_0187"  ]=nullptr;
//  mapp["TrigSigPedSig_0187"   ]=nullptr;
  mapp["ChanSigPedMean_0187"  ]=nullptr;
  mapp["ChanSigPedSig_0187"   ]=nullptr;
  mapp["ChanOscSigY_0187"     ]=nullptr;
//  mapp["TrigSigPedMean_0188"  ]=nullptr;
//  mapp["TrigSigPedSig_0188"   ]=nullptr;
  mapp["ChanSigPedMean_0188"  ]=nullptr;
  mapp["ChanSigPedSig_0188"   ]=nullptr;
  mapp["ChanOscSigY_0188"     ]=nullptr;
//  mapp["TrigSigPedMean_0189"  ]=nullptr;
//  mapp["TrigSigPedSig_0189"   ]=nullptr;
  mapp["ChanSigPedMean_0189"  ]=nullptr;
  mapp["ChanSigPedSig_0189"   ]=nullptr;
  mapp["ChanOscSigY_0189"     ]=nullptr;
//  mapp["TrigSigPedMean_0190"  ]=nullptr;
//  mapp["TrigSigPedSig_0190"   ]=nullptr;
  mapp["ChanSigPedMean_0190"  ]=nullptr;
  mapp["ChanSigPedSig_0190"   ]=nullptr;
  mapp["ChanOscSigY_0190"     ]=nullptr;
//  mapp["TrigSigPedMean_0192"  ]=nullptr;
//  mapp["TrigSigPedSig_0192"   ]=nullptr;
  mapp["ChanSigPedMean_0192"  ]=nullptr;
  mapp["ChanSigPedSig_0192"   ]=nullptr;
  mapp["ChanOscSigY_0192"     ]=nullptr;
//  mapp["TrigSigPedMean_0193"  ]=nullptr;
//  mapp["TrigSigPedSig_0193"   ]=nullptr;
  mapp["ChanSigPedMean_0193"  ]=nullptr;
  mapp["ChanSigPedSig_0193"   ]=nullptr;
  mapp["ChanOscSigY_0193"     ]=nullptr;
//  mapp["TrigSigPedMean_0194"  ]=nullptr;
//  mapp["TrigSigPedSig_0194"   ]=nullptr;
  mapp["ChanSigPedMean_0194"  ]=nullptr;
  mapp["ChanSigPedSig_0194"   ]=nullptr;
  mapp["ChanOscSigY_0194"     ]=nullptr;
//  mapp["TrigSigPedMean_0195"  ]=nullptr;
//  mapp["TrigSigPedSig_0195"   ]=nullptr;
  mapp["ChanSigPedMean_0195"  ]=nullptr;
  mapp["ChanSigPedSig_0195"   ]=nullptr;
  mapp["ChanOscSigY_0195"     ]=nullptr;
//  mapp["TrigSigPedMean_0196"  ]=nullptr;
//  mapp["TrigSigPedSig_0196"   ]=nullptr;
  mapp["ChanSigPedMean_0196"  ]=nullptr;
  mapp["ChanSigPedSig_0196"   ]=nullptr;
  mapp["ChanOscSigY_0196"     ]=nullptr;
//  mapp["TrigSigPedMean_0202"  ]=nullptr;
//  mapp["TrigSigPedSig_0202"   ]=nullptr;
  mapp["ChanSigPedMean_0202"  ]=nullptr;
  mapp["ChanSigPedSig_0202"   ]=nullptr;
  mapp["ChanOscSigY_0202"     ]=nullptr;
//  mapp["TrigSigPedMean_0203"  ]=nullptr;
//  mapp["TrigSigPedSig_0203"   ]=nullptr;
  mapp["ChanSigPedMean_0203"  ]=nullptr;
  mapp["ChanSigPedSig_0203"   ]=nullptr;
  mapp["ChanOscSigY_0203"     ]=nullptr;
//  mapp["TrigSigPedMean_0204"  ]=nullptr;
//  mapp["TrigSigPedSig_0204"   ]=nullptr;
  mapp["ChanSigPedMean_0204"  ]=nullptr;
  mapp["ChanSigPedSig_0204"   ]=nullptr;
  mapp["ChanOscSigY_0204"     ]=nullptr;
//  mapp["TrigSigPedMean_0205"  ]=nullptr;
//  mapp["TrigSigPedSig_0205"   ]=nullptr;
  mapp["ChanSigPedMean_0205"  ]=nullptr;
  mapp["ChanSigPedSig_0205"   ]=nullptr;
  mapp["ChanOscSigY_0205"     ]=nullptr;
//  mapp["TrigSigPedMean_0206"  ]=nullptr;
//  mapp["TrigSigPedSig_0206"   ]=nullptr;
  mapp["ChanSigPedMean_0206"  ]=nullptr;
  mapp["ChanSigPedSig_0206"   ]=nullptr;
  mapp["ChanOscSigY_0206"     ]=nullptr;
//  mapp["TrigSigPedMean_0207"  ]=nullptr;
//  mapp["TrigSigPedSig_0207"   ]=nullptr;
  mapp["ChanSigPedMean_0207"  ]=nullptr;
  mapp["ChanSigPedSig_0207"   ]=nullptr;
  mapp["ChanOscSigY_0207"     ]=nullptr;
//  mapp["TrigSigPedMean_0208"  ]=nullptr;
//  mapp["TrigSigPedSig_0208"   ]=nullptr;
  mapp["ChanSigPedMean_0208"  ]=nullptr;
  mapp["ChanSigPedSig_0208"   ]=nullptr;
  mapp["ChanOscSigY_0208"     ]=nullptr;
//  mapp["TrigSigPedMean_0209"  ]=nullptr;
//  mapp["TrigSigPedSig_0209"   ]=nullptr;
  mapp["ChanSigPedMean_0209"  ]=nullptr;
  mapp["ChanSigPedSig_0209"   ]=nullptr;
  mapp["ChanOscSigY_0209"     ]=nullptr;
//  mapp["TrigSigPedMean_0212"  ]=nullptr;
//  mapp["TrigSigPedSig_0212"   ]=nullptr;
  mapp["ChanSigPedMean_0212"  ]=nullptr;
  mapp["ChanSigPedSig_0212"   ]=nullptr;
  mapp["ChanOscSigY_0212"     ]=nullptr;
//  mapp["TrigSigPedMean_0218"  ]=nullptr;
//  mapp["TrigSigPedSig_0218"   ]=nullptr;
  mapp["ChanSigPedMean_0218"  ]=nullptr;
  mapp["ChanSigPedSig_0218"   ]=nullptr;
  mapp["ChanOscSigY_0218"     ]=nullptr;
//  mapp["TrigSigPedMean_0220"  ]=nullptr;
//  mapp["TrigSigPedSig_0220"   ]=nullptr;
  mapp["ChanSigPedMean_0220"  ]=nullptr;
  mapp["ChanSigPedSig_0220"   ]=nullptr;
  mapp["ChanOscSigY_0220"     ]=nullptr;
//  mapp["TrigSigPedMean_0221"  ]=nullptr;
//  mapp["TrigSigPedSig_0221"   ]=nullptr;
  mapp["ChanSigPedMean_0221"  ]=nullptr;
  mapp["ChanSigPedSig_0221"   ]=nullptr;
  mapp["ChanOscSigY_0221"     ]=nullptr;
//  mapp["TrigSigPedMean_0222"  ]=nullptr;
//  mapp["TrigSigPedSig_0222"   ]=nullptr;
  mapp["ChanSigPedMean_0222"  ]=nullptr;
  mapp["ChanSigPedSig_0222"   ]=nullptr;
  mapp["ChanOscSigY_0222"     ]=nullptr;
//  mapp["TrigSigPedMean_0223"  ]=nullptr;
//  mapp["TrigSigPedSig_0223"   ]=nullptr;
  mapp["ChanSigPedMean_0223"  ]=nullptr;
  mapp["ChanSigPedSig_0223"   ]=nullptr;
  mapp["ChanOscSigY_0223"     ]=nullptr;
//  mapp["TrigSigPedMean_0225"  ]=nullptr;
//  mapp["TrigSigPedSig_0225"   ]=nullptr;
  mapp["ChanSigPedMean_0225"  ]=nullptr;
  mapp["ChanSigPedSig_0225"   ]=nullptr;
  mapp["ChanOscSigY_0225"     ]=nullptr;



  for(auto it=mapp.begin();it!=mapp.end();++it){
    it->second=dynamic_cast<TH1F*>(inf.FindObjectAny(it->first.c_str()));
    if(it->second==nullptr){
      std::cerr<<"problem with "<<it->first<<std::endl;
      continue;
    }
  }
  for(auto it=mapp.begin();it!=mapp.end();++it){
    outf.WriteTObject(it->second);
  }

  outf.Save();
  outf.Close();
  inf.Close();




}

int main(){
  samp();
}
