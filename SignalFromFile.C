#include <fstream>
#include <iostream>
#include <iomanip>
#include "TFile.h"
#include "TF1.h"
#include "TF2.h"
#include "TLine.h"
#include "TObjArray.h"

#include "SignalFromFile.h"

SignalFromFile::SignalFromFile():
  _prefix(), _file(0), _thickness(0),
  _signalfracvstime(0), _weightedposvstime(0),
  _weightedladriftvstime(0), _meanladriftvstime(0),
  _signalfrac(0), _signalfracaux(0), 
  _signalfromdepth(0),  _currentsignalfromdepth(0),
  _currentsignalfromdepthaux(0), 
  _currentintegral(0),
  _weightedpos(0), _weightedpossimpler(0), 
  _totalsignal(0), _chargebary(0), _chargebarysimpler(0)
{ }

SignalFromFile::SignalFromFile( const char* prefix, TFile* file):
  _prefix(prefix), _file(file), _thickness(0.) {

  char fname[300];

  sprintf(fname,"%s_currentsignalvstime",_prefix.c_str());
  _currentsignalvstime = (TF2*)file->Get(fname);
  sprintf(fname,"%s_signalfracvstime",_prefix.c_str());
  _signalfracvstime = (TF2*)file->Get(fname);
  sprintf(fname,"%s_weightposvstime",_prefix.c_str());
  _weightedposvstime = (TF2*)file->Get(fname);
  sprintf(fname,"%s_weightlavstime",_prefix.c_str());
  _weightedladriftvstime = (TF2*)file->Get(fname);

  double xmin=0., xmax=500e-6,tmin=-100e-9,tmax=100e-9;
  double tcmin=-10e-9,tcmax=40e-9;

  if(_signalfracvstime) {
    xmin = _signalfracvstime->GetXmin();
    xmax = _signalfracvstime->GetXmax();
    tmin = _signalfracvstime->GetYmin();
    tmax = _signalfracvstime->GetYmax();
    _thickness= xmax;
  }

  if(_currentsignalvstime) {
    tcmin = _currentsignalvstime->GetYmin();
    tcmax = _currentsignalvstime->GetYmax();
  }



  sprintf(fname,"%s_meanlavstime",_prefix.c_str());
  _meanladriftvstime = new TF2(fname,this,&SignalFromFile::getMeanLADrift2D,xmin,xmax,tmin,tmax,0,"SignalFromFile","SignalFromFile::getMeanLADrift2D");

  sprintf(fname,"%s_signalfrac",_prefix.c_str());
  _signalfrac = new TF1(fname,this,&SignalFromFile::getSignalFraction,xmin,xmax,1);

  sprintf(fname,"%s_signalfracaux",_prefix.c_str());
  _signalfracaux = new TF1(fname,this,&SignalFromFile::getSignalFraction,xmin,xmax,1);

  sprintf(fname,"%s_signalfromdepth",_prefix.c_str());
  _signalfromdepth = new TF1(fname,this,&SignalFromFile::getSignalFromDepth,tmin,tmax,1);

  sprintf(fname,"%s_currentsignalfromdepth",_prefix.c_str());
  _currentsignalfromdepth = new TF1(fname,this,&SignalFromFile::getCurrentSignalFromDepth,tcmin,tcmax,1);

  sprintf(fname,"%s_currentsignalfromdepthaux",_prefix.c_str());
  _currentsignalfromdepthaux = new TF1(fname,this,&SignalFromFile::getCurrentSignalFromDepth,tcmin,tcmax,1);

  sprintf(fname,"%s_currentintegral",_prefix.c_str());
  _currentintegral = new TF1(fname,this,&SignalFromFile::getCurrentIntegral,xmin,xmax,1);

  sprintf(fname,"%s_weightpos",_prefix.c_str());
  _weightedpos = new TF1(fname,this,&SignalFromFile::getWeightedPosition,xmin,xmax,1);

  sprintf(fname,"%s_weightpossimpler",_prefix.c_str());
  _weightedpossimpler = new TF1(fname,this,&SignalFromFile::getWeightedPositionSimpler,xmin,xmax,1);

  sprintf(fname,"%s_weightladrift",_prefix.c_str());
  _weightedladrift = new TF1(fname,this,&SignalFromFile::getWeightedLADrift,xmin,xmax,1);

  sprintf(fname,"%s_totalsignal",_prefix.c_str());
  _totalsignal = new TF1(fname,this,&SignalFromFile::getTotalSignal,tmin,tmax,0);

  sprintf(fname,"%s_chargebary",_prefix.c_str());
  _chargebary = new TF1(fname,this,&SignalFromFile::getChargeBarycenter,tmin,tmax,0);

  sprintf(fname,"%s_chargebarysimpler",_prefix.c_str());
  _chargebarysimpler = new TF1(fname,this,&SignalFromFile::getChargeBarycenterSimpler,tmin,tmax,0);

  sprintf(fname,"%s_ladriftbary",_prefix.c_str());
  _ladriftbary = new TF1(fname,this,&SignalFromFile::getLADriftBarycenter,tmin,tmax,0);


}

