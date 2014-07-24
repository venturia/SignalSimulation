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

// Sensors for thickness scan

 int thickts[12] = {275,300,325,350,375,400,450,500,175,200,225,250};

 Sensor* tobts[12];
 Sensor* tobtsnodepl[12];

 for(unsigned int it=0;it<12;++it) {

   char tobname[20];
   sprintf(tobname,"tob_%d",thickts[it]);
   tobts[it]= new Sensor(tobname,thickts[it]*1.e-6,vtobdepl);
   tobts[it]->setVbias(vbias);
   tobts[it]->SetLineColor(kRed);
   tobts[it]->setBField(3.8);

   sprintf(tobname,"tobnodepl_%d",thickts[it]);
   tobtsnodepl[it]= new Sensor(tobname,thickts[it]*1.e-6,0.);
   tobtsnodepl[it]->setVbias(vbias);
   tobtsnodepl[it]->SetLineColor(kRed);
   tobtsnodepl[it]->setBField(3.8);

 }

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

// Efield for thickness scan

 EfieldTotal* efts[12];
 EfieldTotal* eftsnodepl[12];
 EfieldAlone* eftsalone10u[12];
 EfieldAlone* eftsalone1u[12];

 for(unsigned int it=0;it<12;++it) {
   char fieldname[20];
   sprintf(fieldname,"fieldt_%d",thickts[it]);
   efts[it] = new EfieldTotal(fieldname,tobts[it]->getThickness(),100e-6,10e-6,1.);
   efts[it]->Weight()->SetParameter(0,1e-6);
   efts[it]->setMode(Efield::Depth);

   sprintf(fieldname,"fieldtnodepl_%d",thickts[it]);
   eftsnodepl[it] = new EfieldTotal(fieldname,tobtsnodepl[it]->getThickness(),100e-6,10e-6,1.);
   eftsnodepl[it]->Weight()->SetParameter(0,1e-6);
   eftsnodepl[it]->setMode(Efield::Depth);

   sprintf(fieldname,"fieldtalone10u_%d",thickts[it]);
   eftsalone10u[it] = new EfieldAlone(fieldname,tobts[it]->getThickness(),100e-6,10e-6,1.);
   eftsalone10u[it]->Weight()->SetParameter(0,10e-6);
   eftsalone10u[it]->setMode(Efield::Depth);

   sprintf(fieldname,"fieldtalone1u_%d",thickts[it]);
   eftsalone1u[it] = new EfieldAlone(fieldname,tobts[it]->getThickness(),100e-6,10e-6,1.);
   eftsalone1u[it]->Weight()->SetParameter(0,1e-6);
   eftsalone1u[it]->setMode(Efield::Depth);
 }  

// Drift

Drift hole("holes",&mobholes,&tob);
Drift elect("elects",&mobelects,&tob);

hole.SetLineColor(kRed);

Drift holenodep("holesnodep",&mobholes,&tobnodepl);
Drift electnodep("electsnodep",&mobelects,&tobnodepl);

holenodep.SetLineColor(kBlue);

// Drift for thickness scan

 Drift* holets[12];
 Drift* electts[12];
 Drift* holetsnodepl[12];
 Drift* electtsnodepl[12];

 for(unsigned int it=0;it<12;++it) {
   char holename[20];
   sprintf(holename,"holests_%d",thickts[it]);
   char electname[20];
   sprintf(electname,"electsts_%d",thickts[it]);
   holets[it] = new Drift(holename,&mobholes,tobts[it]);
   electts[it] = new Drift(electname,&mobelects,tobts[it]);
   sprintf(holename,"holestsnodepl_%d",thickts[it]);
   sprintf(electname,"electstsnodepl_%d",thickts[it]);
   holetsnodepl[it] = new Drift(holename,&mobholes,tobtsnodepl[it]);
   electtsnodepl[it] = new Drift(electname,&mobelects,tobtsnodepl[it]);

 }

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

