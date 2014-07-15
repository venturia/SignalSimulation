#include <iostream>
#include "Mobility.h"
#include "NewSensor.h"
#include "TDatime.h"
#include "TF1.h"
#include "TAxis.h"

NewSensor::NewSensor(): 
  _thickness(0.),_Vdepl(0.),_Vbias(0.),_Bfield(0.),_mobility(0), _Efieldfunc(0), 
  _mobilityfunc(0), _tanLAfunc(0), _parallelVdriftfunc(0), _invParallelVdriftfunc(0), 
  _driftTimefunc(0), _signalFractionfunc(0), _totalSignalfunc(0), _weightedPositionfunc(0),
  _chargeBarycenterfunc(0)
{ 
  TDatime now;
  char fname[300];
  sprintf(fname,"%s_decopulse",now.AsString());
  _decoPulse = new TF1(fname,"gaus",-200e-9,200e-9);
  _decoPulse->SetParameters(1.,0.,11e-9);

}

NewSensor::NewSensor(const double thick, const double vdepl, const Mobility* mobility):
  _thickness(thick), _Vdepl(vdepl), _Vbias(0.), _Bfield(0.), _mobility(mobility)
{ 
  TDatime now;
  char fname[300];
  sprintf(fname,"%s_efield",now.AsString());
  _Efieldfunc = new TF1(fname,this,&NewSensor::getEfieldfunc,0,_thickness,0);

  sprintf(fname,"%s_mob",now.AsString());
  _mobilityfunc = new TF1(fname,this,&NewSensor::getMobilityfunc,0,_thickness,0);

  sprintf(fname,"%s_tanla",now.AsString());
  _tanLAfunc = new TF1(fname,this,&NewSensor::getTanLAfunc,0,_thickness,0);

  sprintf(fname,"%s_parvdrift",now.AsString());
  _parallelVdriftfunc = new TF1(fname,this,&NewSensor::getParallelVdriftfunc,0,_thickness,0);

  sprintf(fname,"%s_invparvdrift",now.AsString());
  _invParallelVdriftfunc = new TF1(fname,this,&NewSensor::getInvParallelVdriftfunc,0,_thickness,0);

  sprintf(fname,"%s_drifttime",now.AsString());
  _driftTimefunc = new TF1(fname,this,&NewSensor::getDriftTimefunc,0,_thickness,0);

  sprintf(fname,"%s_signalfrac",now.AsString());
  _signalFractionfunc = new TF1(fname,this,&NewSensor::getSignalFractionfunc,0,_thickness,0);

  sprintf(fname,"%s_totsign",now.AsString());
  _totalSignalfunc = new TF1(fname,this,&NewSensor::getTotalSignalfunc,-100e-9,100e-9,0);

  sprintf(fname,"%s_weightpos",now.AsString());
  _weightedPositionfunc = new TF1(fname,this,&NewSensor::getWeightedPositionfunc,0,_thickness,0);

  sprintf(fname,"%s_chbary",now.AsString());
  _chargeBarycenterfunc = new TF1(fname,this,&NewSensor::getChargeBarycenterfunc,-100e-9,100e-9,0);

  sprintf(fname,"%s_decopulse",now.AsString());
  _decoPulse = new TF1(fname,"gaus",-200e-9,200e-9);
  _decoPulse->SetParameters(1.,0.,11e-9);

  

}

NewSensor::~NewSensor() {

  delete _Efieldfunc;
  delete _mobilityfunc;
  delete _tanLAfunc;
  delete _parallelVdriftfunc;
}

double NewSensor::getEfield(const double z) const {

  return (_Vbias-_Vdepl)/_thickness + 2*_Vdepl/_thickness*(1-z/_thickness);

}

double NewSensor::getMobility(const double z) const {

  double mob = 0;
  if(_mobility) {
    mob = _mobility->getMobility(getEfield(z));
  }
  return mob;
}

double NewSensor::getTanLA(const double z) const {

  double tanla=0;
  if(_mobility) {
    tanla = _mobility->getHallMobility(getEfield(z))*_Bfield;
  }
  return tanla;

}

double NewSensor::getParallelVdrift(const double z) const {

  return getMobility(z)*getEfield(z)/(1+getTanLA(z)*getTanLA(z));
}

double NewSensor::getDriftTime(const double z) const {

  double time = 0;
  if(_invParallelVdriftfunc) {
    time = _invParallelVdriftfunc->Integral(0,z);
  }
  return time;
}

