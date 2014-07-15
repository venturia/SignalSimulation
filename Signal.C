#include <iostream>
#include "Drift.h"
#include "Sensor.h"
#include "Efield.h"
#include "Pulse.h"
#include "TF1.h"
#include "TF2.h"
#include "TAxis.h"
#include "TFile.h"

#include "Signal.h"

Signal::Signal():
  _name(),
  _holed(0),_electd(0),_sens(0),_efield(0),
  _signalFractionfunc(0), _signalFractionfuncaux(0), _signalFractionVsTimefunc(0),
  _currentSignalVsTimefunc(0),
  _totalSignalfunc(0), 
  _weightedPositionfunc(0), _weightedPositionfuncaux(0), 
  _weightedPositionVsTimefunc(0),
  _weightedLADriftfuncaux(0),
  _weightedLADriftVsTimefunc(0),
  _chargeBarycenterfunc(0),
  _laDriftBarycenterfunc(0),
  _holeToBeConvolutedfunc(0),  _electToBeConvolutedfunc(0),
  _holeLADriftToBeConvolutedfunc(0),  _electLADriftToBeConvolutedfunc(0),
  _decoPulse(0),_pulseowner(false)
{ 

  if(_decoPulse==0) {
    char fname[300];
    sprintf(fname,"%s_signaldecopulse",_name.c_str());
    _decoPulse = new TF1(fname,"gaus",-200e-9,200e-9);
    _decoPulse->SetParameters(1.,0.,11e-9);
    _pulseowner = true;
  }


}


Signal::Signal(const char* name, const Sensor* sens, const Drift* hole, const Drift* elect, const Efield* efield, TF1* pulse):
  _name(name),  _holed(hole), _electd(elect), _sens(sens), _efield(efield), _decoPulse(pulse), _pulseowner(false) {

  char fname[300];

  const double tmin=-50e-9, tmax=100e-9;
  const double tcmin=-10e-9, tcmax=40e-9;

  double thickness = 500e-6;
  if(_sens) thickness = _sens->getThickness();

  sprintf(fname,"%s_signalfrac",_name.c_str());
  _signalFractionfunc = new TF1(fname,this,&Signal::getSignalFraction1D,0,thickness,1);

  sprintf(fname,"%s_signalfracaux",_name.c_str());
  _signalFractionfuncaux = new TF1(fname,this,&Signal::getSignalFraction1D,0,thickness,1);

  sprintf(fname,"%s_signalfracvstime",_name.c_str());
  _signalFractionVsTimefunc = 
    new TF2(fname,this,&Signal::getSignalFraction2D,0,thickness,tmin,tmax,0,"Signal","Signal::getSignalFraction2D");
  sprintf(fname,"%s_currentsignalvstime",_name.c_str());
  _currentSignalVsTimefunc = 
    new TF2(fname,this,&Signal::getCurrentSignal2D,0,thickness,tcmin,tcmax,0,"Signal","Signal::getCurrentSignal2D");

  sprintf(fname,"%s_totsign",_name.c_str());
  _totalSignalfunc = new TF1(fname,this,&Signal::getTotalSignal,tmin,tmax,0);

  sprintf(fname,"%s_weightpos",_name.c_str());
  _weightedPositionfunc = new TF1(fname,this,&Signal::getWeightedPosition,0,thickness,1);

  sprintf(fname,"%s_weightposaux",_name.c_str());
  _weightedPositionfuncaux = new TF1(fname,this,&Signal::getWeightedPosition,0,thickness,1);

  sprintf(fname,"%s_weightposvstime",_name.c_str());
  _weightedPositionVsTimefunc = new TF2(fname,this,&Signal::getWeightedPosition2D,0,thickness,tmin,tmax,0,"Signal","Signal::getWeightedPosition2D");

  sprintf(fname,"%s_weightlaaux",_name.c_str());
  _weightedLADriftfuncaux = new TF1(fname,this,&Signal::getWeightedLADrift,0,thickness,1);

  sprintf(fname,"%s_weightlavstime",_name.c_str());
  _weightedLADriftVsTimefunc = new TF2(fname,this,&Signal::getWeightedLADrift2D,0,thickness,tmin,tmax,0,"Signal","Signal::getWeightedLADrift2D");

  sprintf(fname,"%s_chbary",_name.c_str());
  _chargeBarycenterfunc = new TF1(fname,this,&Signal::getChargeBarycenter,tmin,tmax,0);

  sprintf(fname,"%s_labary",_name.c_str());
  _laDriftBarycenterfunc = new TF1(fname,this,&Signal::getLADriftBarycenter,tmin,tmax,0);

  sprintf(fname,"%s_holetobeconv",_name.c_str());
  _holeToBeConvolutedfunc = new TF1(fname,this,&Signal::getHoleSignalToBeConvoluted,tmin,tmax,2);

  sprintf(fname,"%s_electtobeconv",_name.c_str());
  _electToBeConvolutedfunc = new TF1(fname,this,&Signal::getElectronSignalToBeConvoluted,tmin,tmax,2);

  sprintf(fname,"%s_holelatobeconv",_name.c_str());
  _holeLADriftToBeConvolutedfunc = new TF1(fname,this,&Signal::getHoleLADriftToBeConvoluted,tmin,tmax,2);

  sprintf(fname,"%s_electlatobeconv",_name.c_str());
  _electLADriftToBeConvolutedfunc = new TF1(fname,this,&Signal::getElectronLADriftToBeConvoluted,tmin,tmax,2);

  if(_decoPulse==0) {
    sprintf(fname,"%s_decopulse",_name.c_str());
    _decoPulse = new TF1(fname,"gaus",-200e-9,200e-9);
    _decoPulse->SetParameters(1.,0.,11e-9);
    _pulseowner = true;
  }


}

