{
TGraph lapeak;
for(int i=0;i<100;i++) {
  double t0 = i*20.e-9/100.;
  lapeak.SetPoint(lapeak.GetN(),sffnodepl2.ChargeBarycenterSimplerFunc()->Eval(t0),sffnodepl2.LADriftBarycenterFunc()->Eval(t0));
}
TGraph ratpeak;
for(int i=0;i<100;i++) {
  double t0 = i*20.e-9/100.;
  ratpeak.SetPoint(ratpeak.GetN(),t0,sffnodepl2.LADriftBarycenterFunc()->Eval(t0)/sffnodepl2.ChargeBarycenterSimplerFunc()->Eval(t0));
}
}
