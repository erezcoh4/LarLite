import ROOT, os, sys , math
from ROOT import TPlots
from rootpy.interactive import wait
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import GeneralPlot as gen_plot
import Initiation as init
init.createnewdir()
ROOT.gStyle.SetOptStat(0000)



Operation   = "Draw" # "Draw" # "ADC around corners" #
Var         = sys.argv[1] if len(sys.argv)>1 else "straight_vs_segmented_track_length"
cut         = ROOT.TCut()
Path        = "/Users/erezcohen/Desktop/uBoone/AnaFiles"
Filename    = "Ana_larlite_95_wire_pandoraNu_4519_evts.root"#"Ana_larlite_95_wire_pandoraNu_543_evts.root"
ana         = TPlots(Path+"/"+Filename , "TracksTree","",False)


# ------------------------------------------------------------------ #
if Operation == "Draw":


    if (Var=="straight_track_length"):
        plot_args = [Var , cut , 100 , 0 , 80 , "track length [cm]"]


    if (Var=="momentum"):
        plot_args = [Var , cut , 40 , 150 , 700 , "proton momentum [MeV/c]"]

    if (Var=="N_neighboring_tracks"):
        plot_args = [Var , cut , 80 , -1 , 7 , "number of neighboring tracks (closer than 5 cm)"]
    
    if (Var=="Angle_close_track"):
        plot_args = [Var , cut , 30 , 0 , 180 , "respective angle with neighboring tracks [deg.]"]

    

    if (Var=="straight_vs_segmented_track_length"):
        plot_args = ["straight_track_length" , "segmented_track_length" , cut , 100 , 0 , 80 , 100 , 0 , 80 , "straight track length [cm]" , "segmented track length [cm]"]

    gen_plot.plot(ana,"BDTcandidates_"+Var,plot_args)
# ------------------------------------------------------------------ #



# ------------------------------------------------------------------ #
elif Operation == "ADC around corners":
    
    c = ana.CreateCanvas(Operation,"DivideSquare")
    i = 0
    for corner in "lt","rt","lb","rb":
        c.cd(i+1)
#        h = ana.H1("1./ADC_ratio_around_%s"%corner,ROOT.TCut("fabs(SumADC_around_%s) > 1"%corner)
#                   ,"hist" , 30 , -0.1 , 1.1
#                   , "" , "ADC(avg.) around %s corner in direction of track / ADC(avg.) around %s corner"%(corner,corner))
        h = ana.H2("fabs(SumADC_around_%s)"%corner,"1./ADC_ratio_around_%s"%corner,ROOT.TCut("fabs(SumADC_around_%s) > 1"%corner)
                    ,"colz" , 100 , 0 , 2000 , 30 , -0.1 , 1.1
                    , ""
                   , "accumulated ADC around %s corner [a.u.]"%corner
                   , "ADC(avg.) in track direction / ADC(avg.) ")
        ana.Text(0.2 , 0.8*h.GetMaximum() , "(%s corner)"%corner )
        i = i+1

    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/BDTcandidates_ADC_around_corners.pdf")















