{
Mobility mob;

Pulse pp;
pp.decoPulse()->SetParameter(1,1);

TF1* gaus = new TF1("gaus","gaus",-200e-9,200e-9);
gaus->SetParameters(1.,0.,11e-9);

double vtobdepl=220.;
double vbias=300.;
double tobthick = 500e-6;
double vtibdepl=220.;
double tibthick = 300e-6;

Sensor tobdeco("deco",tobthick,vtobdepl,&mob,pp.decoPulse());
Sensor tobgaus("gaus",tobthick,vtobdepl,&mob,gaus);
Sensor tobdecoeconst("decoeconst",tobthick,0,&mob,pp.decoPulse());
Sensor tobgauseconst("gauseconst",tobthick,0,&mob,gaus);

Sensor tibdeco("tibdeco",tibthick,vtibdepl,&mob,pp.decoPulse());
Sensor tibgaus("tibgaus",tibthick,vtibdepl,&mob,gaus);

tobdeco.setVbias(vbias);
tobgaus.setVbias(vbias);
tobdecoeconst.setVbias(vbias);
tobgauseconst.setVbias(vbias);

tibdeco.setVbias(vbias);
tibgaus.setVbias(vbias);

tobdeco.SetLineColor(kRed);
tobgaus.SetLineColor(kRed);
tobgaus.SetLineStyle(2);
tobdecoeconst.SetLineColor(kBlue);
tobgauseconst.SetLineColor(kBlue);
tobgauseconst.SetLineStyle(2);

tibdeco.SetLineColor(kGreen);
tibgaus.SetLineColor(kGreen);
tibgaus.SetLineStyle(2);

new TCanvas("TIB","TIB");
tibdeco.ChargeBarycenterFunc()->Draw();
tibgaus.ChargeBarycenterFunc()->Draw("same");



new TCanvas("first","first");
tobdeco.ChargeBarycenterFunc()->Draw();
tobgaus.ChargeBarycenterFunc()->Draw("same");
tobdecoeconst.ChargeBarycenterFunc()->Draw("same");
tobgauseconst.ChargeBarycenterFunc()->Draw("same");
TLine linedeco(6e-9,0,6e-9,235.2e-6);
linedeco.SetLineColor(kRed);
linedeco.Draw();
TLine linedeco2(-40e-9,235.2e-6,6e-9,235.2e-6);
linedeco2.SetLineColor(kRed);
linedeco2.Draw();
TLine linedecoeconst(7.75e-9,0,7.75e-9,246.5e-6);
linedecoeconst.SetLineColor(kBlue);
linedecoeconst.Draw();
TLine linedecoeconst2(-40e-9,246.5e-6,7.75e-9,246.5e-6);
linedecoeconst2.SetLineColor(kBlue);
linedecoeconst2.Draw();
TLine linegaus(9e-9,0,9e-9,237.3e-6);
linegaus.SetLineColor(kRed);
linegaus.SetLineStyle(2);
linegaus.Draw();
TLine linegaus2(-40e-9,237.3e-6,9e-9,237.3e-6);
linegaus2.SetLineColor(kRed);
linegaus2.SetLineStyle(2);
linegaus2.Draw();
TLine linegauseconst(11e-9,0,11e-9,251e-6);
linegauseconst.SetLineColor(kBlue);
linegauseconst.SetLineStyle(2);
linegauseconst.Draw();
TLine linegauseconst2(-40e-9,251e-6,11e-9,251e-6);
linegauseconst2.SetLineColor(kBlue);
linegauseconst2.SetLineStyle(2);
linegauseconst2.Draw();

new TCanvas("env","env",1050,750);
gPad->Divide(2,2);
gPad->GetCanvas()->cd(1);
tobdeco.EfieldFunc()->Draw();
tobdecoeconst.EfieldFunc()->Draw("same");
gPad->GetCanvas()->cd(2);
tobdeco.MobilityFunc()->Draw();
tobdecoeconst.MobilityFunc()->Draw("same");
gPad->GetCanvas()->cd(3);
tobdeco.parallelVdriftFunc()->Draw();
tobdecoeconst.parallelVdriftFunc()->Draw("same");
gPad->GetCanvas()->cd(4);
tobdeco.DriftTimeFunc()->Draw();
tobdecoeconst.DriftTimeFunc()->Draw("same");

/*
new TCanvas("pulses","pulses");
pp.decoPulse()->Draw();
gaus->SetLineStyle(2);
gaus->Draw("same");
*/

new TCanvas("signal","signal",1050,750);
gPad->Divide(2,2);

gPad->GetCanvas()->cd(1);
gStyle->SetPalette(1,0);
tobdeco.SignalFractionVsTimeFunc()->SetNpx(500);
tobdeco.SignalFractionVsTimeFunc()->SetNpy(500);
tobdeco.SignalFractionVsTimeFunc()->Draw("colz");

gPad->GetCanvas()->cd(2);
tobdeco.SignalFractionFunc()->SetParameter(0,15e-9);
tobdeco.SignalFractionFunc()->Draw();
tobgaus.SignalFractionFunc()->SetParameter(0,15e-9);
tobgaus.SignalFractionFunc()->SetLineStyle(2);
tobgaus.SignalFractionFunc()->Draw("same");


gPad->GetCanvas()->cd(3);
tobgauseconst.TotalSignalFunc()->Draw();
tobdeco.TotalSignalFunc()->Draw("same");
tobdecoeconst.TotalSignalFunc()->Draw("same");
tobgaus.TotalSignalFunc()->Draw("same");

gPad->GetCanvas()->cd(4);
tobdeco.ChargeBarycenterFunc()->Draw();
tobgaus.ChargeBarycenterFunc()->Draw("same");
tobdecoeconst.ChargeBarycenterFunc()->Draw("same");
tobgauseconst.ChargeBarycenterFunc()->Draw("same");






//delete gaus;
}





}
