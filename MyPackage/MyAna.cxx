#ifndef LARLITE_MYANA_CXX
#define LARLITE_MYANA_CXX

#include "MyAna.h"
#include "DataFormat/mctrack.h"
#include "DataFormat/mctruth.h"

namespace larlite {
    
    bool MyAna::initialize() {
        TracksTree  = new TTree("TracksTree","tracks analysis by LArLite");
        TracksTree -> Branch("PdgCode"              ,   &PdgCode                ,   "PdgCode/I");
        TracksTree -> Branch("StartMomentum"        ,   "TLorentzVector"        ,   &StartMomentum );
        TracksTree -> Branch("EndMomentum"          ,   "TLorentzVector"        ,   &EndMomentum);
        TracksTree -> Branch("StraightTrackLength"  ,   &StraightTrackLength    ,   "StraightTrackLength/D");
        TracksTree -> Branch("TrackLength"          ,   &TrackLength            ,   "TrackLength/D");
        Printf("Initialized TracksTree");

        EventsTree  = new TTree("EventsTree","events analysis LArLite");
        EventsTree -> Branch("Ntot"                 ,   &Ntot                   ,   "Ntot/I");
        EventsTree -> Branch("Np"                   ,   &Np                     ,   "Np/I");
        EventsTree -> Branch("Nn"                   ,   &Nn                     ,   "Nn/I");
        EventsTree -> Branch("ThetaPQ"              ,   &ThetaPQ                ,   "ThetaPQ/D");
        EventsTree -> Branch("PoverQ"               ,   &PoverQ                 ,   "PoverQ/D");
        EventsTree -> Branch("Xb"                   ,   &Xb                     ,   "Xb/D");
        EventsTree -> Branch("Q2"                   ,   &Q2                     ,   "Q2/D");
        EventsTree -> Branch("q"                    ,   "TLorentzVector"        ,   &q          );
        EventsTree -> Branch("neutrino"             ,   "TLorentzVector"        ,   &neutrino   );
        EventsTree -> Branch("muon"                 ,   "TLorentzVector"        ,   &muon       );
        EventsTree -> Branch("protons"              ,   &protons        );
        EventsTree -> Branch("neutrons"             ,   &neutrons       );
        EventsTree -> Branch("Pmiss"                ,   "TVector3"              ,   &Pmiss      );
        EventsTree -> Branch("Prec"                 ,   "TVector3"              ,   &Prec       );
        Printf("Initialized EventsTree");
        return true;
    }
    
    
    
    bool MyAna::analyze(storage_manager* storage) {
        InitializeEvent();
        
        auto ev_mctrack = storage -> get_data<event_mctrack> ("mcreco");
        auto ev_mctruth = storage -> get_data<event_mctruth> ("generator");
        
        if(ev_mctruth){
            // neutrino
            auto Nu = ev_mctruth->at(0).GetNeutrino().Nu();
            Ev = Nu.Trajectory().front().E();       // [GeV]
            Ev = Ev * 1000; // [MeV]
            neutrino = TLorentzVector(0,0,Ev,Ev);
            
            if(ev_mctrack){
                
                Ntot        = (int)ev_mctrack->size();
             
                for (auto const& t: *ev_mctrack){
                    // tracks
                    PdgCode             = t.PdgCode();
                    StartMomentum       = t.Start().Momentum(); // 4-vector MeV/c
                    EndMomentum         = t.End().Momentum();   // 4-vector MeV/c
                    StraightTrackLength += (t.End().Position() - t.Start().Position()).Vect().Mag();    // cm
                    TrackLength         = 0;
                    if(t.size()){
                        for(size_t i=0; i<t.size()-1; ++i) {
                            auto const& this_step = t[i];
                            auto const& next_step = t[i+1];
                            TrackLength += (next_step.Position() - this_step.Position()).Vect().Mag();
                        }
                    }
                    TracksTree -> Fill();
                    if (StartMomentum.P() < 10)
                        Printf("t.PdgCode() = %d, t.Start().Momentum().P() = %f, t.End().Momentum().P() = %f",PdgCode,StartMomentum.P(),EndMomentum.P());
                    
                    // outgoing lepton, and nucleons
                    switch (PdgCode) { //[http://pdg.lbl.gov/2002/montecarlorpp.pdf]
                        case 13: // µ-
                            muon = StartMomentum;
                            break;
                        case 2212: // proton
                            Uprotons.push_back(StartMomentum);
                            pMag.push_back(StartMomentum.P());
                            break;
                        case 2112: // neutron
                            neutrons.push_back(StartMomentum);
                            break;
                        default:
                            break;
                    }
                    
                }
                if (Uprotons.size() > 0 || neutrons.size() > 0) {
                    q           = neutrino - muon;
                    Q2          = -q.Mag2();
                    Xb          = Q2 / 2. * 938.272 * q.E();
                    SortProtons();
                    Np          = (int)protons.size();
                    Nn          = (int)neutrons.size();
                    EventsTree -> Fill();
                }
            }
        }
        return true;
    }
    
    bool MyAna::finalize() {
        Printf("Tracks filled with %lld entries, events filled with %lld entries",EventsTree -> GetEntries(),TracksTree -> GetEntries());
        if(_fout){
            TracksTree -> Write();
            if (EventsTree -> GetEntries())
                EventsTree -> Write();
        }
        delete EventsTree;
        delete TracksTree;
        return true;
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void MyAna::InitializeEvent(){
        if (!Uprotons.empty())  Uprotons.clear();   // unsorted protons
        if (!protons.empty())   protons.clear();
        if (!neutrons.empty())  neutrons.clear();
        if (!pMag.empty())      pMag.clear();
        Pmiss       = TVector3();
        Prec        = TVector3();
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void MyAna::SortProtons(){
        for (auto i: sort_pMag_for_indexes(pMag))
            protons.push_back(Uprotons.at(i));
        Plead   = protons.at(0).Vect();
        ThetaPQ = Plead.Angle(q.Vect());
        PoverQ  = Plead.Mag() / q.P();
        Pmiss   = Plead - q.Vect();
        if (Ntot == 2) {
            if (protons.size() == 2 ){
                Prec    = protons.at(1).Vect();
//                if (Prec.Mag() < 10e1) {
//                    Printf("Uprotons.size() = %ld, Uprotons.at(0).P() = %f, Uprotons.at(1).P() = %f"
//                           ,Uprotons.size(),Uprotons.at(0).P(), Uprotons.at(1).P() );
//                    Printf("Pmiss = %f , Precoil = %f, cos (opening angle) = %f"
//                           ,Pmiss.Mag() , Prec.Mag() , cos(Pmiss.Angle(Prec)));
//                }
            }
            else if (protons.size() == 1 && neutrons.size() == 1 )
                Prec    = neutrons.at(0).Vect();
        }
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    std::vector<size_t> MyAna::sort_pMag_for_indexes(const std::vector<float> &v) {
        // initialize original index locations
        std::vector<size_t> idx(v.size());
        for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;
        // sort indexes based on comparing values in v
        std::sort(idx.begin(), idx.end(),
                  [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});
        return idx;
    }
    
    
}
#endif
