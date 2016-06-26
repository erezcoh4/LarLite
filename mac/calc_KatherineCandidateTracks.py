import sys
from larlite import larlite as fmwk

Path = "/Users/erezcohen/Desktop/uBoone"
if len(sys.argv) > 2:
    infilename = sys.argv[1]
else:
    infilename = "larlite_95_wire_pandoraNu_543_evts.root"#"larlite_pandoraNu_95_AllGoodRuns_543_events.root"
    sys.stderr.write("\nUsage: python mac/ana_KatherineCandidateTracks.py <infilename>\n\n" )

sys.stderr.write("\n runnnig %s \n\n" % infilename)

my_proc = fmwk.ana_processor()
my_proc.add_input_file(Path+"/EXTBNB_DATA/"+infilename)
my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file(Path+"/AnaFiles/Ana_%s"%infilename)

my_proc.add_process(fmwk.AnaPandoraNuTracks())

print  "Finished configuring ana_processor. Start event loop!"
my_proc.run()
print "done!"

sys.exit(0)
