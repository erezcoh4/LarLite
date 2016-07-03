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

#define PrintBox(box) cout << #box << ": (" << box._start_wire << "," << box._start_t << ") => (" << box._end_wire << "," << box._end_t << ")" << std::endl;
#define ADC_threshold 5
#define time_tick_max_distance 15


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
      
        
        bool LoadBDTCandidates (bool DoPrint = false);
        bool inBDTcandidates (TVector3 vertex , TVector3 end, box Box);
        
        int     run , subrun ,  event , track_id ,  start_wire , end_wire , NgoodTracks;
        float   start_t , end_t;
        
        
        ofstream out_csv_file;
        bool GoodTrack;
        MyLArTools * lar_tools;

        
        
        Double_t SumADC_around_lt , SumADC_around_lt_in_track_direction  ,  SumADC_around_lb , SumADC_around_lb_in_track_direction;
        Double_t SumADC_around_rt , SumADC_around_rt_in_track_direction  ,  SumADC_around_rb , SumADC_around_rb_in_track_direction;
        Double_t ADC_ratio_around_lt , ADC_ratio_around_lb , ADC_ratio_around_rt , ADC_ratio_around_rb;
        
        int time_tick;
        size_t i;
        TH2F * hTrackROI , * hTrackROIzoomout;
        
        
    protected:
        
               
        //    run - subrun - event - track id - Box( s-wire , s-time , e-wire , e-time )
        map < int , map < int , map < int , map < int , box > > > > BDTcandidates;

        
        Int_t N_close_tracks;
        vector<Double_t> Angle_close_track;
        
        
        // tracks
        TTree             * TracksTree;
        Double_t          straight_track_length , segmented_track_length , momentum;
        
        TVector3          vertex , end , straight_track ;
        

        
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
