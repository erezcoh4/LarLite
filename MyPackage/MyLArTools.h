/**
 * \file MyLArTools.h
 *
 * \ingroup MyPackage
 *
 * \brief Class def header for a class MyLArTools
 *
 * @author erezcohen
 */

/** \addtogroup MyPackage
 
 @{*/
#ifndef MYLARTOOLS_H
#define MYLARTOOLS_H

#include <iostream>
//#include "MySoftwarePackage/TPlots.h"
#include "TGraph.h"
#include "TSpline.h"
#include "TCanvas.h"

using namespace std;
/**
 \class MyLArTools
 User defined class MyLArTools ... these comments are used to generate
 doxygen documentation!
 */
class MyLArTools{
    
public:

    double E;
    
//    TPlots plot;
    
    
    
    /// Default constructor
    MyLArTools();
    
    /// Default destructor
    ~MyLArTools(){}
    
    TGraph *KE_vs_range_proton , *p_vs_range_proton;
    TSpline3 *KE_vs_range_proton_s3 , *p_vs_range_proton_s3;
    TGraph *KE_vs_range_muon , *p_vs_range_muon;
    TSpline3 *KE_vs_range_muon_s3 , *p_vs_range_muon_s3;
    
    TCanvas * Plot_proton_range_in_LAr (TString type = "kinetic energy");
    
    double Get_protonMomentumFromRange ( float range );
    double   Get_muonMomentumFromRange ( float range );

};

#endif
/** @} */ // end of doxygen group

