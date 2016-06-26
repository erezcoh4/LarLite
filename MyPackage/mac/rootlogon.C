
{
    gROOT -> ProcessLine(".x /Users/erezcohen/Desktop/Software/rootlogon.C");
    float KThresholdArgoNeuT = 21; //[MeV]
    float EThresholdArgoNeuT = KThresholdArgoNeuT + 1000*Mp; // E = K + m [MeV/c]
    float pThresholdArgoNeuT = sqrt(EThresholdArgoNeuT*EThresholdArgoNeuT - 1000*Mp*1000*Mp) ; //[MeV/c]

    

    // look for CC events with only 2 protons in the final state
    TCut cutCC2p    = "Ntot == 3 && Nmu == 1 && Np == 2 && Prec.Mag()>1 && Pmiss.Mag()>1";
    TCut cutXb      = "(Xb>1.2)";
    TCut cutPmiss   = "(300<Pmiss.Mag() && Pmiss.Mag()<1000)";
    TCut cutThetaPQ = "ThetaPQ < 25";
    TCut cutPoverQ  = "(0.62<PoverQ && PoverQ<0.96)";
//    TCut SRCcut     = cutCC0pi && "Prec.Mag()>0";//&& cutXb && cutPmiss && cutThetaPQ && cutPoverQ ;

}
