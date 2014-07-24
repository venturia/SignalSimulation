#ifndef SIGNALFROMFILE_H
#define SIGNALFROMFILE_H

#include <string>

//namespace std {
//  class ostream;
//}
class TFile;
class TF1;
class TF2;
class TLine;
class TObjArray;

class SignalFromFile {

 public:

  SignalFromFile();
  SignalFromFile(const char* prefix, TFile* file);

  ~SignalFromFile();

  TF2* CurrentSignalVsTimeFunc() const;
  TF2* SignalFractionVsTimeFunc() const;
  TF2* WeightedLADriftVsTimeFunc() const;
  TF2* MeanLADriftVsTimeFunc() const;
  TF1* SignalFromDepth() const;
  TF1* CurrentSignalFromDepth() const;
  TF1* CurrentIntegral() const;
  TF1* TotalSignalFunc() const;
  TF1* ChargeBarycenterFunc() const;
  TF1* ChargeBarycenterSimplerFunc() const;
  TF1* LADriftBarycenterFunc() const;

  void SetLineColor(Color_t color);
  void SetLineStyle(Style_t style);

  double getMaxSignal() const;
  double getBarycenterAtMax() const;
  double getSlopeAtMax(const double width) const;

  TLine* getMaxSignalLine() const;
  TObjArray* getMaxSignalBarycenterLines() const;

  void printSummary(ostream& out) const;
  void printSummaryTableRow(ostream& out) const;

 private:

  double getMeanLADrift2D(const double* x, const double* p) const;
  double getSignalFraction(const double* x, const double* p) const;
  double getSignalFromDepth(const double* x, const double* p) const;
  double getCurrentSignalFromDepth(const double* x, const double* p) const;
  double getCurrentIntegral(const double* x, const double* p) const;
  double getWeightedPosition(const double* x, const double* p) const;
  double getWeightedPositionSimpler(const double* x, const double* p) const;
  double getWeightedLADrift(const double* x, const double* p) const;
  double getTotalSignal(const double* x, const double* p) const;
  double getChargeBarycenter(const double* x, const double* p) const;
  double getChargeBarycenterSimpler(const double* x, const double* p) const;
  double getLADriftBarycenter(const double* x, const double* p) const;


  std::string _prefix;
  TFile* _file;
  double _thickness;

  TF2* _currentsignalvstime;
  TF2* _signalfracvstime;
  TF2* _weightedposvstime;
  TF2* _weightedladriftvstime;

  TF2* _meanladriftvstime;
  TF1* _signalfrac;
  TF1* _signalfracaux;
  TF1* _signalfromdepth;
  TF1* _currentsignalfromdepth;
  TF1* _currentsignalfromdepthaux;
  TF1* _currentintegral;
  TF1* _weightedpos;
  TF1* _weightedpossimpler;
  TF1* _weightedladrift;

  TF1* _totalsignal;
  TF1* _chargebary;
  TF1* _chargebarysimpler;
  TF1* _ladriftbary;

};


#endif // SIGNALFROMFILE_H
