'''
    
    usage:
    ------
    > python mac/loop_over_GBDT_candidates.py --DataType=EXTBNB -wuboone -v2 -evf=3
    
    evf represents the maximal number of images it will create (=n_max_entries)
    
'''


import sys
from larlite import larlite as fmwk
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
sys.path.insert(0, '/uboone/app/users/ecohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import input_flags
flags = input_flags.get_args()



infilename      = "larlite_BNB_5e19POT_TrainedOn_only_MC_BNB_pscore0.99_3942evts_5nov2016.root"
# "larlite_extBNB9131runs_cosmic_trained_only_on_mc_pscore_0.99_1598evts_23aug2016.root"
roi_map_name    = "passedGBDT_BNB_5e19POT_AnalysisTrees_BNB_TrainedOn_only_MC_BNB_score_0.99_roi.csv"
# "passedGBDT_extBNB_AnalysisTrees_cosmic_trained_only_on_mc_score_0.99.csv"
image_name      = "BNB_trained_only_on_mc_BNB_pscore_0.99"
# "cosmic_trained_only_on_mc_score_0.99"
production_name = "PassedGBDTFiles"
create_images   = True




if flags.worker == 'erez':
    Path = "/Users/erezcohen/Desktop/uBoone/GBDTprotons"
    production_path = "/Users/erezcohen/Desktop/uBoone/AnalysisTreesAna"
    infilename      = "larlite_14evts_mccosmicmc_goodprotonsandbad9999_mcinfo.root"
#    flags.MCmode    = True 
    n_max_entries   = 3

elif flags.worker == 'uboone':
    Path = "/uboone/data/users/ecohen/DATA"
    production_path = "/uboone/app/users/ecohen/AnalysisTreesAna"
    n_max_entries   = -1 if flags.evnts_frac < 1 else int(flags.evnts_frac) # this means we analyze all TTree entries



DATAPath  = Path + "/" + flags.DataType + "_DATA"

#
#if flags.MCmode == True:
#    roi_map_name    = "mc_good_bad_tofilter_ROIs.csv"
#    image_name      = "MCgoodbad"
#    DATAPath        = Path+"/MC_DATA"




images_path = Path+"../GBDTprotons/images/"+image_name
roi_map_path = production_path+"/"+production_name;


sys.stderr.write("\n runnnig %s \n\n" % infilename)

my_proc = fmwk.ana_processor()

my_proc.add_input_file(DATAPath+"/larlite_files/"+infilename)

my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file(Path+"/../AnaFiles/Ana_%s"%infilename)

#my_proc.add_process( fmwk.AnaPandoraNuTracks() )


ana_pandoraNu_tracks = fmwk.AnaPandoraNuTracks()
ana_pandoraNu_tracks.SetWorker( flags.worker , flags.verbose , create_images , images_path , roi_map_path , roi_map_name , n_max_entries )
my_proc.add_process( ana_pandoraNu_tracks )


print  "Finished configuring ana_processor. Start event loop!"
my_proc.run()
print "done!"

sys.exit(0)
