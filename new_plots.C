void tib_summary_plots() {

  string lname[4];
  lname[0]="Peak";
  lname[1]="Peak Vdrift = const";
  lname[2]="Deco";
  lname[3]="Deco Vdrift = const";

  new TCanvas("tib_barycenter_summary","tib_barycenter_summary");

  TLegend *legbary = new TLegend(.6,.75,.8,.9,"Baricenters");

  TH1F* fbary = new TH1F("baricenters","Barycenters",7,-0.5,6.5);
  fbary->GetYaxis()->SetRangeUser(120e-6,170e-6);
  fbary->GetYaxis()->SetTitle("Barycenter [m]");
  fbary->Draw();
  fbary->SetStats(kFALSE);
  fbary->GetXaxis()->SetBinLabel(1,"Delta");
  fbary->GetXaxis()->SetBinLabel(2,"Single 0.001 #mum");
  fbary->GetXaxis()->SetBinLabel(3,"Single 0.01 #mum");
  fbary->GetXaxis()->SetBinLabel(4,"Single 0.1 #mum");
  fbary->GetXaxis()->SetBinLabel(5,"Single 1 #mum");
  fbary->GetXaxis()->SetBinLabel(6,"Single 10 #mum");
  fbary->GetXaxis()->SetBinLabel(7,"Total 1 #mum");

  for(int type=0;type<4;++type) {
    TGraph * gr = new TGraph();
    for(int i=0;i<7;++i) {
      gr->SetPoint(gr->GetN(),i,sfftibtotal[type*7+i]->getBarycenterAtMax());
    }
    gr->SetLineColor(type+1);
    gr->SetMarkerColor(type+1);
    gr->SetMarkerStyle(22);
    gr->Draw("lp");    
    legbary->AddEntry(gr,lname[type].c_str(),"p");
  }
  legbary->Draw();

  new TCanvas("tib_slope_summary","tib_slope_summary");
  gPad->SetLogy(1);

  TLegend *legslope = new TLegend(.6,.75,.8,.9,"Slopes");

  TH1F* fslope = new TH1F("slopes","Slopes",7,-0.5,6.5);
  fslope->GetYaxis()->SetRangeUser(0.01,20);
  fslope->GetYaxis()->SetTitle("Slope [#mum/ns]");
  fslope->Draw();
  fslope->SetStats(kFALSE);
  fslope->GetXaxis()->SetBinLabel(1,"Delta");
  fslope->GetXaxis()->SetBinLabel(2,"Single 0.001 #mum");
  fslope->GetXaxis()->SetBinLabel(3,"Single 0.01 #mum");
  fslope->GetXaxis()->SetBinLabel(4,"Single 0.1 #mum");
  fslope->GetXaxis()->SetBinLabel(5,"Single 1 #mum");
  fslope->GetXaxis()->SetBinLabel(6,"Single 10 #mum");
  fslope->GetXaxis()->SetBinLabel(7,"Total 1 #mum");

  for(int type=0;type<4;++type) {
    TGraph * gr = new TGraph();
    for(int i=0;i<7;++i) {
      gr->SetPoint(gr->GetN(),i,sfftibtotal[type*7+i]->getSlopeAtMax(2.5e-9)/1000.);
    }
    gr->SetLineColor(type+1);
    gr->SetMarkerColor(type+1);
    gr->SetMarkerStyle(22);
    gr->Draw("lp");    
    legslope->AddEntry(gr,lname[type].c_str(),"p");
  }
  legslope->Draw();
}

