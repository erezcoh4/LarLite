/**
 * \file AnalyseEvents.h
 *
 * \ingroup AnalyseLArLiteFiles
 *
 * \brief Class def header for a class AnalyseEvents
 *
 * @author erezcohen
 */

/** \addtogroup AnalyseLArLiteFiles
 
 @{*/

#ifndef LARLITE_ANALYSEEVENTS_H
#define LARLITE_ANALYSEEVENTS_H

#include "Analysis/ana_base.h"
#include "myIncludes.h"
#include "TPlots.h"
#include "PandoraNuTrack.h"
#include "MyLArTools.h"
#include "DataFormat/track.h"
#include "DataFormat/wire.h"

#include "LArUtil/Geometry.h"

namespace larlite {
    /**
     \class AnalyseEvents
     User custom analysis class made by SHELL_USER_NAME
     */
    class AnalyseEvents : public ana_base{
        
    public:
        
        /// Default constructor
        AnalyseEvents(){ _name="AnalyseEvents"; _fout=0;}
        
        /// Default destructor
        virtual ~AnalyseEvents(){}
        virtual bool initialize();
        virtual bool analyze(storage_manager* storage);
        virtual bool finalize();
        
        
        // setters
        bool              SetArgs ( TString fworker="erez", Int_t fdebug=0 , Int_t fNMaxEntries=-1 ,
                                   bool fDoExtractTracks = false, TString fFeaturesFileName="",
                                   bool fDoCreateEvdImages = false, TString fimages_path="" );
        bool     InitFeaturesFile ();
        void            SetWorker ( TString fworker );
        void             SetDebug ( Int_t fdebug )          {debug = fdebug;};
        void       SetNMaxEntries ( Int_t fNMaxEntries)     {NMaxEntries = fNMaxEntries;};
        void        SetImagesPath ( TString fimages_path )  {images_path = fimages_path;};
        void       SetDoEvdImages ( bool fDoCreateEvdImages){DoCreateEvdImages = fDoCreateEvdImages;};
        void     SetDoExtractInfo ( bool fDoExtractTracks)  {DoExtractTracks = fDoExtractTracks;};
        void     SetFeaturesFName ( TString fname)          {FeaturesFileName = fname; };
        void       SetImageFormat ( TString fFormat="pdf" ) {ImageFormat = fFormat; }

        // running
        void      CreateEvdImages ( event_wire *, int[3], std::vector<std::vector<box>>,
                                   std::vector<Int_t> , std::vector<TString> , std::vector<TLorentzVector> );
        bool          LoadROIsMap ( TString , Int_t n = 0 );
        bool    ExtractTracksInfo ();
        bool  ExtractTracksHeader ();
        
        bool        DoCreateEvdImages , DoExtractTracks , found_muon , found_proton;
        int         time_tick ;

        Int_t       debug   , TTreeEntry, NMaxEntries;
        Int_t       ivtx    , itrkMuon  , itrkProton;
        Int_t       run     , subrun    , event     , start_w[3]    , end_w[3]      , start_t[3]    , end_t[3];
        Int_t       w_min[3] , w_max[3] , t_min[3]  , t_max[3]      , Nbins_w[3]    , Nbins_t[3];

        TString     worker  , images_path , ImageFormat , FeaturesFileName;
        TString     hName   , hTitle;
        
        
        TH2F        * hROI[3];
        TPlots      * plot;
        MyLArTools  * lar_tools;

        
        
        Float_t     VertexMomentum;
        
        TVector3    VertexDirection;
        TVector3    mutrack_vertex , mutrack_end , ptrack_vertex , ptrack_end;
        
        
        TLorentzVector muon_momentum , proton_momentum;
        
        
        ofstream fout;
    #ifndef __CINT__
    protected:
        
        //         run              subrun           event            vtx/µ-trk/p-trk ids
        std::map < int , std::map < int , std::map < int , std::vector<Int_t> > > > VtxTrksIDmap;
        //         run              subrun           event            Boxes
        std::map < int , std::map < int , std::map < int , std::vector<std::vector<box>> > > > ROImap;

        
        std::vector<box>      ROIs;
        std::vector<TString>  Labels;

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
