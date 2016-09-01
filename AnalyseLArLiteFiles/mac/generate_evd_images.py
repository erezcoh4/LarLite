'''
    usage:
    -------
    python mac/generate_evd_images.py -werez --DataType=EXTBNB
'''

import sys
from larlite import larlite as fmwk
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
sys.path.insert(0, '/uboone/app/users/ecohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import input_flags , Initiation as init
flags = input_flags.get_args()


# ----------------------- file names ----------------------------- #
data_name       = "mu_p0.90_vertex_32evts_1sep2016"
# ---------------------------------------------------------------- #
image_name      = flags.DataType + "_" + data_name
latlitefilename = "larlite_" + image_name + ".root"
roi_map_name    = "features_" + image_name + ".csv"
# ---------------------------------------------------------------- #




if flags.worker == 'erez':
    Path        = "/Users/erezcohen/Desktop/uBoone"

elif flags.worker == 'uboone':
    Path        = "/uboone/data/users/ecohen"


roi_map_path    = Path + "/AnalysisTreeData/CSVFiles"
data_Path       = Path + "/" + flags.DataType + "_DATA"
images_path     = Path + "/images/" + image_name

init.create_dir( Path + "/images/" , image_name )

my_fwk = fmwk.ana_processor()

my_fwk.add_input_file( data_Path + "/larlite_files/" + latlitefilename )

my_fwk.set_io_mode( fmwk.storage_manager.kREAD )

my_fwk.set_ana_output_file( data_Path + "/../AnaFiles/Ana_%s" % latlitefilename)


# call the analysis unit
ana_process = fmwk.AnalyseEvents()
# set its important arguments (verbosity, worker, etc.)
ana_process.SetArgs( flags.worker , flags.verbose , images_path )
# load ROIs map
NroiPerEvent = 3
ana_process.LoadROIsMap( roi_map_path + "/" + roi_map_name , NroiPerEvent )
# add my analysis process
my_fwk.add_process( ana_process )
# run the analysis
my_fwk.run()
print "done!"

sys.exit(0)
