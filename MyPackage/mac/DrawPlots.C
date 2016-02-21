// Feb-18, 2016


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DrawPlots(){
    
    

    bool DoProtonsMomenta       = false;
    bool DoProtonsTrackLength   = false;
    bool DoSRCEvents            = true;
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    TPlots  * tracks   = new TPlots("Ana.root","TracksTree");
    TPlots  * events   = new TPlots("Ana.root","EventsTree");
   
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    if (DoProtonsMomenta) {
        TH1F * h = tracks -> H1("StartMomentum.P()","PdgCode==2212","",401,-1,1000
                             ,"proton momentum","p [MeV/c]","",38,38);
        analysis -> NormalizeHistogram(h);
        tracks -> Line(251,0,251,h->GetMaximum(),2,4,2);
        tracks -> Text(260,0.8*h->GetMaximum(),"Fermi momentum 251 MeV/c [e-scat.]");
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    if (DoProtonsTrackLength) {
        tracks -> H2("StartMomentum.P()","TrackLength","PdgCode==2212","colz",401,1,1000,401,-1,1000
                  ,"proton momentum","p [MeV/c]","track length [cm]");
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    if (DoSRCEvents){
        // identify v (np) -> µ p p events, and ask reconstruct BNL measurement
        // the angle between the two protons in the inital state vs. the recoil momentum
        events -> H2WithProjections( "Prec.Mag()",plot->CosTheta("Pmiss","Prec"),SRCcut
                                    ,50,1,1000,50,-1.01,1.01,"","recoil momentum [MeV/c]","#theta (p(miss) , p(recoil))" );
//        TCanvas * c = plot -> CreateCanvas("c" , "DivideSquare");
//        c -> cd(1);
//        TH1F * Prec = events -> H1("Prec.Mag()",SRCcut,"colz",50,0,1000,"","recoil momentum [GeV/c]","",38,38);
//        plot -> Line(pThresholdArgoNeuT,0,pThresholdArgoNeuT,Prec->GetMaximum(),2,2);
//        c -> cd(2);
//        events -> H1(plot->CosTheta("Pmiss","Prec"),SRCcut,"colz",50,-1.1,1.1,"","cos( #theta )","",38,38);
//        c -> cd(3);
//        events -> H2("Prec.Mag()",plot->CosTheta("Pmiss","Prec"),SRCcut,"colz"
//                     ,50,1,1000,50,-1.01,1.01,"","recoil momentum [MeV/c]","#theta (p(miss) , p(recoil))");
        plot -> Line(pThresholdArgoNeuT,-1.01,pThresholdArgoNeuT,1.01,2,2);
    }
}

