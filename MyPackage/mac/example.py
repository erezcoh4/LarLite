import sys
from ROOT import gSystem
gSystem.Load("libMyRepo_MyPackage")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing MyPackage..."

sys.exit(0)

