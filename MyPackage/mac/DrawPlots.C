// Feb-18, 2016


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DrawPlots(){
    
    

    bool DoProtonsMomenta       = false;
    bool DoProtonsTrackLength   = false;
    bool DoSRCEvents            = false;
    bool DoAngles               = false;
    bool DoHighMomentumTail     = false;
    bool DothetaPPFinalInitial  = true;
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    TPlots  * tracks   = new TPlots("Ana.root","TracksTree");
    TPlots  * events   = new TPlots("Ana.root","EventsTree","events",false);
   
    
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
        TCanvas * c = plot -> CreateCanvas("c" , "DivideSquare");
        c -> cd(1);
        TH1F * Prec = events -> H1("Prec.Mag()",SRCcut&& "Prec.Mag()>0","colz",50,0,1000,"","recoil momentum [GeV/c]","",38,38);
        plot -> Line(pThresholdArgoNeuT,0,pThresholdArgoNeuT,Prec->GetMaximum(),2,2);
        c -> cd(2);
        events -> H1(plot->CosTheta("Pmiss","Prec"),SRCcut&& "Prec.Mag()>0","colz",50,-1.1,1.1,"","cos( #theta )","",38,38);
        c -> cd(3);
        events -> H2("Prec.Mag()",plot->CosTheta("Pmiss","Prec"),SRCcut&& "Prec.Mag()>0","colz"
                     ,50,1,1000,50,-1.01,1.01,"","recoil momentum [MeV/c]","#theta (p(miss) , p(recoil))");
        plot -> Line(pThresholdArgoNeuT,-1.01,pThresholdArgoNeuT,1.01,2,2);
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    if (DoAngles){
//        plot -> CreateCanvas("Theta_pn_i_Prec");
//        events -> H2("Prec.Mag()",plot->CosTheta("Pmiss","Prec"),cutCC2p,"colz"
//                     ,50,0,1000,50,-1.05,1.05,"","recoil momentum [MeV/c]","cos( #theta_{np}^{i} )");
//        plot -> CreateCanvas("Theta_pn_i_Theta_munu");
//        events -> H2(plot->CosTheta("neutrino.Vect()","muon.Vect()"),plot->CosTheta("Pmiss","Prec"),cutCC2p&&"Prec.Mag()>1","colz"
//                     ,50,-1.01,1.01,50,-1.01,1.01,"","cos( #theta_{#nu#mu} )","cos( #theta_{np}^{i} )");
        plot -> CreateCanvas("Theta_pp_f_Prec");
        events -> H2("Prec.Mag()",plot->CosTheta("protons[0].Vect()","protons[1].Vect()"),cutCC2p,"colz"
                     ,50,1,1000,50,-1.01,1.01,"","recoil momentum [MeV/c]","cos( #theta_{pp}^{f} )");
//        plot -> CreateCanvas("Theta_pp_Theta_numu");
//        events -> H2(plot->CosTheta("neutrino.Vect()","muon.Vect()"),plot->CosTheta("protons[0].Vect()","protons[1].Vect()"),cutCC2p,"colz"
//                     ,50,-1.01,1.01,50,-1.01,1.01,"","cos( #theta_{#nu#mu} )","cos( #theta_{pp}^{f} )");
//        plot -> CreateCanvas("Theta_numu_Prec");
//        events -> H2("Prec.Mag()",plot->CosTheta("neutrino.Vect()","muon.Vect()"),cutCC2p&&"Prec.Mag()>200","colz"
//                     ,50,1,1000,50,-1.01,1.01,"","recoil momentum [MeV/c]","cos( #theta_{#nu#mu} )");
    }
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    if (DoHighMomentumTail){
        plot -> CreateCanvas("DoHighMomentumTail");
        float Max = 1300;
        TH1F * Prec = events -> H1("Prec.Mag()",cutCC2p,"",75,0,Max,"","recoil momentum [MeV/c]","",38,38);
        events -> H1("Prec.Mag()",cutCC2p&&"Prec.Mag()>270","same",75,0,Max,"","recoil momentum [MeV/c]","",48,48,3001);
        float Tail      = Prec -> Integral(Prec->GetXaxis()->FindBin(270),Prec->GetXaxis()->FindBin(Max));
        float TailErr   = sqrt(Tail);
        float Tot       = Prec -> Integral(Prec->GetXaxis()->FindBin(0),Prec->GetXaxis()->FindBin(Max));
        float TotErr    = sqrt(Tot);
        float fTail     = Tail / Tot;
        float fTailErr  = fTail * ( 1./Tail + 1./Tot );
        SHOW(Tail);
        SHOW(Tot);
        SHOW(fTail);
        SHOW(fTailErr);
        TString TailPercentage  = plot->PercentStr(fTail);
        TString TailPercenErr   = plot->PercentStr(fTailErr);
        plot -> Text(300,Prec->GetMaximum(),Form("high momentum tail (>270 MeV/c) %.2f(%.0f)%%",100*fTail,100*100*fTailErr));
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    if (DothetaPPFinalInitial){
        plot -> CreateCanvas("Theta_numu_Prec");
//        TString var = plot->CosTheta("Pmiss","Prec") , XTitle = "cos( #theta_{pn}^{i} )";
        TString var = plot->CosTheta("protons[0].Vect()","protons[1].Vect()") , XTitle = "cos( #theta_{pp}^{f} )";
        const int N = 5;
        TH1F    * h[N];
        TString Labels[N];
        float   PmissMin[N] = {0 , 100 , 200 , 400 , 600 } , PmissMax[N] = {100 , 200 , 400 , 600 , 1000 } ;
        for (int i = 0; i < N ; i++) {
            TCut cut = cutCC2p && Form("%f > Prec.Mag() && Prec.Mag() > %f",PmissMax[i],PmissMin[i]) ;
            Labels[i] = Form("%.0f > p(rec) > %.0f MeV/c",PmissMax[i],PmissMin[i]);
            cut.Print();
            h[i] = events -> H1(var,cut,"goff",50,-1.05,1.05,"",XTitle,"",(i!=4)?i+1:i+2,(i!=4)?i+1:i+2);
            analysis -> NormalizeHistogram(h[i]);
        }
        for (int i = N-1; i >= 0 ; i--){
            h[i] -> Draw((i==N-1)?"":"same");
        }
        plot -> AddLegend("recoil momentum cut",N,h,Labels,1,"f");
        
     }

}

