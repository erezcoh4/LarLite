import ROOT
from ROOT import TPlots
from rootpy.interactive import wait
import time
ROOT.gStyle.SetOptStat(0000)


DoSpinBeforeAfter   = True


Path        = "/Users/erezcohen/larlite/UserDev/LarLite/MyPackage/mac"
FileName    = "CompleteRecEvents"
ana         = TPlots(Path + "/Ana_"+FileName+".root","EventsTree","complete reconstructed events")
Nbins       = 50



if DoSpinBeforeAfter :
    c = ana.CreateCanvas("c.m. momentum","Divide",3,3)
    c.cd(1)
    ana.H1("neutrino.E()",ROOT.TCut(),"HIST",Nbins,0,2000,"#nu energy","E#nu [GeV]","",1,46)
    c.cd(4)
    ana.H2("neutrino.E()","muon.P()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,2000,"","E#nu [GeV]","p(#mu) [GeV/c]")
    c.cd(5)
    ana.H2("neutrino.E()","TMath::RadToDeg()*muon.Theta()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,180,"","E#nu [GeV]","#theta(#mu) [GeV/c]")
    c.cd(6)
    ana.H2("neutrino.E()","TMath::RadToDeg()*muon.Phi()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,-180,180,"","E#nu [GeV]","#phi(#mu) [GeV/c]")
    c.cd(7)
    ana.H2("neutrino.E()","protons[0].P()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,2000,"","E#nu [GeV]","p(p) [GeV/c]")
    c.cd(8)
    ana.H2("neutrino.E()","TMath::RadToDeg()*protons[0].Theta()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,0,180,"","E#nu [GeV]","#theta(p) [GeV/c]")
    c.cd(9)
    ana.H2("neutrino.E()","TMath::RadToDeg()*protons[0].Phi()",ROOT.TCut(),"colz",Nbins,0,2000,Nbins,-180,180,"","E#nu [GeV]","#phi(p) [GeV/c]")
    c.Update()
    wait()