// Signal for thickness scan

 Signal tssigdeco0("sig_275_total_1um_deco_bfield",tobts[0],holets[0],electts[0],efts[0],pp.decoPulse());
 Signal tssigdeco1("sig_300_total_1um_deco_bfield",tobts[1],holets[1],electts[1],efts[1],pp.decoPulse());
 Signal tssigdeco2("sig_325_total_1um_deco_bfield",tobts[2],holets[2],electts[2],efts[2],pp.decoPulse());
 Signal tssigdeco3("sig_350_total_1um_deco_bfield",tobts[3],holets[3],electts[3],efts[3],pp.decoPulse());
 Signal tssigdeco4("sig_375_total_1um_deco_bfield",tobts[4],holets[4],electts[4],efts[4],pp.decoPulse());
 Signal tssigdeco5("sig_400_total_1um_deco_bfield",tobts[5],holets[5],electts[5],efts[5],pp.decoPulse());
 Signal tssigdeco6("sig_450_total_1um_deco_bfield",tobts[6],holets[6],electts[6],efts[6],pp.decoPulse());
 Signal tssigdeco7("sig_500_total_1um_deco_bfield",tobts[7],holets[7],electts[7],efts[7],pp.decoPulse());
 Signal tssigdeco8("sig_175_total_1um_deco_bfield",tobts[8],holets[8],electts[8],efts[8],pp.decoPulse());
 Signal tssigdeco9("sig_200_total_1um_deco_bfield",tobts[9],holets[9],electts[9],efts[9],pp.decoPulse());
 Signal tssigdeco10("sig_225_total_1um_deco_bfield",tobts[10],holets[10],electts[10],efts[10],pp.decoPulse());
 Signal tssigdeco11("sig_250_total_1um_deco_bfield",tobts[11],holets[11],electts[11],efts[11],pp.decoPulse());

 Signal tssigpeak0("sig_275_total_1um_peak_bfield",tobts[0],holets[0],electts[0],efts[0],pp.peakPulse());
 Signal tssigpeak1("sig_300_total_1um_peak_bfield",tobts[1],holets[1],electts[1],efts[1],pp.peakPulse());
 Signal tssigpeak2("sig_325_total_1um_peak_bfield",tobts[2],holets[2],electts[2],efts[2],pp.peakPulse());
 Signal tssigpeak3("sig_350_total_1um_peak_bfield",tobts[3],holets[3],electts[3],efts[3],pp.peakPulse());
 Signal tssigpeak4("sig_375_total_1um_peak_bfield",tobts[4],holets[4],electts[4],efts[4],pp.peakPulse());
 Signal tssigpeak5("sig_400_total_1um_peak_bfield",tobts[5],holets[5],electts[5],efts[5],pp.peakPulse());
 Signal tssigpeak6("sig_450_total_1um_peak_bfield",tobts[6],holets[6],electts[6],efts[6],pp.peakPulse());
 Signal tssigpeak7("sig_500_total_1um_peak_bfield",tobts[7],holets[7],electts[7],efts[7],pp.peakPulse());
 Signal tssigpeak8("sig_175_total_1um_peak_bfield",tobts[8],holets[8],electts[8],efts[8],pp.peakPulse());
 Signal tssigpeak9("sig_200_total_1um_peak_bfield",tobts[9],holets[9],electts[9],efts[9],pp.peakPulse());
 Signal tssigpeak10("sig_225_total_1um_peak_bfield",tobts[10],holets[10],electts[10],efts[10],pp.peakPulse());
 Signal tssigpeak11("sig_250_total_1um_peak_bfield",tobts[11],holets[11],electts[11],efts[11],pp.peakPulse());

 Signal tssignodepldeco0("sig_275_total_1um_deco_bfield_nodepl",tobtsnodepl[0],holetsnodepl[0],electtsnodepl[0],eftsnodepl[0],pp.decoPulse());
 Signal tssignodepldeco1("sig_300_total_1um_deco_bfield_nodepl",tobtsnodepl[1],holetsnodepl[1],electtsnodepl[1],eftsnodepl[1],pp.decoPulse());
 Signal tssignodepldeco2("sig_325_total_1um_deco_bfield_nodepl",tobtsnodepl[2],holetsnodepl[2],electtsnodepl[2],eftsnodepl[2],pp.decoPulse());
 Signal tssignodepldeco3("sig_350_total_1um_deco_bfield_nodepl",tobtsnodepl[3],holetsnodepl[3],electtsnodepl[3],eftsnodepl[3],pp.decoPulse());
 Signal tssignodepldeco4("sig_375_total_1um_deco_bfield_nodepl",tobtsnodepl[4],holetsnodepl[4],electtsnodepl[4],eftsnodepl[4],pp.decoPulse());
 Signal tssignodepldeco5("sig_400_total_1um_deco_bfield_nodepl",tobtsnodepl[5],holetsnodepl[5],electtsnodepl[5],eftsnodepl[5],pp.decoPulse());
 Signal tssignodepldeco6("sig_450_total_1um_deco_bfield_nodepl",tobtsnodepl[6],holetsnodepl[6],electtsnodepl[6],eftsnodepl[6],pp.decoPulse());
 Signal tssignodepldeco7("sig_500_total_1um_deco_bfield_nodepl",tobtsnodepl[7],holetsnodepl[7],electtsnodepl[7],eftsnodepl[7],pp.decoPulse());
 Signal tssignodepldeco8("sig_175_total_1um_deco_bfield_nodepl",tobtsnodepl[8],holetsnodepl[8],electtsnodepl[8],eftsnodepl[8],pp.decoPulse());
 Signal tssignodepldeco9("sig_200_total_1um_deco_bfield_nodepl",tobtsnodepl[9],holetsnodepl[9],electtsnodepl[9],eftsnodepl[9],pp.decoPulse());
 Signal tssignodepldeco10("sig_225_total_1um_deco_bfield_nodepl",tobtsnodepl[10],holetsnodepl[10],electtsnodepl[10],eftsnodepl[10],pp.decoPulse());
 Signal tssignodepldeco11("sig_250_total_1um_deco_bfield_nodepl",tobtsnodepl[11],holetsnodepl[11],electtsnodepl[11],eftsnodepl[11],pp.decoPulse());

 Signal tssignodeplpeak0("sig_275_total_1um_peak_bfield_nodepl",tobtsnodepl[0],holetsnodepl[0],electtsnodepl[0],eftsnodepl[0],pp.peakPulse());
 Signal tssignodeplpeak1("sig_300_total_1um_peak_bfield_nodepl",tobtsnodepl[1],holetsnodepl[1],electtsnodepl[1],eftsnodepl[1],pp.peakPulse());
 Signal tssignodeplpeak2("sig_325_total_1um_peak_bfield_nodepl",tobtsnodepl[2],holetsnodepl[2],electtsnodepl[2],eftsnodepl[2],pp.peakPulse());
 Signal tssignodeplpeak3("sig_350_total_1um_peak_bfield_nodepl",tobtsnodepl[3],holetsnodepl[3],electtsnodepl[3],eftsnodepl[3],pp.peakPulse());
 Signal tssignodeplpeak4("sig_375_total_1um_peak_bfield_nodepl",tobtsnodepl[4],holetsnodepl[4],electtsnodepl[4],eftsnodepl[4],pp.peakPulse());
 Signal tssignodeplpeak5("sig_400_total_1um_peak_bfield_nodepl",tobtsnodepl[5],holetsnodepl[5],electtsnodepl[5],eftsnodepl[5],pp.peakPulse());
 Signal tssignodeplpeak6("sig_450_total_1um_peak_bfield_nodepl",tobtsnodepl[6],holetsnodepl[6],electtsnodepl[6],eftsnodepl[6],pp.peakPulse());
 Signal tssignodeplpeak7("sig_500_total_1um_peak_bfield_nodepl",tobtsnodepl[7],holetsnodepl[7],electtsnodepl[7],eftsnodepl[7],pp.peakPulse());
 Signal tssignodeplpeak8("sig_175_total_1um_peak_bfield_nodepl",tobtsnodepl[8],holetsnodepl[8],electtsnodepl[8],eftsnodepl[8],pp.peakPulse());
 Signal tssignodeplpeak9("sig_200_total_1um_peak_bfield_nodepl",tobtsnodepl[9],holetsnodepl[9],electtsnodepl[9],eftsnodepl[9],pp.peakPulse());
 Signal tssignodeplpeak10("sig_225_total_1um_peak_bfield_nodepl",tobtsnodepl[10],holetsnodepl[10],electtsnodepl[10],eftsnodepl[10],pp.peakPulse());
 Signal tssignodeplpeak11("sig_250_total_1um_peak_bfield_nodepl",tobtsnodepl[11],holetsnodepl[11],electtsnodepl[11],eftsnodepl[11],pp.peakPulse());

 Signal tssigdeltadeco0("sig_275_delta_deco_bfield",tobts[0],holets[0],electts[0],0,pp.decoPulse());
 Signal tssigdeltadeco1("sig_300_delta_deco_bfield",tobts[1],holets[1],electts[1],0,pp.decoPulse());
 Signal tssigdeltadeco2("sig_325_delta_deco_bfield",tobts[2],holets[2],electts[2],0,pp.decoPulse());
 Signal tssigdeltadeco3("sig_350_delta_deco_bfield",tobts[3],holets[3],electts[3],0,pp.decoPulse());
 Signal tssigdeltadeco4("sig_375_delta_deco_bfield",tobts[4],holets[4],electts[4],0,pp.decoPulse());
 Signal tssigdeltadeco5("sig_400_delta_deco_bfield",tobts[5],holets[5],electts[5],0,pp.decoPulse());
 Signal tssigdeltadeco6("sig_450_delta_deco_bfield",tobts[6],holets[6],electts[6],0,pp.decoPulse());
 Signal tssigdeltadeco7("sig_500_delta_deco_bfield",tobts[7],holets[7],electts[7],0,pp.decoPulse());
 Signal tssigdeltadeco8("sig_175_delta_deco_bfield",tobts[8],holets[8],electts[8],0,pp.decoPulse());
 Signal tssigdeltadeco9("sig_200_delta_deco_bfield",tobts[9],holets[9],electts[9],0,pp.decoPulse());
 Signal tssigdeltadeco10("sig_225_delta_deco_bfield",tobts[10],holets[10],electts[10],0,pp.decoPulse());
 Signal tssigdeltadeco11("sig_250_delta_deco_bfield",tobts[11],holets[11],electts[11],0,pp.decoPulse());

 Signal tssigdeltapeak0("sig_275_delta_peak_bfield",tobts[0],holets[0],electts[0],0,pp.peakPulse());
 Signal tssigdeltapeak1("sig_300_delta_peak_bfield",tobts[1],holets[1],electts[1],0,pp.peakPulse());
 Signal tssigdeltapeak2("sig_325_delta_peak_bfield",tobts[2],holets[2],electts[2],0,pp.peakPulse());
 Signal tssigdeltapeak3("sig_350_delta_peak_bfield",tobts[3],holets[3],electts[3],0,pp.peakPulse());
 Signal tssigdeltapeak4("sig_375_delta_peak_bfield",tobts[4],holets[4],electts[4],0,pp.peakPulse());
 Signal tssigdeltapeak5("sig_400_delta_peak_bfield",tobts[5],holets[5],electts[5],0,pp.peakPulse());
 Signal tssigdeltapeak6("sig_450_delta_peak_bfield",tobts[6],holets[6],electts[6],0,pp.peakPulse());
 Signal tssigdeltapeak7("sig_500_delta_peak_bfield",tobts[7],holets[7],electts[7],0,pp.peakPulse());
 Signal tssigdeltapeak8("sig_175_delta_peak_bfield",tobts[8],holets[8],electts[8],0,pp.peakPulse());
 Signal tssigdeltapeak9("sig_200_delta_peak_bfield",tobts[9],holets[9],electts[9],0,pp.peakPulse());
 Signal tssigdeltapeak10("sig_225_delta_peak_bfield",tobts[10],holets[10],electts[10],0,pp.peakPulse());
 Signal tssigdeltapeak11("sig_250_delta_peak_bfield",tobts[11],holets[11],electts[11],0,pp.peakPulse());

 Signal tssigdeltanodepldeco0("sig_275_delta_deco_bfield_nodepl",tobtsnodepl[0],holetsnodepl[0],electtsnodepl[0],0,pp.decoPulse());
 Signal tssigdeltanodepldeco1("sig_300_delta_deco_bfield_nodepl",tobtsnodepl[1],holetsnodepl[1],electtsnodepl[1],0,pp.decoPulse());
 Signal tssigdeltanodepldeco2("sig_325_delta_deco_bfield_nodepl",tobtsnodepl[2],holetsnodepl[2],electtsnodepl[2],0,pp.decoPulse());
 Signal tssigdeltanodepldeco3("sig_350_delta_deco_bfield_nodepl",tobtsnodepl[3],holetsnodepl[3],electtsnodepl[3],0,pp.decoPulse());
 Signal tssigdeltanodepldeco4("sig_375_delta_deco_bfield_nodepl",tobtsnodepl[4],holetsnodepl[4],electtsnodepl[4],0,pp.decoPulse());
 Signal tssigdeltanodepldeco5("sig_400_delta_deco_bfield_nodepl",tobtsnodepl[5],holetsnodepl[5],electtsnodepl[5],0,pp.decoPulse());
 Signal tssigdeltanodepldeco6("sig_450_delta_deco_bfield_nodepl",tobtsnodepl[6],holetsnodepl[6],electtsnodepl[6],0,pp.decoPulse());
 Signal tssigdeltanodepldeco7("sig_500_delta_deco_bfield_nodepl",tobtsnodepl[7],holetsnodepl[7],electtsnodepl[7],0,pp.decoPulse());
 Signal tssigdeltanodepldeco8("sig_175_delta_deco_bfield_nodepl",tobtsnodepl[8],holetsnodepl[8],electtsnodepl[8],0,pp.decoPulse());
 Signal tssigdeltanodepldeco9("sig_200_delta_deco_bfield_nodepl",tobtsnodepl[9],holetsnodepl[9],electtsnodepl[9],0,pp.decoPulse());
 Signal tssigdeltanodepldeco10("sig_225_delta_deco_bfield_nodepl",tobtsnodepl[10],holetsnodepl[10],electtsnodepl[10],0,pp.decoPulse());
 Signal tssigdeltanodepldeco11("sig_250_delta_deco_bfield_nodepl",tobtsnodepl[11],holetsnodepl[11],electtsnodepl[11],0,pp.decoPulse());

 Signal tssigdeltanodeplpeak0("sig_275_delta_peak_bfield_nodepl",tobtsnodepl[0],holetsnodepl[0],electtsnodepl[0],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak1("sig_300_delta_peak_bfield_nodepl",tobtsnodepl[1],holetsnodepl[1],electtsnodepl[1],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak2("sig_325_delta_peak_bfield_nodepl",tobtsnodepl[2],holetsnodepl[2],electtsnodepl[2],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak3("sig_350_delta_peak_bfield_nodepl",tobtsnodepl[3],holetsnodepl[3],electtsnodepl[3],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak4("sig_375_delta_peak_bfield_nodepl",tobtsnodepl[4],holetsnodepl[4],electtsnodepl[4],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak5("sig_400_delta_peak_bfield_nodepl",tobtsnodepl[5],holetsnodepl[5],electtsnodepl[5],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak6("sig_450_delta_peak_bfield_nodepl",tobtsnodepl[6],holetsnodepl[6],electtsnodepl[6],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak7("sig_500_delta_peak_bfield_nodepl",tobtsnodepl[7],holetsnodepl[7],electtsnodepl[7],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak8("sig_175_delta_peak_bfield_nodepl",tobtsnodepl[8],holetsnodepl[8],electtsnodepl[8],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak9("sig_200_delta_peak_bfield_nodepl",tobtsnodepl[9],holetsnodepl[9],electtsnodepl[9],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak10("sig_225_delta_peak_bfield_nodepl",tobtsnodepl[10],holetsnodepl[10],electtsnodepl[10],0,pp.peakPulse());
 Signal tssigdeltanodeplpeak11("sig_250_delta_peak_bfield_nodepl",tobtsnodepl[11],holetsnodepl[11],electtsnodepl[11],0,pp.peakPulse());

 Signal tssigalone10udeco0("sig_275_alone_10um_deco_bfield",tobts[0],holets[0],electts[0],eftsalone10u[0],pp.decoPulse());
 Signal tssigalone10udeco1("sig_300_alone_10um_deco_bfield",tobts[1],holets[1],electts[1],eftsalone10u[1],pp.decoPulse());
 Signal tssigalone10udeco2("sig_325_alone_10um_deco_bfield",tobts[2],holets[2],electts[2],eftsalone10u[2],pp.decoPulse());
 Signal tssigalone10udeco3("sig_350_alone_10um_deco_bfield",tobts[3],holets[3],electts[3],eftsalone10u[3],pp.decoPulse());
 Signal tssigalone10udeco4("sig_375_alone_10um_deco_bfield",tobts[4],holets[4],electts[4],eftsalone10u[4],pp.decoPulse());
 Signal tssigalone10udeco5("sig_400_alone_10um_deco_bfield",tobts[5],holets[5],electts[5],eftsalone10u[5],pp.decoPulse());
 Signal tssigalone10udeco6("sig_450_alone_10um_deco_bfield",tobts[6],holets[6],electts[6],eftsalone10u[6],pp.decoPulse());
 Signal tssigalone10udeco7("sig_500_alone_10um_deco_bfield",tobts[7],holets[7],electts[7],eftsalone10u[7],pp.decoPulse());
 Signal tssigalone10udeco8("sig_175_alone_10um_deco_bfield",tobts[8],holets[8],electts[8],eftsalone10u[8],pp.decoPulse());
 Signal tssigalone10udeco9("sig_200_alone_10um_deco_bfield",tobts[9],holets[9],electts[9],eftsalone10u[9],pp.decoPulse());
 Signal tssigalone10udeco10("sig_225_alone_10um_deco_bfield",tobts[10],holets[10],electts[10],eftsalone10u[10],pp.decoPulse());
 Signal tssigalone10udeco11("sig_250_alone_10um_deco_bfield",tobts[11],holets[11],electts[11],eftsalone10u[11],pp.decoPulse());

 Signal tssigalone10upeak0("sig_275_alone_10um_peak_bfield",tobts[0],holets[0],electts[0],eftsalone10u[0],pp.peakPulse());
 Signal tssigalone10upeak1("sig_300_alone_10um_peak_bfield",tobts[1],holets[1],electts[1],eftsalone10u[1],pp.peakPulse());
 Signal tssigalone10upeak2("sig_325_alone_10um_peak_bfield",tobts[2],holets[2],electts[2],eftsalone10u[2],pp.peakPulse());
 Signal tssigalone10upeak3("sig_350_alone_10um_peak_bfield",tobts[3],holets[3],electts[3],eftsalone10u[3],pp.peakPulse());
 Signal tssigalone10upeak4("sig_375_alone_10um_peak_bfield",tobts[4],holets[4],electts[4],eftsalone10u[4],pp.peakPulse());
 Signal tssigalone10upeak5("sig_400_alone_10um_peak_bfield",tobts[5],holets[5],electts[5],eftsalone10u[5],pp.peakPulse());
 Signal tssigalone10upeak6("sig_450_alone_10um_peak_bfield",tobts[6],holets[6],electts[6],eftsalone10u[6],pp.peakPulse());
 Signal tssigalone10upeak7("sig_500_alone_10um_peak_bfield",tobts[7],holets[7],electts[7],eftsalone10u[7],pp.peakPulse());
 Signal tssigalone10upeak8("sig_175_alone_10um_peak_bfield",tobts[8],holets[8],electts[8],eftsalone10u[8],pp.peakPulse());
 Signal tssigalone10upeak9("sig_200_alone_10um_peak_bfield",tobts[9],holets[9],electts[9],eftsalone10u[9],pp.peakPulse());
 Signal tssigalone10upeak10("sig_225_alone_10um_peak_bfield",tobts[10],holets[10],electts[10],eftsalone10u[10],pp.peakPulse());
 Signal tssigalone10upeak11("sig_250_alone_10um_peak_bfield",tobts[11],holets[11],electts[11],eftsalone10u[11],pp.peakPulse());


 Signal tssigalone1udeco0("sig_275_alone_1um_deco_bfield",tobts[0],holets[0],electts[0],eftsalone1u[0],pp.decoPulse());
 Signal tssigalone1udeco1("sig_300_alone_1um_deco_bfield",tobts[1],holets[1],electts[1],eftsalone1u[1],pp.decoPulse());
 Signal tssigalone1udeco2("sig_325_alone_1um_deco_bfield",tobts[2],holets[2],electts[2],eftsalone1u[2],pp.decoPulse());
 Signal tssigalone1udeco3("sig_350_alone_1um_deco_bfield",tobts[3],holets[3],electts[3],eftsalone1u[3],pp.decoPulse());
 Signal tssigalone1udeco4("sig_375_alone_1um_deco_bfield",tobts[4],holets[4],electts[4],eftsalone1u[4],pp.decoPulse());
 Signal tssigalone1udeco5("sig_400_alone_1um_deco_bfield",tobts[5],holets[5],electts[5],eftsalone1u[5],pp.decoPulse());
 Signal tssigalone1udeco6("sig_450_alone_1um_deco_bfield",tobts[6],holets[6],electts[6],eftsalone1u[6],pp.decoPulse());
 Signal tssigalone1udeco7("sig_500_alone_1um_deco_bfield",tobts[7],holets[7],electts[7],eftsalone1u[7],pp.decoPulse());
 Signal tssigalone1udeco8("sig_175_alone_1um_deco_bfield",tobts[8],holets[8],electts[8],eftsalone1u[8],pp.decoPulse());
 Signal tssigalone1udeco9("sig_200_alone_1um_deco_bfield",tobts[9],holets[9],electts[9],eftsalone1u[9],pp.decoPulse());
 Signal tssigalone1udeco10("sig_225_alone_1um_deco_bfield",tobts[10],holets[10],electts[10],eftsalone1u[10],pp.decoPulse());
 Signal tssigalone1udeco11("sig_250_alone_1um_deco_bfield",tobts[11],holets[11],electts[11],eftsalone1u[11],pp.decoPulse());

 Signal tssigalone1upeak0("sig_275_alone_1um_peak_bfield",tobts[0],holets[0],electts[0],eftsalone1u[0],pp.peakPulse());
 Signal tssigalone1upeak1("sig_300_alone_1um_peak_bfield",tobts[1],holets[1],electts[1],eftsalone1u[1],pp.peakPulse());
 Signal tssigalone1upeak2("sig_325_alone_1um_peak_bfield",tobts[2],holets[2],electts[2],eftsalone1u[2],pp.peakPulse());
 Signal tssigalone1upeak3("sig_350_alone_1um_peak_bfield",tobts[3],holets[3],electts[3],eftsalone1u[3],pp.peakPulse());
 Signal tssigalone1upeak4("sig_375_alone_1um_peak_bfield",tobts[4],holets[4],electts[4],eftsalone1u[4],pp.peakPulse());
 Signal tssigalone1upeak5("sig_400_alone_1um_peak_bfield",tobts[5],holets[5],electts[5],eftsalone1u[5],pp.peakPulse());
 Signal tssigalone1upeak6("sig_450_alone_1um_peak_bfield",tobts[6],holets[6],electts[6],eftsalone1u[6],pp.peakPulse());
 Signal tssigalone1upeak7("sig_500_alone_1um_peak_bfield",tobts[7],holets[7],electts[7],eftsalone1u[7],pp.peakPulse());
 Signal tssigalone1upeak8("sig_175_alone_1um_peak_bfield",tobts[8],holets[8],electts[8],eftsalone1u[8],pp.peakPulse());
 Signal tssigalone1upeak9("sig_200_alone_1um_peak_bfield",tobts[9],holets[9],electts[9],eftsalone1u[9],pp.peakPulse());
 Signal tssigalone1upeak10("sig_225_alone_1um_peak_bfield",tobts[10],holets[10],electts[10],eftsalone1u[10],pp.peakPulse());
 Signal tssigalone1upeak11("sig_250_alone_1um_peak_bfield",tobts[11],holets[11],electts[11],eftsalone1u[11],pp.peakPulse());

gSystem->cd("data");

}
