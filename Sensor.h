#ifndef SENSOR_H
#define SENSOR_H

#include "TF1.h"
#include "TF2.h"
#include <string>

class Sensor {

 public:
  Sensor(const char* name);
  Sensor(const char* name, const double thick, const double vdepl);
  ~Sensor();

  double eField(const double z) const;

  double getBfield(const double) const { return _Bfield;} 
  double getThickness() const {return _thickness;}

  void setThickness(const double thick) {_thickness = thick;};
  void setVdepl(const double vdepl) {_Vdepl = vdepl;}
  void setVbias(const double vbias) {_Vbias = vbias;}
  void setBField(const double bfield) {_Bfield = bfield;}

  void SetLineColor(Color_t color);
  void SetLineStyle(Style_t style);

  TF1* EfieldFunc() const;

 private:

  double getEfield(const double *x, const double *p) const;

  
  std::string _name;
  double _thickness;
  double _Vdepl;
  double _Vbias;
  double _Bfield;

  TF1* _Efieldfunc;
  
};

#endif // SENSOR_H
