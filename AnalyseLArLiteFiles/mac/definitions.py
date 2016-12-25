# imports
# ---------------------------------------------------------------- #
import sys
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
sys.path.insert(0, '/uboone/app/users/ecohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
from larlite import larlite as fmwk
import input_flags , Initiation as init , my_tools as tools
flags = input_flags.get_args()




# paths
# ---------------------------------------------------------------- #
if flags.worker == 'erez':
    Path        = "/Users/erezcohen/Desktop/uBoone"
elif flags.worker == 'uboone':
    Path        = "/uboone/data/users/ecohen"

roi_map_path    = Path + "/AnalysisTreeData/CSVFiles"
rse_map_path    = Path + "/AnalysisTreeData/CSVFiles"
data_Path       = Path + "/DATA/" + flags.DataType + "_DATA"
ana_Path        = Path + "/analysis/AnaFiles/" + flags.DataType + "_ANA"
pass_GBDTs_path = Path + "/AnalysisTreesAna/PassedGBDTFiles"




# directory names
# ---------------------------------------------------------------- #

