
Double_t signal_func(Double_t *x,Double_t *par){
  Double_t f;
  Double_t y;
  Double_t c;
  //Parameter description:
  //par[0] - Normalization (~Amplitude)
  //par[1] - start of the signal (t0)
  //par[2] - scintillator decay time (tau)
  //par[3] - c = (1/tau - 1/b), b~ decay const for the PMT
  //   OR
  //par[3] - b: ~ decay const for the PMT
  //par[4] - a:  ~ signal width for PMT

  if(x[0] < par[1]) {
    f=0.;
  } else {
    y = x[0] - par[1];
    c = (1./par[2]) - (1./par[3]);
    //c = par[3] ;


    /* f = - (par[0]/((par[4]*par[4]) + c * c ) ) * (exp(-y/par[2])/par[2]) * */
    /*   (exp(c*y)* */
    /*    ( (c*sin(par[4]*y)) - (par[4]*cos(par[4]*y)) )  + par[4] ) ; */



    if(par[4]*y < M_PI) {
      /* f = - par[0] * (exp(-y/par[2])/par[2]) *  */
      /*     (exp(c*y)* */
      /*      ( (c*sin(par[4]*y)) - (par[4]*cos(par[4]*y)) )  + par[4] ) ; */

      f = - (par[0]/((par[4]*par[4]) + c * c ) ) * (exp(-y/par[2])/par[2]) *
        (exp(c*y)*
         ( (c*sin(par[4]*y)) - (par[4]*cos(par[4]*y)) )  + par[4] ) ;

    } else {
      /* f = - par[0] * (exp(-y/par[2])/par[2]) *  */
      /*     ( (exp(c* M_PI/par[4])*par[4])+ par[4] ) ; */

      f = - (par[0]/((par[4]*par[4]) + c * c ) ) * (exp(-y/par[2])/par[2]) *
    ( (exp(c* M_PI/par[4])*par[4])+ par[4] ) ;


    }



  }
  return f;
} 



void sigfunc(){
    TF1 *func = new TF1("fit_func",signal_func,0,1024,5);
}
