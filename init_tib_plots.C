{
ifstream input("tib_delta_signal_list.dat");
char file[300];
char name[300];
SignalFromFile* sfftib[12];
int i=0;
while( input >> file >> name) {

  TFile *f = new TFile(file);
  sfftib[i] = new SignalFromFile(name,f);
  ++i;
}
input.close();
}
