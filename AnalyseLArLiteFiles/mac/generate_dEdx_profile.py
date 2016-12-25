'''
    For a classification score, we filter out all proton candidates events (R/S/E),
    and convert them into larlite format tp perform some analyses.
    This script generates a ROOT file with energy deposition profile for classified protons:
    For each classified track, we collect all hits, and write out to the ROOT file the hits dE/dx for each hit.
    Then, the final step would be to open this output ROOT file and plot the dE/dx profile for each proton
    
    
    usage:
    -------
    python mac/generate_dEdx_profile.py --DataType=EXTBNB --option=dEdx -werez
'''
from definitions import *

# ----------------------- file names ----------------------------- #
model_name      = "cosmic_trained_only_on_mc"
p_score         = 0.99
data_name       = "9131runs_" + model_name + "_pscore_%.2f_1598evts_23aug2016"%p_score
# ---------------------------------------------------------------- #
data_full_name  = flags.DataType + "_" + data_name
latlitefilename = "larlite_" + data_full_name + ".root"
rse_map_name    = pass_GBDTs_path + "/extBNB_AnalysisTrees_"+model_name+"/passedGBDT_extBNB_AnalysisTrees_"+model_name+"_score_%.2f.csv"%p_score
# ---------------------------------------------------------------- #


dirname = init.create_dir( Path + "/analysis/" + flags.option , data_full_name )
tools.print_important('work directory: \n%s'%dirname)

# call the analysis unit
my_fwk = fmwk.ana_processor()
my_fwk.add_input_file( data_Path + "/larlite_files/" + latlitefilename )
my_fwk.set_io_mode( fmwk.storage_manager.kREAD )
my_fwk.set_ana_output_file( ana_Path + "/Ana_%s" % latlitefilename )
ana_process = fmwk.ExtractPhysVars()

# set its important arguments (verbosity, worker, etc.)
ana_process.SetWorker( flags.worker )
ana_process.SetVerbosity( flags.verbose )

# load R/S/E map
ana_process.LoadRSEpTracksMap( rse_map_name )

# add my analysis process
my_fwk.add_process( ana_process )

# run the analysis
my_fwk.run()
print "done!"

sys.exit(0)
