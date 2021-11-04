#ifndef _VSamplingChannel_hh_
#define _VSamplingChannel_hh_
#include<string>
#include<map>
typedef unsigned short int UShort_t;
typedef short int          Short_t ;

class VSamplingChannel{
  public:
    virtual ~VSamplingChannel(){}
    VSamplingChannel():
      fSamples(nullptr),
      fPedCalDat(nullptr),
      fNSamples(0),
      fT0(0),
      fType("DefaultType") {}
    //VSamplingChannel(UShort_t n,Short_t* arr){VSamplingChannel(); SetNSamples(n); SetSamplesArr(arr);}
    void SetNSamples  (UShort_t n){fNSamples=n;}
    void SetSamplesArr(Short_t* arr){fSamples=arr;}
    void SetSamples(UShort_t n,Short_t* arr){SetNSamples(n); SetSamplesArr(arr);}
    void SetStartIndexCell(unsigned short cell_i){fStartIndexCell=cell_i;}
    unsigned short GetStartIndexCell(){return fStartIndexCell;}
    int  GetT0()const {return fT0;}
    void SetT0(int t){fT0=t;}
    Short_t GetSampT0Cor(int t)const {t-=fT0;return GetSamp(t);}
    Short_t GetSampNoCellPedCor(int t)const {
      return t>=0&&t<fNSamples?
        fSamples[t]
        :0;}
    Short_t GetSamp     (long long int t)const {
      return t>=0&&t<fNSamples?
        fSamples[t]
        -fPedCalDat[(t+fStartIndexCell)%1024][0]
        -fPedCalDat[(t+fStartIndexCell)%1024][1]*t
        -fPedCalDat[(t+fStartIndexCell)%1024][2]*t*t
        -fPedCalDat[(t+fStartIndexCell)%1024][3]*t*t*t
        -fPedCalDat[(t+fStartIndexCell)%1024][4]*t*t*t*t
        -fPedCalDat[(t+fStartIndexCell)%1024][5]*t*t*t*t*t
        :0;}
    void SetPedestalCalibration(double caldat[1024][6]){fPedCalDat=caldat;}
    UShort_t GetNSamples()const{return fNSamples;}
    void SetName(const std::string&n){fName=n;}
    const std::string& GetName()const{return fName;}
    const std::string& GetType()const{return fType;}

  protected:
    Short_t* fSamples;  ///< [ADU]
    double  (*fPedCalDat)[6];
    unsigned short fStartIndexCell;
    UShort_t fNSamples;
    int fT0;
    std::string fName;
    std::string fType;
};
#endif
