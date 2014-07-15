{
gSystem->cd("data");
ifstream input("tib_signal_list.dat");
char file[300];
char name[300];
SignalFromFile* sfftibtotal[28];
int i=0;
while( input >> file >> name) {

  TFile *f = new TFile(file);
  sfftibtotal[i] = new SignalFromFile(name,f);
  ++i;
}
input.close();
gSystem->cd("/afs/cern.ch/user/v/venturia/PeakVsDecoAlignment");
}
