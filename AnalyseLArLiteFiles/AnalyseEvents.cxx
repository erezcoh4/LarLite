#ifndef LARLITE_ANALYSEEVENTS_CXX
#define LARLITE_ANALYSEEVENTS_CXX

#include "AnalyseEvents.h"

namespace larlite {
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::initialize() {
        return true;
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void AnalyseEvents::SetWorker ( TString fworker ){
        worker = fworker;
        if (worker == "uboone"){
            gROOT->SetBatch(kTRUE);
        }
    };

    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::SetArgs ( TString fworker, Int_t fdebug, TString fimages_path ){
        SetWorker       (fworker);
        SetDebug        (fdebug);
        SetImagesPath   (fimages_path);
        return true;
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::analyze(storage_manager* storage) {
        
        
        auto ev_track = storage -> get_data<event_track> ("pandoraNu");
        auto ev_wire  = storage -> get_data<event_wire> ("caldata");
        
        
        
        if(ev_wire){
            
            run = ev_wire->run(); subrun = ev_wire->subrun(); event = ev_wire->event_id();
            
            //Search run
            auto run_iter = ROImap.find(run);
            if(run_iter == ROImap.end()) {
                std::cout << " run " << run << " not found..." << std::endl;
                return false;
            }
            // Grab run-map's value (i.e. subrun map)
            auto const& subrun_map = (*run_iter).second;
            //Search sub run
            auto subrun_iter = subrun_map.find(subrun);
            if(subrun_iter == subrun_map.end()) {
                std::cout << " subrun " << subrun << " not found..." << std::endl;
                return false;
            }
            // Grab subrun-map's value (i.e. event map)
            auto const& event_map = (*subrun_iter).second;
            // Search event
            auto event_iter = event_map.find(event);
            if(event_iter == event_map.end()) {
                std::cout << " event " << event << " not found..." << std::endl;
                return false;
            }
            
            
            // Grab event-map's value (i.e. track-id map)
            auto const& track_id_map = (*event_iter).second;
            
            
            CreateEvdImages( ev_wire , RSE , ROIs , Labels );
        }
        
        return true;
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::finalize() {
         return true;
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void AnalyseEvents::CreateEvdImages( event_wire * wire , int fRSE[3] , std::vector<box> fROIs , std::vector<TString> fLabels ){
        
    }
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::LoadROIsMap( TString ROIMapName , Int_t NroiPerEvent ){
        
        ifstream fin(ROIMapName);
        
        if (debug > 0) std::cout << "loading data from file \n" << ROIMapName << endl;
        
        // Read one line at a time.
        string line ;
        std::vector<box> ROIs;
        
        while ( getline(fin, line) ) {
            
            istringstream ss(line);
            
            ss >> run >> subrun >>  event >> ivtx >> itrkMuon >> itrkProton;
            
            for (int i_roi = 0 ; i_roi < NroiPerEvent ; i_roi++ ) {
                
                if (!ROIs.empty()) ROIs.clear();
                
                for (int plane = 0 ; plane < 3 ; plane ++ ) {
                    ss  >>  start_w[plane] >>  start_t[plane] >> end_w[plane] >> end_t[plane];
                    ROIs.push_back( box ( start_w[plane] ,  start_t[plane] , end_w[plane] , end_t[plane] ) );
                }
                
                ROImap[run][subrun][event].push_back( ROIs );
            }
        }
        // check
        if (debug > 3) {
            for(auto it : ROImap) {
                std::cout << "run "  << it.first ;
                for(auto inner_it : it.second ) {
                    std::cout  << ", subrun " << inner_it.first ;
                    for(auto inner_inner_it : inner_it.second ) {
                        std::cout  << ", event " << inner_inner_it.first;
                        std::cout  << ", ROIs: " << "\n";
                            auto boxes = inner_inner_it.second ;
                            for (int i_roi = 0 ; i_roi < NroiPerEvent ; i_roi++ ) {
                                SHOW(i_roi);
                                for (int plane = 0 ; plane < 3 ; plane ++ ) {
                                    box roi = boxes[i_roi][plane];
                                    SHOW(plane);
                                    PrintBox(roi);
                            }
                        }
                    }
                }
                std::cout << std::endl;
            }
        }
        
        fin.close();
        return true;
    }
    

    
}
#endif



