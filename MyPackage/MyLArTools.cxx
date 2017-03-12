#ifndef MYLARTOOLS_CXX
#define MYLARTOOLS_CXX

#include "MyLArTools.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MyLArTools::MyLArTools(){
    cout << "MyLArTools..." << endl;
    // range in gr/cm2
    Float_t Range_grampercm_proton[31] =
    {1.887E-1, 3.823E-1, 6.335E-1, 1.296, 2.159, 7.375, 1.092E1,
        2.215E1, 3.627E1, 5.282E1, 7.144E1, 9.184E1, 1.138E2,
        1.370E2, 1.614E2, 1.869E2, 2.132E2, 2.403E2, 2.681E2,
        2.965E2, 3.254E2, 3.548E2, 3.846E2, 4.148E2, 4.454E2,
        7.626E2, 1.090E3, 1.418E3, 1.745E3, 2.391E3, 3.022E3
    };
    Float_t KE_MeV_proton[31] =
    {10, 15, 20, 30, 40, 80, 100, 150, 200, 250, 300, 350, 400,
        450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000,
        1500, 2000, 2500, 3000, 4000, 5000
    };
    
    
    double LAr_density = 1.396; //g/cm^3
    
    
    Float_t Range_grampercm_proton_LAr[31];
    Float_t p_MeVc_proton[31];
    for (int i = 0 ; i < 31; i++) {
        Range_grampercm_proton_LAr[i] = Range_grampercm_proton[i] / LAr_density; // range [cm] = range [gr/cm^2] / rho [gr/cm^3]
        E = 938.272 + KE_MeV_proton[i];
        p_MeVc_proton[i] = sqrt(E*E - 938.272*938.272);
    }
    
    KE_vs_range_proton = new TGraph(31, Range_grampercm_proton_LAr, KE_MeV_proton);
    KE_vs_range_proton_s3 = new TSpline3("KE_vs_range_proton", KE_vs_range_proton);
    p_vs_range_proton = new TGraph(31, Range_grampercm_proton_LAr, p_MeVc_proton);
    p_vs_range_proton_s3 = new TSpline3("p_vs_range_proton", p_vs_range_proton);

    // range in gr/cm2
    Float_t Range_grampercm_muon[29] = {9.833E-1, 1.786E0, 3.321E0, 6.598E0, 1.058E1, 3.084E1, 4.250E1,
        6.732E1, 1.063E2, 1.725E2, 2.385E2, 4.934E2,
        6.163E2, 8.552E2, 1.202E3, 1.758E3, 2.297E3,
        4.359E3, 5.354E3, 7.298E3, 1.013E4, 1.469E4,
        1.910E4, 3.558E4, 4.326E4, 5.768E4, 7.734E4, 1.060E5, 1.307E5
    };
    
    Float_t KE_MeV_muon[29] = {10, 14, 20, 30, 40, 80, 100, 140, 200, 300, 400, 800, 1000,
        1400, 2000, 3000, 4000, 8000, 10000, 14000, 20000, 30000,
        40000, 80000, 100000, 140000, 200000, 300000, 400000
    };
   
    Float_t Range_grampercm_muon_LAr[29];
    Float_t p_MeVc_muon[29];
    for (int i = 0 ; i < 29; i++) {
        Range_grampercm_muon_LAr[i] = Range_grampercm_muon[i] / LAr_density;
        E = 105.6 + KE_MeV_muon[i];
        p_MeVc_muon[i] = sqrt(E*E - 105.6*105.6);
    }
    
    KE_vs_range_muon = new TGraph(29, Range_grampercm_muon_LAr, KE_MeV_muon);
    KE_vs_range_muon_s3 = new TSpline3("KE_vs_range_muon", KE_vs_range_muon);
    p_vs_range_muon = new TGraph(29, Range_grampercm_muon_LAr, p_MeVc_muon);
    p_vs_range_muon_s3 = new TSpline3("p_vs_range_muon", p_vs_range_muon);

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TCanvas * MyLArTools::Plot_proton_range_in_LAr(TString type){
   
    
    TCanvas * c = new TCanvas(type,type);
    if (type == "kinetic energy") {
        KE_vs_range_proton_s3 -> Draw();
    }
    else if (type == "momentum"){
        p_vs_range_proton_s3 -> Draw();
    }
    c->SaveAs("~/Desktop/"+type+"proton_range.pdf");
    return c;

}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double MyLArTools::Get_protonMomentumFromRange( float range ){
    return p_vs_range_proton_s3 -> Eval(range);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double MyLArTools::Get_muonMomentumFromRange( float range ){
    return p_vs_range_muon_s3 -> Eval(range);
}

#endif