void summary_plots() {

  string lname[4];
  lname[0]="Peak";
  lname[1]="Peak Vdrift = const";
  lname[2]="Deco";
  lname[3]="Deco Vdrift = const";

  new TCanvas("barycenter_summary","barycenter_summary");

  TLegend *legbary = new TLegend(.6,.75,.8,.9,"Baricenters");

  TH1F* fbary = new TH1F("baricenters","Barycenters",7,-0.5,6.5);
  fbary->GetYaxis()->SetRangeUser(220e-6,270e-6);
  fbary->GetYaxis()->SetTitle("Barycenter [m]");
  fbary->Draw();
  fbary->SetStats(kFALSE);
  fbary->GetXaxis()->SetBinLabel(1,"Delta");
  fbary->GetXaxis()->SetBinLabel(2,"Single 0.001 #mum");
  fbary->GetXaxis()->SetBinLabel(3,"Single 0.01 #mum");
  fbary->GetXaxis()->SetBinLabel(4,"Single 0.1 #mum");
  fbary->GetXaxis()->SetBinLabel(5,"Single 1 #mum");
  fbary->GetXaxis()->SetBinLabel(6,"Single 10 #mum");
  fbary->GetXaxis()->SetBinLabel(7,"Total 1 #mum");

  for(int type=0;type<4;++type) {
    TGraph * gr = new TGraph();
    for(int i=0;i<7;++i) {
      gr->SetPoint(gr->GetN(),i,sfftotal[type*7+i]->getBarycenterAtMax());
    }
    gr->SetLineColor(type+1);
    gr->SetMarkerColor(type+1);
    gr->SetMarkerStyle(22);
    gr->Draw("lp");    
    legbary->AddEntry(gr,lname[type].c_str(),"p");
  }
  legbary->Draw();

  new TCanvas("slope_summary","slope_summary");
  gPad->SetLogy(1);

  TLegend *legslope = new TLegend(.6,.75,.8,.9,"Slopes");

  TH1F* fslope = new TH1F("slopes","Slopes",7,-0.5,6.5);
  fslope->GetYaxis()->SetRangeUser(0.1,20);
  fslope->GetYaxis()->SetTitle("Slope [#mum/ns]");
  fslope->Draw();
  fslope->SetStats(kFALSE);
  fslope->GetXaxis()->SetBinLabel(1,"Delta");
  fslope->GetXaxis()->SetBinLabel(2,"Single 0.001 #mum");
  fslope->GetXaxis()->SetBinLabel(3,"Single 0.01 #mum");
  fslope->GetXaxis()->SetBinLabel(4,"Single 0.1 #mum");
  fslope->GetXaxis()->SetBinLabel(5,"Single 1 #mum");
  fslope->GetXaxis()->SetBinLabel(6,"Single 10 #mum");
  fslope->GetXaxis()->SetBinLabel(7,"Total 1 #mum");

  for(int type=0;type<4;++type) {
    TGraph * gr = new TGraph();
    for(int i=0;i<7;++i) {
      gr->SetPoint(gr->GetN(),i,sfftotal[type*7+i]->getSlopeAtMax(2.5e-9)/1000.);
    }
    gr->SetLineColor(type+1);
    gr->SetMarkerColor(type+1);
    gr->SetMarkerStyle(22);
    gr->Draw("lp");    
    legslope->AddEntry(gr,lname[type].c_str(),"p");
  }
  legslope->Draw();
}

void barycenter_deco_plots() {
  
  new TCanvas("barycenter_deco","barycenter_deco");
  //  gPad->Divide(2,2);
  
  TLegend* leg = new TLegend(.2,.6,.4,.8,"Barycenter");
  
  string sname[4];
  sname[0]="Deco Single (0.1 #mum)";
  sname[1]="Deco Single (1 #mum)";
  sname[2]="Deco Single (10 #mum)";
  sname[3]="Deco Total (1 #mum)";
  
  for(unsigned int i=0;i<4;++i) {
    if(i==3)     sff[i+4]->SetLineStyle(2);
    if(i==3)     sff[i+4]->SetLineColor(kBlack);
    if(i==2)     sff[i+4]->SetLineColor(kBlue);
    if(i==1)     sff[i+4]->SetLineColor(kGreen);
    if(i==0)     sff[i+4]->SetLineColor(kRed);
    sff[i+4]->ChargeBarycenterSimplerFunc()->SetNpx(1000);
  }
  
  for(unsigned int i=0;i<4;++i) {
    //    gPad->GetCanvas()->cd(i+1);
    if(i==0) {
      sff[7-i]->ChargeBarycenterSimplerFunc()->Draw();
      sff[7-i]->ChargeBarycenterSimplerFunc()->GetXaxis()->SetRangeUser(-5e-9,15e-9);
      sff[7-i]->ChargeBarycenterSimplerFunc()->GetYaxis()->SetRangeUser(200e-6,300e-6);
    }
    if(i!=0) sff[7-i]->ChargeBarycenterSimplerFunc()->Draw("same");
    sff[7-i]->ChargeBarycenterSimplerFunc()->GetXaxis()->SetTitle("Sampling Time [s]");
    sff[7-i]->ChargeBarycenterSimplerFunc()->GetYaxis()->SetTitle("Barycenter [m]");
    sff[7-i]->getMaxSignalBarycenterLines()->Draw();
    
    leg->AddEntry(sff[7-i]->ChargeBarycenterSimplerFunc(),sname[3-i].c_str(),"l");
  }
  leg->Draw();
  
  
}

