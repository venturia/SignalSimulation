int batch_generic_macro(char* signame) {

  gROOT->ProcessLine(".x /afs/cern.ch/user/v/venturia/PeakVsDecoAlignment/common_init.C");

  char command[100];
  sprintf(command,"%s.SaveFunctions(500,500,2000);",signame);
  cout << "Executing " << command << endl;
  gROOT->ProcessLine(command);
  return 0;
}
