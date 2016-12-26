#ifndef LARLITE_ANALYSEEVENTS_CXX
#define LARLITE_ANALYSEEVENTS_CXX

#include "AnalyseEvents.h"
#include "TPlots.cxx"
#include "MyLArTools.cxx"
#include "TSystem.h"
#include "LArUtil/GeometryHelper.h"

namespace larlite {
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::initialize() {
        plot = new TPlots();
        lar_tools = new MyLArTools();
        Labels = std::vector<TString>{"Sel. II #mu-track","GBDT p-track"};
        TTreeEntry = 0;
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
    bool AnalyseEvents::SetArgs ( TString fworker, Int_t fdebug, TString fimages_path, Int_t fNMaxEntries ){
        SetWorker       (fworker);
        SetDebug        (fdebug);
        SetImagesPath   (fimages_path);
        SetNMaxEntries  (fNMaxEntries);
        return true;
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::analyze(storage_manager* storage) {
    
        TTreeEntry++;
        if (NMaxEntries > 0 && (TTreeEntry > NMaxEntries)) return false;

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
            
            // Grab event-map's value (i.e. ROIs)
            auto const& ROIs = (*event_iter).second;

            if (ev_track){
                mutrack_vertex = mutrack_end = ptrack_vertex = ptrack_end = TVector3();
                
                auto run_iter = VtxTrksIDmap.find(run);
                if(run_iter == VtxTrksIDmap.end())          return false;
                auto const& subrun_map = (*run_iter).second;
                auto subrun_iter = subrun_map.find(subrun);
                if(subrun_iter == subrun_map.end())         return false;
                auto const& event_map = (*subrun_iter).second;
                auto event_iter = event_map.find(event);
                if(event_iter == event_map.end())           return false;
                // Grab event-map's value (i.e. vertex and tracks IDs)
                auto const& VtxTrksIDs = (*event_iter).second;
                ivtx = VtxTrksIDs[0]; itrkMuon = VtxTrksIDs[1]; itrkProton = VtxTrksIDs[2];
                
                // loop over the tracks
                for (auto const& t: *ev_track){
                    if (t.ID() == itrkMuon){
                        mutrack_vertex = t.Vertex();
                        mutrack_end = t.End();
                        VertexMomentum = lar_tools -> Get_muonMomentumFromRange( (t.End() - t.Vertex()).Mag() );
                        VertexDirection = t.VertexDirection();
                        muon_momentum.SetVectMag( VertexMomentum * VertexDirection , 105.6 );
                        if (debug > 3) SHOW3(itrkMuon,VertexMomentum,muon_momentum.P());
                    }
                    if (t.ID() == itrkProton){
                        ptrack_vertex = t.Vertex();
                        ptrack_end = t.End();

                        VertexMomentum = lar_tools -> Get_protonMomentumFromRange( (t.End() - t.Vertex()).Mag() );
                        VertexDirection = t.VertexDirection();
                        proton_momentum.SetVectMag( VertexMomentum * VertexDirection , 938.3 );
                        if (debug > 3) SHOW3(itrkProton,VertexMomentum,proton_momentum.P());
                    }
                }
                if (debug > 2) {
                    SHOWTLorentzVector(muon_momentum);
                    SHOWTLorentzVector(proton_momentum);
                }
                
            }

            std::vector<Int_t> tracks_id = { itrkMuon , itrkProton };
            Int_t RSE[3] = { run , subrun , event };
            std::vector<TLorentzVector> tracks_momenta = { muon_momentum , proton_momentum };
            CreateEvdImages( ev_wire , RSE , ROIs , tracks_id , Labels , tracks_momenta );
            
            
        }
        
        return true;
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::finalize() {
         return true;
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void AnalyseEvents::CreateEvdImages( event_wire * ev_wire , Int_t RSE[3] ,
                                        std::vector<std::vector<box>> fROIs ,
                                        std::vector<Int_t> tracks_id ,
                                        std::vector<TString> fLabels ,
                                        std::vector<TLorentzVector> tracks_momenta ){
        
        if (debug > 2) { cout << "creating image for "; SHOW3( RSE[0],RSE[1],RSE[2] );}
        
        std::vector<box> LargestBox = fROIs.at( fROIs.size() - 1 );
        
        
        
        // define the 2-d histogram
        for (int plane = 0 ; plane < 3; plane++) {
            hName   = Form("r%d_s%d_e%d_p%d", RSE[0] , RSE[1] , RSE[2] , plane);
            hTitle  = Form("run-%d/subrun-%d/event-%d/plane-%d", RSE[0] , RSE[1] , RSE[2] , plane);
            
            w_min[plane] = LargestBox[plane].start_wire  - 20;
            w_max[plane] = LargestBox[plane].end_wire    + 20;
            t_min[plane] = LargestBox[plane].start_time  - 40;
            t_max[plane] = LargestBox[plane].end_time    + 40;
            
            Nbins_w[plane] = w_max[plane] - w_min[plane] + 1;
            Nbins_t[plane] = t_max[plane] - t_min[plane] + 1;
            
            hROI[plane] = new TH2F( hName , hTitle , Nbins_w[plane] , w_min[plane] , w_max[plane] , Nbins_t[plane] , t_min[plane] , t_max[plane]);
            
            hROI[plane] -> GetXaxis() -> SetTitle("wire number");
            hROI[plane] -> GetXaxis() -> CenterTitle();
            hROI[plane] -> GetYaxis() -> SetTitle("time tick");
            hROI[plane] -> GetYaxis() -> CenterTitle();
            hROI[plane] -> GetYaxis() -> SetTitleOffset(1.3);
        }
        
        
        // plug wire data into histogram
        auto geoService = ::larutil::Geometry::GetME();

        for (auto const& wire : *ev_wire) {
            
            unsigned int ch = wire.Channel();
            unsigned int detWire = geoService->ChannelToWire(ch);
            unsigned int detPlane = geoService->ChannelToPlane(ch);
            if(debug > 4) cout << "ch " << ch << ", wire " << detWire << ", plane " << detPlane <<  endl;
            
            
            
            // accumulate the ADC signal around the left bottom corner of the track ROI box
            if ( w_min[detPlane] <= detWire && detWire <= w_max[detPlane] ) {
                
                for (auto & iROI : wire.SignalROI().get_ranges()) {
                    
                    const int FirstTick = iROI.begin_index();
                    time_tick = FirstTick;
                    
                    for (float ADC : iROI) {
                        if ( t_min[detPlane] <= time_tick && time_tick <= t_max[detPlane] ) {
                            hROI[detPlane] -> SetBinContent( detWire - w_min[detPlane] , time_tick - t_min[detPlane] , ADC );
                        }
                        time_tick++;
                    } // ADC
                } // iROI
            } // detWire
            
        }
        
        TString c_image_directory = Form("%s/run%d_subrun%d_event%d",images_path.Data(),RSE[0],RSE[1],RSE[2]);
        // save the 2d histograms to images
        if (debug > 3) std::cout << "saving images of " + c_image_directory << std::endl;
        gSystem -> mkdir(c_image_directory);
        TCanvas * c[3] ;
        gStyle -> SetOptStat(0000);
        for ( int plane = 0 ; plane < 3 ; plane++ ){
            c[plane] = new TCanvas(Form("track ROI plane %d",plane));
            c[plane] -> SetRightMargin(0.20);
            hROI[plane] -> Draw("col");
        }
        
        // add ROIs
        std::vector<Int_t> colors = {1 , 4 , 0};
        
        // load GeometryHelper utility
        auto geomHelper = ::larutil::GeometryHelper::GetME();
        double mu_start_xyz[3] = {mutrack_vertex.x() , mutrack_vertex.y() , mutrack_vertex.z() };
        double mu_end_xyz[3] = {mutrack_end.x() , mutrack_end.y() , mutrack_end.z() };
        double p_start_xyz[3] = {ptrack_vertex.x() , ptrack_vertex.y() , ptrack_vertex.z() };
        double p_end_xyz[3] = {ptrack_end.x() , ptrack_end.y() , ptrack_end.z() };
        double time_shift =  802;
        int mu_start_wire[3] , mu_start_time[3] , mu_end_wire[3] , mu_end_time[3];
        int p_start_wire[3] , p_start_time[3] , p_end_wire[3] , p_end_time[3];
        
        for (int plane = 0 ; plane < 3 ; plane++){
            auto const& mu_start_projection2D = geomHelper->Point_3Dto2D(mu_start_xyz, plane);
            auto const& mu_end_projection2D = geomHelper->Point_3Dto2D(mu_end_xyz, plane);
            mu_start_wire[plane] = (int) ( mu_start_projection2D.w / geomHelper->WireToCm() );
            mu_start_time[plane] = (int) ( mu_start_projection2D.t / geomHelper->TimeToCm() ) + time_shift;
            mu_end_wire[plane] = (int) ( mu_end_projection2D.w / geomHelper->WireToCm() );
            mu_end_time[plane] = (int) ( mu_end_projection2D.t / geomHelper->TimeToCm() ) + time_shift;
            
            auto const& p_start_projection2D = geomHelper->Point_3Dto2D(p_start_xyz, plane);
            auto const& p_end_projection2D = geomHelper->Point_3Dto2D(p_end_xyz, plane);
            p_start_wire[plane] = (int) ( p_start_projection2D.w / geomHelper->WireToCm() );
            p_start_time[plane] = (int) ( p_start_projection2D.t / geomHelper->TimeToCm() ) + time_shift;
            p_end_wire[plane] = (int) ( p_end_projection2D.w / geomHelper->WireToCm() );
            p_end_time[plane] = (int) ( p_end_projection2D.t / geomHelper->TimeToCm() ) + time_shift;
        }

        int i_roi = 0;
        for (auto ROIs : fROIs) {
            
            for (int plane = 0 ; plane < 3 ; plane++){
            
                ROIs[plane].start_wire -= i_roi;
                ROIs[plane].start_time -= i_roi;
                ROIs[plane].end_wire += i_roi;
                ROIs[plane].end_time += i_roi;
                c[plane] -> cd();
                
                // add tracks information
                double xNDC = 0.82 , yNDC = 0.9 , dyNDC = 0.05;
                plot -> Latex( xNDC , yNDC , Form("plane %d",plane) , 1 , 0.03 );
                if ( i_roi < tracks_momenta.size() ) {
                    
                    plot -> ROI((double)ROIs[plane].start_wire,(double)ROIs[plane].start_time,(double)ROIs[plane].end_wire,(double)ROIs[plane].end_time , colors[i_roi]);
                    if(debug > 2) cout << "adding information about "<< Labels[i_roi] << " at plane " << plane << endl;
                    // label
                    plot -> Latex( xNDC , yNDC - (1+5*i_roi)*dyNDC , Labels[i_roi] + Form(" [t %d]",tracks_id[i_roi]) , colors[i_roi] , 0.03 );
                    // ROI box
                    if (debug > 2) { cout <<
                    Form("(%d,%d)->(%d,%d)",ROIs[plane].start_wire,ROIs[plane].start_time,ROIs[plane].end_wire,ROIs[plane].end_time)
                        << endl;}
                    plot -> Latex( xNDC , yNDC - (2+5*i_roi)*dyNDC  ,
                                  Form("(%d,%d)->(%d,%d)",
                                       ROIs[plane].start_wire,ROIs[plane].start_time,ROIs[plane].end_wire,ROIs[plane].end_time) , colors[i_roi] , 0.02 );
                    // direction
                    TVector3 dir = tracks_momenta[i_roi].Vect().Unit();
                    plot -> Latex( xNDC , yNDC - (3+5*i_roi)*dyNDC  , Form("dir. (%.2f,%.2f,%.2f)",dir.x(),dir.y(),dir.z()) , colors[i_roi] , 0.03 );
                    
                    // momentum and kinetic energy
                    double p = tracks_momenta[i_roi].P() / 1000. , pErr = 0.05*p;
                    double K = (tracks_momenta[i_roi].E()- tracks_momenta[i_roi].M()) / 1000. , KErr = 0.05*K;
                    plot -> Latex( xNDC , yNDC - (4+5*i_roi)*dyNDC , Form("p: %.3f(%.0f) GeV/c", p , 100*pErr ) , colors[i_roi] , 0.03 );
                    plot -> Latex( xNDC , yNDC - (5+5*i_roi)*dyNDC , Form("K: %.3f(%.0f) GeV" , K , 100*KErr ) , colors[i_roi] , 0.03 );
                    
                    
                    // lines of the pandoraNu tracking
                    if (Labels[i_roi] == "Sel. II #mu-track")
                    {
                        if (debug > 2) { cout <<
                            Form("muon: (%d,%d)->(%d,%d)",mu_start_wire[plane],mu_start_time[plane],mu_end_wire[plane],mu_end_time[plane])
                            << endl; }
                        plot -> Line( mu_start_wire[plane] , mu_start_time[plane] , mu_end_wire[plane] , mu_end_time[plane] , colors[i_roi] , 1 , 3 );
                    }
                    else if (Labels[i_roi] == "GBDT p-track")
                    {
                        if (debug > 2) { cout <<
                            Form("proton: (%d,%d)->(%d,%d)",p_start_wire[plane],p_start_time[plane],p_end_wire[plane],p_end_time[plane])
                            << endl; }

                        plot -> Line( p_start_wire[plane] , p_start_time[plane] , p_end_wire[plane] , p_end_time[plane] , colors[i_roi] , 1 , 3 );}
                    

                }
            }
            
            i_roi++;
        }
        
        
        // save and delete
        for (int plane = 0 ; plane < 3 ; plane++){
            c[plane] -> SaveAs(Form("%s/run%d_subrun%d_event%d/ROI_plane%d.%s",
                                    images_path.Data(),RSE[0],RSE[1],RSE[2],plane,ImageFormat.Data()));
            delete c[plane];
        }
        
        
        


    }
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnalyseEvents::LoadROIsMap( TString ROIMapName , Int_t NroiPerEvent ){
        
        ifstream fin(ROIMapName);
        
        if (debug > 0) std::cout << "loading data from file \n" << ROIMapName << endl;
        
        // Read one line at a time.
        string line , tmp;
        std::vector<box> ROIs;
        getline(fin, line, '\n'); // header line
        cout << "header line:" <<  line ;

        while ( getline(fin, line , '\n') ) {
            
            istringstream ss(line);
            cout << "ss:" <<  ss  << endl;
            ss >> run >> tmp >> subrun >> tmp >>  event >> tmp >> ivtx >> tmp >> itrkMuon >> tmp >> itrkProton;
            
//            ss >> run >> subrun >>  event >> ivtx >> itrkMuon >> itrkProton;

            std::vector<Int_t> VtxTrksIDs = {ivtx , itrkMuon , itrkProton};
            VtxTrksIDmap[run][subrun][event] = VtxTrksIDs ;

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
            for(auto it : VtxTrksIDmap) {
                std::cout << "run "  << it.first ;
                for(auto inner_it : it.second ) {
                    std::cout  << ", subrun " << inner_it.first ;
                    for(auto inner_inner_it : inner_it.second ) {
                        std::cout  << ", event " << inner_inner_it.first;
                        std::cout  << ", IDs: " << "\n";
                        auto IDs = inner_inner_it.second ;
                        std::cout  << "vertex: " << IDs[0] << ", muon track:" << IDs[1] << ", proton track: " << IDs[2] << "\n";
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



