double mobilitymap(double* x, double* param) {

  const double Bfield = 3.8;

  double mob = (500-x[1])*param[1]+param[0];

  double tanla = mob*Bfield;
  
  double a = -param[1];
  double b =  param[0]+param[1]*500;

  double pot = param[2]*(x[0]+log(Bfield*(a*x[1]+b))/(Bfield*a));

//  return Bfield*(a*x[1]+b);
return pot;

}

void mymobilitymap() {
  TF2* f2 = new TF2("mymobilitymap",mobilitymap,0,5000,0,500,3);
  f2->SetParameter(0,0.02);
  f2->SetParameter(1,0.02/500.);
  f2->SetParameter(2,1.);
  f2->Draw("arrow");
  f2->Draw("same");
}