void signal1D_deco_plots() {
  
  new TCanvas("signal1D_deco","signal1D_deco");
  //  gPad->Divide(2,2);
  
  TLegend* leg = new TLegend(.6,.3,.8,.5,"Signals");
  
  string sname[4];
  sname[0]="Deco Single (0.1 #mum)";
  sname[1]="Deco Single (1 #mum)";
  sname[2]="Deco Single (10 #mum)";
  sname[3]="Deco Total (1 #mum)";

  for(unsigned int i=0;i<4;++i) {
    if(i==3)     sff[i+4]->SetLineStyle(2);
    if(i==3)     sff[i+4]->SetLineColor(kBlack);
    if(i==2)     sff[i+4]->SetLineColor(kBlue);
    if(i==1)     sff[i+4]->SetLineColor(kGreen);
    if(i==0)     sff[i+4]->SetLineColor(kRed);
    sff[i+4]->TotalSignalFunc()->SetNpx(1000);
  }

  for(unsigned int i=0;i<4;++i) {
    //    gPad->GetCanvas()->cd(i+1);
    if(i==0) sff[7-i]->TotalSignalFunc()->Draw();
    if(i!=0) sff[7-i]->TotalSignalFunc()->Draw("same");
    sff[7-i]->TotalSignalFunc()->GetXaxis()->SetTitle("Sampling Time [s]");
    sff[7-i]->getMaxSignalLine()->Draw();
    
    leg->AddEntry(sff[7-i]->TotalSignalFunc(),sname[3-i].c_str(),"l");
  }
  leg->Draw();


}

void signal2D_deco_plots() {

  new TCanvas("signal2Ddeco","signal2Ddeco",1050,750);
  gPad->Divide(2,2);

  for(unsigned int i=0;i<4;++i) {
    gPad->GetCanvas()->cd(i+1);
    sff[4+i]->SignalFractionVsTimeFunc()->Draw("colz");
    sff[4+i]->SignalFractionVsTimeFunc()->GetXaxis()->SetTitle("depth [m]");    
    sff[4+i]->SignalFractionVsTimeFunc()->GetYaxis()->SetTitle("Sampling Time [s]");
  }

  new TCanvas("signal2Ddecovconst","signal2Ddecovconst",1050,750);
  gPad->Divide(2,2);

  for(unsigned int i=0;i<4;++i) {
    gPad->GetCanvas()->cd(i+1);
    sff[8+i]->SignalFractionVsTimeFunc()->Draw("colz");
    sff[8+i]->SignalFractionVsTimeFunc()->GetXaxis()->SetTitle("depth [m]");    
    sff[8+i]->SignalFractionVsTimeFunc()->GetYaxis()->SetTitle("Sampling Time [s]");
  }


}


