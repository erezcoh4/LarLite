#ifndef LARLITE_ANAPANDORANUTRACKS_CXX
#define LARLITE_ANAPANDORANUTRACKS_CXX

#include "AnaPandoraNuTracks.h"
#include <sstream>
#include "LArUtil/GeometryHelper.h"
#include <cstdlib>
#include "TSystem.h"
#include "MySoftwarePackage/TPlots.cxx"

namespace larlite {
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::SetWorker( TString worker , Int_t fdebug
                                       , bool fCreateImagas , TString fimages_path
                                       , TString froi_map_path , TString froi_map_name ) {
        
        if (worker == "erez")
        on_uboone_grid = false ;
        
        else if (worker == "uboone"){
            on_uboone_grid = true ;
            gROOT->SetBatch(kTRUE);
        }
        
        debug           = fdebug;
        CreateImagas    = fCreateImagas;
        images_path     = fimages_path;
        roi_map_path    = froi_map_path;
        roi_map_name    = froi_map_name;
        calculate_adc_in_corners = false;
        
        std::cout << "worker: " << worker << ", debug: " << debug << std::endl;
        std::cout << "create-images: " << CreateImagas << std::endl;
        return true;
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::initialize() {
        
        
        
        TracksTree  = new TTree("TracksTree"        ,"GBDT classified proton tracks analysis by LArLite"   );
        TracksTree -> Branch("vertex"               ,   "TVector3"          ,   &vertex );
        TracksTree -> Branch("end"                  ,   "TVector3"          ,   &end );
        TracksTree -> Branch("straight_track"       ,   "TVector3"          ,   &straight_track );
        TracksTree -> Branch("run"                  , &run                  ,   "run/I");
        TracksTree -> Branch("subrun"               , &subrun               ,   "subrun/I");
        TracksTree -> Branch("event"                , &event                ,   "event/I");
        TracksTree -> Branch("track_id"             , &track_id             ,   "track_id/I");
        TracksTree -> Branch("straight track length [cm]"   , &straight_track_length      ,   "straight_track_length/D");
        TracksTree -> Branch("segmented track length [cm]"  , &segmented_track_length     ,   "segmented_track_length/D");
        TracksTree -> Branch("momentum [MeV/c]"             , &momentum                   ,   "momentum/D");
        TracksTree -> Branch("number of close tracks"       , &N_close_tracks             ,   "N_neighboring_tracks/I");
        TracksTree -> Branch("Angle_close_track"            , &Angle_close_track             );// std::vector<Double_t>
        
        
        
        TracksTree -> Branch("ADC around lt corner [a.u.]"  , &SumADC_around_lt           ,   "SumADC_around_lt/D");
        TracksTree -> Branch("ADC lt in track-direction [a.u.]"
                             , &SumADC_around_lt_in_track_direction ,   "SumADC_around_lt_in_track_direction/D");
        TracksTree -> Branch("ratio around lt corner [a.u.]", &ADC_ratio_around_lt        ,   "ADC_ratio_around_lt/D");
        
        
        
        TracksTree -> Branch("ADC around lb corner [a.u.]"  , &SumADC_around_lb           ,   "SumADC_around_lb/D");
        TracksTree -> Branch("ADC lb in track-direction [a.u.]"
                             , &SumADC_around_lb_in_track_direction ,   "SumADC_around_lb_in_track_direction/D");
        TracksTree -> Branch("ratio around lb corner [a.u.]", &ADC_ratio_around_lb        ,   "ADC_ratio_around_lb/D");
        
        
        
        TracksTree -> Branch("ADC around rt corner [a.u.]"  , &SumADC_around_rt           ,   "SumADC_around_rt/D");
        TracksTree -> Branch("ADC rt in track-direction [a.u.]"
                             , &SumADC_around_rt_in_track_direction  ,   "SumADC_around_rt_in_track_direction/D");
        TracksTree -> Branch("ratio around rt corner [a.u.]", &ADC_ratio_around_rt        ,   "ADC_ratio_around_rt/D");
        
        
        TracksTree -> Branch("ADC around rb corner [a.u.]"  , &SumADC_around_rb           ,   "SumADC_around_rb/D");
        TracksTree -> Branch("ADC rb in track-direction [a.u.]"
                             , &SumADC_around_rb_in_track_direction ,   "SumADC_around_rb_in_track_direction/D");
        TracksTree -> Branch("ratio around rb corner [a.u.]", &ADC_ratio_around_rb        ,   "ADC_ratio_around_rb/D");
        
        
        Printf("Initialized TracksTree");
        
        //        out_csv_file = ofstream("/Users/erezcohen/larlite/UserDev/LarLite/MyPackage/lists/selected_GBDTcandidates_score_95.csv");
        //        out_csv_file << "run, subrun, event, track-id, start wire, start time-tick, end wire, end time-tick " << endl;
        
        LoadBDTCandidates();
        
        lar_tools = new MyLArTools();
        plot = new TPlots();
        
        NgoodTracks = 0;
        TTreeEntry = 0;
        
        
        return true;
    }
    //..............................................................................
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::analyze(storage_manager* storage) {
        
        TTreeEntry++;
//        if ( 1 < TTreeEntry || TTreeEntry > 2 ) return true; // just for playing a little before runnig the entire script
        
        auto ev_track = storage -> get_data<event_track> ("pandoraNu");
        auto ev_wire  = storage -> get_data<event_wire> ("caldata");
        
        
        if(ev_track){
            
            run = ev_track->run(); subrun = ev_track->subrun(); event = ev_track->event_id();
            
            //Search run
            auto run_iter = BDTcandidates.find(run);
            if(run_iter == BDTcandidates.end()) {
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
            
            
            // loop over the tracks
            for (auto const& t: *ev_track){
                
                N_close_tracks = 0;
                GoodTrack = true;
                bool CreatingTrackImage = false;
                if(!Angle_close_track.empty()) Angle_close_track.clear();
                track_id = t.ID();
                
                // Search event
                auto track_id_iter = track_id_map.find(track_id);
                if(track_id_iter == track_id_map.end()) {
                    std::cout << "track " <<  track_id << " not in our list..." << std::endl;
                    continue;
                }
                
                // Grab box
                auto const& b = (*track_id_iter).second;
                
                // (suffix - add 1)
                if (debug>0) {
                    PrintLine();
                    std::cout << "run " << run << ", subrun " << subrun << ", event " << event << ", track id " << track_id << std::endl;
                    PrintBox(b[0]); PrintBox(b[1]); PrintBox(b[2]);
                }
                
                
                
                
                
                
                
                // (2) wire data....
                if (ev_wire){
                    
                    
                    
                    // (2-a) define histograms and arrays....
                    if(debug > 2) Printf("(2-a) define histograms and arrays....");
                    if (CreateImagas) {
                        
                        for (int plane = 0 ; plane < 3; plane++) {
                            
                            TString hName = Form("r%d_s%d_e%d_t%d_plane%d", run,subrun,event,track_id,plane);
                            
                            TString hTitle = Form("r%d s%d e%d t%d window in plane %d (%d,%.1f)=>(%d,%.1f)"
                                                  ,run,subrun,event,track_id,plane
                                                  ,b[plane]._start_wire,b[plane]._start_t,b[plane]._end_wire,b[plane]._end_t);
                            
                            Nbins_w = b[plane]._end_wire - b[plane]._start_wire + 11;
                            Nbins_t = (int)(b[plane]._end_t - b[plane]._start_t) + 21;
                            
                            hTrackROI[plane] = new TH2F(hName , hTitle
                                                        , Nbins_w  , b[plane]._start_wire - 5 , b[plane]._end_wire + 5
                                                        , Nbins_t  , b[plane]._start_t - 10 , b[plane]._end_t + 10 );
                            SetFrame( hTrackROI[plane] , "wire number" , "time tick" );
                            
                            Nbins_w_zoomout = b[plane]._end_wire - b[plane]._start_wire + 41;
                            Nbins_t_zoomout = (int)(b[plane]._end_t - b[plane]._start_t) + 81;
                            
                            hTrackROIzoomout[plane] = new TH2F(Form("%s_zoomout",hName.Data()) ,Form("%s zoomout",hName.Data())
                                                               , Nbins_w_zoomout  , b[plane]._start_wire - 20 , b[plane]._end_wire + 20
                                                               , Nbins_t_zoomout  , b[plane]._start_t - 40 , b[plane]._end_t + 40);
                            SetFrame( hTrackROIzoomout[plane] , "wire number" , "time tick" );
                            
                        }
                        if (debug > 2) Printf("done creating U/V/Y planes histograms, now starting x-y / y-z planes");
                        
                        
                        // histograms in x-z and y-z planes from
                        Xmin = std::min(t.Vertex().x(),t.End().x()) - 30 ; Xmax = std::max(t.Vertex().x(),t.End().x()) + 30 ;
                        Ymin = std::min(t.Vertex().y(),t.End().y()) - 30 ; Ymax = std::max(t.Vertex().y(),t.End().y()) + 30 ;
                        Zmin = std::min(t.Vertex().z(),t.End().z()) - 30 ; Zmax = std::max(t.Vertex().z(),t.End().z()) + 30 ;
                        Nbins_x = 2*(int)(Xmax-Xmin)+1; Nbins_y = 2*(int)(Ymax-Ymin)+1 ; Nbins_z = 2*(int)(Zmax-Zmin)+1;
                        
                        TString hName = Form("r%d_s%d_e%d_t%d",run,subrun,event,track_id);
                        TString hTitle = Form("r%d s%d e%d t%d",run,subrun,event,track_id);
                        TString hNamexy = Form("%s_xy",hName.Data()) , hNameyz = Form("%s_yz",hName.Data());
                        TString hTitlexy = Form("%s x-y plane (%.2f,%.2f)=>(%.2f,%.2f)",
                                                hTitle.Data() , t.Vertex().x(),t.Vertex().y(),t.End().x(),t.End().y() ) ;
                        TString hTitleyz = Form("%s y-z plane (%.2f,%.2f)=>(%.2f,%.2f)",
                                                hTitle.Data() , t.Vertex().z(),t.Vertex().y(),t.End().z(),t.End().y());
                        
                        hTrack_xy = new TH2F(hNamexy , hTitlexy , Nbins_x  , Xmin , Xmax , Nbins_y , Ymin , Ymax );
                        SetFrame( hTrack_xy , "x [cm] (horizontal)" , "y [cm] (vertical)" );
                        
                        hTrack_zy = new TH2F(hNameyz , hTitleyz , Nbins_z  , Zmin , Zmax , Nbins_y  , Ymin , Ymax );
                        SetFrame( hTrack_zy , "z [cm] (beam direction)" , "y [cm] (vertical)"  );
                        
                        if(debug > 2){
                            Printf("generated histograms for \
                                   (x,y,z) : (%.2f,%.2f,%.2f) -> (%.2f,%.2f,%.2f)",Xmin,Ymin,Zmin,Xmax,Ymax,Zmax);
                            SHOW3(t.Vertex().x() , t.End().x() , Nbins_x);
                            SHOW3(t.Vertex().y() , t.End().y() , Nbins_y);
                            SHOW3(t.Vertex().z() , t.End().z() , Nbins_z);
                            SHOW(Nbins_w_zoomout);SHOW(Nbins_t_zoomout);

                        }
                    }
                    // (suffix - add 2)
                    
                    // (2-b) services and helpers....
                    auto geoService = ::larutil::Geometry::GetME();
                    auto geomH = ::larutil::GeometryHelper::GetME();

                    // (2-c) grab wire data
                    if(debug > 2) Printf("(2-c) grab wire data");
                    for (auto const& wire : *ev_wire) {
                        
                        unsigned int ch = wire.Channel();
                        unsigned int detWire = geoService->ChannelToWire(ch);
                        unsigned int c_plane = geoService->ChannelToPlane(ch);
                        if(debug > 4) cout << "ch " << ch << ", wire " << detWire << ", plane " << c_plane <<  endl;
                        
                        
                        
                        if(debug > 4) Printf("(2-c-1) loop over all three planes");
                        // (2-c-1) loop over all three planes
                        if (CreateImagas) {
                            for (int plane = 0 ; plane < 3 ; plane++){
                                // accumulate the ADC signal around the left bottom corner of the track ROI box
                                if ( b[plane]._start_wire - 20 <= detWire && detWire <= b[plane]._end_wire + 20 ) {
                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
                                        const int FirstTick = iROI.begin_index();
                                        time_tick = FirstTick;
                                        FirstTickZoomout = FirstTick;
                                        for (float ADC : iROI) {
                                            if ( b[plane]._start_t - 40 <= time_tick && time_tick <= b[plane]._end_t + 40 ) {
                                                hTrackROIzoomout[plane] -> SetBinContent( detWire - b[plane]._start_wire + 20 ,
                                                                                         time_tick - b[plane]._start_t + 40 , ADC );
                                                if (debug>4 && plane == 2) {
                                                    printf("on Y plane: \t");
                                                    SHOW3(detWire, time_tick,ADC);
                                                }

                                            }
                                            time_tick++;
                                        }
                                    }
                                }
                                if ( b[plane]._start_wire - 5 <= detWire && detWire <= b[plane]._end_wire + 5 ) {
                                    CreatingTrackImage = true;
                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
                                        const int FirstTick = iROI.begin_index();
                                        time_tick = FirstTick;
                                        for (float ADC : iROI) {
                                            if ( b[plane]._start_t - 10 <= time_tick && time_tick <= b[plane]._end_t + 10 ) {
                                                hTrackROI[plane] -> SetBinContent( detWire - b[plane]._start_wire + 5 ,
                                                                                   time_tick - b[plane]._start_t + 10 , ADC );
                                            }
                                            time_tick++;
                                        }
                                    }
                                }
                            }
                         }
                        
                    }
                    
                    
                    // (2-c) histograms in detector coordinate
                    // for each 3D point, take the information form the Y plane corresponding pixel
                    // and plug it into the right X-Y or Y-Z plane pixel we want....
                    if (CreatingTrackImage) {

                        

                        
//
//                        for (int bin_x = 0 ; bin_x < Nbins_x ; bin_x ++ ) {
//                            float x = hTrack_xy -> GetXaxis() -> GetBinCenter( bin_x );
//
//                            for (int bin_y = 0 ; bin_y < Nbins_y ; bin_y ++  ) {
//                                float y = hTrack_xy -> GetYaxis() -> GetBinCenter( bin_y );
//
//                                float ADC_U = 0;
//                                if(!wire_and_time_bins.empty()) wire_and_time_bins.clear();
//                                
//                                
//                                float z = (Zmin+Zmax)/2.;
//                                double xyz[3] = { x , y , z };
//                                
//                                
//                                
//                                // project on the collection plane
//                                larutil::Point2D projection_U = geomH->Point_3Dto2D( xyz , 0 );
//                                
//                                // find the ADC value on the collection plane
//                                auto wire_U = projection_U.w / geomH->WireToCm();
//                                auto time_U = projection_U.t / geomH->TimeToCm() + time_shift;
//                                int   bin_w = hTrackROIzoomout[0] -> GetXaxis() -> FindBin(wire_U);
//                                int   bin_t = hTrackROIzoomout[0] -> GetYaxis() -> FindBin(time_U);
//                                if (debug>2){
//                                    SHOW3(Nbins_x,Nbins_y,Nbins_z);
//                                    SHOW3(x,y,z);
//                                    Printf( "wire=%.1f (start & %.1f), time=%.1f (start & %.1f) ,bin_w = %d , bin_t = %d, bin content = %.1f",
//                                       wire_U , wire_U - hTrackROIzoomout[0] -> GetXaxis() -> GetBinCenter(0) ,
//                                       time_U , time_U - hTrackROIzoomout[0] -> GetYaxis() -> GetBinCenter(0) ,
//                                       bin_w ,  bin_t , hTrackROIzoomout[0] -> GetBinContent( bin_w, bin_t ));
//                                    Printf("ADC_U (add %f) = %f",hTrackROIzoomout[0] -> GetBinContent( bin_w, bin_t ),ADC_U );
//                                    PrintLine();
//
//                                }
//                                if (bin_w<0 || bin_w > Nbins_w_zoomout || bin_t < 0 || bin_t > Nbins_t_zoomout ) continue;
//
//                                    if ( FirstSeedWireAndTime ( bin_w, bin_t ) ){
//                                        ADC_U += hTrackROIzoomout[0] -> GetBinContent( bin_w, bin_t );
//                                        std::vector<int> c_wire_and_time_bins = {bin_w, bin_t};
//                                        wire_and_time_bins.push_back( c_wire_and_time_bins );
//
//                                }
//                                // plug this ADC value into the right bin in the det. coor. histograms
//                                hTrack_xy -> SetBinContent( bin_x , bin_y , ADC_U );
//                                if (debug>2) Printf( "\n\nx = %f , y =%f , bin_x = %d , bin_y = %d, hTrack_xy = %f\n\n"
//                                                    ,x , y , bin_x ,  bin_y , hTrack_xy -> GetBinContent( bin_x , bin_y ) );
//                            }
//                        }
//                        
//                        
//                        
//                        
                        
//                        for (int bin_z = 0 ; bin_z < Nbins_z ; bin_z ++ ) {
//                            float z = hTrack_zy -> GetXaxis() -> GetBinCenter( bin_z );
//                            if(!wire_and_time_bins.empty()) wire_and_time_bins.clear();
//                            
//                            for (int bin_y = 0 ; bin_y < Nbins_y ; bin_y ++  ) {
//                                float y = hTrack_zy -> GetYaxis() -> GetBinCenter( bin_y );
//                                
//                                float ADC_U = 0;
//                                
//                                
//                                
////                                for (int bin_x = 0 ; bin_x < Nbins_x ; bin_x ++  ) {
////                                    float x = hTrack_xy -> GetXaxis() -> GetBinCenter( bin_x );
//                                                                    float x = (Xmin+Xmax)/2.;
//                                    double xyz[3] = { x , y , z };
//                                    
//                                    // project on the collection plane
//                                    larutil::Point2D projection_U = geomH->Point_3Dto2D( xyz , 0 );
//                                    
//                                    // find the ADC value on the collection plane
//                                    auto wire_U = projection_U.w / geomH->WireToCm();
//                                    auto time_U = projection_U.t / geomH->TimeToCm() + time_shift;
//                                    int   bin_w = hTrackROIzoomout[0] -> GetXaxis() -> FindBin(wire_U);
//                                    int   bin_t = hTrackROIzoomout[0] -> GetYaxis() -> FindBin(time_U);
//                                    
//                                    if (    wire_U < hTrackROIzoomout[0] -> GetXaxis() -> GetBinCenter(0)
//                                        ||  wire_U > hTrackROIzoomout[0] -> GetXaxis() -> GetBinCenter(Nbins_w_zoomout)
//                                        ||  time_U < hTrackROIzoomout[0] -> GetYaxis() -> GetBinCenter(0)
//                                        ||  time_U > hTrackROIzoomout[0] -> GetYaxis() -> GetBinCenter(Nbins_t_zoomout) ) continue;
//
//                                    if (debug>2){
//                                        SHOW3(x,y,z);
//                                        Printf( "plane-U (w=%.1f,t=%.1f), bin[%d,%d] content = %.1f",
//                                               wire_U ,time_U ,
//                                               bin_w ,  bin_t , hTrackROIzoomout[0] -> GetBinContent( bin_w, bin_t ));
//                                        
//                                    }
//                                    
//                                    if ( FirstSeedWireAndTime ( bin_w, bin_t ) ){
//                                        ADC_U += hTrackROIzoomout[0] -> GetBinContent( bin_w, bin_t );
//                                        std::vector<int> c_wire_and_time_bins = {bin_w, bin_t};
//                                        wire_and_time_bins.push_back( c_wire_and_time_bins );
//                                        if (debug>2){
//                                            Printf("ADC_U [%d][%d] (add %f) = %f",bin_z,bin_y,hTrackROIzoomout[0] -> GetBinContent( bin_w, bin_t ),ADC_U );
//                                            PrintLine();
//                                        }
//                                    }
////                                }
//                                // plug this ADC value into the right bin in the det. coor. histograms
//                                hTrack_zy -> SetBinContent( bin_z , bin_y , ADC_U );
//                                if (debug>2) Printf( "\n\nz = %f , y =%f , bin_z = %d , bin_y = %d, hTrack_zy = %f\n\n"
//                                                    ,z , y , bin_z ,  bin_y , hTrack_zy -> GetBinContent( bin_z , bin_y ) );
//
//                            }
//                        }
                        
                        float adc_UV[MAXbins][MAXbins];
                        for (int bin_z = 0 ; bin_z < Nbins_z ; bin_z ++ ) {
                            for (int bin_y = 0 ; bin_y < Nbins_y ; bin_y ++  ) {
                                adc_UV[bin_z][bin_y] = 0;
                            }
                        }
                        for (int i_w = 0 ; i_w < Nbins_w_zoomout; i_w++) {
                            for (int i_t = 0 ; i_t < Nbins_t_zoomout; i_t++) {
                                
                                float wire_U = hTrackROIzoomout[0] -> GetXaxis() -> GetBinCenter(i_w) ;
                                float ww_U = wire_U * geomH->WireToCm() ;
                                float time_U = hTrackROIzoomout[0] -> GetYaxis() -> GetBinCenter(i_t) ;
                                float tt_U = time_U * geomH->TimeToCm() ;
                                float  adc_U = hTrackROIzoomout[0] -> GetBinContent( i_w , i_t );
                                larutil::Point2D * projection_U = new larutil::Point2D( 0 , ww_U , tt_U );
                                
                                float wire_V = hTrackROIzoomout[1] -> GetXaxis() -> GetBinCenter(i_w) ;
                                float ww_V = wire_V * geomH->WireToCm();
                                float time_V = hTrackROIzoomout[1] -> GetYaxis() -> GetBinCenter(i_t) ;
                                float tt_V = time_V * geomH->TimeToCm();
                                float  adc_V = hTrackROIzoomout[1] -> GetBinContent( i_w , i_t );
                                larutil::Point2D * projection_V = new larutil::Point2D( 1 , ww_V , tt_V );
                                
                                
                                
                                Double_t yz[2];
                                geomH -> GetYZ( projection_U , projection_V , yz );
                                
                                int bin_z = (int)hTrack_zy -> GetXaxis() -> FindBin(yz[1]);
                                int bin_y = (int)hTrack_zy -> GetYaxis() -> FindBin(yz[0]);
                                adc_UV[bin_z][bin_y] += adc_U + adc_V;
                                if(debug>2){

                                    SHOW3( wire_U , time_U , adc_U );

                                    SHOW3( wire_V , time_V , adc_V );

                                    Printf( "z = %f , y = %f , adc_U = %f , adc_V = %f" , yz[1] , yz[0] , adc_U , adc_V );
                                    Printf( "bin_z = %d , bin_y = %d , adc_UV = %f" , bin_z , bin_y , adc_UV[bin_z][bin_y] );
                                }

                            }
                        }
                        for (int bin_z = 0 ; bin_z < Nbins_z ; bin_z ++ ) {
                            for (int bin_y = 0 ; bin_y < Nbins_y ; bin_y ++  ) {
                                hTrack_zy -> SetBinContent( bin_z , bin_y , adc_UV[bin_z][bin_y] );
                            }
                        }


                        // suffix - add (5)
                        // (suffix - add 3)
                    }

                    // (2-d) create images and save them
                    if (CreatingTrackImage) {
                        
                        // (2-d-1) in U/V/Y planes
                        std::cout << "creating images of " << Form("R%d S%d E%d T%d",run,subrun,event,track_id) << std::endl;
                        gSystem -> mkdir(Form("%s/r%d",images_path.Data(),run));
                        gSystem -> mkdir(Form("%s/r%d/s%d_e%d_t%d",images_path.Data(),run,subrun,event,track_id));
                        TCanvas * cZoomIn[3] , * cZoomOut[3] ;
                        for (int plane = 0 ; plane < 3 ; plane++){
                            cZoomOut[plane] = new TCanvas(Form("track ROI plane %d zoomout",plane));
                            hTrackROIzoomout[plane] -> Draw("colz");
                            plot -> Box((double)b[plane]._start_wire,(double)b[plane]._start_t,(double)b[plane]._end_wire,(double)b[plane]._end_t , 46 , 0 , 1);
                            gStyle->SetOptStat(0000);
                            cZoomOut[plane] -> SetGrid(1,1);
                            for (bin_x = 0 ; bin_x < hTrackROIzoomout[plane]->GetXaxis()->GetNbins() ; bin_x++) {
                                plot -> Line(hTrackROIzoomout[plane]->GetXaxis()->GetBinCenter(bin_x),0,hTrackROIzoomout[plane]->GetXaxis()->GetBinCenter(bin_x), hTrackROIzoomout[plane]->GetMaximum() , 1 , 2);
                            }
                            cZoomOut[plane] -> SaveAs(Form("%s/r%d/s%d_e%d_t%d/t%d_zoomout_plane%d.pdf",images_path.Data(),run,subrun,event,track_id,track_id,plane));
                            delete cZoomOut[plane];
                            
                            cZoomIn[plane] = new TCanvas(Form("track ROI plane %d zoomin",plane));
                            hTrackROI[plane] -> Draw("colz");
                            plot -> Box((double)b[plane]._start_wire,(double)b[plane]._start_t,(double)b[plane]._end_wire,(double)b[plane]._end_t , 46 , 0 , 1);
                            gStyle->SetOptStat(0000);
                            cZoomIn[plane] -> SaveAs(Form("%s/r%d/s%d_e%d_t%d/t%d_ROI_plane%d.pdf",images_path.Data(),run,subrun,event,track_id,track_id,plane));
                            delete cZoomIn[plane];
                        }
//                        // (2-d-2) in detector coordinates planes
//                        TCanvas * cxy = new TCanvas("track ROI x-y plane");
//                        hTrack_xy -> Draw("colz");
//                        plot -> Box(t.Vertex().x(),t.Vertex().y(),t.End().x(),t.End().y() , 46 , 0 , 1);
//                        gStyle->SetOptStat(0000);
//                        cxy -> SaveAs(Form("%s/r%d/s%d_e%d_t%d/t%d_xy.pdf",images_path.Data(),run,subrun,event,track_id,track_id));
//                        delete cxy;
//                        
//                        TCanvas * cyz = new TCanvas("track ROI y-z plane");
//                        hTrack_zy -> Draw("colz");
//                        plot -> Box(t.Vertex().z(),t.Vertex().y(),t.End().z(),t.End().y() , 46 , 0 , 1);
//                        gStyle->SetOptStat(0000);
//                        cyz -> SaveAs(Form("%s/r%d/s%d_e%d_t%d/t%d_yz.pdf",images_path.Data(),run,subrun,event,track_id,track_id));
//                        delete cyz;
                        
                    }
                    
                    
                
//                    if (CreateImagas) {
//                        for (int bin_x = 0 ; bin_x < Nbins_x ; bin_x ++ ) {
//                            float x = hTrack_xy -> GetXaxis() -> GetBinCenter( bin_x );
//                            
//                            for (int bin_y = 0 ; bin_y < Nbins_y ; bin_y ++  ) {
//                                float y = hTrack_xy -> GetYaxis() -> GetBinCenter( bin_y );
//                                
//                                for (int bin_z = 0 ; bin_z < Nbins_x ; bin_z ++ ) {
//                                    float z = hTrack_zy -> GetXaxis() -> GetBinCenter( bin_z );
//                                    
//                                    double xyz[3] = { x , y , z };
//                                    
//                                    // project on the collection plane
//                                    larutil::Point2D projection_U = geomH->Point_3Dto2D( xyz , 0 );
//                                    
//                                    // find the ADC value on the collection plane
//                                    auto wire_U = projection_U.w / geomH->WireToCm();
//                                    auto time_U = projection_U.t / geomH->TimeToCm() + time_shift;
//
//                                    
//                                    
//                                    for (auto const& wire : *ev_wire) {
//                                        
//                                        unsigned int ch = wire.Channel();
//                                        unsigned int c_wire = geoService->ChannelToWire(ch);
//                                        unsigned int c_plane = geoService->ChannelToPlane(ch);
//                                        
//                                        if (c_plane == 0 && c_wire == wire_U) {
//                                            
//                                            for (auto & iROI : wire.SignalROI().get_ranges()) {
//                                                
//                                                const int FirstTick = iROI.begin_index();
//                                                int c_time_tick = FirstTick;
//                                                
//                                                for (float ADC : iROI) {
//                                                    if ( c_time_tick == time_U ) {
//                                                        
//                                                        Printf("(%.2f,%.2f,%.2f) ADC on plane U (wire %d time %d): %f"
//                                                               ,x,y,z,c_wire,c_time_tick,ADC);
//                                                        
//                                                    }
//                                                    c_time_tick++;
//                                                }
//                                            }
//                                        }
//
//                                    }
//                                }
//                            }
//                        }
//
//                    }
                    
                    // (suffix - add 4)
                 }
            }
        }
        return true;
    }
    //..............................................................................
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::FirstSeedWireAndTime ( int bin_w, int bin_t ){
        for(auto w_t_bins : wire_and_time_bins){
            if (w_t_bins.at(0)==bin_w && w_t_bins.at(1)==bin_t){
                return false;
            }
        }
        return true;
    }
    
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::finalize() {
        
        Printf("Tracks filled with %lld entries",TracksTree -> GetEntries());
        if(_fout){
            TracksTree -> Write();
        }
        //        Printf("and the total number of good (accepted) tracks is %d",NgoodTracks);
        //        Printf("\n\ndon't forget, upload \n /Users/erezcohen/larlite/UserDev/LarLite/MyPackage/lists/selected_GBDTcandidates_score_95.csv \n to \n $uboone:/uboone/data/users/ecohen/BDTprotonCandidates/\n\n");
        delete TracksTree;
        out_csv_file.close();
        
        return true;
    }
    //..............................................................................
    
    
    
    
    
    
    
