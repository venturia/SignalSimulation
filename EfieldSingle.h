#ifndef EFIELDSINGLE_H
#define EFIELDSINGLE_H

#include "Efield.h"

class EfieldSingle:
public Efield {

 public:

  EfieldSingle(const char* name, const double thick, const double pitch, const double width, const double V);

 private:

  double getPotential(const double* x, const double* p) const;
  double getEz(const double* x, const double* p) const;
  double getEx(const double* x, const double* p) const;
  
};

#endif // EFIELDSINGLE_H
