#ifndef LARLITE_MYANA_CXX
#define LARLITE_MYANA_CXX

#include "MyAna.h"
#include "DataFormat/mctrack.h"

namespace larlite {
    
    bool MyAna::initialize() {
        OutTree = new TTree("anaTree","tracks analysis by LArLite");
        OutTree -> Branch("pdgID"               ,   &T                  ,   "pdgID/I");
        OutTree -> Branch("StraightTrackLength" ,   &StraightTrackLength    ,   "StraightTrackLength/D");
        OutTree -> Branch("TrackLength"         ,   &TrackLength            ,   "TrackLength/D");
        //
        // This function is called in the beggining of event loop
        // Do all variable initialization you wish to do here.
        // If you have a histogram to fill in the event loop, for example,
        // here is a good place to create one on the heap (i.e. "new TH1D").
        //
        
        return true;
    }
    
    bool MyAna::analyze(storage_manager* storage) {
        
        //
        // Do your event-by-event analysis here. This function is called for
        // each event in the loop. You have "storage" pointer which contains
        // event-wise data. To see what is available, check the "Manual.pdf":
        //
        // http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
        //
        // Or you can refer to Base/DataFormatConstants.hh for available data type
        // enum values. Here is one example of getting PMT waveform collection.
        //
        // event_fifo* my_pmtfifo_v = (event_fifo*)(storage->get_data(DATA::PMFIFO));
        //
        // if( event_fifo )
        //
        //   std::cout << "Event ID: " << my_pmtfifo_v->event_id() << std::endl;
        //
        auto ev_mctrack = storage -> get_data<event_mctrack> ("mcreco");
        
        if(ev_mctrack)
            for (auto const& t: *ev_mctrack){
                pdgID           = t.PdgCode();
                StraightTrackLength += (t.End().Position() - t.Start().Position()).Vect().Mag();
                TrackLength     = 0;
                if(t.size()){
                    for(size_t i=0; i<t.size()-1; ++i) {
                        auto const& this_step = t[i];
                        auto const& next_step = t[i+1];
                        TrackLength += (next_step.Position() - this_step.Position()).Vect().Mag();
                    }
                }
                OutTree -> Fill();
            }
    
        
        return true;
    }
    
    bool MyAna::finalize() {
        
        // This function is called at the end of event loop.
        // Do all variable finalization you wish to do here.
        // If you need, you can store your ROOT class instance in the output
        // file. You have an access to the output file through "_fout" pointer.
        //
        // Say you made a histogram pointer h1 to store. You can do this:
        //
        // if(_fout) { _fout->cd(); h1->Write(); }
        //
        // else 
        //   print(MSG::ERROR,__FUNCTION__,"Did not find an output file pointer!!! File not opened?");
        //
        if(_fout)
            OutTree -> Write();
        return true;
    }
    
}
#endif
