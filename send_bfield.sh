#!/usr/local/bin/tcsh

#bsub -q cmscaf1nw -J sig_bfield batch_script.sh
#bsub -q cmscaf1nw -J sig2 batch_script.sh
#bsub -q cmscaf1nw -J sig3 batch_script.sh
#bsub -q cmscaf1nw -J sig4 batch_script.sh
#bsub -q cmscaf1nw -J sig5 batch_script.sh
#bsub -q cmscaf1nw -J sig6 batch_script.sh
bsub -q cmscaf1nd -J sigdelta_bfield batch_script.sh

#bsub -q cmscaf1nw -J signodepl_bfield batch_script.sh
#bsub -q cmscaf1nw -J sig2nodepl batch_script.sh
#bsub -q cmscaf1nw -J sig3nodepl batch_script.sh
#bsub -q cmscaf1nw -J sig4nodepl batch_script.sh
#bsub -q cmscaf1nw -J sig5nodepl batch_script.sh
#bsub -q cmscaf1nw -J sig6nodepl batch_script.sh
bsub -q cmscaf1nd -J sigdeltanodepl_bfield batch_script.sh

#bsub -q cmscaf1nw -J peaksig_bfield batch_script.sh
#bsub -q cmscaf1nw -J peaksig2 batch_script.sh
#bsub -q cmscaf1nw -J peaksig3 batch_script.sh
#bsub -q cmscaf1nw -J peaksig4 batch_script.sh
#bsub -q cmscaf1nw -J peaksig5 batch_script.sh
#bsub -q cmscaf1nw -J peaksig6 batch_script.sh
bsub -q cmscaf1nd -J peaksigdelta_bfield batch_script.sh

#bsub -q cmscaf1nw -J peaksignodepl_bfield batch_script.sh
#bsub -q cmscaf1nw -J peaksig2nodepl batch_script.sh
#bsub -q cmscaf1nw -J peaksig3nodepl batch_script.sh
#bsub -q cmscaf1nw -J peaksig4nodepl batch_script.sh
#bsub -q cmscaf1nw -J peaksig5nodepl batch_script.sh
#bsub -q cmscaf1nw -J peaksig6nodepl batch_script.sh
bsub -q cmscaf1nd -J peaksigdeltanodepl_bfield batch_script.sh