Signal::~Signal() {

  delete _signalFractionfunc;
  delete _signalFractionfuncaux;
  delete _signalFractionVsTimefunc;
  delete _currentSignalVsTimefunc;
  delete _weightedPositionfunc;
  delete _weightedPositionfuncaux;
  delete _weightedPositionVsTimefunc;
  delete _weightedLADriftfuncaux;
  delete _weightedLADriftVsTimefunc;
  delete _chargeBarycenterfunc;
  delete _laDriftBarycenterfunc;

  delete _holeToBeConvolutedfunc;
  delete _electToBeConvolutedfunc;
  delete _holeLADriftToBeConvolutedfunc;
  delete _electLADriftToBeConvolutedfunc;

  if(_pulseowner) delete _decoPulse;

}



TF1* Signal::SignalFractionFunc() const {
  //  if(_signalFractionfunc->GetXaxis()!=0 && _signalFractionfunc->GetYaxis()!=0) {
  //    _signalFractionfunc->GetXaxis()->SetTitle("depth [m]");
  //    _signalFractionfunc->GetYaxis()->SetTitle("Signal Fraction");
  //  }
  return _signalFractionfunc;
}
TF2* Signal::SignalFractionVsTimeFunc() const {
  //  if(_signalFractionVsTimefunc->GetXaxis()!=0 && _signalFractionVsTimefunc->GetYaxis()!=0) {
  //    _signalFractionVsTimefunc->GetXaxis()->SetTitle("depth [m]");
  //    _signalFractionVsTimefunc->GetYaxis()->SetTitle("time [s]");
  //  }
  return _signalFractionVsTimefunc;
}
TF2* Signal::CurrentSignalVsTimeFunc() const {
  //  if(_currentSignalVsTimefunc->GetXaxis()!=0 && _currentSignalVsTimefunc->GetYaxis()!=0) {
  //    _currentSignalVsTimefunc->GetXaxis()->SetTitle("depth [m]");
  //    _currentSignalVsTimefunc->GetYaxis()->SetTitle("time [s]");
  //  }
  return _currentSignalVsTimefunc;
}
TF1* Signal::TotalSignalFunc() const {
  //  if(_totalSignalfunc->GetXaxis()!=0 && _totalSignalfunc->GetYaxis()!=0) {
  //    _totalSignalfunc->GetXaxis()->SetTitle("time [s]");
  //    _totalSignalfunc->GetYaxis()->SetTitle("Signal [a.u]");
  //  }
  return _totalSignalfunc;
}
TF1* Signal::WeightedPositionFunc() const {
  //  if(_weightedPositionfunc->GetXaxis()!=0 && _weightedPositionfunc->GetYaxis()!=0) {
  //    _weightedPositionfunc->GetXaxis()->SetTitle("depth [m]");
  //    _weightedPositionfunc->GetYaxis()->SetTitle("Signal*depth [m]");
  //  }
  return _weightedPositionfunc;
}
TF2* Signal::WeightedPositionVsTimeFunc() const {
  return _weightedPositionVsTimefunc;
}
TF2* Signal::WeightedLADriftVsTimeFunc() const {
  return _weightedLADriftVsTimefunc;
}
TF1* Signal::ChargeBarycenterFunc() const {
  //  if(_chargeBarycenterfunc->GetXaxis()!=0 && _chargeBarycenterfunc->GetYaxis()!=0) {
  //    _chargeBarycenterfunc->GetXaxis()->SetTitle("time [s]");
  //    _chargeBarycenterfunc->GetYaxis()->SetTitle("Barycenter depth [m]");
  //  }
  return _chargeBarycenterfunc;}