void current1D_plots() {

  new TCanvas("current1D","current1D",1050,750);
  gPad->Divide(2,2);

  double depth[]={50e-6,200e-6,350e-6,460e-6};

  for(unsigned int i=0;i<4;++i) {
    if(i==3)     sff[i+4]->SetLineStyle(2);
    if(i==3)     sff[i+4]->SetLineColor(kBlack);
    if(i==2)     sff[i+4]->SetLineColor(kBlue);
    if(i==1)     sff[i+4]->SetLineColor(kGreen);
    if(i==0)     sff[i+4]->SetLineColor(kRed);
    sff[i+4]->CurrentSignalFromDepth()->SetNpx(1000);
  }

  for(unsigned int j=0;j<4;++j) {
    gPad->GetCanvas()->cd(j+1);
    gPad->SetLogy(1);

    for(unsigned int i=0;i<4;++i) {
      sff[i+4]->CurrentSignalFromDepth()->SetParameter(0,depth[j]);
      if(i==0) {
	//      TF1* cscopy = sff[i+4]->CurrentSignalFromDepth();
	TF1* cscopy = sff[i+4]->CurrentSignalFromDepth()->DrawCopy();
	cscopy->GetYaxis()->SetTitle("current [1/s]");    
	cscopy->GetXaxis()->SetTitle("Time [s]");
      }
      else {
	sff[i+4]->CurrentSignalFromDepth()->DrawCopy("same");
      }      
    }
    char lname[200];
    sprintf(lname,"Current from depth %5.0f #mum",1000000*depth[j]);
    TLegend* leg = new TLegend(.55,.45,.9,.75,lname);
    leg->AddEntry(sff[7]->CurrentSignalFromDepth(),"Total (1 #mum)","l");
    leg->AddEntry(sff[6]->CurrentSignalFromDepth(),"Single (10 #mum)","l");
    leg->AddEntry(sff[5]->CurrentSignalFromDepth(),"Single (1 #mum)","l");
    leg->AddEntry(sff[4]->CurrentSignalFromDepth(),"Single (0.1 #mum)","l");
    
    leg->Draw();


  }
  

}

void tib_current2D_plots() {

  new TCanvas("tib_current2D","tib_current2D",1050,750);
  gPad->Divide(2,2);

  for(unsigned int i=0;i<4;++i) {
    gPad->GetCanvas()->cd(i+1);
    gPad->SetLogz(1);
    sfftib[i+4]->CurrentSignalVsTimeFunc()->Draw("colz");
    sfftib[i+4]->CurrentSignalVsTimeFunc()->GetXaxis()->SetTitle("depth [m]");    
    sfftib[i+4]->CurrentSignalVsTimeFunc()->GetYaxis()->SetTitle("Sampling Time [s]");
  }


}

void current2D_plots() {

  new TCanvas("current2D","current2D",1050,750);
  gPad->Divide(2,2);

  for(unsigned int i=0;i<4;++i) {
    gPad->GetCanvas()->cd(i+1);
    gPad->SetLogz(1);
    sff[i+4]->CurrentSignalVsTimeFunc()->Draw("colz");
    sff[i+4]->CurrentSignalVsTimeFunc()->GetXaxis()->SetTitle("depth [m]");    
    sff[i+4]->CurrentSignalVsTimeFunc()->GetYaxis()->SetTitle("Sampling Time [s]");
  }


}

void weightfield_plots() {

  new TCanvas("weightfield","weightfield");
  gPad->SetLogy(1);

  ef.SetLineColor(kBlack);
  ef.SetLineStyle(2);
  ef2.SetLineColor(kRed);
  ef3.SetLineColor(kGreen);
  ef4.SetLineColor(kBlue);
  ef5.SetLineColor(kMagenta);
  ef6.SetLineColor(kCyan);

  TH1F* fweight = new TH1F("fweight","Weight Functions",100,0,500e-6);
  fweight->GetYaxis()->SetRangeUser(200,35000000);
  fweight->GetXaxis()->SetTitle("depth [m]");  fweight->GetYaxis()->SetTitle("Weight [1/m]");
  fweight->SetStats(kFALSE);
  fweight->Draw();

  ef6.Weight()->SetNpx(100000);  ef6.Weight()->Draw("same");
  ef5.Weight()->SetNpx(100000);  ef5.Weight()->Draw("same");
  ef4.Weight()->SetNpx(100000);  ef4.Weight()->Draw("same");
  ef3.Weight()->SetNpx(100000);  ef3.Weight()->Draw("same");
  ef2.Weight()->SetNpx(100000);  ef2.Weight()->Draw("same");
  ef.Weight()->SetNpx(100000);  ef.Weight()->Draw("same");
  
  TLegend* leg = new TLegend(.6,.45,.8,.75,"Weights");
  leg->AddEntry(ef.Weight(),"Total (1 #mum)","l");
  leg->AddEntry(ef4.Weight(),"Single (10 #mum)","l");
  leg->AddEntry(ef3.Weight(),"Single (1 #mum)","l");
  leg->AddEntry(ef2.Weight(),"Single (0.1 #mum)","l");
  leg->AddEntry(ef5.Weight(),"Single (0.01 #mum)","l");
  leg->AddEntry(ef6.Weight(),"Single (0.001 #mum)","l");

  leg->Draw();

}

