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
  fLinkRO2DetCh[eROCh::eX1    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX2    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX3    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX4    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX5    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX6    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX7    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX8    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY1    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY2    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY3    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY4    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY5    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY6    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY7    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY8    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eH1    ]=eDetCh::eVBD;
  fLinkRO2DetCh[eROCh::eH2    ]=eDetCh::eVTD;
  fLinkRO2DetCh[eROCh::eH3    ]=eDetCh::eVTU;
  fLinkRO2DetCh[eROCh::eH4    ]=eDetCh::eD2;
  fLinkRO2DetCh[eROCh::eH5    ]=eDetCh::eVBU;
  fLinkRO2DetCh[eROCh::eH6    ]=eDetCh::eD6;
  fLinkRO2DetCh[eROCh::eH7    ]=eDetCh::eD4;
  fLinkRO2DetCh[eROCh::eH8    ]=eDetCh::eD8;
  fLinkRO2DetCh[eROCh::eCalo  ]=eDetCh::eCalo;
  fLinkRO2DetCh[eROCh::eTerm  ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eAntena]=eDetCh::NC;

  fROChNames[eROCh::eX1    ]="00_X1_D2";
  fROChNames[eROCh::eX2    ]="01_X2_NC";
  fROChNames[eROCh::eX3    ]="02_X3_D6";
  fROChNames[eROCh::eX4    ]="03_X4_VBD";
  fROChNames[eROCh::eX5    ]="04_X5_VBU";
  fROChNames[eROCh::eX6    ]="05_X6_D4";
  fROChNames[eROCh::eX7    ]="06_X7_NC";
  fROChNames[eROCh::eX8    ]="07_X8_D8";
  fROChNames[eROCh::eY1    ]="08_Y1_D7Al";
  fROChNames[eROCh::eY2    ]="09_Y2_NC";
  fROChNames[eROCh::eY3    ]="10_Y3_D3Al";
  fROChNames[eROCh::eY4    ]="11_Y4_VTU";
  fROChNames[eROCh::eY5    ]="12_Y5_VTD";
  fROChNames[eROCh::eY6    ]="13_Y6_D5Al";
  fROChNames[eROCh::eY7    ]="14_Y7_NC";
  fROChNames[eROCh::eY8    ]="15_Y8_D1Al";
  fROChNames[eROCh::eH1    ]="16_H1_VBD";
  fROChNames[eROCh::eH2    ]="17_H2_VTD";
  fROChNames[eROCh::eH3    ]="18_H3_VTU";
  fROChNames[eROCh::eH4    ]="19_H4_D2";
  fROChNames[eROCh::eH5    ]="20_H5_VBU";
  fROChNames[eROCh::eH6    ]="21_H6_D6";
  fROChNames[eROCh::eH7    ]="22_H7_D4";
  fROChNames[eROCh::eH8    ]="23_H8_D8";
  fROChNames[eROCh::eCalo  ]="Calorimeter";
  fROChNames[eROCh::eTerm  ]="Terminated";
  fROChNames[eROCh::eAntena]="Antena";

  for(auto it=fLinkRO2DetCh.begin();it!=fLinkRO2DetCh.end();++it){
    fLinkDet2ROCh.emplace(it->second,it->first);
  }
  //fROChNames
  //fDetChNames

}