TF1* Signal::LADriftBarycenterFunc() const {
  return _laDriftBarycenterfunc;}


void Signal::SaveFunctions(const int npsig, const int npcurrx, const int npcurry, const int nplax, const int nplay) const {

  std::string filename = "result_" + _name + ".root";
  TFile file(filename.c_str(),"new");

  if(npsig>0) {
    SignalFractionVsTimeFunc()->SetNpx(npsig);
    SignalFractionVsTimeFunc()->SetNpy(npsig);
    SignalFractionVsTimeFunc()->Write();
  }

  if(npcurrx > 0 && npcurry > 0) {
    CurrentSignalVsTimeFunc()->SetNpx(npcurrx);
    CurrentSignalVsTimeFunc()->SetNpy(npcurry);
    CurrentSignalVsTimeFunc()->Write();
  }

  if(nplax > 0 && nplay > 0) {
    WeightedLADriftVsTimeFunc()->SetNpx(nplax);
    WeightedLADriftVsTimeFunc()->SetNpy(nplax);
    WeightedLADriftVsTimeFunc()->Write();
  }

  /*
  WeightedPositionVsTimeFunc()->SetNpx(npoint);
  WeightedPositionVsTimeFunc()->SetNpy(npoint);
  WeightedPositionVsTimeFunc()->Write();

  ChargeBarycenterFunc()->SetNpx(200);
  ChargeBarycenterFunc()->Write();
  */

  file.Close();
}

std::string Signal::getName() const { return _name;}

double Signal::getCurrentSignal(const double z, const double t0) const {

  double holes = 0;
  if(_holed && _efield) {
    
    if(t0<=_holed->GenericDriftTimeFunc()->Eval(z,0)) {
      _holed->ToDriftTimeFunc()->SetParameter(0,z);
      //      double position = _holed->ToDriftTimeFunc()->GetX(t0,0,_sens->getThickness());
      // position looked for outside the detector range
      double position = _holed->ToDriftTimeFunc()->GetX(t0,-10e-6,_sens->getThickness()+10e-6);
      // check if the position is within the detector range
      if(position<=z && position >=0 && position <=_sens->getThickness()) {
	holes = _efield->Weight()->Eval(position)*_holed->parallelVdriftFunc()->Eval(position);
      }
    }
  }
  double elects = 0;
  if(_electd && _efield) {
    
    if(t0<=_electd->GenericDriftTimeFunc()->Eval(z,_sens->getThickness())) {
      _electd->ToDriftTimeFunc()->SetParameter(0,z);
      //      double position = _electd->ToDriftTimeFunc()->GetX(t0,0,_sens->getThickness());
      double position = _electd->ToDriftTimeFunc()->GetX(t0,-10e-6,_sens->getThickness()+10e-6);
      if(position >= 0 && position<=_sens->getThickness() && position >=z) {
	elects =  -(_efield->Weight()->Eval(position)*_electd->parallelVdriftFunc()->Eval(position));
      }
    }
  }


  return holes + elects;

}

double Signal::getSignalFraction(const double z, const double t0) const {

  if(_efield==0) {
    if(_holed) {
      double hdt = _holed->DriftTimeFunc()->Eval(z);
      //      cout << "ririecco " << endl;
      //      cout << "ririecco " << hdt << " " << z << " " << t0 << " " << (*_decoPulse)(t0-hdt) << endl;
      //      cout << _decoPulse << " " << t0-hdt << endl;
      //      return _decoPulse->Eval(t0-hdt);
      return (*_decoPulse)(t0-hdt);
    }
    else {
      return 0;
    }
  }
  else {

    /*
    double xmin =0.;
    if(_efield) xmin = _efield->Weight()->GetParameter(0);

    double ztrue = max(z,xmin);
    */

    double holes = 0.;
    if(_holeToBeConvolutedfunc) {
      
      _holeToBeConvolutedfunc->SetParameters(z,t0);
      holes = _holeToBeConvolutedfunc->Integral(0,z);

    }
    double elects = 0.;
    if(_electToBeConvolutedfunc) {
      
      _electToBeConvolutedfunc->SetParameters(z,t0);
      elects = _electToBeConvolutedfunc->Integral(z,_sens->getThickness());

    }

    return holes+elects;
  }

}

