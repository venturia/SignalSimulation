#include <iostream>
#include "TF1.h"
#include "Pulse.h"
#include "TDatime.h"

Pulse::Pulse(const double bx, const double ratio): _bx(bx), _ratio(ratio) {

  TDatime now;
  char fname[300];
  sprintf(fname,"%s_peak",now.AsString());
  _peakfunc = new TF1(fname,this,&Pulse::peakpulse,-200e-9,500e-9,2);
  sprintf(fname,"%s_deco",now.AsString());
  _decofunc = new TF1(fname,this,&Pulse::decopulse,-200e-9,500e-9,2);

  _peakfunc->SetParameter(0,bx*ratio);
  _decofunc->SetParameter(0,bx*ratio);

  _peakfunc->SetNpx(50000);
  _decofunc->SetNpx(50000);
}

Pulse::~Pulse() {
  
  delete _peakfunc;
  delete _decofunc;

}

TF1* Pulse::peakPulse() const { return _peakfunc;}
TF1* Pulse::decoPulse() const { return _decofunc;}


double Pulse::peakpulse(const double* x, const double* p) const {

  double rat = (x[0]+p[1]*_bx)/p[0];
  return rat > 0 ? rat*exp(1.-rat) : 0.;

}

double Pulse::decopulse(const double* x, const double* p) const {

  /*
  double w1 = 1.5403;
  double w2 = -2.2073;
  double w3 = 0.7908;
  */
    
  double w1 = exp(1/_ratio-1)*_ratio;
  double w2 = -2*exp(-1.)*_ratio;
  double w3 = exp(-1/_ratio-1)*_ratio;
    
  double x1[1];
  double x2[1];
  double x3[1];
  x1[0] = x[0]+2*_bx-p[1]*_bx;
  x2[0] = x[0]+  _bx-p[1]*_bx;
  x3[0] = x[0]      -p[1]*_bx;

  double ppeak[2];
  ppeak[0] = p[0];
  ppeak[1] = 0;
  
  return w1*peakpulse(x1,ppeak)+w2*peakpulse(x2,ppeak)+w3*peakpulse(x3,ppeak);

}


