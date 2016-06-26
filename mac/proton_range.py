import sys
#from larlite import larlite as fmwk
import MyLArTools

lartools = MyLArTools()

lartools.Plot_proton_range_in_LAr("kinetic energy")
lartools.Plot_proton_range_in_LAr("momentum")