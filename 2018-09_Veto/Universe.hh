#ifndef _Universe_hh_
#define _Universe_hh_ 0
#include<string>
#include<map>
#include"utlMessageBus.hh"

class Universe{
  public:
    enum class eROCh{
      eFirst=0,
      eB1S1=0,
      eB1S2,
      eB1S3,
      eB1S4,
      eB2S1,
      eB2S2,
      eB2S3,
      eB2S4,
      eB3S1,
      eB3S2,
      eB3S3,
      eB3S4,
      eB4S1,
      eB4S2,
      eB4S3,
      eB4S4,
      eBTFCalo,
      eB5S1,
      eB5S2,
      eB5S3,
      eB5S4,
      eLast
    };
    enum class eDetCh{
      eFirst=0,
      e1 =0,
      e2  ,
      e3  ,
      e4  ,
      e5  ,
      e6  ,
      e7  ,
      e8  ,
      e9  ,
      e10 ,
      e11 ,
      e12 ,
      e13 ,
      e14 ,
      e15 ,
      e16 ,
      eBTFCalo,
      eLast,
      NC
    };
    static Universe& GetInstance();
    const std::string&GetROName(int i)const{
      //INFO("GetROName ROCh"+std::to_string(i));
      return fROChNames.at(eROCh(i));
    }
  private:
    Universe(){
      LinksNames();
    }
    void LinksNames();
    std::map<eROCh , std::string>fROChNames;
    std::map<eDetCh, std::string>fDetChNames;
    std::map     <eROCh,eDetCh>  fLinkRO2DetCh;
    std::multimap<eDetCh,eROCh>  fLinkDet2ROCh;
};
#endif