    // unused - delete by Sep-09,2016
    //    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    //    bool AnaPandoraNuTracks::inBDTcandidates(TVector3 vertex , TVector3 end, box b){
    //
    //        auto geomH = ::larutil::GeometryHelper::GetME();
    //
    //        for (int plane = 0 ; plane < 3 ; plane++){
    //
    //            larutil::Point2D start_point_plane2 = geomH->Point_3Dto2D(vertex.X() ,vertex.Y() ,vertex.Z() , plane);
    //            start_wire[plane] = start_point_plane2.w / geomH->WireToCm();
    //            start_t[plane]    = start_point_plane2.t / geomH->TimeToCm();
    //
    //            larutil::Point2D end_point_plane2 = geomH->Point_3Dto2D(end.X() , end.Y() , end.Z() , plane);
    //            end_wire[plane] = end_point_plane2.w / geomH->WireToCm();
    //            end_t[plane]    = end_point_plane2.t / geomH->TimeToCm();
    //
    //
    //            cout << "plane "<<plane<<", (" << start_wire[plane] << "," << start_t[plane]
    //            << ") => ("
    //            << end_wire[plane] << "," << end_t[plane] << ")" << std::endl;
    //        }
    //
    //
    //        //        if (    fabs( start_wire-b._start_wire )  < 2
    //        //            &&  fabs( end_wire-b._end_wire )      < 2 ) return true;
    //        //        else if( fabs( start_wire-b._end_wire )   < 2
    //        //            &&   fabs( end_wire-b._start_wire )   < 2 ) return true;
    //        //
    //        return false;
    //    }
    //
    //    //..............................................................................
    
    
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::LoadBDTCandidates(){
        
        ifstream fin(Form("%s/%s",roi_map_path.Data(),roi_map_name.Data()));
        
        if (debug > 0)
        std::cout << "loading data from file \n" << Form("%s/%s",roi_map_path.Data(),roi_map_name.Data()) << endl;
        // Read one line at a time.
        string line ;
        
        while ( getline(fin, line) ) {
            
            istringstream ss(line);
            //            ss >> run >> subrun >>  event >> track_id >>  start_wire >>  start_t >> end_wire >> end_t;
            //            box b( start_wire , start_t , end_wire , end_t);
            
            ss >> run >> subrun >>  event >> track_id
            >>  start_wire[0] >>  start_t[0] >> end_wire[0] >> end_t[0]
            >>  start_wire[1] >>  start_t[1] >> end_wire[1] >> end_t[1]
            >>  start_wire[2] >>  start_t[2] >> end_wire[2] >> end_t[2];
            
            box b_U( start_wire[0] , start_t[0] , end_wire[0] , end_t[0]);
            box b_V( start_wire[1] , start_t[1] , end_wire[1] , end_t[1]);
            box b_Y( start_wire[2] , start_t[2] , end_wire[2] , end_t[2]);
            box b[3] = {b_U,b_V,b_Y};
            for (int plane = 0 ; plane < 3 ; plane++){
                BDTcandidates[run][subrun][event][track_id].push_back(b[plane]);
            }
            //            BDTcandidates[run][subrun][event][track_id] = b;
            
        }
        
        // check
        if (debug > 3) {
            for(auto it : BDTcandidates) {
                std::cout << "run"  << it.first << "\n";
                for(auto inner_it : it.second ) {
                    std::cout  << "subrun " << inner_it.first;
                    for(auto inner_inner_it : inner_it.second ) {
                        std::cout  << ",event "       << inner_inner_it.first;
                        for(auto inner_inner_inner_it : inner_inner_it.second ) {
                            std::cout  << ",track_id "       << inner_inner_inner_it.first << "\n";
                            auto b = inner_inner_inner_it.second ;
                            
                            PrintBox(b[0]); PrintBox(b[1]); PrintBox(b[2]);
                            
                        }
                    }
                }
                std::cout << std::endl;
            }
        }
        
        // cleanup
        fin.close();
        Printf("loaded BDT candidates");
        return true;
    }
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::SetFrame( TH2F*h , TString xtit , TString ytit ){
        
        h -> GetXaxis() -> SetTitle(xtit);
        h -> GetXaxis() -> CenterTitle();
        h -> GetYaxis() -> SetTitle(ytit);
        h -> GetYaxis() -> CenterTitle();
        h -> GetYaxis() -> SetTitleOffset(1.3);
        
        return true;
        
    }
    
