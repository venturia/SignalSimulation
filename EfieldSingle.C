#include "EfieldSingle.h"
#include <math.h>


EfieldSingle::EfieldSingle(const char* name, const double thick, const double pitch, const double width, const double V):
    Efield(name,thick,pitch,width,V) { }


double EfieldSingle::getPotential( const double* x, const double*) const {

  double chargeeps = chargeEps();

  double pot = -chargeeps/(2.*M_PI);
  double rz0 = sqrt(pow(x[0],2)+pow(x[1],2));
  double rz0bar = sqrt(pow(x[0],2)+pow(2*_thick-x[1],2));

  pot *= log(rz0) - log(rz0bar);

  return pot;

}

double EfieldSingle::getEz( const double* x, const double*) const {

  double chargeeps = chargeEps();

  double ez = chargeeps/(2.*M_PI);
  double rz0 = sqrt(pow(x[0],2)+pow(x[1],2));
  double rz0bar = sqrt(pow(x[0],2)+pow(2*_thick-x[1],2));

  ez *= -x[1]/pow(rz0,2) -(2*_thick-x[1])/pow(rz0bar,2);

  return ez;

}

double EfieldSingle::getEx( const double*, const double*) const {

  double chargeeps = chargeEps();

  /*
  double ex = chargeeps/(2.*M_PI);
  double rz0 = sqrt(pow(x[0],2)+pow(x[1],2));
  double rz0bar = sqrt(pow(x[0],2)+pow(2*_thick-x[1],2));
  */

  double ex = 0;

  return ex;

}