void weightpotential_plots() {

  new TCanvas("weightpotential","weightpotential",1050,750);
  gPad->Divide(2,2);

  gPad->GetCanvas()->cd(1);
  ef.PotentialFunc()->SetNpx(1000);  ef.PotentialFunc()->SetNpy(1000);
  TF2* efcopy = ef.PotentialFunc()->DrawCopy("colz");
  efcopy->GetXaxis()->SetTitle("u [m]");
  efcopy->GetYaxis()->SetTitle("w [m]");

  gPad->GetCanvas()->cd(2);
  ef2.PotentialFunc()->SetNpx(1000);  ef2.PotentialFunc()->SetNpy(1000);
  TF2* ef2copy = ef2.PotentialFunc()->DrawCopy("colz");
  ef2copy->GetXaxis()->SetTitle("u [m]");
  ef2copy->GetYaxis()->SetTitle("w [m]");

  gPad->GetCanvas()->cd(3);
  ef.PotentialFunc()->SetNpx(1000);  ef.PotentialFunc()->SetNpy(1000);
  ef.PotentialFunc()->Draw("colz");
  ef.PotentialFunc()->GetXaxis()->SetRangeUser(-50e-6,50e-6);
  ef.PotentialFunc()->GetYaxis()->SetRangeUser(0,100e-6);
  ef.PotentialFunc()->GetXaxis()->SetTitle("u [m]");
  ef.PotentialFunc()->GetYaxis()->SetTitle("w [m]");

  gPad->GetCanvas()->cd(4);
  ef2.PotentialFunc()->SetNpx(1000);  ef2.PotentialFunc()->SetNpy(1000);
  ef2.PotentialFunc()->Draw("colz");
  ef2.PotentialFunc()->GetXaxis()->SetRangeUser(-50e-6,50e-6);
  ef2.PotentialFunc()->GetYaxis()->SetRangeUser(0,100e-6);
  ef2.PotentialFunc()->GetXaxis()->SetTitle("u [m]");
  ef2.PotentialFunc()->GetYaxis()->SetTitle("w [m]");


}

void barycenter_plots() {
  
  new TCanvas("barycenter","barycenter");
  //  gPad->Divide(2,2);
  
  TLegend* leg = new TLegend(.2,.6,.4,.8,"Barycenter");
  
  string sname[4];
  sname[0]="Peak";
  sname[1]="Peak Vdrift=const";
  sname[2]="Deco";
  sname[3]="Deco Vdrift=const";
  
  for(unsigned int i=0;i<4;++i) {
    //    gPad->GetCanvas()->cd(i+1);
    sff[i]->SetLineColor(i+2);
    sff[i]->ChargeBarycenterSimplerFunc()->SetNpx(1000);
    if(i==0) {
      sff[i]->ChargeBarycenterSimplerFunc()->Draw();
      sff[i]->ChargeBarycenterSimplerFunc()->GetXaxis()->SetRangeUser(-5e-9,15e-9);
      sff[i]->ChargeBarycenterSimplerFunc()->GetYaxis()->SetRangeUser(200e-6,300e-6);
    }
    if(i!=0) sff[i]->ChargeBarycenterSimplerFunc()->Draw("same");
    sff[i]->ChargeBarycenterSimplerFunc()->GetXaxis()->SetTitle("Sampling Time [s]");
    sff[i]->ChargeBarycenterSimplerFunc()->GetYaxis()->SetTitle("Barycenter [m]");
    sff[i]->getMaxSignalBarycenterLines()->Draw();
    
    leg->AddEntry(sff[i]->ChargeBarycenterSimplerFunc(),sname[i].c_str(),"l");
  }
  leg->Draw();
  
  
}

