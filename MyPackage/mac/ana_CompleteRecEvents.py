import ROOT
from ROOT import TPlots
from rootpy.interactive import wait
import time
ROOT.gStyle.SetOptStat(0000)


DoVarsDependingOnEv     = False
DoLowEv                 = True


Path        = "/Users/erezcohen/Desktop/uBoone/AnaFiles"
FileName    = "CompleteRecEvents_mcc6"
ana         = TPlots(Path + "/Ana_"+FileName+".root","EventsTree","complete reconstructed events")
Nbins       = 50
N2p         = 12000 # uboone expectation (GENIE)
Nccqe       = 0.4 * N2p # 40% of 2p CCQE events at ArgoNeuT were CCQE



if DoVarsDependingOnEv :
    c = ana.CreateCanvas("c","Divide",3,4)
    c.cd(1)
    ana.H1("neutrino.E()",ROOT.TCut(),"HIST",Nbins,0,2000,"#nu energy","E#nu [GeV]","",1,46)
    c.cd(4)
    ana.H2("neutrino.E()","muon.P()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,2000,"","E#nu [GeV]","p(#mu) [GeV/c]")
    c.cd(5)
    ana.H2("neutrino.E()","TMath::RadToDeg()*muon.Theta()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,180,"","E#nu [GeV]","#theta(#mu) [de.g]")
    c.cd(6)
    ana.H2("neutrino.E()","TMath::RadToDeg()*muon.Phi()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,-180,180,"","E#nu [GeV]","#phi(#mu) [deg.]")
    c.cd(7)
    ana.H2("neutrino.E()","protons[0].P()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,2000,"","E#nu [GeV]","p(p) [GeV/c]")
    c.cd(8)
    ana.H2("neutrino.E()","TMath::RadToDeg()*protons[0].Theta()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,180,"","E#nu [GeV]","#theta(p) [deg.]")
    c.cd(9)
    ana.H2("neutrino.E()","TMath::RadToDeg()*protons[0].Phi()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,-180,180,"","E#nu [GeV]","#phi(p) [deg.]")
    c.cd(10)
    ana.H2("neutrino.E()","protons[0].P()+muon.P()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,2500,"","E#nu [GeV]","p(p)+p(#mu) [GeV/c]")
    c.cd(11)
    ana.H2("neutrino.E()",ana.Theta("protons[0].Vect()","muon.Vect()"),ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,180,"","E#nu [GeV]","#theta(p , #mu) [deg.]")
    c.cd(12)
    ana.H2("protons[0].P()+muon.P()",ana.Theta("protons[0].Vect()","muon.Vect()"),ROOT.TCut(),"colz",Nbins,0,2500,Nbins,0,180,"","p(p)+p(#mu) [GeV/c]","#theta(p , #mu) [deg.]")
    c.Update()
    wait()



if DoLowEv:
    cLowEv = ana.CreateCanvas("low Ev","Divide",2,3)
    cLowEv.cd(1)
    ana.H1("neutrino.E()",ROOT.TCut(),"HIST",Nbins,0,2000,"#nu energy","E#nu [GeV]","",1,1)

    # BINS in |p(p)|+|p(mu)|
    file = ROOT.TFile("~/Desktop/uBoone/SpecialAttention/Data/MCC6recEventsEv.root","recreate")
    PpPmuMin = [0   , 400 , 600 , 800  , 1000]
    PpPmuMax = [400 , 600 , 800 , 1000 , 3000]
    CutPpPmu = []
    h        = []
    for i in range(0,len(PpPmuMin)):
        CutPpPmu.append(ROOT.TCut("%f < protons[0].P()+muon.P() && protons[0].P()+muon.P() < %f"%(PpPmuMin[i],PpPmuMax[i])))
        cLowEv.cd(i+2)
        frac    = float(ana.GetEntries(CutPpPmu[i]))/ana.GetEntries()
        Nevents = int(frac * Nccqe)
        h.append(ana.H1("neutrino.E()",CutPpPmu[i],"HIST",Nbins,0,2000
                      ,"%.0f<p(p)+p(#mu)<%.0f MeV/c (%.1f%% ~ %d +/- %d events)"%(PpPmuMin[i],PpPmuMax[i],100.*frac,int(Nevents),int(ROOT.sqrt(Nevents)))
                      ,"E#nu [GeV]","",i+2,i+2))
        h[i].SetName("hEflux_%dPpPlusPmu%d"%(int(PpPmuMin[i]),int(PpPmuMax[i])))
        h[i].Scale(float(Nevents)/h[i].Integral())
        h[i].Write()
    cLowEv.Update()
    wait()
    cLowEv.SaveAs("~/Desktop/EvBins.pdf")
    file.Close()