SignalFromFile::~SignalFromFile() {

  delete _currentsignalvstime;
  delete _signalfracvstime;
  delete _weightedposvstime;
  delete _weightedladriftvstime;
  delete _meanladriftvstime;
  delete _signalfrac;
  delete _signalfracaux;
  delete _signalfromdepth;
  delete _currentsignalfromdepth;
  delete _currentsignalfromdepthaux;
  delete _currentintegral;
  delete _weightedpos;
  delete _weightedpossimpler;
  delete _weightedladrift;
  delete _totalsignal;
  delete _chargebary;
  delete _chargebarysimpler;
  delete _ladriftbary;

}

TF2* SignalFromFile::CurrentSignalVsTimeFunc() const {return _currentsignalvstime;}

TF2* SignalFromFile::SignalFractionVsTimeFunc() const {return _signalfracvstime;}

TF2* SignalFromFile::WeightedLADriftVsTimeFunc() const {return _weightedladriftvstime;}

TF2* SignalFromFile::MeanLADriftVsTimeFunc() const {return _meanladriftvstime;}

TF1* SignalFromFile::SignalFromDepth() const {return _signalfromdepth;}

TF1* SignalFromFile::CurrentSignalFromDepth() const {return _currentsignalfromdepth;}

TF1* SignalFromFile::CurrentIntegral() const {return _currentintegral;}

TF1* SignalFromFile::TotalSignalFunc() const {return _totalsignal;}

TF1* SignalFromFile::ChargeBarycenterFunc() const {return _chargebary;}

TF1* SignalFromFile::ChargeBarycenterSimplerFunc() const {return _chargebarysimpler;}

TF1* SignalFromFile::LADriftBarycenterFunc() const {return _ladriftbary;}

void SignalFromFile::SetLineColor(Color_t color) {

  _signalfromdepth->SetLineColor(color);
  _currentsignalfromdepth->SetLineColor(color);
  _currentintegral->SetLineColor(color);
  _totalsignal->SetLineColor(color);
  _chargebary->SetLineColor(color);
  _chargebarysimpler->SetLineColor(color);

}

void SignalFromFile::SetLineStyle(Style_t style) {

  _signalfromdepth->SetLineStyle(style);
  _currentsignalfromdepth->SetLineStyle(style);
  _currentintegral->SetLineStyle(style);
  _totalsignal->SetLineStyle(style);
  _chargebary->SetLineStyle(style);
  _chargebarysimpler->SetLineStyle(style);

}

double SignalFromFile::getMaxSignal() const {

  return TotalSignalFunc()->GetMaximumX(-20e-9,20e-9);

}

double SignalFromFile::getBarycenterAtMax() const {

  return ChargeBarycenterSimplerFunc()->Eval(getMaxSignal());

}

double SignalFromFile::getSlopeAtMax(const double width) const {

  double signalmax=getMaxSignal();

  return (ChargeBarycenterSimplerFunc()->Eval(signalmax+width)-
	  ChargeBarycenterSimplerFunc()->Eval(signalmax-width))/(2.*width);

}

TLine* SignalFromFile::getMaxSignalLine() const {

  double signalmax = getMaxSignal();

  TLine* line = new TLine(signalmax,0,signalmax,1);

  line->SetLineColor(_totalsignal->GetLineColor());
  line->SetLineStyle(_totalsignal->GetLineStyle());

  return line;
}

TObjArray* SignalFromFile::getMaxSignalBarycenterLines() const {

  TObjArray* arr = new TObjArray(2);

  double signalmax = getMaxSignal();
  double baryatmax = getBarycenterAtMax();

  TLine* linex = new TLine(signalmax,0,signalmax,baryatmax);

  linex->SetLineColor(_chargebarysimpler->GetLineColor());
  linex->SetLineStyle(_chargebarysimpler->GetLineStyle());

  TLine* liney = new TLine(-100e-9,baryatmax,signalmax,baryatmax);

  liney->SetLineColor(_chargebarysimpler->GetLineColor());
  liney->SetLineStyle(_chargebarysimpler->GetLineStyle());

  arr->Add(linex);
  arr->Add(liney);


  arr->SetOwner(kTRUE);
  return arr;
}

void SignalFromFile::printSummary(ostream& out) const {
  
  out << _prefix.c_str() << " from file " << _file->GetName() << endl;
  out << "signal maximum at " << getMaxSignal() << " sec " << endl;
  out << "barycenter at signal maximum  " << getBarycenterAtMax() << " m " << endl;
  out << "slope at signal maximum  (+/- 5nsec)  " << getSlopeAtMax(5e-9)/1000. << " um/nsec " << endl;
  out << "slope at signal maximum  (+/- 2nsec)  " << getSlopeAtMax(2e-9)/1000. << " um/nsec " << endl;
  
}

