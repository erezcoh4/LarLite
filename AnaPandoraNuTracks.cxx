#ifndef LARLITE_ANAPANDORANUTRACKS_CXX
#define LARLITE_ANAPANDORANUTRACKS_CXX

#include "AnaPandoraNuTracks.h"
#include <sstream>
#include "LArUtil/GeometryHelper.h"

namespace larlite {
    
    
    
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
        
        out_csv_file = ofstream("/Users/erezcohen/larlite/UserDev/LarLite/MyPackage/lists/selected_GBDTcandidates_score_95.csv");
        out_csv_file << "run, subrun, event, track-id, start wire, start time-tick, end wire, end time-tick " << endl;
        
        LoadBDTCandidates( false );
        
        lar_tools = new MyLArTools();
        
        NgoodTracks = 0;
        

        
        return true;
    }
    //..............................................................................
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    bool AnaPandoraNuTracks::analyze(storage_manager* storage) {
        
        bool DoPrint = false;
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
                if(!Angle_close_track.empty()) Angle_close_track.clear();
                track_id = t.ID();
                
                
                // Search event
                auto track_id_iter = track_id_map.find(track_id);
                if(track_id_iter == track_id_map.end()) {
                    //                    std::cout << "track " <<  track_id << " not in our list..." << std::endl;
                    continue;
                }
                //                std::cout << " run " << run << " subrun " << subrun << " event " << event  << ": track " <<  track_id << "..." << std::endl;

                // Grab box
                auto const& b = (*track_id_iter).second;
                
                

                
                // straight track
                vertex = t.Vertex();
                end = t.End();
                straight_track = end - vertex;
                straight_track_length = straight_track.Mag();
                // segmented track
                segmented_track_length = 0;
                for (size_t i = 1; i < t.NumberTrajectoryPoints() ; i++ ) {
                    segmented_track_length += (t.LocationAtPoint(i) - t.LocationAtPoint(i-1)).Mag();
                }
                momentum = lar_tools->GetMomentumFromRange(straight_track_length);
                
                
                
                
                // (1) filter fregmented tracks that that yielded proton candidates
                // by looking at near by tracks and ask if they are in the same direction
                for (auto const& other_track: *ev_track){
                    float min_distace = 5; // [cm]
                    float max_angle   = 10; // [deg.]
                    
                    if (other_track.ID() != track_id ) {
                        if (    fabs((other_track.Vertex() - t.Vertex()).Mag()) < min_distace
                            ||  fabs((other_track.End() - t.Vertex()).Mag())    < min_distace
                            ||  fabs((other_track.Vertex() - t.End()).Mag())    < min_distace
                            ||  fabs((other_track.End() - t.End()).Mag())       < min_distace      ){
                            
                            Angle_close_track.push_back(TMath::RadToDeg()*(t.End()-t.Vertex()).Angle(other_track.End()-other_track.Vertex()));
                            float angle = Angle_close_track.back();
                            
                            if (fabs(angle) < max_angle || fabs(180.-angle) < max_angle ) {
                                //                                cout << "angle between t " << t.ID() << " & " << other_track.ID() << " is " << angle << ", remove.." << endl;
                                GoodTrack = false;
                            }
                            
                            N_close_tracks++;
                        }
                    }
                }
                if (N_close_tracks >= 3) {
                    //                    cout << "track " << t.ID() << " had too many neighbors (" << N_close_tracks << ")" << endl;
                    GoodTrack = false;
                }

//                if (run == 5906 && subrun == 124 && event == 6212)
//                    DoPrint = true;
                
                if (DoPrint) {
                    PrintLine();
                    cout << "run " << run << ", subrun " << subrun << ", event " << event << ", track id " << track_id << endl;
                    PrintBox(b);
                }
                
                
                
                
                
                
                
                // (2) wire data....
                if (ev_wire){
                    
                    
                    // services and helpers
                    
                    auto geoService = ::larutil::Geometry::GetME();
                    auto detProp = ::larutil::DetectorProperties::GetME();
                    auto geomH = ::larutil::GeometryHelper::GetME();
                    
                    
                    
                    // define a box of 4 wires x 20 time ticks around the corners of the track ROI box
                    
                    box lb_corner_box(b._start_wire - 7  , b._start_t - 10   , b._start_wire - 1     , b._start_t + 10);
                    box lt_corner_box(b._start_wire - 7  , b._end_t - 10     , b._start_wire - 1     , b._end_t + 10  );
                    box rb_corner_box(b._end_wire + 1    , b._start_t - 10   , b._end_wire + 7       , b._start_t + 10);
                    box rt_corner_box(b._end_wire + 1    , b._end_t - 10     , b._end_wire + 7       , b._end_t + 10);
                    SumADC_around_lb = SumADC_around_lb_in_track_direction = 0;
                    SumADC_around_lt = SumADC_around_lt_in_track_direction = 0;
                    SumADC_around_rb = SumADC_around_rb_in_track_direction = 0;
                    SumADC_around_rt = SumADC_around_rt_in_track_direction = 0;
                    
                    
                    if (DoPrint) {
                        PrintBox(lb_corner_box);
                        PrintBox(lt_corner_box);
                        PrintBox(rt_corner_box);
                        PrintBox(rb_corner_box);
                    }
                    
                
                    for (auto const& wire : *ev_wire) {
                        
                        unsigned int ch = wire.Channel();
                        unsigned int detWire = geoService->ChannelToWire(ch);
                        unsigned int plane = geoService->ChannelToPlane(ch);

                        //if(DoPrint) cout << "ch " << ch << ", wire " << detWire << ", plane " << plane <<  endl;
                        
                        if ( plane == 2 ) {
                            
                            
                            // accumulate the ADC signal around the left bottom corner of the track ROI box
                            if ( lb_corner_box._start_wire <= detWire && detWire <= lb_corner_box._end_wire ) {
                                for (auto & iROI : wire.SignalROI().get_ranges()) {
                                    const int FirstTick = iROI.begin_index();
                                    time_tick = FirstTick;
                                    for (float ADC : iROI) {
                                        if ( lb_corner_box._start_t <= time_tick && time_tick <= lb_corner_box._end_t ) {
                                            
                                            float t_slope = (b._end_t-b._start_t)/(float)(b._end_wire-b._start_wire);
                                            float t_slope_tick = b._start_t + t_slope * ((float)detWire-b._start_wire ) ;
                                            
                                            SumADC_around_lb += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                            if (DoPrint) cout << "LB corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;

                                            if (    fabs( time_tick - t_slope_tick ) < time_tick_max_distance ) {
                                                SumADC_around_lb_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                                if (DoPrint) cout << "filling also SumADC_around_lb_in_track_direction \n";
                                            }
                                        }
                                        time_tick++;
                                    }
                                }
                                if (SumADC_around_lb_in_track_direction) {
                                    ADC_ratio_around_lb = SumADC_around_lb / SumADC_around_lb_in_track_direction;
                                }
                            }
                            
                            // accumulate the ADC signal around the left top corner of the track ROI box
                            if ( lt_corner_box._start_wire <= detWire && detWire <= lt_corner_box._end_wire ) {
                                for (auto & iROI : wire.SignalROI().get_ranges()) {
                                    const int FirstTick = iROI.begin_index();
                                    time_tick = FirstTick;
                                    for (float ADC : iROI) {
                                        if ( lt_corner_box._start_t <= time_tick && time_tick <= lt_corner_box._end_t ) {
                                            
                                            float t_slope = (b._end_t-b._start_t)/(float)(b._start_wire-b._end_wire);
                                            float t_slope_tick = b._end_t + t_slope * ((float)detWire-b._start_wire) ;

                                            SumADC_around_lt += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                            
                                            if (DoPrint) cout << "LT corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;
                                            
                                            if (    fabs( time_tick - t_slope_tick ) < time_tick_max_distance ) {
                                                SumADC_around_lt_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                                if (DoPrint) cout << "filling also SumADC_around_lt_in_track_direction \n";

                                            }
                                        }
                                        time_tick++;
                                    }
                                }
                                if (SumADC_around_lt_in_track_direction) {
                                    ADC_ratio_around_lt = SumADC_around_lt / SumADC_around_lt_in_track_direction;
                                }
                            }
                            
                            
                            
                            // accumulate the ADC signal around the right bottom corner of the track ROI box
                            if ( rb_corner_box._start_wire <= detWire && detWire <= rb_corner_box._end_wire ) {
                                for (auto & iROI : wire.SignalROI().get_ranges()) {
                                    const int FirstTick = iROI.begin_index();
                                    time_tick = FirstTick;
                                    for (float ADC : iROI) {
                                        if ( rb_corner_box._start_t <= time_tick && time_tick <= rb_corner_box._end_t ) {
                                            
                                            float t_slope = (b._end_t-b._start_t)/(float)(b._end_wire-b._start_wire);
                                            float t_anti_slope_tick = b._end_t + t_slope * (detWire-b._end_wire) ;
                                            
                                            SumADC_around_rb += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                            if (DoPrint) cout << "RB corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;

                                            if (    fabs( time_tick - t_anti_slope_tick ) < time_tick_max_distance ) {
                                                SumADC_around_rb_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                                if (DoPrint) cout << "filling also SumADC_around_rb_in_track_direction \n";

                                            }
                                        }
                                        time_tick++;
                                    }
                                }
                                if (SumADC_around_rb_in_track_direction) {
                                    ADC_ratio_around_rb = SumADC_around_rb / SumADC_around_rb_in_track_direction;
                                }
                            }
                            
                          
                            
                            // accumulate the ADC signal around the right top corner of the track ROI box
                            if ( rt_corner_box._start_wire <= detWire && detWire <= rt_corner_box._end_wire ) {
                                for (auto & iROI : wire.SignalROI().get_ranges()) {
                                    const int FirstTick = iROI.begin_index();
                                    time_tick = FirstTick;
                                    for (float ADC : iROI) {
                                        if ( rt_corner_box._start_t <= time_tick && time_tick <= rt_corner_box._end_t ) {
                                            
                                            float t_slope = b.diag_slope;
                                            float t_slope_tick = rt_corner_box._start_t + t_slope * (detWire-rt_corner_box._start_wire ) ;
                                            
                                            SumADC_around_rt += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                            if (DoPrint) cout << "RT corner: w-" << detWire << ", t-" << time_tick  << "ADC = " << fabs(ADC) << endl;

                                            if (    fabs( time_tick - t_slope_tick ) < time_tick_max_distance ) {
                                                SumADC_around_rt_in_track_direction += (fabs(ADC)>ADC_threshold) ? fabs(ADC) : 0;
                                                if (DoPrint) cout << "filling also SumADC_around_rt_in_track_direction \n";

                                            }
                                        }
                                        time_tick++;
                                    }
                                }
                                if (SumADC_around_rt_in_track_direction) {
                                    ADC_ratio_around_rt = SumADC_around_rt / SumADC_around_rt_in_track_direction;
                                }
                            }
                            
                            
                            
                            
                            
                            
                            
                            
                            
                        }
                    }
                    if (DoPrint) {

                        cout
                        << "accumulated ADC around lt " << SumADC_around_lt
                        << "\naccumulated ADC around lt in track direction " << SumADC_around_lt_in_track_direction
                        
                        << "\naccumulated ADC around lb " << SumADC_around_lb
                        << "\naccumulated ADC around lb in track direction " << SumADC_around_lb_in_track_direction

                        << "\naccumulated ADC around rt " << SumADC_around_rt
                        << "\naccumulated ADC around rt in track direction " << SumADC_around_rt_in_track_direction
                        
                        << "\naccumulated ADC around rb " << SumADC_around_rb
                        << "\naccumulated ADC around rb in track direction " << SumADC_around_rb_in_track_direction << endl;

                    
                    }
                    if ((SumADC_around_rt>100 && ADC_ratio_around_rt<0.2) ||
                        (SumADC_around_rb>100 && ADC_ratio_around_rb<0.2) ||
                        (SumADC_around_lt>100 && ADC_ratio_around_lt<0.2) ||
                        (SumADC_around_lb>100 && ADC_ratio_around_lb<0.2) ){
                        GoodTrack = false;
                    }
                }
                
                
                
                
                
                

                
                
                
                TracksTree -> Fill();
                
                if(GoodTrack){
                    NgoodTracks++;
                    out_csv_file
                    << run          << ", "
                    << subrun       << ", "
                    << event        << ", "
                    << track_id     << ", "
                    << b._start_wire<< ", "
                    << b._start_t   << ", "
                    << b._end_wire   << ", "
                    << b._end_t     << endl;
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
        
        larutil::Point2D start_point_plane2 = geomH->Point_3Dto2D(vertex.X() ,vertex.Y() ,vertex.Z() , 2);
        start_wire = start_point_plane2.w / geomH->WireToCm();
        start_t    = start_point_plane2.t / geomH->TimeToCm();
        
        larutil::Point2D end_point_plane2 = geomH->Point_3Dto2D(end.X() , end.Y() , end.Z() , 2);
        end_wire = end_point_plane2.w / geomH->WireToCm();
        end_t    = end_point_plane2.t / geomH->TimeToCm();
        
        
        cout << " (" << start_wire << "," << start_t
        << ") => ("
        << end_wire << "," << end_t << ")" << std::endl;
        
        
        
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
     
        ifstream fin("/Users/erezcohen/larlite/UserDev/LarLite/MyPackage/lists/passing_score_95_4874_tracks.csv");
         
        // Read one line at a time.
        string line ;

        while ( getline(fin, line) ) {
            
            istringstream ss(line);
            ss >> run >> subrun >>  event >> track_id >>  start_wire >>  start_t >> end_wire >> end_t;
            box b( start_wire , start_t , end_wire , end_t);
            BDTcandidates[run][subrun][event][track_id] = b;

        }
        
        // check
        if (DoPrint) {
            for(auto it : BDTcandidates) {
                cout << "run "  << it.first;
                for(auto inner_it : it.second ) {
                    cout  << ",subrun " << inner_it.first;
                    for(auto inner_inner_it : inner_it.second ) {
                        cout  << ",event "       << inner_inner_it.first;
                        for(auto inner_inner_inner_it : inner_inner_it.second ) {
                            cout  << ",track_id "       << inner_inner_inner_it.first;
                            auto b = inner_inner_inner_it.second ;
                            cout
                            << " box (" << b._start_wire << "," << b._start_t
                            << ") => ("
                            << b._end_wire << "," << b._end_t << ")" << std::endl;
                        }
                    }
                }
                cout << endl;
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







