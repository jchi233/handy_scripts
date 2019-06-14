// YOU PROBABLY DONT WANT TO EDIT THIS TOO MUCH WITHOUT CONSULTING JCH. AS OF 12/9/18
// THE USER SHOULD ONLY CHANGE THE VALUES OF STENOSISDEGREE AND LAMBDAOR, WHICH ARE IN
// LINES 34 AND 35 CURRENTLY. THE GOAL IS TO USE CORRECT PARAMETERS FROM "THREE 
// DIMENSIONAL INSTABILITIES AND TRANSITION OF STEADY AND PULSATILE AXISYMMETRIC 
// STENOTIC FLOWS" BY SHERWIN AND BLACKBURN.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <iomanip>
#include <cmath>
using namespace std;
//  
//
//             1       2                3
//         __________     ___________________________
//        |          \   /                           |
//        |           \_/                            |
//        |                                          |
// origin-|-  - - - - - - - - - - - - - - - - - - - -|- - -       setup with dimensionless groups is horizontal
//    8   |            _                             | 4
//        |           / \                            |
//        |__________/   \___________________________|
//
//             7       6               5               
//
int main()    
{
  // ONLY THE FIRST 3 VARIABLES SHOULD BE MODIFIED. PROBABLY ONLY 2 AND 3, ACTUALLY THOUGH.. 
  double D                               = 1.0;         // stipulated, gives the diameter of the artery
  double stenosisDegree                  = 0.75;        // stipulated, gives the diameter of the stenosis
  double lambdaOR                        = 8.0;         // used to calculate lambda
  //
  double dimSurf1Length         = 10.5;
  double dimSurf2Length         = 4.;
  double dimSurf3Length         = 50. - dimSurf1Length - dimSurf2Length;
  double dimSurf4Length         = D;
  double dimSurf5Length         = dimSurf3Length;
  double dimSurf6Length         = dimSurf2Length;
  double dimSurf7Length         = dimSurf1Length;
  double dimSurf8Length         = dimSurf4Length;
  //
  int surf1divisions      = 1000;
  int surf2divisions      = 1000;
  int surf3divisions      = 1000;
  int surf4divisions      = 1000;
  int surf5divisions      = 1000;
  int surf6divisions      = 1000;
  int surf7divisions      = 1000;
  int surf8divisions      = 1000;
  int nnodes              = surf1divisions+surf2divisions+surf3divisions+surf4divisions+surf5divisions+surf6divisions+surf7divisions+surf8divisions;
  //
  int noElem                 = nnodes;
  //string filename            = "circle_1200.vtk";
  //string filename2           = "arteryBifurcation.vtk";
  string filename3           = "arteryStenosis_L8_S75.vtk";
  //
  double surf1Delta       = dimSurf1Length / surf1divisions;
  double surf2Delta       = dimSurf2Length / surf2divisions;
  double surf3Delta       = dimSurf3Length / surf3divisions;
  double surf4Delta       = dimSurf4Length / surf4divisions;
  double surf5Delta       = dimSurf5Length / surf5divisions;
  double surf6Delta       = dimSurf6Length / surf6divisions;
  double surf7Delta       = dimSurf7Length / surf7divisions;
  double surf8Delta       = dimSurf8Length / surf8divisions;
  //
  double z                               = 0.0;         // this is the local location distance in the stenosis
  double lambda                          = 0.0;         // calculated
  double stenosisLength                  = 0.0;         // stipulated lambda over R
  double Dmin                            = 0.0;         // calculated from stenosisDegree
  //                                          FOR VISIT
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //assign file
  ofstream file3;
  file3.open(filename3);
  if(file3.fail()) cout << "Bad file in writeTriangulation function" << endl;;
  file3.precision(10);
  file3.setf(ios::fixed);
  file3.setf(ios::showpoint);
  //
  file3 << "# ";
  file3 << "vtk ";
  file3 << "DataFile ";
  file3 << "Version ";
  file3 << "3.0";
  file3 << endl;
  file3 << "vtk ";
  file3 << "output";
  file3 << endl;
  file3 << "ASCII";
  file3 << endl;
  file3 << "DATASET ";
  file3 << "POLYDATA ";
  file3 << endl;
  file3 << "POINTS ";
  file3 << nnodes;
  file3 << " float";
  file3 << endl;
  // 
  double xCoord = 0.;                      //start at the origin
  double yCoord = 0.;                      //start at the origin
  double zCoord = 0.;                      //start at the origin  
  //
  lambda = lambdaOR * (D/2) ; 
  stenosisLength = lambda * (D/2);         //stenosis length to diameter ratio  
  //cout << "stenosis length 4 or 8 = " << lambdaOR << endl;;
  //cout << "stenosis length  = " << stenosisLength << endl;;
  //cout << "sec 1 length  = " << dimSurf1Length << endl;;
  //cout << "sec 2 length  = " << dimSurf2Length << endl;;
  //cout << "sec 3 length  = " << dimSurf3Length << endl;;
  //cout << "sec 4 length  = " << dimSurf4Length << endl;;
  dimSurf2Length=stenosisLength;
  dimSurf6Length=stenosisLength;
  surf2Delta = dimSurf2Length / surf2divisions;
  surf6Delta = dimSurf6Length / surf6divisions;
  double L = dimSurf2Length;
  yCoord = D / 2;                                //place the origin axisymmetric
  Dmin = D * (sqrt(1 - stenosisDegree));         //stenosis min diameter
  //
  double pi = 3.1415926535897932384626433;
  //writing nodal locations
  //Run nodes for Surface 1
  for (int i=0;i<surf1divisions;++i)
    { 
      xCoord = xCoord + surf1Delta;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord;
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 2
  for (int i=0;i<surf2divisions;++i)
    { 
      xCoord = xCoord + surf2Delta;
      z = xCoord - dimSurf1Length - (dimSurf2Length/2);
      file3 << xCoord;
      file3 << " ";
      yCoord = 0;
      yCoord = 0.5*Dmin+0.5*(D-Dmin)*((sin(pi*(z/L)))*(sin(pi*(z/L))));
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 3
  for (int i=0;i<surf3divisions;++i)
    { 
      xCoord = xCoord + surf3Delta;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord;
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 4
  for (int i=0;i<surf4divisions;++i)
    { 
      xCoord = xCoord;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord - surf4Delta;
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 5
  for (int i=0;i<surf5divisions;++i)
    { 
      xCoord = xCoord - surf5Delta;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord;
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 6
  for (int i=0;i<surf6divisions;++i)
    {
      xCoord = xCoord - surf6Delta;
      z = xCoord - dimSurf1Length - (dimSurf2Length/2);
      file3 << xCoord;
      file3 << " ";
      yCoord = 0;
      yCoord = -0.5*Dmin-0.5*(D-Dmin)*((sin(pi*(z/L)))*(sin(pi*(z/L))));  
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 7
  for (int i=0;i<surf7divisions;++i)
    { 
      xCoord = xCoord - surf7Delta;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord;
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //Run nodes for Surface 8
  for (int i=0;i<surf8divisions;++i)
    { 
      xCoord = xCoord;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord + surf8Delta;
      file3 << yCoord;
      file3 << " ";
      file3 << zCoord;
      file3 << endl;
    }
  //
  int idata = 2;
  //write segment(element) connectivity
  file3 << "LINES "; 
  file3 << noElem;
  file3 << " ";  
  file3 << noElem*3;
  file3 << endl;    
  //
  for (int i=0;i<nnodes-1;++i)  
    {
      //
      file3 << idata;
      file3 << " ";
      file3 << i;
      file3 << " ";
      file3 << i+1;
      file3 << endl;
      //
    }
  //
  file3 << idata;
  file3 << " ";
  file3 << noElem-1;
  file3 << " ";
  file3 << 0;
  file3 << endl;
  //
  file3 << "CELL_DATA ";
  file3 << noElem;
  file3 << endl;
  file3 << "SCALARS ";
  file3 << "Components ";
  file3 << "int";
  file3 << endl;
  file3 << "LOOKUP_TABLE ";
  file3 << "default";
  file3 << endl;
  //stipulate which elements(segments) are on each surface 
  //elements in(on) surface 1
  for (int f=0;f<surf1divisions-1;++f) 
    {
      file3 << 1;
      file3 << endl;
    }
  //elements in(on) surface 2
  for (int f=0;f<surf2divisions;++f) 
    {                          
      file3 << 2;              
      file3 << endl;           
    }                          
  //elements in(on) surface 3  
  for (int f=0;f<surf3divisions;++f) 
    {                          
      file3 << 3;              
      file3 << endl;          
    }                          
  //elements in(on) surface 4  
  for (int f=0;f<surf4divisions;++f) 
    {                          
      file3 << 4;              
      file3 << endl;           
    }                          
  //elements in(on) surface 5  
  for (int f=0;f<surf5divisions;++f) 
    {                          
      file3 << 5;              
      file3 << endl;           
    }                          
  //elements in(on) surface 6  
  for (int f=0;f<surf6divisions;++f) 
    {                          
      file3 << 6;             
      file3 << endl;           
    }                          
  //elements in(on) surface 7  
  for (int f=0;f<surf7divisions;++f) 
    {                         
      file3 << 7;              
      file3 << endl;           
    }                          
  //elements in(on) surface 8  
  for (int f=0;f<surf8divisions;++f) 
    {                          
      file3 << 8;              
      file3 << endl;           
    }                          
  //the last element is on surface 1 for some reason, just manually computed.
  file3 << 1;
  file3 << endl;
  //
  file3.close();
  //    
}


























 
