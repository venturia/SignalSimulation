#ifndef EFIELDALONE_H
#define EFIELDALONE_H

#include "Efield.h"
#include "TF2.h"
#include "TDatime.h"
#include <string>
#include <math.h>

class EfieldAlone:
public Efield {

 public:

  EfieldAlone(const char* name, const double thick, const double pitch, const double width, const double V):
    _thick(thick), 
    _name(name),
    _mode(Spherical), _pitch(pitch), _width(width), _v0(V) {

    TDatime now;
    char fname[300];
    sprintf(fname,"%s_%s_potential",_name.c_str(),now.AsString());
    _potential = new TF2(fname,this,&EfieldAlone::getPotential,-1*pitch,1*pitch,0,_thick,0,"EfieldAlone","EfieldAlone::getPotential");
    sprintf(fname,"%s_%s_ex",_name.c_str(),now.AsString());
    _ex = new TF2(fname,this,&EfieldAlone::getEx,-1*pitch,1*pitch,0,_thick,0,"EfieldAlone","EfieldAlone::getEx");
    sprintf(fname,"%s_%s_ez",_name.c_str(),now.AsString());
    _ez = new TF2(fname,this,&EfieldAlone::getEz,-1*pitch,1*pitch,0,_thick,0,"EfieldAlone","EfieldAlone::getEz");
    sprintf(fname,"%s_%s_etot",_name.c_str(),now.AsString());
    _etot = new TF2(fname,this,&EfieldAlone::getE,-1*pitch,1*pitch,0,_thick,0,"EfieldAlone","EfieldAlone::getE");
    sprintf(fname,"%s_%s_weight",_name.c_str(),now.AsString());
    _weight = new TF1(fname,this,&EfieldAlone::getWeight,0,_thick,1,"EfieldAlone","EfieldAlone::getWeight");

}

  ~EfieldAlone() { delete _potential;}

  void setMode(const int mode) { _mode = mode; }
  double chargeEps() const {

    double chargeeps = 0.;
    if(_mode==Spherical) chargeeps = -(2*M_PI*_v0)/log(_width/(2*_thick));
    if(_mode==Depth) chargeeps = -(2*M_PI*_v0)/log(_width/(2*_thick-_width));
    if(_mode==Width) chargeeps = -(2*M_PI*_v0)/log(_width/sqrt(pow(_width,2)+pow(2*_thick,2)));
    return chargeeps;

  }

  void SetLineColor(Color_t color) {

    _weight->SetLineColor(color);

  }

  void SetLineStyle(Style_t style) {

    _weight->SetLineStyle(style);

  }

  TF2* PotentialFunc() const { return _potential;}
  TF2* EzFunc() const { return _ez;}
  TF2* ExFunc() const { return _ex;}
  TF2* EFunc() const { return _etot;}
  virtual TF1* Weight() const { return _weight;}

 protected:

  const double _thick;

 private:

double getPotential( const double* x, const double*) const {

  double chargeeps = chargeEps();

  double pot = -chargeeps/(2.*M_PI);
  double rz0 = sqrt(pow(x[0],2)+pow(x[1],2));
  double rz0bar = sqrt(pow(x[0],2)+pow(2*_thick-x[1],2));

  pot *= log(rz0) - log(rz0bar);

  return pot;

}

double getEz( const double* x, const double*) const {

  double chargeeps = chargeEps();

  double ez = chargeeps/(2.*M_PI);
  double rz0 = sqrt(pow(x[0],2)+pow(x[1],2));
  double rz0bar = sqrt(pow(x[0],2)+pow(2*_thick-x[1],2));

  ez *= -x[1]/pow(rz0,2) -(2*_thick-x[1])/pow(rz0bar,2);

  return ez;

}

double getEx( const double* x, const double*) const {

  double chargeeps = chargeEps();

  double ex = chargeeps/(2.*M_PI);
  double rz0 = sqrt(pow(x[0],2)+pow(x[1],2));
  double rz0bar = sqrt(pow(x[0],2)+pow(2*_thick-x[1],2));

  ex *= x[0]*(1./pow(rz0,2) - 1./pow(rz0bar,2));

  return ex;

}

  double getE(const double* x, const double* p) const {

    return sqrt(pow(getEx(x,p),2)+pow(getEz(x,p),2));
  }

  std::string _name;
  int _mode;
  const double _pitch;
  const double _width;
  const double _v0;
    
  TF2* _potential;
  TF2* _ez;
  TF2* _ex;
  TF2* _etot;
  TF1* _weight;

  double getWeight(const double* x, const double* p) const {

    if(x[0]>=p[0]) {
      double xcoord[2];
      xcoord[0]=0.;
      xcoord[1]=p[0];
      double norm = getPotential(xcoord,0);
      xcoord[1]=x[0];
      return getE(xcoord,0)/norm;
    }
    else {
      return 0.;
    }
  }

};

#endif // EFIELDALONE_H
