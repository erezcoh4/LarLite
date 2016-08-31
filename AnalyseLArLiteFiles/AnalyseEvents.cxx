#ifndef LARLITE_ANALYSEEVENTS_CXX
#define LARLITE_ANALYSEEVENTS_CXX

#include "AnalyseEvents.h"

namespace larlite {
    
    bool AnalyseEvents::initialize() {
        return true;
        // define the 2d histograms?
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::analyze(storage_manager* storage) {
        
        
        auto ev_track = storage -> get_data<event_track> ("pandoraNu");
        auto ev_wire  = storage -> get_data<event_wire> ("caldata");

        CreateEvdImages( ev_wire , RSE , ROIs , Labels );
        
        return true;
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::finalize() {
        
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
            
            ss >> run >> subrun >>  event;
            
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
                std::cout << "run"  << it.first << "\n";
                for(auto inner_it : it.second ) {
                    std::cout  << "subrun " << inner_it.first;
                    for(auto inner_inner_it : inner_it.second ) {
                        std::cout  << ",event " << inner_inner_it.first;
                        std::cout  << ",ROIs: " << "\n";
                            auto boxes = inner_inner_it.second ;
                            for (int i_roi = 0 ; i_roi < NroiPerEvent ; i_roi++ ) {
                                for (int plane = 0 ; plane < 3 ; plane ++ ) {
                                    PrintBox(boxes[i_roi][plane]);
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



