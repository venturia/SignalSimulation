#!/bin/tcsh -x
source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.csh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.19/${LCGPLAT}/root/bin/thisroot.csh /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.19/${LCGPLAT}/root

cd /afs/cern.ch/user/v/venturia/PeakVsDecoAlignment

#set command = \'batch_generic_macro.C\(\"${LSB_JOBNAME}\"\)\'
set command = batch_generic_macro.C\(\"${LSB_JOBNAME}\"\)
echo $command
root -b -q $command 



