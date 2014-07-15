#ifndef NEWSENSOR_H
#define NEWSENSOR_H

#include "TF1.h"

class Mobility;

class NewSensor {

 public:
  NewSensor();
  NewSensor(const double thick, const double vdepl, const Mobility* mobility);
  ~NewSensor();

  double getEfield(const double z) const;
  double getMobility(const double z) const;
  double getTanLA(const double z) const;
  double getParallelVdrift(const double z) const;
  double getDriftTime(const double z) const;
  double getSignalFraction(const double z) const;
  double getTotalSignal(const double z) ;
  double getChargeBarycenter(const double z) ;

  double getBfield(const double) const { return _Bfield;} 

  void setThickness(const double thick) {_thickness = thick;};
  void setVdepl(const double vdepl) {_Vdepl = vdepl;}
  void setVbias(const double vbias) {_Vbias = vbias;}
  void setBField(const double bfield) {_Bfield = bfield;}
  void setMobility(const Mobility* mobility) {_mobility = mobility;}
  void setTimeOffset(const double t0) {_decoPulse->SetParameter(1,t0);}
  void setPulseWidth(const double width) {_decoPulse->SetParameter(2,width);}


  TF1* EfieldFunc() const;
  TF1* MobilityFunc() const;
  TF1* tanLAFunc() const;
  TF1* parallelVdriftFunc() const;
  TF1* invParallelVdriftFunc() const;
  TF1* DriftTimeFunc() const;
  TF1* SignalFractionFunc() const;
  TF1* TotalSignalFunc() const;
  TF1* WeightedPositionFunc() const;
  TF1* ChargeBarycenterFunc() const;

 private:

  double getEfieldfunc(const double *x, const double *p) const;
  double getMobilityfunc(const double *x, const double *p) const;
  double getTanLAfunc(const double *x, const double *p) const;
  double getParallelVdriftfunc(const double *x, const double *p) const;
  double getInvParallelVdriftfunc(const double *x, const double *p) const;
  double getDriftTimefunc(const double *x, const double *p) const;
  double getSignalFractionfunc(const double *x, const double *p) const;
  double getTotalSignalfunc(const double *x, const double *p) ;
  double getWeightedPositionfunc(const double *x, const double *p) const;
  double getChargeBarycenterfunc(const double *x, const double *p);

  
  double _thickness;
  double _Vdepl;
  double _Vbias;
  double _Bfield;
  const Mobility* _mobility;
  TF1* _Efieldfunc;
  TF1* _mobilityfunc;
  TF1* _tanLAfunc;
  TF1* _parallelVdriftfunc;
  TF1* _invParallelVdriftfunc;
  TF1* _driftTimefunc;
  TF1* _signalFractionfunc;
  TF1* _totalSignalfunc;
  TF1* _weightedPositionfunc;
  TF1* _chargeBarycenterfunc;

  TF1* _decoPulse;

};

#endif // SENSOR_H
