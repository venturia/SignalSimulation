#ifndef MOBILITY_H
#define MOBILITY_H

class Mobility {

 public:
  Mobility():
    _mulow(0.04705), _vsat(83700), _beta(1.213), _rhall(0.7) { }
  Mobility(const double mulow, const double vsat, const double beta, const double rhall):
    _mulow(mulow), _vsat(vsat), _beta(beta), _rhall(rhall) { }

  double operator()(const double efield) const;
  double getMobility(const double efield) const;
  double getHallMobility(const double efield) const;

  
 private:

  double _mulow;
  double _vsat;
  double _beta;
  double _rhall;

};

#endif // MOBILITY_H
