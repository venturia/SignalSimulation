{

Mobility mobholes;
Mobility mobelects(-1417e-4,1.07e5,1.109,1.15);

Pulse pp;
pp.decoPulse()->SetParameter(1,1);

TF1* gaus = new TF1("gaus","gaus",-200e-9,200e-9);
gaus->SetParameters(1./(sqrt(2*3.14159)*1e-9),0.,1e-9);


double vtobdepl=220.;
double vbias=300.;
double tobthick = 500e-6;

Sensor tobdeco("deco",tobthick,vtobdepl,&mobholes,pp.decoPulse());
tobdeco.setVbias(vbias);
tobdeco.SetLineColor(kRed);

//Sensor tobgaus("deco",tobthick,vtobdepl,&mobholes,gaus);
//tobgaus.setVbias(vbias);
//tobgaus.SetLineColor(kBlue);


EfieldTotal ef("field1",tobdeco.getThickness(),100e-6,10e-6,1.);
ef.Weight()->SetParameter(0,1e-6);
ef.setMode(Efield::Depth);

EfieldAlone ef2("field2",tobdeco.getThickness(),100e-6,10e-6,1.);
ef2.Weight()->SetParameter(0,1e-6);
ef2.setMode(Efield::Depth);

Drift hole("holes",&mobholes,&tobdeco.EfieldFunc(),0,tobdeco.getThickness());
Drift elect("elects",&mobelects,&tobdeco.EfieldFunc(),0,tobdeco.getThickness());

Signal sig("allsig",&tobdeco,&hole,&elect,&ef,pp.decoPulse());
Signal sig2("allsig2",&tobdeco,&hole,&elect,&ef2,pp.decoPulse());
Signal sigdelta("deltasig",&tobdeco,&hole,&elect,0,pp.decoPulse());

Signal sighole("holesig",&tobdeco,&hole,0,&ef,pp.decoPulse());

Signal siggaus("allsiggaus",&tobdeco,&hole,&elect,&ef,gaus);
Signal siggaus2("allsiggaus2",&tobdeco,&hole,&elect,&ef2,gaus);

}
