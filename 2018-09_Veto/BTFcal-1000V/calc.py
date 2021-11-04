from scipy.special import erf
from math import *

C=93.5468162769817

def gausI(a,x0,w,x):
    return - sqrt(pi)/sqrt(2)*a*w*erf((x0-x)/sqrt(2)/w)

def  gaus0(x):
    return  gausI(0.927253275580978  , -0.28593495643995 , 4.58043653458996,x)
def  gaus1(x):
    return  gausI(0.161092341028107  , 93.5468162769817  , 15.0154326892424,x)
def  gaus2(x):
    return  gausI(0.135253790366666  , 186.282680248253  , 19.9480252265804,x)
def  gaus3(x):
    return  gausI(0.0884672770426647 , 280.288969648445  , 25.5612499113796,x)
def  gaus4(x):
    return  gausI(0.056073201146668  , 373.430280516006  , 25.7556299269035,x)
def  gaus5(x):
    return  gausI(0.0303713337474879 , 464.204794188778  , 31.7794861066563,x)


def gausIAll(xl,xr):
    return gaus0(xr)-gaus0(xl)+gaus1(xr)-gaus1(xl)+gaus2(xr)-gaus2(xl)+gaus3(xr)-gaus3(xl)+gaus4(xr)-gaus4(xl)+gaus5(xr)-gaus5(xl)

def gausIAllwo1(xl,xr):
    return gaus0(xr)-gaus0(xl)+gaus2(xr)-gaus2(xl)+gaus3(xr)-gaus3(xl)+gaus4(xr)-gaus4(xl)+gaus5(xr)-gaus5(xl)

def gausI1(xl,xr):
    return gaus1(xr)-gaus1(xl)


T=30

print(1-gausI1(C-T,C+T)/gausI1(-inf,inf))
print(gausIAllwo1(C-T,C+T)/gausIAll(C-T,C+T))