double NewSensor::getSignalFraction(const double z) const {

  return (*_decoPulse)(getDriftTime(z));

}

double NewSensor::getTotalSignal(const double t0)  {

  setTimeOffset(t0);
  return _signalFractionfunc->Integral(0,_thickness)/_thickness;

}

double NewSensor::getChargeBarycenter(const double t0) {

  setTimeOffset(t0);
  return _weightedPositionfunc->Integral(0,_thickness)/(getTotalSignal(t0)*_thickness);

}


TF1* NewSensor::EfieldFunc() const {
  _Efieldfunc->GetXaxis()->SetTitle("depth [m]");
  _Efieldfunc->GetYaxis()->SetTitle("E [V/m]");
  return _Efieldfunc;
}
TF1* NewSensor::MobilityFunc() const {
  _mobilityfunc->GetXaxis()->SetTitle("depth [m]");
  _mobilityfunc->GetYaxis()->SetTitle("#mu [m2/Vs]");
  return _mobilityfunc;
}
TF1* NewSensor::tanLAFunc() const {
  _tanLAfunc->GetXaxis()->SetTitle("depth [m]");
  _tanLAfunc->GetYaxis()->SetTitle("tan(#thetaL)");
  return _tanLAfunc;
}
TF1* NewSensor::parallelVdriftFunc() const {
  _parallelVdriftfunc->GetXaxis()->SetTitle("depth [m]");
  _parallelVdriftfunc->GetYaxis()->SetTitle("Vdrift [m/s]");
  return _parallelVdriftfunc;
}
TF1* NewSensor::invParallelVdriftFunc() const {
  _invParallelVdriftfunc->GetXaxis()->SetTitle("depth [m]");
  _invParallelVdriftfunc->GetYaxis()->SetTitle("1/Vdrift [s/m]");
  return _invParallelVdriftfunc;
}
TF1* NewSensor::DriftTimeFunc() const {
  _driftTimefunc->GetXaxis()->SetTitle("depth [m]");
  _driftTimefunc->GetYaxis()->SetTitle("Tdrift [s]");
  return _driftTimefunc;
}
TF1* NewSensor::SignalFractionFunc() const {
  _signalFractionfunc->GetXaxis()->SetTitle("depth [m]");
  _signalFractionfunc->GetYaxis()->SetTitle("Signal Fraction");
  return _signalFractionfunc;
}
TF1* NewSensor::TotalSignalFunc() const {
  _totalSignalfunc->GetXaxis()->SetTitle("time [s]");
  _totalSignalfunc->GetYaxis()->SetTitle("Signal [a.u]");
  return _totalSignalfunc;
}
TF1* NewSensor::WeightedPositionFunc() const {
  _weightedPositionfunc->GetXaxis()->SetTitle("depth [m]");
  _weightedPositionfunc->GetYaxis()->SetTitle("Signal*depth [m]");
  return _weightedPositionfunc;
}
TF1* NewSensor::ChargeBarycenterFunc() const {
  _chargeBarycenterfunc->GetXaxis()->SetTitle("time [s]");
  _chargeBarycenterfunc->GetYaxis()->SetTitle("Barycenter depth [m]");
  return _chargeBarycenterfunc;}


double NewSensor::getEfieldfunc(const double* x, const double*) const {

  return getEfield(x[0]);

}     

double NewSensor::getMobilityfunc(const double* x, const double*) const {

  return getMobility(x[0]);

}

double NewSensor::getTanLAfunc(const double* x, const double*) const {

  return getTanLA(x[0]);

}

double NewSensor::getParallelVdriftfunc(const double* x, const double*) const {

  return getParallelVdrift(x[0]);

}

double NewSensor::getInvParallelVdriftfunc(const double* x, const double*) const {

  return getParallelVdrift(x[0])!=0 ? 1./getParallelVdrift(x[0]): 1e6;

}

double NewSensor::getDriftTimefunc(const double* x, const double*) const {

  return getDriftTime(x[0]);

}

double NewSensor::getSignalFractionfunc(const double* x, const double*) const {

  return getSignalFraction(x[0]);

}

double NewSensor::getTotalSignalfunc(const double* x, const double*) {

  return getTotalSignal(x[0]);

}

double NewSensor::getWeightedPositionfunc(const double* x, const double*) const {

  return getSignalFraction(x[0])*x[0];

}

double NewSensor::getChargeBarycenterfunc(const double* x, const double*) {

  return getChargeBarycenter(x[0]);

}





