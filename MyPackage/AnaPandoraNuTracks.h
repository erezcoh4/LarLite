/**
 * \file AnaPandoraNuTracks.h
 *
 * \ingroup MyPackage
 *
 * \brief Class def header for a class AnaPandoraNuTracks
 *
 * @author erezcohen
 */

/** \addtogroup MyPackage
 
 @{*/

#ifndef LARLITE_ANAPANDORANUTRACKS_H
#define LARLITE_ANAPANDORANUTRACKS_H

#include "Analysis/ana_base.h"
#include "MySoftwarePackage/TPlots.h"
#include <map>
#include "DataFormat/track.h"
#include "DataFormat/wire.h"
#include "DataFormat/data_base.h"
#include "LArUtil/Geometry.h"
#include "LArUtil/DetectorProperties.h"

#include <fstream>
#include "MyLArTools.h"

#ifndef __CINT__

#define PrintBox(box) cout << #box << ": (" << box._start_wire << "," << box._start_t << ") => (" << box._end_wire << "," << box._end_t << ")" << std::endl;
#endif

#define ADC_threshold 5
#define time_tick_max_distance 15
#define MAXbins 500

using namespace std;
struct box {
    int     _start_wire , _end_wire;
    float   _start_t    , _end_t;
    float   diag_slope;
    
    box() { _start_wire = _start_t = _end_wire = _end_t = 0; }
    
    box(int start_wire, float start_t, int end_wire, float end_t)
    : _start_wire(start_wire), _start_t(start_t), _end_wire(end_wire), _end_t(end_t)
    {
        // order the box start and end positions
        if (_start_wire > _end_wire){
            
            int tmp_wire= _end_wire;
            _end_wire   = _start_wire;
            _start_wire = tmp_wire;
            
        }
        if (_start_t > _end_t){
            
            float tmp_t = _end_t;
            _end_t      = _start_t;
            _start_t    = tmp_t;
            
        }
        diag_slope = ( _end_t - _start_t ) / ( _end_wire - _start_wire );
        
    }
    
};



namespace larlite {
    /**
     \class AnaPandoraNuTracks
     User custom analysis class made by SHELL_USER_NAME
     */
    class AnaPandoraNuTracks : public ana_base{
        
    public:
        
        AnaPandoraNuTracks(){ _name="AnaPandoraNuTracks"; _fout=0;}
        virtual ~AnaPandoraNuTracks(){}
        
        
        virtual bool initialize();
        
        
        virtual bool analyze(storage_manager* storage);
        
        
        virtual bool finalize();

        
        
        // my methods...
        bool    LoadBDTCandidates ();
        bool            SetWorker ( TString worker = "uboone", Int_t fdebug = 0, bool fCreateImagas = false
                                   , TString fimages_path = ""
                                   , TString froi_map_path = "" , TString froi_map_name = ""
                                   , int fNMaxEntries = - 1 );
        
        bool             SetFrame ( TH2F*h , TString xtit , TString ytit );
        bool FirstSeedWireAndTime ( int bin_w, int bin_t );

        //        bool    inBDTcandidates (TVector3 vertex , TVector3 end, box Box); // unused - delete Sep-09,2016
        
        
      
        TString images_path , roi_map_path  , roi_map_name;
        
        bool    GoodTrack;
        bool    on_uboone_grid  , CreateImagas , calculate_adc_in_corners ;
        
        int     TTreeEntry  , NMaxEntries;
        int     run , subrun ,  event , track_id ,  start_wire[3] , end_wire[3] , NgoodTracks;
        int     Nbins_w , Nbins_t   , Nbins_w_zoomout , Nbins_t_zoomout;
        int     Nbins_x , Nbins_y   , Nbins_z ;
        Int_t   debug;

        float   start_t[3] , end_t[3];
        float   Xmin , Xmax , Ymin , Ymax , Zmin , Zmax;

        
        
        ofstream out_csv_file;
        MyLArTools * lar_tools;
        TPlots * plot;
        
        
        Double_t SumADC_around_lt , SumADC_around_lt_in_track_direction  ,  SumADC_around_lb , SumADC_around_lb_in_track_direction;
        Double_t SumADC_around_rt , SumADC_around_rt_in_track_direction  ,  SumADC_around_rb , SumADC_around_rb_in_track_direction;
        Double_t ADC_ratio_around_lt , ADC_ratio_around_lb , ADC_ratio_around_rt , ADC_ratio_around_rb;
        
        int     time_tick , FirstTickZoomout , FirstTickZoomin;
        double  time_shift =  802;
        double ADC_xy[MAXbins][MAXbins] , ADC_yz[MAXbins][MAXbins];
        int bin_x , bin_y , bin_z;
        size_t i;
        TH2F * hTrackROI[3] , * hTrackROIzoomout[3] , * hTrack_xy , * hTrack_zy;

        
        
    #ifndef __CINT__
   protected:
        
               
        //    run - subrun - event - track id - Box( s-wire , s-time , e-wire , e-time )
        std::map < int , std::map < int , std::map < int , std::map < int , std::vector<box> > > > > BDTcandidates;

        
        Int_t N_close_tracks;
        std::vector<Double_t> Angle_close_track;
        std::vector< std::vector<int> > wire_and_time_bins;

        
        // tracks
        TTree             * TracksTree;
        Double_t          straight_track_length , segmented_track_length , momentum;
        
        TVector3          vertex , end , straight_track ;
    #endif
       

        
    };
}
#endif

//**************************************************************************
//
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
