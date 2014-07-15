#ifndef EFIELD_H
#define EFIELD_H

class TF1;

class Efield {

 public:

  virtual ~Efield();
  virtual TF1* Weight() const = 0;

  enum {Spherical, Depth, Width};



};


#endif // EFIELD_H