    //..............................................................................
    
    
}
#endif



// (suffix - add 1)
//                // straight track
//                vertex = t.Vertex();
//                end = t.End();
//                straight_track = end - vertex;
//                straight_track_length = straight_track.Mag();
//                // segmented track
//                segmented_track_length = 0;
//                for (size_t i = 1; i < t.NumberTrajectoryPoints() ; i++ ) {
//                    segmented_track_length += (t.LocationAtPoint(i) - t.LocationAtPoint(i-1)).Mag();
//                }
//                momentum = lar_tools->GetMomentumFromRange(straight_track_length);
//
//
//
//
//                // (1) filter fregmented tracks that that yielded proton candidates
//                // by looking at near by tracks and ask if they are in the same direction
//                for (auto const& other_track: *ev_track){
//                    float min_distace = 5; // [cm]
//                    float max_angle   = 10; // [deg.]
//
//                    if (other_track.ID() != track_id ) {
//                        if (    fabs((other_track.Vertex() - t.Vertex()).Mag()) < min_distace
//                            ||  fabs((other_track.End() - t.Vertex()).Mag())    < min_distace
//                            ||  fabs((other_track.Vertex() - t.End()).Mag())    < min_distace
//                            ||  fabs((other_track.End() - t.End()).Mag())       < min_distace      ){
//
//                            Angle_close_track.push_back(TMath::RadToDeg()*(t.End()-t.Vertex()).Angle(other_track.End()-other_track.Vertex()));
//                            float angle = Angle_close_track.back();
//
//                            if (fabs(angle) < max_angle || fabs(180.-angle) < max_angle ) {
//                                //                                cout << "angle between t " << t.ID() << " & " << other_track.ID() << " is " << angle << ", remove.." << endl;
//                                GoodTrack = false;
//                            }
//
//                            N_close_tracks++;
//                        }
//                    }
//                }
//                if (N_close_tracks >= 3) {
//                    //                    cout << "track " << t.ID() << " had too many neighbors (" << N_close_tracks << ")" << endl;
//                    GoodTrack = false;
//                }
//
//


