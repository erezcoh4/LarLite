import sys
from larlite import larlite as fmwk
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
sys.path.insert(0, '/uboone/app/users/ecohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import input_flags
flags = input_flags.get_args()


infilename      = "larlite_44evts_mccosmicmc_goodprotonsandbad9999_mcinfo.root"
roi_map_name    = "mc_good_bad_tofilter_ROIs.csv"

image_name      = "MCgoodbad"
production_name = "PassedGBDTFiles"
create_images   = True



if flags.worker == 'erez':
    Path = "/Users/erezcohen/Desktop/uBoone/GBDTprotons"


elif flags.worker == 'uboone':
    Path = "/uboone/data/users/ecohen/GBDTprotons"


DATAPath = Path+"/MC_DATA" if flags.MCmode == True else Path+"/EXTBNB_DATA"

images_path = Path+"/"+image_name
roi_map_path = Path+"/"+production_name;


sys.stderr.write("\n runnnig %s \n\n" % infilename)

my_proc = fmwk.ana_processor()

my_proc.add_input_file(DATAPath+"/larlite_files/"+infilename)

my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file(Path+"/AnaFiles/Ana_%s"%infilename)

#my_proc.add_process( fmwk.AnaPandoraNuTracks() )


ana_pandoraNu_tracks = fmwk.AnaPandoraNuTracks()
ana_pandoraNu_tracks.SetWorker( flags.worker , flags.verbose , create_images , images_path , roi_map_path , roi_map_name )
my_proc.add_process( ana_pandoraNu_tracks )


print  "Finished configuring ana_processor. Start event loop!"
my_proc.run()
print "done!"

sys.exit(0)
