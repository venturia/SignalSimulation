#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

class Drift;
class Sensor;
class Efield;

class Signal {

 public:

  Signal();
  Signal(const char* name, const Sensor* sens, const Drift* hole, const Drift* elect, const Efield* efield, TF1* pulse);
  ~Signal();
  
  TF1* SignalFractionFunc() const;
  TF2* SignalFractionVsTimeFunc() const;
  TF2* CurrentSignalVsTimeFunc() const;
  TF1* TotalSignalFunc() const;
  TF1* WeightedPositionFunc() const;
  TF2* WeightedPositionVsTimeFunc() const;
  TF2* WeightedLADriftVsTimeFunc() const;
  TF1* ChargeBarycenterFunc() const;
  TF1* LADriftBarycenterFunc() const;

  void SaveFunctions(const int npsig=0, const int npcurrx=0, const int npcurry=0, const int nplax=0, const int nplay=0) const;
  std::string getName() const;

 private:

  double getCurrentSignal(const double z, const double t0) const;
  double getSignalFraction(const double z, const double t0) const;
  double getConvolutedLADrift(const double z, const double t0) const;

  double signalToBeConvoluted(const double x, const double x0, const double t0, const Drift* drift) const;
  double laDriftToBeConvoluted(const double x, const double x0, const double t0, const Drift* drift) const;

  double getHoleSignalToBeConvoluted(const double* x, const double* p) const;
  double getElectronSignalToBeConvoluted(const double* x, const double* p) const;
  double getHoleLADriftToBeConvoluted(const double* x, const double* p) const;
  double getElectronLADriftToBeConvoluted(const double* x, const double* p) const;

  double getSignalFraction1D(const double *x, const double *p) const;
  double getSignalFraction2D(const double *x, const double *p) const;
  double getCurrentSignal2D(const double *x, const double *p) const;
  double getTotalSignal(const double *x, const double *p) const;
  double getWeightedPosition(const double *x, const double *p) const;
  double getWeightedPosition2D(const double *x, const double *p) const;
  double getWeightedLADrift(const double *x, const double *p) const;
  double getWeightedLADrift2D(const double *x, const double *p) const;
  double getChargeBarycenter(const double *x, const double *p) const;
  double getLADriftBarycenter(const double *x, const double *p) const;

  std::string _name;
  const Drift* _holed;
  const Drift* _electd;
  const Sensor* _sens;
  const Efield* _efield;

  TF1* _signalFractionfunc;
  TF1* _signalFractionfuncaux;
  TF2* _signalFractionVsTimefunc;
  TF2* _currentSignalVsTimefunc;
  TF1* _totalSignalfunc;
  TF1* _weightedPositionfunc;
  TF1* _weightedPositionfuncaux;
  TF2* _weightedPositionVsTimefunc;
  TF1* _weightedLADriftfuncaux;
  TF2* _weightedLADriftVsTimefunc;
  TF1* _chargeBarycenterfunc;
  TF1* _laDriftBarycenterfunc;

  TF1* _holeToBeConvolutedfunc;
  TF1* _electToBeConvolutedfunc;
  TF1* _holeLADriftToBeConvolutedfunc;
  TF1* _electLADriftToBeConvolutedfunc;

  TF1* _decoPulse;
  bool _pulseowner;

};

#endif // SIGNAL_H
