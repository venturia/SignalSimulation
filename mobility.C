double mobility(double* x, double* param) {

  double dcm = param[3]/10000.;
  double ef = (param[1]-param[2])/dcm+(2*param[2]/dcm*(1-x[0]/param[3]));

  double mulow = 470.5*pow(param[0]/300,-2.5);
  double beta = 1.213*pow(param[0]/300,0.17);
  double vsat = 8370000*pow(param[0]/300,0.52);

  double mob = mulow/pow(1+pow(mulow*ef/vsat,beta),1/beta);

  return mob;

}

void mymobility() {
  TF1* f1 = new TF1("mymobility",mobility,0,500,4);
  f1->SetParameter(0,290.);
  f1->SetParameter(1,350.);
  f1->SetParameter(2,280.);
  f1->SetParameter(3,500.);
  f1->Draw();
}