void SignalFromFile::printSummaryTableRow(ostream& out) const {
  
  out << fixed;
  out << _prefix.c_str() << " " << _file->GetName();
  out << " " << setw(7) << setprecision(3) << getMaxSignal()*1000000000.;
  out << " " << setw(9) << setprecision(4) << getBarycenterAtMax()*1000000.;
  out << " " << setw(8) << setprecision(4) << getSlopeAtMax(5e-9)/1000.;
  out << " " << setw(8) << setprecision(4) << getSlopeAtMax(2e-9)/1000. << endl;
  
}

double SignalFromFile::getMeanLADrift2D(const double* x, const double*) const {

  if(_signalfracvstime!=0 && _weightedladriftvstime!=0) {
    return _signalfracvstime->Eval(x[0],x[1])<=1e-3 ? 0. : 
      _weightedladriftvstime->Eval(x[0],x[1])/_signalfracvstime->Eval(x[0],x[1]); 
  }
  else {
    return 0;
  }
}

double SignalFromFile::getSignalFraction(const double* x, const double* p) const {

  if(_signalfracvstime) {
    return _signalfracvstime->Eval(x[0],p[0]);
  }
  else {
    return 0;
  }
}

double SignalFromFile::getSignalFromDepth(const double* x, const double* p) const {

  if(_signalfracvstime) {
    return _signalfracvstime->Eval(p[0],x[0]);
  }
  else {
    return 0;
  }
}

double SignalFromFile::getCurrentSignalFromDepth(const double* x, const double* p) const {

  if(_currentsignalvstime) {
    return _currentsignalvstime->Eval(p[0],x[0]);
  }
  else {
    return 0;
  }
}

double SignalFromFile::getCurrentIntegral(const double* x, const double*) const {

  double tcmin=-100e-9, tcmax = 100e-9;

  if(_currentsignalvstime) {
    tcmin = _currentsignalvstime->GetYmin();
    tcmax = _currentsignalvstime->GetYmax();
  }

  if(_currentsignalfromdepthaux) {  
    _currentsignalfromdepthaux->SetParameter(0,x[0]);
    return _currentsignalfromdepthaux->Integral(tcmin,tcmax);
  }
  else {
    return 0;
  }
}

double SignalFromFile::getWeightedPosition(const double* x, const double* p) const {

  if(_weightedposvstime) {
    return _weightedposvstime->Eval(x[0],p[0]);
  }
  else {
    return 0;
  }
}

double SignalFromFile::getWeightedPositionSimpler(const double* x, const double* p) const {

  if(_signalfracvstime) {
    return _signalfracvstime->Eval(x[0],p[0])*x[0];
  }
  else {
    return 0;
  }
  /*
  if(_signalfrac) {
    return _signalfrac->Eval(x[0],p[0])*x[0];
  }
  else {
    return 0;
  }
  */
}

double SignalFromFile::getWeightedLADrift(const double* x, const double* p) const {

  if(_weightedladriftvstime) {
    return _weightedladriftvstime->Eval(x[0],p[0]);
  }
  else {
    return 0;
  }
}

double SignalFromFile::getTotalSignal(const double* x, const double*) const {

  if(_signalfracaux) {
    _signalfracaux->SetParameter(0,x[0]);
    return _signalfracaux->Integral(0,_thickness)/_thickness;
  }
  else {
    return 0;
  }
}

double SignalFromFile::getChargeBarycenter(const double* x, const double*) const {

  if(_weightedpos!=0) {
    _weightedpos->SetParameter(0,x[0]);
    double norm = getTotalSignal(x,0)*_thickness;
    return norm!=0 ? _weightedpos->Integral(0,_thickness)/norm : 0;
  }
  else {
    return 0;
  }
}

double SignalFromFile::getChargeBarycenterSimpler(const double* x, const double*) const {

  if(_weightedpossimpler!=0) {
    _weightedpossimpler->SetParameter(0,x[0]);
    double norm = getTotalSignal(x,0)*_thickness;
    return norm!=0 ? _weightedpossimpler->Integral(0,_thickness)/norm : 0;
  }
  else {
    return 0;
  }
}

double SignalFromFile::getLADriftBarycenter(const double* x, const double*) const {

  if(_weightedladrift!=0) {
    _weightedladrift->SetParameter(0,x[0]);
    double norm = getTotalSignal(x,0)*_thickness;
    return norm!=0 ? _weightedladrift->Integral(0,_thickness)/norm : 0;
  }
  else {
    return 0;
  }
}

