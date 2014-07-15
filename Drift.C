#include "Mobility.h"
#include "TF1.h"
#include "TF2.h"
#include "TDatime.h"
#include "TAxis.h"
#include "Sensor.h"

#include "Drift.h"

Drift::Drift(): 
  _name(), _mob(0), _sens(0),
  _mobilityfunc(0), _tanLAfunc(0), _parallelVdriftfunc(0), _invParallelVdriftfunc(0), 
  _driftTimefunc(0), _fromDriftTimefunc(0), _toDriftTimefunc(0), _genericDriftTimefunc(0),
  _genericLorentzDriftfunc(0)
{ }

//Drift::Drift(const char* name, const Mobility* mob, const TF1* efield, const double& bfield, const double thickness):
Drift::Drift(const char* name, const Mobility* mob, const Sensor* sens):
  _name(name), _mob(mob), _sens(sens) { 


  double thickness = _sens->getThickness();

  TDatime now;
  char fname[300];
  sprintf(fname,"%s_%s_mob",now.AsString(),_name.c_str());
  _mobilityfunc = new TF1(fname,this,&Drift::getMobility,0,thickness,0);

  sprintf(fname,"%s_%s_tanla",now.AsString(),_name.c_str());
  _tanLAfunc = new TF1(fname,this,&Drift::getTanLA,0,thickness,0);

  sprintf(fname,"%s_%s_parvdrift",now.AsString(),_name.c_str());
  _parallelVdriftfunc = new TF1(fname,this,&Drift::getParallelVdrift,0,thickness,0);

  sprintf(fname,"%s_%s_invparvdrift",now.AsString(),_name.c_str());
  _invParallelVdriftfunc = new TF1(fname,this,&Drift::getInvParallelVdrift,0,thickness,0);

  sprintf(fname,"%s_%s_drifttime",now.AsString(),_name.c_str());
  _driftTimefunc = new TF1(fname,this,&Drift::getDriftTime,0,thickness,0);

  sprintf(fname,"%s_%s_fromdrifttime",now.AsString(),_name.c_str());
  _fromDriftTimefunc = new TF1(fname,this,&Drift::getFromDriftTime,0,thickness,1);

  sprintf(fname,"%s_%s_todrifttime",now.AsString(),_name.c_str());
  _toDriftTimefunc = new TF1(fname,this,&Drift::getToDriftTime,0,thickness,1);

  sprintf(fname,"%s_%s_genericdrifttime",now.AsString(),_name.c_str());
  _genericDriftTimefunc = new TF2(fname,this,&Drift::getGenericDriftTime,0,thickness,0,thickness,0,"Drift","Drift::getGenericDriftTime");

  sprintf(fname,"%s_%s_genericlorentzdrift",now.AsString(),_name.c_str());
  _genericLorentzDriftfunc = new TF2(fname,this,&Drift::getGenericLorentzDrift,0,thickness,0,thickness,0,"Drift","Drift::getGenericLorentzDrift");

}

Drift::~Drift() {

  delete _mobilityfunc;
  delete _tanLAfunc;
  delete _parallelVdriftfunc;
  delete _invParallelVdriftfunc;
  delete _driftTimefunc;
  delete _fromDriftTimefunc;
  delete _toDriftTimefunc;
  delete _genericDriftTimefunc;
  delete _genericLorentzDriftfunc;

}

void Drift::SetLineColor(Color_t color) {

  _mobilityfunc->SetLineColor(color);
  _tanLAfunc->SetLineColor(color);
  _parallelVdriftfunc->SetLineColor(color);
  _driftTimefunc->SetLineColor(color);
  _fromDriftTimefunc->SetLineColor(color);
  _toDriftTimefunc->SetLineColor(color);

}

void Drift::SetLineStyle(Style_t style) {
  _mobilityfunc->SetLineStyle(style);
  _tanLAfunc->SetLineStyle(style);
  _parallelVdriftfunc->SetLineStyle(style);
  _driftTimefunc->SetLineStyle(style);
  _fromDriftTimefunc->SetLineStyle(style);
  _toDriftTimefunc->SetLineStyle(style);

}

