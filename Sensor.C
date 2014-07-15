#include <iostream>
#include "Sensor.h"
#include "TDatime.h"
#include "TF1.h"
#include "TAxis.h"

Sensor::Sensor(const char* name): 
  _name(name),
  _thickness(0.),_Vdepl(0.),_Vbias(0.),_Bfield(0.), _Efieldfunc(0)
{   }



Sensor::Sensor(const char* name, const double thick, const double vdepl):
  _name(name),
  _thickness(thick), _Vdepl(vdepl), _Vbias(0.), _Bfield(0.)
{ 
  TDatime now;
  char fname[300];

  sprintf(fname,"%s_%s_efield",now.AsString(),_name.c_str());
  _Efieldfunc = new TF1(fname,this,&Sensor::getEfield,0,_thickness,0);

}

Sensor::~Sensor() {

  delete _Efieldfunc;

}

double Sensor::eField(const double z) const {

  return getEfield(&z,0);

}

void Sensor::SetLineColor(Color_t color) {

  _Efieldfunc->SetLineColor(color);
}

void Sensor::SetLineStyle(Style_t style) {

  _Efieldfunc->SetLineStyle(style);
}



TF1* Sensor::EfieldFunc() const {
  //  if(_Efieldfunc->GetXaxis()!=0 && _Efieldfunc->GetYaxis()!=0) {
  //    _Efieldfunc->GetXaxis()->SetTitle("depth [m]");
  //    _Efieldfunc->GetYaxis()->SetTitle("E [V/m]");
  //  }
  return _Efieldfunc;
}

double Sensor::getEfield(const double* x, const double*) const {

  double z = x[0];
  return (_Vbias-_Vdepl)/_thickness + 2*_Vdepl/_thickness*(1-z/_thickness);

}     




