/**
 * \file ExtractPhysVars.h
 *
 * \ingroup AnalyseLArLiteFiles
 * 
 * \brief Class def header for a class ExtractPhysVars
 *
 * @author erezcohen
 */

/** \addtogroup AnalyseLArLiteFiles

    @{*/

#ifndef LARLITE_EXTRACTPHYSVARS_H
#define LARLITE_EXTRACTPHYSVARS_H


#include "Analysis/ana_base.h"
#include "myIncludes.h"
#include "TPlots.h"
#include "PandoraNuTrack.h"
#include "MyLArTools.h"
#include "DataFormat/track.h"
#include "DataFormat/wire.h"
#include <initializer_list>

#define Debug( DoDebug, a ){ if (debug>DoDebug) cout << #a << ":" << a << endl; }


namespace larlite {
  /**
     \class ExtractPhysVars
     User custom analysis class made by SHELL_USER_NAME
   */
  class ExtractPhysVars : public ana_base{
  
  public:

      /// Default constructor
      ExtractPhysVars(){ _name="ExtractPhysVars"; _fout=0;}
      virtual ~ExtractPhysVars(){}


      
      // setters
      void        SetWorker ( TString fworker )         {worker = fworker;};
      void     SetVerbosity ( Int_t fdebug )            {debug = fdebug;};
      void   SetNMaxEntries ( Int_t fNMaxEntries )      {NMaxEntries = fNMaxEntries;};
      
      
      // other methods
      virtual bool initialize();
      virtual bool   analyze (storage_manager* storage);
      virtual bool  finalize ();
      bool LoadRSEpTracksMap ( TString );
      Int_t     FindpTrackID ();
      Float_t      dQdx2dEdx ( Float_t );
      
      
      TString   worker;
      
      Int_t     debug   , NMaxEntries;
      Int_t     run     , subrun    , event , itrk_proton;
      
      
      Float_t   dx      , dQdx      , dEdx;
      
      
      
    #ifndef __CINT__
    protected:
      
      //         run              subrun           event p-trk ids
      std::map < int , std::map < int , std::map < int , int > > > RSEpTracksMap;
      std::map < int , std::map < int , std::map < int , std::vector<Int_t> > > > VtxTrksIDmap;
      
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
