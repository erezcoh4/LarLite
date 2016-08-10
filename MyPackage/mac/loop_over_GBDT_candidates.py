import sys
from larlite import larlite as fmwk
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
sys.path.insert(0, '/uboone/app/users/ecohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import input_flags
flags = input_flags.get_args()


create_images = False

Path = "/Users/erezcohen/Desktop/uBoone" if flags.worker == 'erez' else "/uboone/data/users/ecohen/GBDTprotons"

DATAPath = Path+"/MC_DATA" if flags.MCmode == True else Path+"/EXTBNB_DATA"

infilename = "larlite_14evts_mccosmicmc_goodprotonsandbad9999_mcinfo.root"
#"larlite_95_wire_pandoraNu_543_evts.root"#"larlite_95_wire_pandoraNu_4519_evts.root"

sys.stderr.write("\n runnnig %s \n\n" % infilename)

my_proc = fmwk.ana_processor()

my_proc.add_input_file(DATAPath+"/larlite_files/"+infilename)

my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file(Path+"/AnaFiles/Ana_%s"%infilename)

#my_proc.add_process( fmwk.AnaPandoraNuTracks() )


ana_pandoraNu_tracks = fmwk.AnaPandoraNuTracks()
ana_pandoraNu_tracks.SetWorker( flags.worker , flags.verbose )
my_proc.add_process( ana_pandoraNu_tracks )


print  "Finished configuring ana_processor. Start event loop!"
my_proc.run()
print "done!"

sys.exit(0)
