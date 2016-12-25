#ifndef LARLITE_EXTRACTPHYSVARS_CXX
#define LARLITE_EXTRACTPHYSVARS_CXX

#include "ExtractPhysVars.h"

namespace larlite {

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool ExtractPhysVars::initialize() {
        return true;
    }
  
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool ExtractPhysVars::analyze(storage_manager* storage) {
        
        auto ev_track = storage -> get_data<event_track> ("pandoraNu");
//        auto ev_wire  = storage -> get_data<event_wire> ("caldata");
        
        if (ev_track){
            auto p_track_id = FindpTrackID();
            if (p_track_id<0) return false;
            
            for (auto const& t: *ev_track){ // loop over the tracks
                if (t.ID() == p_track_id){
                    if(t.NumberTrajectoryPoints()){
                        for(size_t i=0; i<t.NumberTrajectoryPoints()-1; ++i) {
                            dx = (t.LocationAtPoint(i+1) - t.LocationAtPoint(i)).Mag();
                            Debug( 1 , dx );
                            dQdx = t.DQdxAtPoint( i , geo::kU );
                            SHOW2( dx, dQdx );
                            dEdx = dQdx2dEdx(dQdx);
                            Debug( 1 , dQdx );
                        }
                    }
                    
                }
            } // end loop over the tracks
            
        }
        
        return true;
    }

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool ExtractPhysVars::finalize() {
        return true;
    }
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool ExtractPhysVars::LoadRSEpTracksMap ( TString RSEpTracksMapName ){

        ifstream fin(RSEpTracksMapName);
        Debug( 0, RSEpTracksMapName );
        
        // Read one line at a time.
        string line;
        while ( getline(fin, line) ) { // read the R/S/E map
            istringstream ss(line);
            ss >> run >> subrun >> event >> itrk_proton;
            RSEpTracksMap[run][subrun][event] = itrk_proton ;
        }
        Debug( 2, "read RSEpTracksMapName file");

        // check
        if (debug > 3) {
            for(auto it : RSEpTracksMap) {
                std::cout << "run "  << it.first << std::endl;
                for(auto inner_it : it.second ) {
                    std::cout  << "\t subrun " << inner_it.first;
                    for(auto inner_inner_it : inner_it.second ) {
                        auto i_trk_proton = inner_inner_it.second ;
                        std::cout << "\n\t\t";
                        SHOW2( event , i_trk_proton );
                    }
                }
                PrintLine();
            }
        }
        fin.close();
        Debug( 2, "loaded RSEpTracksMap");
        return true;
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    Int_t ExtractPhysVars::FindpTrackID(){
        // return the p-track id, or -1 if its not found
        
        auto run_iter = RSEpTracksMap.find(run);
        if(run_iter == RSEpTracksMap.end())             return -1;
        auto const& subrun_map = (*run_iter).second;
        auto subrun_iter = subrun_map.find(subrun);
        if(subrun_iter == subrun_map.end())             return -1;
        auto const& event_map = (*subrun_iter).second;
        auto event_iter = event_map.find(event);
        if(event_iter == event_map.end())               return -1;
        // Grab event-map's value (i.e. proton track-id)
        auto const& p_track_id = (*event_iter).second;
        Debug(2 , p_track_id );
        return p_track_id;
    }

    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    Float_t ExtractPhysVars::dQdx2dEdx( Float_t dQ_dx ){
        // convert from dQ/dx to dE/dx using recombination correction
        // Recombination is the process through which ionized electrons will recombine with the positive ions produced along a particle’s trajectory. This physical process depends on the density of ions and the magnitude of this effect depends both on dE/dx, as well as the strength of the external electric field which drifts charge towards the TPC wires.
        // we model the effects of recombination following [MICROBOONE-NOTE-1008-PUB], according to the treatment and results obtained by the ArgoNeuT collaboration [P08005 http://arxiv.org/abs/1306.1712]
        // ArgoNeuT makes use of the Modified Box Model to convert from charge to energy
        
        float rho       = 1.395;// [g/cm3] {at 87.15K, see µB proposal p. 70}
        float Efield    = 0.273;// [kV/cm]
        float Wion      = 23.6; // [eV]
        float e         = 1;    // [e]
        float alpha     = 0.93;
        float kb        = 0.212;
        float beta      = kb / ( rho * Efield ); // [cm4 / g kV]
        Float_t dE_dx   = (exp( beta * (Wion/e) * dQ_dx ) - alpha) / beta; // [MeV/cm]
        
        
        return dE_dx;
        
    }
}
#endif
