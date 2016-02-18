/**
 * \file MyAna.h
 *
 * \ingroup MyPackage
 * 
 * \brief Class def header for a class MyAna
 *
 * @author erezcohen
 */

/** \addtogroup MyPackage

    @{*/

#ifndef LARLITE_MYANA_H
#define LARLITE_MYANA_H

#include "Analysis/ana_base.h"

namespace larlite {
  /**
     \class MyAna
     User custom analysis class made by SHELL_USER_NAME
   */
  class MyAna : public ana_base{
  
  public:

    /// Default constructor
    MyAna(){ _name="MyAna"; _fout=0;}

    /// Default destructor
    virtual ~MyAna(){}

    /** IMPLEMENT in MyAna.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in MyAna.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in MyAna.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

  protected:
      
      Int_t     Ntracks ,   pdgID;
      Double_t  StraightTrackLength , TrackLength;
      TTree * OutTree;
    
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