double Signal::getConvolutedLADrift(const double z, const double t0) const {

  if(_efield==0) {
    if(_holed) {
      double hdt = _holed->DriftTimeFunc()->Eval(z);
      double ladrift = _holed->GenericLorentzDriftFunc()->Eval(z,0);
      //      cout << "ririecco " << endl;
      //      cout << "ririecco " << hdt << " " << z << " " << t0 << " " << (*_decoPulse)(t0-hdt) << endl;
      //      cout << _decoPulse << " " << t0-hdt << endl;
      //      return _decoPulse->Eval(t0-hdt);
      return ladrift*(*_decoPulse)(t0-hdt);
    }
    else {
      return 0;
    }
  }
  else {

    /*
    double xmin =0.;
    if(_efield) xmin = _efield->Weight()->GetParameter(0);

    double ztrue = max(z,xmin);
    */

    double holes = 0.;
    if(_holeLADriftToBeConvolutedfunc) {
      
      _holeLADriftToBeConvolutedfunc->SetParameters(z,t0);
      holes = _holeLADriftToBeConvolutedfunc->Integral(0,z);

    }
    double elects = 0.;
    if(_electLADriftToBeConvolutedfunc) {
      
      _electLADriftToBeConvolutedfunc->SetParameters(z,t0);
      elects = _electLADriftToBeConvolutedfunc->Integral(z,_sens->getThickness());

    }

    return holes+elects;
  }

}

double Signal::signalToBeConvoluted(const double x, const double x0, const double t0, const Drift* drift) const {

  if(drift && _efield) {
    double dt = drift->GenericDriftTimeFunc()->Eval(x0,x);
    return (_efield->Weight()->Eval(x))*(_decoPulse->Eval(t0-dt));
  }
  else {
    return 0.;
  }
}

double Signal::laDriftToBeConvoluted(const double x, const double x0, const double t0, const Drift* drift) const {

  if(drift && _efield) {
    double dt = drift->GenericDriftTimeFunc()->Eval(x0,x);
    return (drift->GenericLorentzDriftFunc()->Eval(x0,x))*(_efield->Weight()->Eval(x))*(_decoPulse->Eval(t0-dt));
  }
  else {
    return 0.;
  }
}

double Signal::getHoleSignalToBeConvoluted(const double* x, const double* p) const {

  return signalToBeConvoluted(x[0],p[0],p[1],_holed);

    
}

double Signal::getElectronSignalToBeConvoluted(const double* x, const double* p) const {

  return signalToBeConvoluted(x[0],p[0],p[1],_electd);

    
}

double Signal::getHoleLADriftToBeConvoluted(const double* x, const double* p) const {

  return laDriftToBeConvoluted(x[0],p[0],p[1],_holed);

    
}

double Signal::getElectronLADriftToBeConvoluted(const double* x, const double* p) const {

  return laDriftToBeConvoluted(x[0],p[0],p[1],_electd);

    
}

double Signal::getSignalFraction1D(const double* x, const double* p) const {

  return getSignalFraction(x[0],p[0]);

}

double Signal::getSignalFraction2D(const double* x, const double*) const {

  return getSignalFraction(x[0],x[1]);

}

double Signal::getCurrentSignal2D(const double* x, const double*) const {

  return getCurrentSignal(x[0],x[1]);

}

double Signal::getTotalSignal(const double* x, const double*) const {

  _signalFractionfuncaux->SetParameter(0,x[0]);
  return _signalFractionfuncaux->Integral(0,_sens->getThickness())/_sens->getThickness();

}

double Signal::getWeightedPosition(const double* x, const double* p) const {

  return getSignalFraction(x[0],p[0])*x[0];

}

double Signal::getWeightedPosition2D(const double* x, const double*) const {

  return getSignalFraction(x[0],x[1])*x[0];

}

double Signal::getWeightedLADrift(const double* x, const double* p) const {

  return getConvolutedLADrift(x[0],p[0]);

}

double Signal::getWeightedLADrift2D(const double* x, const double*) const {

  return getConvolutedLADrift(x[0],x[1]);

}

double Signal::getChargeBarycenter(const double* x, const double*) const {

  _weightedPositionfuncaux->SetParameter(0,x[0]);
  double totsig = getTotalSignal(x,0);
  return totsig!=0 ? _weightedPositionfuncaux->Integral(0,_sens->getThickness())/(totsig*_sens->getThickness()) : 0;
}

double Signal::getLADriftBarycenter(const double* x, const double*) const {

  _weightedLADriftfuncaux->SetParameter(0,x[0]);
  double totsig = getTotalSignal(x,0);
  return totsig!=0 ? _weightedLADriftfuncaux->Integral(0,_sens->getThickness())/(totsig*_sens->getThickness()) : 0;
}



