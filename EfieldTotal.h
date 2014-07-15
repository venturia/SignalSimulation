#ifndef EFIELDTOTAL_H
#define EFIELDTOTAL_H

#include "Efield.h"
#include "TF2.h"
#include "TDatime.h"
#include <string>
#include <math.h>

class EfieldTotal:
public Efield {

 public:

  EfieldTotal(const char* name, const double thick, const double pitch, const double width, const double V):
    _thick(thick), 
    _name(name),
    _mode(Spherical), _pitch(pitch), _width(width), _v0(V) {

    TDatime now;
    char fname[300];
    sprintf(fname,"%s_%s_potential",_name.c_str(),now.AsString());
    _potential = new TF2(fname,this,&EfieldTotal::getPotential,-1*pitch,1*pitch,0,_thick,0,"EfieldTotal","EfieldTotal::getPotential");
    sprintf(fname,"%s_%s_ex",_name.c_str(),now.AsString());
    _ex = new TF2(fname,this,&EfieldTotal::getEx,-1*pitch,1*pitch,0,_thick,0,"EfieldTotal","EfieldTotal::getEx");
    sprintf(fname,"%s_%s_ez",_name.c_str(),now.AsString());
    _ez = new TF2(fname,this,&EfieldTotal::getEz,-1*pitch,1*pitch,0,_thick,0,"EfieldTotal","EfieldTotal::getEz");
    sprintf(fname,"%s_%s_etot",_name.c_str(),now.AsString());
    _etot = new TF2(fname,this,&EfieldTotal::getE,-1*pitch,1*pitch,0,_thick,0,"EfieldTotal","EfieldTotal::getE");
    sprintf(fname,"%s_%s_weight",_name.c_str(),now.AsString());
    _weight = new TF1(fname,this,&EfieldTotal::getWeight,0,_thick,1,"EfieldTotal","EfieldTotal::getWeight");

}

  ~EfieldTotal() { delete _potential;}

  void setMode(const int mode) { _mode = mode; }
  double chargeEps() const {

    double chargeeps = 0.;
    if(_mode==Spherical) chargeeps = _v0/(_thick/(_pitch)*(1-_pitch/(2*M_PI*_thick)*log(2*M_PI*_width/_pitch)));
    if(_mode==Depth) chargeeps = -(4*M_PI*_v0)/log(pow(sinh(M_PI/_pitch*(-_width)),2)/pow(sinh(M_PI/_pitch*(2*_thick-_width)),2));
    if(_mode==Width) chargeeps = -(4*M_PI*_v0)/log(pow(sin(M_PI/_pitch*(_width)),2)/(pow(sin(M_PI/_pitch*(_width)),2)+pow(sinh(M_PI/_pitch*(2*_thick)),2)));
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

  double getPotential(const double* x, const double*) const {

    double chargeeps = chargeEps();

    double pot = -chargeeps/(4*M_PI);
    pot *= log((pow(sin(M_PI/_pitch*x[0]),2)+pow(sinh(M_PI/_pitch*(-x[1])),2))/
	       (pow(sin(M_PI/_pitch*x[0]),2)+pow(sinh(M_PI/_pitch*(2*_thick-x[1])),2)));

    

    //    return pot < _v0 ? pot : _v0;
    return pot ;

  }

  double getEz(const double* x, const double*) const {

    double chargeeps = chargeEps();

    double twopis= 2*M_PI/_pitch;
    double dx = x[0];
    double dz = -x[1];
    double sz = -x[1]+2*_thick;

    double a1 = cosh(twopis*dz)-cos(twopis*dx);
    double a2 = cosh(twopis*sz)-cos(twopis*dx);

    double ez = chargeeps/(2*_pitch)*(sinh(twopis*dz)/a1-sinh(twopis*sz)/a2);

    return ez;
  }

  double getEx(const double* x, const double*) const {


    double chargeeps = chargeEps();

    double twopis= 2*M_PI/_pitch;
    double dx = x[0];
    double dz = -x[1];
    double sz = -x[1]+2*_thick;

    double a1 = cosh(twopis*dz)-cos(twopis*dx);
    double a2 = cosh(twopis*sz)-cos(twopis*dx);

    double ex = chargeeps/(2*_pitch)*sin(twopis*dx)*(1/a1-1/a2);

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

#endif // EFIELDTOTAL_H
