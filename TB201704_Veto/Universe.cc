#include"Universe.hh"

  Universe&
Universe::GetInstance()
{
  static Universe a;
  return a;
}

  void
Universe::LinksNames()
{
  fLinkRO2DetCh[eROCh::eB1S1    ]=eDetCh::e1 ;
  fLinkRO2DetCh[eROCh::eB1S2    ]=eDetCh::e2 ;
  fLinkRO2DetCh[eROCh::eB1S3    ]=eDetCh::e3 ;
  fLinkRO2DetCh[eROCh::eB1S4    ]=eDetCh::e4 ;
  fLinkRO2DetCh[eROCh::eB2S1    ]=eDetCh::e5 ;
  fLinkRO2DetCh[eROCh::eB2S2    ]=eDetCh::e6 ;
  fLinkRO2DetCh[eROCh::eB2S3    ]=eDetCh::e7 ;
  fLinkRO2DetCh[eROCh::eB2S4    ]=eDetCh::e8 ;
  fLinkRO2DetCh[eROCh::eB3S1    ]=eDetCh::e9 ;
  fLinkRO2DetCh[eROCh::eB3S2    ]=eDetCh::e10;
  fLinkRO2DetCh[eROCh::eB3S3    ]=eDetCh::e11;
  fLinkRO2DetCh[eROCh::eB3S4    ]=eDetCh::e12;
  fLinkRO2DetCh[eROCh::eB4S1    ]=eDetCh::e13;
  fLinkRO2DetCh[eROCh::eB4S2    ]=eDetCh::e14;
  fLinkRO2DetCh[eROCh::eB4S3    ]=eDetCh::e15;
  fLinkRO2DetCh[eROCh::eB4S4    ]=eDetCh::e16;
  fLinkRO2DetCh[eROCh::eB5S1    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eB5S2    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eB5S3    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eB5S4    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eBTFCalo ]=eDetCh::eBTFCalo;


  fROChNames[eROCh::eB1S1    ]="Board1SiPM1";
  fROChNames[eROCh::eB1S2    ]="Board1SiPM2";
  fROChNames[eROCh::eB1S3    ]="Board1SiPM3";
  fROChNames[eROCh::eB1S4    ]="Board1SiPM4";
  fROChNames[eROCh::eB2S1    ]="Board2SiPM1";
  fROChNames[eROCh::eB2S2    ]="Board2SiPM2";
  fROChNames[eROCh::eB2S3    ]="Board2SiPM3";
  fROChNames[eROCh::eB2S4    ]="Board2SiPM4";
  fROChNames[eROCh::eB3S1    ]="Board3SiPM1";
  fROChNames[eROCh::eB3S2    ]="Board3SiPM2";
  fROChNames[eROCh::eB3S3    ]="Board3SiPM3";
  fROChNames[eROCh::eB3S4    ]="Board3SiPM4";
  fROChNames[eROCh::eB4S1    ]="Board4SiPM1";
  fROChNames[eROCh::eB4S2    ]="Board4SiPM2";
  fROChNames[eROCh::eB4S3    ]="Board4SiPM3";
  fROChNames[eROCh::eB4S4    ]="Board4SiPM4";
  //fROChNames[eROCh::eB5S1    ]="Board5SiPM1";
  //fROChNames[eROCh::eB5S2    ]="Board5SiPM2";
  //fROChNames[eROCh::eB5S3    ]="Board5SiPM3";
  //fROChNames[eROCh::eB5S4    ]="Board5SiPM4";
  fROChNames[eROCh::eBTFCalo ]="BTFCalo";

  for(auto it=fLinkRO2DetCh.begin();it!=fLinkRO2DetCh.end();++it){
    fLinkDet2ROCh.emplace(it->second,it->first);
  }
  //fROChNames
  //fDetChNames

}