void signal1D_plots() {

  new TCanvas("signal","signal");
  //  gPad->Divide(2,2);

  TLegend* leg = new TLegend(.6,.3,.8,.5,"Signals");
 
  string sname[4];
  sname[0]="Peak";
  sname[1]="Peak Vdrift=const";
  sname[2]="Deco";
  sname[3]="Deco Vdrift=const";

  for(unsigned int i=0;i<4;++i) {
    //    gPad->GetCanvas()->cd(i+1);
    sff[i]->SetLineColor(i+2);
    sff[i]->TotalSignalFunc()->SetNpx(1000);
    if(i==0) sff[i]->TotalSignalFunc()->Draw();
    if(i!=0) sff[i]->TotalSignalFunc()->Draw("same");
    sff[i]->TotalSignalFunc()->GetXaxis()->SetTitle("Sampling Time [s]");
    sff[i]->getMaxSignalLine()->Draw();
    
    leg->AddEntry(sff[i]->TotalSignalFunc(),sname[i].c_str(),"l");
  }
  leg->Draw();


}


void signal2D_plots() {

  new TCanvas("signal2D","signal2D",1050,750);
  gPad->Divide(2,2);

  for(unsigned int i=0;i<4;++i) {
    gPad->GetCanvas()->cd(i+1);
    sff[i]->SignalFractionVsTimeFunc()->Draw("colz");
    sff[i]->SignalFractionVsTimeFunc()->GetXaxis()->SetTitle("depth [m]");    
    sff[i]->SignalFractionVsTimeFunc()->GetYaxis()->SetTitle("Sampling Time [s]");
  }


}

void pulse_plots() {

  new TCanvas("pulse","pulse");

  pp.peakPulse()->SetLineStyle(2);

  pp.decoPulse()->Draw();
  pp.peakPulse()->Draw("same");
  pp.decoPulse()->GetXaxis()->SetTitle("t0 [s]");

  TLegend* leg = new TLegend(.6,.5,.8,.6,"Pulses");
  leg->AddEntry(pp.decoPulse(),"Deconvolution","l");
  leg->AddEntry(pp.peakPulse(),"Peak","l");
  leg->Draw();

}

void electron_plots() {

  elect.SetLineColor(kRed);
  electnodep.SetLineColor(kBlue);

  new TCanvas("TOBsensor","TOBsensor",1050,750);
  gPad->Divide(2,2);
  
  // Efield

  gPad->GetCanvas()->cd(1);
  tob.EfieldFunc()->Draw();
  tobnodepl.EfieldFunc()->Draw("same");
  tob.EfieldFunc()->GetXaxis()->SetTitle("depth [m]");  tob.EfieldFunc()->GetYaxis()->SetTitle("E [V/m]");

  gPad->GetCanvas()->cd(2);
  elect.MobilityFunc()->Draw();
  electnodep.MobilityFunc()->Draw("same");
  elect.MobilityFunc()->GetXaxis()->SetTitle("depth [m]");  elect.MobilityFunc()->GetYaxis()->SetTitle("#mu [m2/Vs]");

  gPad->GetCanvas()->cd(3);
  elect.parallelVdriftFunc()->Draw();
  electnodep.parallelVdriftFunc()->Draw("same");
  elect.parallelVdriftFunc()->GetXaxis()->SetTitle("depth [m]");  elect.parallelVdriftFunc()->GetYaxis()->SetTitle("Vdrift [m/s]");

  gPad->GetCanvas()->cd(4);
  elect.DriftTimeFunc()->Draw();
  electnodep.DriftTimeFunc()->Draw("same");
  elect.DriftTimeFunc()->GetXaxis()->SetTitle("depth [m]");  elect.DriftTimeFunc()->GetYaxis()->SetTitle("Tdrift [s]");


}

