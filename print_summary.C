{
ifstream input("signal_list.dat");
ofstream out("summary.out.test");
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