TF1* Drift::MobilityFunc() const {
  //  if(_mobilityfunc->GetXaxis()!=0 && _mobilityfunc->GetYaxis()!=0) {
  //    _mobilityfunc->GetXaxis()->SetTitle("depth [m]");
  //    _mobilityfunc->GetYaxis()->SetTitle("#mu [m2/Vs]");
  //  }
  return _mobilityfunc;
}
TF1* Drift::tanLAFunc() const {
  //  if(_tanLAfunc->GetXaxis()!=0 && _tanLAfunc->GetYaxis()!=0) {
  //    _tanLAfunc->GetXaxis()->SetTitle("depth [m]");
  //    _tanLAfunc->GetYaxis()->SetTitle("tan(#thetaL)");
  //  }
  return _tanLAfunc;
}
TF1* Drift::parallelVdriftFunc() const {
//  if(_parallelVdriftfunc->GetXaxis()!=0 && _parallelVdriftfunc->GetYaxis()!=0) {
//    _parallelVdriftfunc->GetXaxis()->SetTitle("depth [m]");
//    _parallelVdriftfunc->GetYaxis()->SetTitle("Vdrift [m/s]");
//  }
  return _parallelVdriftfunc;
}
TF1* Drift::invParallelVdriftFunc() const {
  //  if(_invParallelVdriftfunc->GetXaxis()!=0 && _invParallelVdriftfunc->GetYaxis()!=0) {
  //    _invParallelVdriftfunc->GetXaxis()->SetTitle("depth [m]");
  //    _invParallelVdriftfunc->GetYaxis()->SetTitle("1/Vdrift [s/m]");
  //  }
  return _invParallelVdriftfunc;
}
TF1* Drift::DriftTimeFunc() const {
  //  if(_driftTimefunc->GetXaxis()!=0 && _driftTimefunc->GetYaxis()!=0) {
  //    _driftTimefunc->GetXaxis()->SetTitle("depth [m]");
  //    _driftTimefunc->GetYaxis()->SetTitle("Tdrift [s]");
  //  }
  return _driftTimefunc;
}

TF1* Drift::FromDriftTimeFunc() const {
  //  if(_fromDriftTimefunc->GetXaxis()!=0 && _fromDriftTimefunc->GetYaxis()!=0) {
  //  _fromDriftTimefunc->GetXaxis()->SetTitle("depth [m]");
  //  _fromDriftTimefunc->GetYaxis()->SetTitle("Tdrift [s]");
  //  }
  return _fromDriftTimefunc;
}

TF1* Drift::ToDriftTimeFunc() const {
  //  if(_toDriftTimefunc->GetXaxis()!=0 && _toDriftTimefunc->GetYaxis()!=0) {
  //    _toDriftTimefunc->GetXaxis()->SetTitle("depth [m]");
  //    _toDriftTimefunc->GetYaxis()->SetTitle("Tdrift [s]");
  //  }
  return _toDriftTimefunc;
}

TF2* Drift::GenericDriftTimeFunc() const {
  //  if(_genericDriftTimefunc->GetXaxis()!=0 && _genericDriftTimefunc->GetYaxis()!=0) {
  //    _genericDriftTimefunc->GetXaxis()->SetTitle("start [m]");
  //    _genericDriftTimefunc->GetYaxis()->SetTitle("stop [m]");
  //  }
  return _genericDriftTimefunc;
}

TF2* Drift::GenericLorentzDriftFunc() const {
  return _genericLorentzDriftfunc;
}

double Drift::getEfield(const double* x, const double*) const {
 
  double efield = 0;
  if(_sens->EfieldFunc()) {
    efield = _sens->EfieldFunc()->Eval(x[0]);
  }
  return efield;

}

double Drift::getMobility(const double* x, const double*) const {
 
  return _mob->getMobility(getEfield(x,0));

}

double Drift::getTanLA(const double* x, const double*) const {

  return _mob->getHallMobility(getEfield(x,0))*_sens->getBfield(x[0]);

}

double Drift::getParallelVdrift(const double* x, const double*) const {

  return getMobility(x,0)*getEfield(x,0)/(1+getTanLA(x,0)*getTanLA(x,0));

}

double Drift::getInvParallelVdrift(const double* x, const double*) const {

  return getParallelVdrift(x,0)!=0 ? 1./getParallelVdrift(x,0): 1e6;

}

double Drift::getDriftTime(const double* x, const double*) const {

  /*
  double time = 0;
  if(_invParallelVdriftfunc) {
    time = _invParallelVdriftfunc->Integral(0,x[0]);
  }
  return time;
  */

  return genericDriftTime(0,x[0]);
}

double Drift::getFromDriftTime(const double* x, const double* p) const {

  return genericDriftTime(p[0],x[0]);

}

double Drift::getToDriftTime(const double* x, const double* p) const {

  return genericDriftTime(x[0],p[0]);

}

double Drift::getGenericDriftTime(const double* x, const double*) const {

  return genericDriftTime(x[1],x[0]);

}

double Drift::getGenericLorentzDrift(const double* x, const double*) const {

  return genericLorentzDrift(x[1],x[0]);

}

double Drift::genericDriftTime(const double x, const double x0) const {

  double time = 0;
  if(_invParallelVdriftfunc) {
    time = _invParallelVdriftfunc->Integral(x,x0);
  }
  return time;

}

double Drift::genericLorentzDrift(const double x, const double x0) const {

  double ladrift = 0;
  if(_tanLAfunc) {
    ladrift = _tanLAfunc->Integral(x,x0);
  }
  return ladrift;

}





