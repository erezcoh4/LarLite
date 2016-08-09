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
    bool AnaPandoraNuTracks::initialize() {
        
        // change this path in order to generate the images elsewhere
//        images_path = "/Users/erezcohen/Desktop/uBoone/GBDTprotonCandidates/images/JustMCtraining"; // my mac
        images_path = "/uboone/data/users/ecohen/GBDTprotons/images/JustMCtraining"; // uboone servers

        
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
        
        LoadBDTCandidates( true );
        
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
        bool DoPrint = false;
        bool CreateImagas = false;
        bool calculate_adc_in_corners = false;
        
        auto ev_track = storage -> get_data<event_track> ("pandoraNu");
        auto ev_wire  = storage -> get_data<event_wire> ("caldata");
        
        
        if(ev_track){
            
            run     = ev_track->run();
            subrun  = ev_track->subrun();
            event   = ev_track->event_id();
            
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
                    //                    std::cout << "track " <<  track_id << " not in our list..." << std::endl;
                    continue;
                }
                
                // Grab box
                auto const& b = (*track_id_iter).second;
                
                
                //
                //
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
                if (DoPrint) {
                    PrintLine();
                    std::cout << "run " << run << ", subrun " << subrun << ", event " << event << ", track id " << track_id << std::endl;
                    for (int plane = 0 ; plane < 3 ; plane++){
                        PrintBox(b[plane]);
                    }
                }
                
                
                
                
                
                
                
                // (2) wire data....
                if (ev_wire){
                    
                    
                    if (CreateImagas) {
                        for (int plane = 0 ; plane < 3; plane++) {
                            
                            TString hName = Form("r%d_s%d_e%d_t%d_plane%d"
                                                 ,run,subrun,event,track_id,plane);
                            
                            TString hTitle = Form("r%d s%d e%d t%d window in plane %d (%d,%.1f)=>(%d,%.1f)"
                                                  ,run,subrun,event,track_id,plane
                                                  ,b[plane]._start_wire,b[plane]._start_t,b[plane]._end_wire,b[plane]._end_t);
                            
                            int Nbins_w = b[plane]._end_wire - b[plane]._start_wire + 11;
                            int Nbins_t = (int)(b[plane]._end_t - b[plane]._start_t) + 21;
                            
                            hTrackROI[plane] = new TH2F(hName , hTitle
                                                        , Nbins_w  , b[plane]._start_wire - 5 , b[plane]._end_wire + 5
                                                        , Nbins_t  , b[plane]._start_t - 10 , b[plane]._end_t + 10 );
                            hTrackROI[plane] -> GetXaxis() -> SetTitle("wire number");
                            hTrackROI[plane] -> GetXaxis() -> CenterTitle();
                            hTrackROI[plane] -> GetYaxis() -> SetTitle("time tick");
                            hTrackROI[plane] -> GetYaxis() -> CenterTitle();
                            hTrackROIzoomout[plane] = new TH2F(Form("%s_zoomout",hName.Data()) ,Form("%s zoomout",hName.Data())
                                                               , Nbins_w + 40  , b[plane]._start_wire-20 , b[plane]._end_wire+20
                                                               , Nbins_t + 60  , b[plane]._start_t-30 , b[plane]._end_t+30);
                            hTrackROIzoomout[plane] -> GetXaxis() -> SetTitle("wire number");
                            hTrackROIzoomout[plane] -> GetXaxis() -> CenterTitle();
                            hTrackROIzoomout[plane] -> GetYaxis() -> SetTitle("time tick");
                            hTrackROIzoomout[plane] -> GetYaxis() -> CenterTitle();
                            
                        }
                    }
                    
                    
                    // services and helpers
                    
                    auto geoService = ::larutil::Geometry::GetME();
                    auto detProp = ::larutil::DetectorProperties::GetME();
                    auto geomH = ::larutil::GeometryHelper::GetME();
                    
                    //
                    ////
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
                    ////
                    //
                    for (auto const& wire : *ev_wire) {
                        
                        unsigned int ch = wire.Channel();
                        unsigned int detWire = geoService->ChannelToWire(ch);
                        unsigned int plane = geoService->ChannelToPlane(ch);
                        
                        //if(DoPrint) cout << "ch " << ch << ", wire " << detWire << ", plane " << plane <<  endl;
                        
                        for (int plane = 0 ; plane < 3 ; plane++){
                            
                            if (CreateImagas) {
                                // accumulate the ADC signal around the left bottom corner of the track ROI box
                                if ( b[plane]._start_wire - 20 <= detWire && detWire <= b[plane]._end_wire + 20 ) {
                                    for (auto & iROI : wire.SignalROI().get_ranges()) {
                                        const int FirstTick = iROI.begin_index();
                                        time_tick = FirstTick;
                                        for (float ADC : iROI) {
                                            if ( b[plane]._start_t - 30 <= time_tick && time_tick <= b[plane]._end_t + 30 ) {
                                                hTrackROIzoomout[plane] -> SetBinContent( detWire - b[plane]._start_wire + 20
                                                                                         , time_tick - b[plane]._start_t + 30 , ADC );
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
                                                hTrackROI[plane] -> SetBinContent( detWire - b[plane]._start_wire + 5
                                                                                  , time_tick - b[plane]._start_t + 10 , ADC );
                                            }
                                            time_tick++;
                                        }
                                    }
                                }
                            }
                        }
                    }
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
                    if (CreatingTrackImage) {
                        std::cout << "creating images of " << Form("r%d_s%d_e%d_t%d.pdf",run,subrun,event,track_id) << std::endl;
                        gSystem -> mkdir(Form("%s/r%d",images_path.Data(),run));
                        gSystem -> mkdir(Form("%s/r%d/s%d_e%d_t%d",images_path.Data(),run,subrun,event,track_id));
                        TCanvas * cZoomIn[3] , * cZoomOut[3];
                        for (int plane = 0 ; plane < 3 ; plane++){
                            cZoomOut[plane] = new TCanvas(Form("track ROI plane %d zoomout",plane));
                            hTrackROIzoomout[plane] -> Draw("colz");
                            plot -> Box((double)b[plane]._start_wire,(double)b[plane]._start_t,(double)b[plane]._end_wire,(double)b[plane]._end_t , 46 , 0 , 1);
                            cZoomOut[plane] -> SaveAs(Form("%s/r%d/s%d_e%d_t%d/t%d_zoomout_plane%d.pdf",images_path.Data(),run,subrun,event,track_id,track_id,plane));
                            cZoomIn[plane] = new TCanvas(Form("track ROI plane %d zoomin",plane));
                            hTrackROI[plane] -> Draw("colz");
                            plot -> Box((double)b[plane]._start_wire,(double)b[plane]._start_t,(double)b[plane]._end_wire,(double)b[plane]._end_t , 46 , 0 , 1);
                            cZoomIn[plane] -> SaveAs(Form("%s/r%d/s%d_e%d_t%d/t%d_ROI_plane%d.pdf",images_path.Data(),run,subrun,event,track_id,track_id,plane));
                            delete cZoomOut[plane];
                            delete cZoomIn[plane];
                        }
                    }
                    //
                    //
                    //                TracksTree -> Fill();
                    //
                    //                if(GoodTrack){
                    //                    NgoodTracks++;
                    //                    out_csv_file
                    //                    << run          << ", "
                    //                    << subrun       << ", "
                    //                    << event        << ", "
                    //                    << track_id     << ", "
                    //                    << b._start_wire<< ", "
                    //                    << b._start_t   << ", "
                    //                    << b._end_wire   << ", "
                    //                    << b._end_t     << endl;
                    //                }
                }
            }
        }
        return true;
    }
    //..............................................................................
    
    
    
    
    
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::finalize() {
        
        Printf("Tracks filled with %lld entries",TracksTree -> GetEntries());
        if(_fout){
            TracksTree -> Write();
        }
        Printf("and the total number of good (accepted) tracks is %d",NgoodTracks);
        Printf("\n\ndon't forget, upload \n /Users/erezcohen/larlite/UserDev/LarLite/MyPackage/lists/selected_GBDTcandidates_score_95.csv \n to \n $uboone:/uboone/data/users/ecohen/BDTprotonCandidates/\n\n");
        delete TracksTree;
        out_csv_file.close();
        
        return true;
    }
    //..............................................................................
    
    
    
    
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::inBDTcandidates(TVector3 vertex , TVector3 end, box b){
        
        auto geomH = ::larutil::GeometryHelper::GetME();
        
        for (int plane = 0 ; plane < 3 ; plane++){
            
            larutil::Point2D start_point_plane2 = geomH->Point_3Dto2D(vertex.X() ,vertex.Y() ,vertex.Z() , plane);
            start_wire[plane] = start_point_plane2.w / geomH->WireToCm();
            start_t[plane]    = start_point_plane2.t / geomH->TimeToCm();
            
            larutil::Point2D end_point_plane2 = geomH->Point_3Dto2D(end.X() , end.Y() , end.Z() , plane);
            end_wire[plane] = end_point_plane2.w / geomH->WireToCm();
            end_t[plane]    = end_point_plane2.t / geomH->TimeToCm();
            
            
            cout << "plane "<<plane<<", (" << start_wire[plane] << "," << start_t[plane]
            << ") => ("
            << end_wire[plane] << "," << end_t[plane] << ")" << std::endl;
        }
        
        
        //        if (    fabs( start_wire-b._start_wire )  < 2
        //            &&  fabs( end_wire-b._end_wire )      < 2 ) return true;
        //        else if( fabs( start_wire-b._end_wire )   < 2
        //            &&   fabs( end_wire-b._start_wire )   < 2 ) return true;
        //
        return false;
    }
    
    //..............................................................................
    
    
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::LoadBDTCandidates(bool DoPrint){
        
        //        ifstream fin("/Users/erezcohen/larlite/UserDev/LarLite/MyPackage/lists/passing_score_95_4874_tracks.csv");
//        ifstream fin("/Users/erezcohen/Desktop/uBoone/AnalysisTreesAna/PassedGBDTFiles/extBNB_AnalysisTrees/passedGBDT_extBNB_AnalysisTrees_score_0.95.csv"); // my mac
        ifstream fin("/uboone/app/users/ecohen/AnalysisTreesAna/PassedGBDTFiles/passedGBDT_extBNB_AnalysisTrees_JustMCtraining_score_0.95.csv"); // uboone

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
        if (DoPrint) {
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
    //..............................................................................
    
    
}
#endif