// (suffix - add 2)

////                    // define a box of 4 wires x 20 time ticks around the corners of the track ROI box
////                    box lb_corner_box(b._start_wire - 7  , b._start_t - 10   , b._start_wire - 1     , b._start_t + 10);
////                    box lt_corner_box(b._start_wire - 7  , b._end_t - 10     , b._start_wire - 1     , b._end_t + 10  );
////                    box rb_corner_box(b._end_wire + 1    , b._start_t - 10   , b._end_wire + 7       , b._start_t + 10);
////                    box rt_corner_box(b._end_wire + 1    , b._end_t - 10     , b._end_wire + 7       , b._end_t + 10);
////                    SumADC_around_lb = SumADC_around_lb_in_track_direction = 0;
////                    SumADC_around_lt = SumADC_around_lt_in_track_direction = 0;
////                    SumADC_around_rb = SumADC_around_rb_in_track_direction = 0;
////                    SumADC_around_rt = SumADC_around_rt_in_track_direction = 0;
////
////
////                    if (DoPrint) {
////                        PrintBox(lb_corner_box);
////                        PrintBox(lt_corner_box);
////                        PrintBox(rt_corner_box);
////                        PrintBox(rb_corner_box);
////                    }

// (suffix - add 3)

//                        for (auto i = 0 ; i < t.NumberTrajectoryPoints() ; i++ ) {
//
//                            TVector3 position_at_point( t.LocationAtPoint(i) );
//                            // project on the collection plane
//                            larutil::Point2D projection_Y = geomH->Point_3Dto2D(position_at_point.X() ,
//                                                                                position_at_point.Y() ,
//                                                                                position_at_point.Z() , 2 );
//                            // find the ADC value on the collection plane
//                            auto wire_Y = projection_Y.w / geomH->WireToCm();
//                            auto time_Y = projection_Y.t / geomH->TimeToCm() + time_shift;
//
//                            int   bin_w = wire_Y - b[2]._start_wire + 20;
//                            int   bin_t = time_Y - b[2]._start_t + 40;
//                            SHOW3( bin_w , bin_t , hTrackROIzoomout[2] -> GetBinContent( bin_w, bin_t ) );
//
//                            int bin_w_Y = hTrackROIzoomout[2] -> GetXaxis()->FindBin( wire_Y );
//                            int bin_t_Y = hTrackROIzoomout[2] -> GetYaxis()->FindBin( time_Y + FirstTickZoomout );
//                            SHOW3( bin_w_Y , bin_t_Y , hTrackROIzoomout[2] -> GetBinContent( bin_w_Y, bin_t_Y ) );
//
//                            float ADC_Y = hTrackROIzoomout[2] -> GetBinContent( bin_w, bin_t );
//
//                            // plugh this ADC value into the right bin in the det. coor. histograms
//                            bin_x = hTrack_xy->GetXaxis() -> FindBin(position_at_point.X());
//                            bin_y = hTrack_xy->GetXaxis() -> FindBin(position_at_point.Y());
//                            hTrack_xy -> SetBinContent( bin_x , bin_y , ADC_Y );
//
//                            bin_y = hTrack_zy->GetXaxis() -> FindBin(position_at_point.Y());
//                            bin_z = hTrack_zy->GetYaxis() -> FindBin(position_at_point.Z());
//                            hTrack_zy -> SetBinContent( bin_y , bin_z , ADC_Y );
//
//                            if (debug>2) {
//                                Printf("position_at_point: (%.2f,%.2f,%.2f), projection on Y plane: (w=%f,t=%f) ",
//                                       position_at_point.X() ,
//                                       position_at_point.Y() ,
//                                       position_at_point.Z() ,
//                                       wire_Y, time_Y);
//                                SHOW3(bin_w,bin_t,ADC_Y);
//                                SHOW3(bin_x,bin_y,bin_z);
//                                PrintLine();
//                            }
//
//                        }


