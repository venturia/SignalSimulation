#ifndef PULSE_H
#define PULSE_H

class TF1;

class Pulse {

 public:

  Pulse(const double bx=25e-9, const double ratio=2.);
  ~Pulse();

  TF1* peakPulse() const;
  TF1* decoPulse() const;

 private:
  double peakpulse(const double* x, const double* p) const;
  double decopulse(const double* x, const double* p) const;

  const double _bx;
  const double _ratio;
  TF1* _peakfunc;
  TF1* _decofunc;

};


#endif // PULSE_H
