#ifndef DRIFT_H
#define DRIFT_H

#include <string>

class Mobility;
class TF1;
class TF2;
class Sensor;

class Drift {

 public:

  Drift();
  //  Drift(const char* name, const Mobility* mob, const TF1* efield, const double& bfield, const double thickness);
  Drift(const char* name, const Mobility* mob, const Sensor* sens);
  ~Drift();

  void SetLineColor(Color_t color);
  void SetLineStyle(Style_t style);

  TF1* MobilityFunc() const;
  TF1* tanLAFunc() const;
  TF1* parallelVdriftFunc() const;
  TF1* invParallelVdriftFunc() const;
  TF1* DriftTimeFunc() const;
  TF1* FromDriftTimeFunc() const;
  TF1* ToDriftTimeFunc() const;
  TF2* GenericDriftTimeFunc() const;
  TF2* GenericLorentzDriftFunc() const;

 private:

  double getEfield(const double *x, const double *p) const;
  double getMobility(const double *x, const double *p) const;
  double getTanLA(const double *x, const double *p) const;
  double getParallelVdrift(const double *x, const double *p) const;
  double getInvParallelVdrift(const double *x, const double *p) const;
  double getDriftTime(const double *x, const double *p) const;
  double getFromDriftTime(const double *x, const double *p) const;
  double getToDriftTime(const double *x, const double *p) const;
  double getGenericDriftTime(const double *x, const double *p) const;
  double getGenericLorentzDrift(const double *x, const double *p) const;

  double genericDriftTime(const double x, const double x0) const;
  double genericLorentzDrift(const double x, const double x0) const;

  std::string _name;
  const Mobility* _mob;

  const Sensor* _sens;

  TF1* _mobilityfunc;
  TF1* _tanLAfunc;
  TF1* _parallelVdriftfunc;
  TF1* _invParallelVdriftfunc;
  TF1* _driftTimefunc;
  TF1* _fromDriftTimefunc;
  TF1* _toDriftTimefunc;
  TF2* _genericDriftTimefunc;
  TF2* _genericLorentzDriftfunc;

};




#endif // DRIFT_H
