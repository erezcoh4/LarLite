import ROOT
from ROOT import TPlots
from rootpy.interactive import wait
import time
ROOT.gStyle.SetOptStat(0000)


DoVarsDependingOnEv     = True
DoLowEv                 = True


Path        = "/Users/erezcohen/Desktop/uBoone/AnaFiles"
FileName    = "CompleteRecEvents"
ana         = TPlots(Path + "/Ana_"+FileName+".root","EventsTree","complete reconstructed events")
Nbins       = 50



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
    cLowEv = ana.CreateCanvas("low Ev")
    ana.H1("neutrino.E()",ROOT.TCut(),"HIST",Nbins,0,2000,"#nu energy","E#nu [GeV]","",1,1)
    CutLowEv = ROOT.TCut("protons[0].P() < 400")
    ana.H1("neutrino.E()",CutLowEv,"HIST same",Nbins,0,2000,"#nu energy","E#nu [GeV]","",2,2)
    CutLowEv = ROOT.TCut("protons[0].P()+muon.P() < 400")
    ana.H1("neutrino.E()",CutLowEv,"HIST same",Nbins,0,2000,"#nu energy","E#nu [GeV]","",3,3)
    CutLowEv = ROOT.TCut( "%s< 40" % ana.Theta("protons[0].Vect()","muon.Vect()") )
    ana.H1("neutrino.E()",CutLowEv,"HIST same",Nbins,0,2000,"#nu energy","E#nu [GeV]","",4,4)
    cLowEv.Update()
    wait()









