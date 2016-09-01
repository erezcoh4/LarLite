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
#include "MySoftwarePackage/myIncludes.h"
#include "PandoraNuTrack.h"
#include "DataFormat/track.h"
#include "DataFormat/wire.h"


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
        bool          SetArgs ( TString fworker="erez", Int_t fdebug=0, TString fimages_path="" );
        void        SetWorker ( TString fworker );
        void         SetDebug ( Int_t fdebug )          {debug = fdebug;};
        void    SetImagesPath ( TString fimages_path )  {images_path = fimages_path;};

        // running
        void  CreateEvdImages ( event_wire *, int[3], std::vector<box>, std::vector<TString> );
        bool      LoadROIsMap ( TString , Int_t );
        
        
        
        
        
        Int_t       debug;
        Int_t       RSE[3];
        Int_t       ivtx, itrkMuon , itrkProton;
        Int_t       run , subrun ,  event , start_w[3] , end_w[3] , start_t[3] , end_t[3];
        
        
        TString     worker  , images_path ;
        
        
        
        
    #ifndef __CINT__
    protected:
        
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
