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
#include "TLorentzVector.h"
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

    virtual bool initialize();

    virtual bool analyze(storage_manager* storage);

    virtual bool finalize();

  protected:
      
      
      // tracks
      TTree             * TracksTree;
      Int_t             PdgCode;
      Double_t          StraightTrackLength , TrackLength;
      TLorentzVector    StartMomentum       , EndMomentum ;
      
      // events
      TTree                         * EventsTree;
      // nucleons
      Int_t                         Ntot        ,   Ne      , Nmu   ,   Nl      ,   Np      ,   Nn;
      TLorentzVector                neutrino    ,   muon    ,   q;
      std::vector<TLorentzVector>   Uprotons    ,   protons ,   neutrons;
      std::vector<float>            pMag;
      Double_t                      Ev          ,   PoverQ  , ThetaPQ   ,   Q2  ,   Xb;
      TVector3                      Plead       ,   Pmiss   , Prec;
 
      
      
      
      // my methods
      void SortProtons();
      void InitializeEvent();
      std::vector<size_t> sort_pMag_for_indexes(const std::vector<float> &v);
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