// (suffix - add 4)
//                    }
//
//
////                            if (calculate_adc_in_corners) {
////                                // accumulate the ADC signal around the left bottom corner of the track ROI box
////                                if ( lb_corner_box._start_wire <= detWire && detWire <= lb_corner_box._end_wire ) {
////                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
////                                        const int FirstTick = iROI.begin_index();
////                                        time_tick = FirstTick;
////                                        for (float ADC : iROI) {
////                                            if ( lb_corner_box._start_t <= time_tick && time_tick <= lb_corner_box._end_t ) {
////
////                                                float t_slope = (b._end_t-b._start_t)/(float)(b._end_wire-b._start_wire);
////                                                float t_slope_tick = b._start_t + t_slope * ((float)detWire-b._start_wire ) ;
////
////                                                SumADC_around_lb += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                if (DoPrint) cout << "LB corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;
////
////                                                if (    fabs( time_tick - t_slope_tick ) < time_tick_max_distance ) {
////                                                    SumADC_around_lb_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                    if (DoPrint) cout << "filling also SumADC_around_lb_in_track_direction \n";
////                                                }
////                                            }
////                                            time_tick++;
////                                        }
////                                    }
////                                    if (SumADC_around_lb_in_track_direction) {
////                                        ADC_ratio_around_lb = SumADC_around_lb / SumADC_around_lb_in_track_direction;
////                                    }
////                                }
////
////                                // accumulate the ADC signal around the left top corner of the track ROI box
////                                if ( lt_corner_box._start_wire <= detWire && detWire <= lt_corner_box._end_wire ) {
////                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
////                                        const int FirstTick = iROI.begin_index();
////                                        time_tick = FirstTick;
////                                        for (float ADC : iROI) {
////                                            if ( lt_corner_box._start_t <= time_tick && time_tick <= lt_corner_box._end_t ) {
////
////                                                float t_slope = (b._end_t-b._start_t)/(float)(b._start_wire-b._end_wire);
////                                                float t_slope_tick = b._end_t + t_slope * ((float)detWire-b._start_wire) ;
////
////                                                SumADC_around_lt += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////
////                                                if (DoPrint) cout << "LT corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;
////
////                                                if (    fabs( time_tick - t_slope_tick ) < time_tick_max_distance ) {
////                                                    SumADC_around_lt_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                    if (DoPrint) cout << "filling also SumADC_around_lt_in_track_direction \n";
////
////                                                }
////                                            }
////                                            time_tick++;
////                                        }
////                                    }
////                                    if (SumADC_around_lt_in_track_direction) {
////                                        ADC_ratio_around_lt = SumADC_around_lt / SumADC_around_lt_in_track_direction;
////                                    }
////                                }
////
////
////
////                                // accumulate the ADC signal around the right bottom corner of the track ROI box
////                                if ( rb_corner_box._start_wire <= detWire && detWire <= rb_corner_box._end_wire ) {
////                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
////                                        const int FirstTick = iROI.begin_index();
////                                        time_tick = FirstTick;
////                                        for (float ADC : iROI) {
////                                            if ( rb_corner_box._start_t <= time_tick && time_tick <= rb_corner_box._end_t ) {
////
////                                                float t_slope = (b._end_t-b._start_t)/(float)(b._end_wire-b._start_wire);
////                                                float t_anti_slope_tick = b._end_t + t_slope * (detWire-b._end_wire) ;
////
////                                                SumADC_around_rb += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                if (DoPrint) cout << "RB corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;
////
////                                                if (    fabs( time_tick - t_anti_slope_tick ) < time_tick_max_distance ) {
////                                                    SumADC_around_rb_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                    if (DoPrint) cout << "filling also SumADC_around_rb_in_track_direction \n";
////
////                                                }
////                                            }
////                                            time_tick++;
////                                        }
////                                    }
////                                    if (SumADC_around_rb_in_track_direction) {
////                                        ADC_ratio_around_rb = SumADC_around_rb / SumADC_around_rb_in_track_direction;
////                                    }
////                                }
////
////
////
////                                // accumulate the ADC signal around the right top corner of the track ROI box
////                                if ( rt_corner_box._start_wire <= detWire && detWire <= rt_corner_box._end_wire ) {
////                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
////                                        const int FirstTick = iROI.begin_index();
////                                        time_tick = FirstTick;
////                                        for (float ADC : iROI) {
////                                            if ( rt_corner_box._start_t <= time_tick && time_tick <= rt_corner_box._end_t ) {
////
////                                                float t_slope = b.diag_slope;
////                                                float t_slope_tick = rt_corner_box._start_t + t_slope * (detWire-rt_corner_box._start_wire ) ;
////
////                                                SumADC_around_rt += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                if (DoPrint) cout << "RT corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;
////
////                                                if (    fabs( time_tick - t_slope_tick ) < time_tick_max_distance ) {
////                                                    SumADC_around_rt_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
////                                                    if (DoPrint) cout << "filling also SumADC_around_rt_in_track_direction \n";
////
////                                                }
////                                            }
////                                            time_tick++;
////                                        }
////                                    }
////                                    if (SumADC_around_rt_in_track_direction) {
////                                        ADC_ratio_around_rt = SumADC_around_rt / SumADC_around_rt_in_track_direction;
////                                    }
////                                }
//                            }
//
//                        }
//                    }
////                    if (DoPrint) {
////
////                        cout
////                        << "accumulated ADC around lt " << SumADC_around_lt
////                        << "\naccumulated ADC around lt in track direction " << SumADC_around_lt_in_track_direction
////
////                        << "\naccumulated ADC around lb " << SumADC_around_lb
////                        << "\naccumulated ADC around lb in track direction " << SumADC_around_lb_in_track_direction
////
////                        << "\naccumulated ADC around rt " << SumADC_around_rt
////                        << "\naccumulated ADC around rt in track direction " << SumADC_around_rt_in_track_direction
////
////                        << "\naccumulated ADC around rb " << SumADC_around_rb
////                        << "\naccumulated ADC around rb in track direction " << SumADC_around_rb_in_track_direction << endl;
////
////
////                    }
////                    if ((SumADC_around_rt>100 && ADC_ratio_around_rt<0.2) ||
////                        (SumADC_around_rb>100 && ADC_ratio_around_rb<0.2) ||
////                        (SumADC_around_lt>100 && ADC_ratio_around_lt<0.2) ||
////                        (SumADC_around_lb>100 && ADC_ratio_around_lb<0.2) ){
////                        GoodTrack = false;
////                    }
//                }
//
//                    }

