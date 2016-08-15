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
