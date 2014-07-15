#include "Mobility.h"

double Mobility::operator()(const double efield) const {

  double mob = _mulow/pow(1+pow(fabs(_mulow*efield)/_vsat,_beta),1/_beta);

  return mob;

}

double Mobility::getMobility(const double efield) const {

    return operator()(efield);
}

double Mobility::getHallMobility(const double efield) const {

    return _rhall*operator()(efield);
}

