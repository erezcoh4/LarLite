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

    /** IMPLEMENT in AnalyseEvents.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in AnalyseEvents.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in AnalyseEvents.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

      void  CreateEvdImages ( event_wire * wire , int fRSE[3] , std::vector<box> fROIs , std::vector<TString> fLabels );
      bool      LoadROIsMap ( TString , Int_t );
      
      Int_t     debug;
      Int_t     RSE[3];
      Int_t     run , subrun ,  event , start_w[3] , end_w[3] , start_t[3] , end_t[3];

      std::vector<box>      ROIs;
      std::vector<TString>  Labels;

      
      
      //         run              subrun           event            Boxes
      std::map < int , std::map < int , std::map < int , std::vector<std::vector<box>> > > > ROImap;

  protected:
      
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
