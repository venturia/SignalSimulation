{

gROOT->ProcessLine(".x /afs/cern.ch/user/v/venturia/PeakVsDecoAlignment/LoadLibraries.C");

// Mobilities

Mobility mobholes;
Mobility mobelects(-1417e-4,1.07e5,1.109,1.15);

// Pulses

Pulse pp;
pp.decoPulse()->SetParameter(1,1);
pp.peakPulse()->SetParameter(1,2);

TF1* gaus = new TF1("gaus","gaus",-200e-9,200e-9);
gaus->SetParameters(1./(sqrt(2*3.14159)*1e-9),0.,1e-9);

// Sensors

double vtobdepl=220.;
double vbias=300.;
double tobthick = 500e-6;
double tibthick = 300e-6;

Sensor tob("tob",tobthick,vtobdepl);
tob.setVbias(vbias);
tob.SetLineColor(kRed);
tob.setBField(3.8);

Sensor tobnodepl("tobnodepl",tobthick,0.);
tobnodepl.setVbias(vbias);
tobnodepl.SetLineColor(kBlue);
tobnodepl.setBField(3.8);

// Efield for signal creations

EfieldTotal ef("field1",tob.getThickness(),100e-6,10e-6,1.);
ef.Weight()->SetParameter(0,1e-6);
ef.setMode(Efield::Depth);

EfieldTotal ef7("field7",tob.getThickness(),100e-6,10e-6,1.);
ef7.Weight()->SetParameter(0,10e-6);
ef7.setMode(Efield::Depth);

EfieldTotal ef8("field8",tob.getThickness(),122e-6,10e-6,1.);
ef8.Weight()->SetParameter(0,10e-6);
ef8.setMode(Efield::Depth);

EfieldTotal ef9("field9",tob.getThickness(),183e-6,10e-6,1.);
ef9.Weight()->SetParameter(0,10e-6);
ef9.setMode(Efield::Depth);

EfieldAlone ef2("field2",tob.getThickness(),100e-6,10e-6,1.);
ef2.Weight()->SetParameter(0,0.1e-6);
ef2.setMode(Efield::Depth);

EfieldAlone ef3("field3",tob.getThickness(),100e-6,10e-6,1.);
ef3.Weight()->SetParameter(0,1e-6);
ef3.setMode(Efield::Depth);

EfieldAlone ef4("field4",tob.getThickness(),100e-6,10e-6,1.);
ef4.Weight()->SetParameter(0,10e-6);
ef4.setMode(Efield::Depth);

EfieldAlone ef5("field5",tob.getThickness(),100e-6,10e-6,1.);
ef5.Weight()->SetParameter(0,0.01e-6);
ef5.setMode(Efield::Depth);

EfieldAlone ef6("field6",tob.getThickness(),100e-6,10e-6,1.);
ef6.Weight()->SetParameter(0,0.001e-6);
ef6.setMode(Efield::Depth);

// Drift

Drift hole("holes",&mobholes,&tob);
Drift elect("elects",&mobelects,&tob);

hole.SetLineColor(kRed);

Drift holenodep("holesnodep",&mobholes,&tobnodepl);
Drift electnodep("electsnodep",&mobelects,&tobnodepl);

holenodep.SetLineColor(kBlue);

// Signals

Signal sig("sig_tob_total_1um_deco_bfield",&tob,&hole,&elect,&ef,pp.decoPulse());
Signal sig7("sig_tob_total_10um_deco_bfield",&tob,&hole,&elect,&ef7,pp.decoPulse());
Signal sig8("sig_tob_total_10um-122_deco_bfield",&tob,&hole,&elect,&ef8,pp.decoPulse());
Signal sig9("sig_tob_total_10um-183_deco_bfield",&tob,&hole,&elect,&ef9,pp.decoPulse());
Signal sig2("sig_tob_alone_01um_deco",&tob,&hole,&elect,&ef2,pp.decoPulse());
Signal sig3("sig_tob_alone_1um_deco",&tob,&hole,&elect,&ef3,pp.decoPulse());
Signal sig4("sig_tob_alone_10um_deco",&tob,&hole,&elect,&ef4,pp.decoPulse());
Signal sig5("sig_tob_alone_001um_deco",&tob,&hole,&elect,&ef5,pp.decoPulse());
Signal sig6("sig_tob_alone_0001um_deco",&tob,&hole,&elect,&ef6,pp.decoPulse());

Signal sigdelta("sig_tob_delta_deco_bfield",&tob,&hole,&elect,0,pp.decoPulse());

Signal signodepl("sig_tob_nodepl_total_1um_deco_bfield",&tobnodepl,&holenodep,&electnodep,&ef,pp.decoPulse());
Signal sig7nodepl("sig_tob_nodepl_total_10um_deco_bfield",&tobnodepl,&holenodep,&electnodep,&ef7,pp.decoPulse());
Signal sig8nodepl("sig_tob_nodepl_total_10um-122_deco_bfield",&tobnodepl,&holenodep,&electnodep,&ef8,pp.decoPulse());
Signal sig9nodepl("sig_tob_nodepl_total_10um-183_deco_bfield",&tobnodepl,&holenodep,&electnodep,&ef9,pp.decoPulse());
Signal sig2nodepl("sig_tob_nodepl_alone_01um_deco",&tobnodepl,&holenodep,&electnodep,&ef2,pp.decoPulse());
Signal sig3nodepl("sig_tob_nodepl_alone_1um_deco",&tobnodepl,&holenodep,&electnodep,&ef3,pp.decoPulse());
Signal sig4nodepl("sig_tob_nodepl_alone_10um_deco",&tobnodepl,&holenodep,&electnodep,&ef4,pp.decoPulse());
Signal sig5nodepl("sig_tob_nodepl_alone_001um_deco",&tobnodepl,&holenodep,&electnodep,&ef5,pp.decoPulse());
Signal sig6nodepl("sig_tob_nodepl_alone_0001um_deco",&tobnodepl,&holenodep,&electnodep,&ef6,pp.decoPulse());

Signal sigdeltanodepl("sig_tob_nodepl_delta_deco_bfield",&tobnodepl,&holenodep,&electnodep,0,pp.decoPulse());

Signal peaksig("sig_tob_total_1um_peak_bfield",&tob,&hole,&elect,&ef,pp.peakPulse());
Signal peaksig7("sig_tob_total_10um_peak_bfield",&tob,&hole,&elect,&ef7,pp.peakPulse());
Signal peaksig8("sig_tob_total_10um-122_peak_bfield",&tob,&hole,&elect,&ef8,pp.peakPulse());
Signal peaksig9("sig_tob_total_10um-183_peak_bfield",&tob,&hole,&elect,&ef9,pp.peakPulse());
Signal peaksig2("sig_tob_alone_01um_peak",&tob,&hole,&elect,&ef2,pp.peakPulse());
Signal peaksig3("sig_tob_alone_1um_peak",&tob,&hole,&elect,&ef3,pp.peakPulse());
Signal peaksig4("sig_tob_alone_10um_peak",&tob,&hole,&elect,&ef4,pp.peakPulse());
Signal peaksig5("sig_tob_alone_001um_peak",&tob,&hole,&elect,&ef5,pp.peakPulse());
Signal peaksig6("sig_tob_alone_0001um_peak",&tob,&hole,&elect,&ef6,pp.peakPulse());

Signal peaksigdelta("sig_tob_delta_peak_bfield",&tob,&hole,&elect,0,pp.peakPulse());

Signal peaksignodepl("sig_tob_nodepl_total_1um_peak_bfield",&tobnodepl,&holenodep,&electnodep,&ef,pp.peakPulse());
Signal peaksig7nodepl("sig_tob_nodepl_total_10um_peak_bfield",&tobnodepl,&holenodep,&electnodep,&ef7,pp.peakPulse());
Signal peaksig8nodepl("sig_tob_nodepl_total_10um-122_peak_bfield",&tobnodepl,&holenodep,&electnodep,&ef8,pp.peakPulse());
Signal peaksig9nodepl("sig_tob_nodepl_total_10um-183_peak_bfield",&tobnodepl,&holenodep,&electnodep,&ef9,pp.peakPulse());
Signal peaksig2nodepl("sig_tob_nodepl_alone_01um_peak",&tobnodepl,&holenodep,&electnodep,&ef2,pp.peakPulse());
Signal peaksig3nodepl("sig_tob_nodepl_alone_1um_peak",&tobnodepl,&holenodep,&electnodep,&ef3,pp.peakPulse());
Signal peaksig4nodepl("sig_tob_nodepl_alone_10um_peak",&tobnodepl,&holenodep,&electnodep,&ef4,pp.peakPulse());
Signal peaksig5nodepl("sig_tob_nodepl_alone_001um_peak",&tobnodepl,&holenodep,&electnodep,&ef5,pp.peakPulse());
Signal peaksig6nodepl("sig_tob_nodepl_alone_0001um_peak",&tobnodepl,&holenodep,&electnodep,&ef6,pp.peakPulse());

Signal peaksigdeltanodepl("sig_tob_nodepl_delta_peak_bfield",&tobnodepl,&holenodep,&electnodep,0,pp.peakPulse());

gSystem->cd("data");

}
