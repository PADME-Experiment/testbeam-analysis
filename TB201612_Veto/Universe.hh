#ifndef _Universe_hh_
#define _Universe_hh_ 0
#include<string>
#include<map>

class Universe{
  public:
    enum class eROCh{
      eFirst=0,
      eX1=0,
      eX2, eX3, eX4, eX5, eX6, eX7, eX8, eY1, eY2, eY3, eY4,
      eY5, eY6, eY7, eY8, eH1, eH2, eH3, eH4, eH5, eH6, eH7,
      eH8, eCalo  , eTerm  , eAntena,
      eLast
    };
    enum class eDetCh{
      eFirst=0,
      eVTU, eVBU, eVTD, eVBD,
      eD1,eD2,eD3,eD4,eD5,eD6,eD7,eD8,
      eCalo,
      eLast,
      NC
    };
    static Universe& GetInstance();
    const std::string&GetROName(int i)const{
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
