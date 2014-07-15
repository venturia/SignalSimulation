#!/bin/tcsh

cd /afs/cern.ch/user/v/venturia/PeakVsDecoAlignment
root -b -q batch_${LSB_JOBNAME}.C