void sensor_plots() {

  new TCanvas("TOBsensor","TOBsensor",1050,750);
  gPad->Divide(2,2);
  
  // Efield

  gPad->GetCanvas()->cd(1);
  tob.EfieldFunc()->Draw();
  tobnodepl.EfieldFunc()->Draw("same");
  tob.EfieldFunc()->GetXaxis()->SetTitle("depth [m]");  tob.EfieldFunc()->GetYaxis()->SetTitle("E [V/m]");

  gPad->GetCanvas()->cd(2);
  hole.MobilityFunc()->Draw();
  holenodep.MobilityFunc()->Draw("same");
  hole.MobilityFunc()->GetXaxis()->SetTitle("depth [m]");  hole.MobilityFunc()->GetYaxis()->SetTitle("#mu [m2/Vs]");

  gPad->GetCanvas()->cd(3);
  hole.parallelVdriftFunc()->Draw();
  holenodep.parallelVdriftFunc()->Draw("same");
  hole.parallelVdriftFunc()->GetXaxis()->SetTitle("depth [m]");  hole.parallelVdriftFunc()->GetYaxis()->SetTitle("Vdrift [m/s]");

  gPad->GetCanvas()->cd(4);
  hole.DriftTimeFunc()->Draw();
  holenodep.DriftTimeFunc()->Draw("same");
  hole.DriftTimeFunc()->GetXaxis()->SetTitle("depth [m]");  hole.DriftTimeFunc()->GetYaxis()->SetTitle("Tdrift [s]");


}

