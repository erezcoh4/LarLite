import sys
from larlite import larlite as fmwk
sys.path.insert(0, '../../mySoftware/MySoftwarePackage/mac')
import input_flags
flags = input_flags.get_args()

Path = "/Users/erezcohen/Desktop/uBoone" if flags.worker == 'erez' else "/uboone/data/users/ecohen/GBDTp\
rotons"

infilename = "larlite_9131runs_multipscore0.95_595evts_03082016.root"
#"larlite_95_wire_pandoraNu_543_evts.root"#"larlite_95_wire_pandoraNu_4519_evts.root"
sys.stderr.write("\nUsage: python mac/calc_KatherineCandidateTracks.py <infilename>\n\n" )

sys.stderr.write("\n runnnig %s \n\n" % infilename)

my_proc = fmwk.ana_processor()
my_proc.add_input_file(Path+"/EXTBNB_DATA/larlite_files/"+infilename)
my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file(Path+"/AnaFiles/Ana_%s"%infilename)

my_proc.add_process(fmwk.AnaPandoraNuTracks())

print  "Finished configuring ana_processor. Start event loop!"
my_proc.run()
print "done!"

sys.exit(0)
