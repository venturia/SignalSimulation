{
ifstream input("signal_thickscan_list.dat");
ofstream out("summary_thickscan.out");
char file[300];
char name[300];
while( input >> file >> name) {

  TFile f(file);
  SignalFromFile* signal = new SignalFromFile(name,&f);
  signal->printSummary(out);
  delete signal;

  f.Close();
}
input.close();
out.close();
}