void signal_plots()  {
TFile fdelta("result_sig_tob_delta_deco.root");

TFile ftotal("result_sig_tob_total_1um_deco.root");
TFile falone01("result_sig_tob_alone_01um_deco.root");
TFile falone1("result_sig_tob_alone_1um_deco.root");
TFile falone10("result_sig_tob_alone_10um_deco.root");
/*
SignalFromFile sigdelta("Tue Oct 20 22:03:43 2009_sig_tob_delta_deco",&fdelta);
SignalFromFile sigtotal("Tue Oct 20 22:22:51 2009_sig_tob_total_1um_deco",&ftotal);
SignalFromFile sigalone01("Tue Oct 20 22:22:50 2009_sig_tob_alone_01um_deco",&falone01);
SignalFromFile sigalone1("Tue Oct 20 22:23:05 2009_sig_tob_alone_1um_deco",&falone1);
SignalFromFile sigalone10("Tue Oct 20 22:22:54 2009_sig_tob_alone_10um_deco",&falone10);
*/
SignalFromFile sigdelta("sig_tob_delta_deco",&fdelta);
SignalFromFile sigtotal("sig_tob_total_1um_deco",&ftotal);
SignalFromFile sigalone01("sig_tob_alone_01um_deco",&falone01);
SignalFromFile sigalone1("sig_tob_alone_1um_deco",&falone1);
SignalFromFile sigalone10("sig_tob_alone_10um_deco",&falone10);

sigdelta.SetLineColor(kYellow);
sigtotal.SetLineColor(kBlack);
sigalone01.SetLineColor(kRed);
sigalone1.SetLineColor(kBlue);
sigalone10.SetLineColor(kGreen);

sigdelta.TotalSignalFunc()->SetNpx(1000);
sigtotal.TotalSignalFunc()->SetNpx(1000);
sigalone01.TotalSignalFunc()->SetNpx(1000);
sigalone1.TotalSignalFunc()->SetNpx(1000);
sigalone10.TotalSignalFunc()->SetNpx(1000);

sigdelta.ChargeBarycenterSimplerFunc()->SetNpx(1000);
sigtotal.ChargeBarycenterSimplerFunc()->SetNpx(1000);
sigalone01.ChargeBarycenterSimplerFunc()->SetNpx(1000);
sigalone1.ChargeBarycenterSimplerFunc()->SetNpx(1000);
sigalone10.ChargeBarycenterSimplerFunc()->SetNpx(1000);

new TCanvas("signal","signal");
sigdelta.TotalSignalFunc()->Draw();
sigtotal.TotalSignalFunc()->Draw("same");
sigalone01.TotalSignalFunc()->Draw("same");
sigalone1.TotalSignalFunc()->Draw("same");
sigalone10.TotalSignalFunc()->Draw("same");
sigdelta.getMaxSignalLine()->Draw();
sigtotal.getMaxSignalLine()->Draw();
sigalone01.getMaxSignalLine()->Draw();
sigalone1.getMaxSignalLine()->Draw();
sigalone10.getMaxSignalLine()->Draw();

new TCanvas("bary","bary");
sigdelta.ChargeBarycenterSimplerFunc()->Draw();
sigtotal.ChargeBarycenterSimplerFunc()->Draw("same");
sigalone01.ChargeBarycenterSimplerFunc()->Draw("same");
sigalone1.ChargeBarycenterSimplerFunc()->Draw("same");
sigalone10.ChargeBarycenterSimplerFunc()->Draw("same");
sigdelta.getMaxSignalBarycenterLines()->Draw();
sigtotal.getMaxSignalBarycenterLines()->Draw();
sigalone01.getMaxSignalBarycenterLines()->Draw();
sigalone1.getMaxSignalBarycenterLines()->Draw();
sigalone10.getMaxSignalBarycenterLines()->Draw();
TFile fdelta("result_sig_tob_delta_deco.root");

TFile ndfdelta("result_sig_tob_nodepl_delta_deco.root");
TFile ndftotal("result_sig_tob_nodepl_total_1um_deco.root");
TFile ndfalone01("result_sig_tob_nodepl_alone_01um_deco.root");
TFile ndfalone1("result_sig_tob_nodepl_alone_1um_deco.root");
TFile ndfalone10("result_sig_tob_nodepl_alone_10um_deco.root");

SignalFromFile ndsigdelta("sig_tob_nodepl_delta_deco",&ndfdelta);
SignalFromFile ndsigtotal("sig_tob_nodepl_total_1um_deco",&ndftotal);
SignalFromFile ndsigalone01("sig_tob_nodepl_alone_01um_deco",&ndfalone01);
SignalFromFile ndsigalone1("sig_tob_nodepl_alone_1um_deco",&ndfalone1);
SignalFromFile ndsigalone10("sig_tob_nodepl_alone_10um_deco",&ndfalone10);

ndsigdelta.SetLineColor(kYellow);
ndsigtotal.SetLineColor(kBlack);
ndsigalone01.SetLineColor(kRed);
ndsigalone1.SetLineColor(kBlue);
ndsigalone10.SetLineColor(kGreen);

ndsigdelta.TotalSignalFunc()->SetNpx(1000);
ndsigtotal.TotalSignalFunc()->SetNpx(1000);
ndsigalone01.TotalSignalFunc()->SetNpx(1000);
ndsigalone1.TotalSignalFunc()->SetNpx(1000);
ndsigalone10.TotalSignalFunc()->SetNpx(1000);

ndsigdelta.ChargeBarycenterSimplerFunc()->SetNpx(1000);
ndsigtotal.ChargeBarycenterSimplerFunc()->SetNpx(1000);
ndsigalone01.ChargeBarycenterSimplerFunc()->SetNpx(1000);
ndsigalone1.ChargeBarycenterSimplerFunc()->SetNpx(1000);
ndsigalone10.ChargeBarycenterSimplerFunc()->SetNpx(1000);

new TCanvas("signal_nodepl","signal_nodepl");
ndsigdelta.TotalSignalFunc()->Draw();
ndsigtotal.TotalSignalFunc()->Draw("same");
ndsigalone01.TotalSignalFunc()->Draw("same");
ndsigalone1.TotalSignalFunc()->Draw("same");
ndsigalone10.TotalSignalFunc()->Draw("same");
ndsigdelta.getMaxSignalLine()->Draw();
ndsigtotal.getMaxSignalLine()->Draw();
ndsigalone01.getMaxSignalLine()->Draw();
ndsigalone1.getMaxSignalLine()->Draw();
ndsigalone10.getMaxSignalLine()->Draw();

new TCanvas("bary_nodepl","bary_nodepl");
ndsigdelta.ChargeBarycenterSimplerFunc()->Draw();
ndsigtotal.ChargeBarycenterSimplerFunc()->Draw("same");
ndsigalone01.ChargeBarycenterSimplerFunc()->Draw("same");
ndsigalone1.ChargeBarycenterSimplerFunc()->Draw("same");
ndsigalone10.ChargeBarycenterSimplerFunc()->Draw("same");
ndsigdelta.getMaxSignalBarycenterLines()->Draw();
ndsigtotal.getMaxSignalBarycenterLines()->Draw();
ndsigalone01.getMaxSignalBarycenterLines()->Draw();
ndsigalone1.getMaxSignalBarycenterLines()->Draw();
ndsigalone10.getMaxSignalBarycenterLines()->Draw();


}