// suffix - add (5)

//                        for (int bin_x = 0 ; bin_x < Nbins_x ; bin_x ++ ) {
//                            for (int bin_y = 0 ; bin_y < Nbins_y ; bin_y ++  ) {
//                                for (int bin_z = 0 ; bin_z < Nbins_z ; bin_z ++  ) {
//
//                                    float x = hTrack_xy -> GetXaxis() -> GetBinCenter( bin_x );
//                                    float y = hTrack_xy -> GetYaxis() -> GetBinCenter( bin_y );
//                                    float z = hTrack_zy -> GetXaxis() -> GetBinCenter( bin_z );
//
//                                    // project on the collection plane
//                                    larutil::Point2D projection_Y = geomH->Point_3Dto2D( x , y , z, 2 );
//
//                                    // find the ADC value on the collection plane
//                                    auto wire_Y = projection_Y.w / geomH->WireToCm();
//                                    auto time_Y = projection_Y.t / geomH->TimeToCm() + time_shift;
//
//                                    int   bin_w = wire_Y - b[2]._start_wire + 20;
//                                    int   bin_t = time_Y - b[2]._start_t + 40;
//                                    float ADC_Y = hTrackROIzoomout[2] -> GetBinContent( bin_w, bin_t );
//
//                                    // plugh this ADC value into the right bin in the det. coor. histograms
//                                    hTrack_xy -> SetBinContent( bin_x , bin_y , hTrack_xy -> GetBinContent( bin_x , bin_y ) + ADC_Y );
//
//                                    hTrack_zy -> SetBinContent( bin_z , bin_y , hTrack_zy -> GetBinContent( bin_z , bin_y ) + ADC_Y );
//
//                                    if (debug>2 && (Xmin < x && x < Xmax && Ymin < y && y < Ymax && Zmin < z && z < Zmax)) {
//                                        SHOW3(Xmin,Ymin,Zmin);
//                                        SHOW3(x,y,z);
//                                        SHOW3(Xmax,Ymax,Zmax);
//                                        SHOW3(Nbins_x,Nbins_y,Nbins_z);
//                                        Printf("position_at_point: (%.2f,%.2f,%.2f), projection on Y plane: (w=%f,t=%f) ",
//                                               x , y , z  , wire_Y, time_Y);
//                                        SHOW3(bin_w,bin_t,ADC_Y);
//                                        SHOW3(bin_x,bin_y,bin_z);
//                                        SHOW3( bin_x , bin_y , hTrack_xy -> GetBinContent( bin_x , bin_y ));
//
//                                        PrintLine();
//                                    }
//
//                                }
//                            }
//                        }
//                        for (float x = Xmin - 5 ; x < Xmax + 5 ; x += 1 ) {
//                            for (float y = Ymin - 5 ; y < Ymax + 5 ; y += 1 ) {
//                                for (float z = Zmin - 5 ; z < Zmax + 5 ; z += 1 ) {
//                                    bin_x = hTrack_xy->GetXaxis() -> FindBin(x);
//                                    bin_y = hTrack_xy->GetYaxis() -> FindBin(y);
//                                    bin_z = hTrack_zy->GetXaxis() -> FindBin(z);
//                                    SHOW3( bin_x , bin_y , hTrack_xy -> GetBinContent( bin_x , bin_y ));
//
//                                }
//                            }
//                        }
