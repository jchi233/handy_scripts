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
//The general bifurcation shape is shown below with the original settings. Each segment can have a stipulated length and angle. 
//Basic geometry can give an idea of where the final figure will be. There is a calculation setup for component 9, which calculates 
//the neccessary angle and length to close the geometry. This is handy, but can be quickly commented out be setting the variable
//"computeSegment9" to 0 if need be. The anlges can be quickly adjusted so that the flow goes left to right. In principle, just 
//subracting 90 degrees from all angles will do the trick. Additionally, it should be obvious that 9 is the inflow, while 3 and 6
//are set as the ouflows. It may be worth noting that each of the angles is stipulated from the positive x axis. The atan2 
//function(near line 238) that computes length and angle for segment 9 has not been exhaustively tested and may or may not be robust.
//
//
//
//                       3                    6
//                    ______                _____
//                    \     \              /    /
//                     \     \            /    /
//                      \     \ 4      5 /    /
//                       \     \        /    /
//                        \     \      /    /
//                         \     \    /    /  7
//                       2  \     \  /    /
//                           \     \/    /
//                            \         /
//                             \       /
//                              \     /
//                              |     |
//                              |     |
//                              |     |
//                              |     |
//                          1   |     |  8
//                              |     |
//                              |     |
//                              |_____|
//                                
//                                 9
//
int main()    
{
  //user input here:
  int computeSegment9        = 1;    //set this to 1 to autocompute segment 9. Otherwise, set it to anything else.
  //
  double surf1Length         = 10.;
  double surf2Length         = 10.;
  double surf3Length         = 1.;
  double surf4Length         = 10.;
  double surf5Length         = 10.;
  double surf6Length         = 1.;
  double surf7Length         = 10.;
  double surf8Length         = 10.;
  if(computeSegment9!=1)  double surf9Length         = 1;;
  //
  int surf1divisions      = 10;
  int surf2divisions      = 10;
  int surf3divisions      = 2;
  int surf4divisions      = 10;
  int surf5divisions      = 10;
  int surf6divisions      = 2;
  int surf7divisions      = 10;
  int surf8divisions      = 10;
  int surf9divisions      = 2;
  int nnodes              = surf1divisions+surf2divisions+surf3divisions+surf4divisions+surf5divisions+surf6divisions+surf7divisions+surf8divisions+surf9divisions;
  //
  //If symmetric, 1=-8, 2=-7, 3=-6, 4=-5,
  // 
  double angle1              = 90.;
  double angle2              = 135.;
  double angle3              = 45.;
  double angle4              = -45.;
  double angle5              = 45.;
  double angle6              = -45.;
  double angle7              = -135.;
  double angle8              = -90.;
  //double angle9              = -180;
  //
  int noElem                 = nnodes;
  string filename            = "circle_1200.vtk";
  string filename2           = "bifurcation2D.vtk";
  //
  double surf1Delta       = surf1Length / surf1divisions;
  double surf2Delta       = surf2Length / surf2divisions;
  double surf3Delta       = surf3Length / surf3divisions;
  double surf4Delta       = surf4Length / surf4divisions;
  double surf5Delta       = surf5Length / surf5divisions;
  double surf6Delta       = surf6Length / surf6divisions;
  double surf7Delta       = surf7Length / surf7divisions;
  double surf8Delta       = surf8Length / surf8divisions;
  //double surf9Delta       = surf9Length / surf9divisions;
  //                                          FOR VISIT
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////
  //assign file
  ofstream file2;
  file2.open(filename2);
  if(file2.fail()) cout << "Bad file in writeTriangulation function" << endl;;
  file2.precision(10);
  file2.setf(ios::fixed);
  file2.setf(ios::showpoint);
  //
  file2 << "# ";
  file2 << "vtk ";
  file2 << "DataFile ";
  file2 << "Version ";
  file2 << "3.0";
  file2 << endl;
  file2 << "vtk ";
  file2 << "output";
  file2 << endl;
  file2 << "ASCII";
  file2 << endl;
  file2 << "DATASET ";
  file2 << "POLYDATA ";
  file2 << endl;
  file2 << "POINTS ";
  file2 << nnodes;
  file2 << " float";
  file2 << endl;
  // 
  double xCoord = 0.;
  double yCoord = 0.;
  double zCoord = 0.;
  double pi = 3.1415926535897932384626433;
  xCoord = -(surf3Length*cos(pi*angle3/180)+surf6Length*cos(pi*angle6/180))/2;
  cout << "start x coord= " << xCoord << endl;;
  //
  //writing nodal locations
  //Run nodes for Surface 1
  for (int i=0;i<surf1divisions;++i)
    { 
      xCoord = xCoord + surf1Delta * cos(pi*angle1/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf1Delta  * sin(pi*angle1/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 2
  for (int i=0;i<surf2divisions;++i)
    { 
      xCoord = xCoord + surf2Delta * cos(pi*angle2/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf2Delta * sin(pi*angle2/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 3
  for (int i=0;i<surf3divisions;++i)
    { 
      xCoord = xCoord + surf3Delta * cos(pi*angle3/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf3Delta * sin(pi*angle3/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 4
  for (int i=0;i<surf4divisions;++i)
    { 
      xCoord = xCoord + surf4Delta * cos(pi*angle4/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf4Delta * sin(pi*angle4/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 5
  for (int i=0;i<surf5divisions;++i)
    { 
      xCoord = xCoord + surf5Delta * cos(pi*angle5/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf5Delta * sin(pi*angle5/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 6
  for (int i=0;i<surf6divisions;++i)
    {
      xCoord = xCoord + surf6Delta * cos(pi*angle6/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf6Delta * sin(pi*angle6/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 7
  for (int i=0;i<surf7divisions;++i)
    { 
      xCoord = xCoord + surf7Delta * cos(pi*angle7/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf7Delta * sin(pi*angle7/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 8
  for (int i=0;i<surf8divisions;++i)
    { 
      xCoord = xCoord + surf8Delta * cos(pi*angle8/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf8Delta * sin(pi*angle8/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Compute Length and Angle for Segment 9
  
  if(xCoord < 0) cout << "Reconsider Inputs, xCoord < 1" << endl;;
  if(yCoord > 0.000001) cout << "Reconsider Inputs, yCoord !=0, yCoord=" << yCoord <<endl;;
  if(yCoord < -0.000001) cout << "Reconsider Inputs, yCoord !=0, yCoord=" << yCoord <<endl;;
  double surf9Length = 2*sqrt(xCoord*xCoord + yCoord*yCoord);
  cout << "surf9Length= " << surf9Length << endl;;
  double angle9 = atan2(xCoord,yCoord);
  cout << "angl9= " << angle9 << "  in radians, measured from the positive x axis" <<endl;;
  double surf9Delta=surf9Length / surf9divisions;
  //
  //Run nodes for Surface 9
  for (int i=0;i<surf9divisions;++i)
    { 
      xCoord = xCoord + surf9Delta * sin(angle9-pi);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf9Delta * cos(angle9-pi);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //
  int idata = 2;
  //write segment(element) connectivity
  file2 << "LINES "; 
  file2 << noElem;
  file2 << " ";  
  file2 << noElem*3;
  file2 << endl;    
  //
  for (int i=0;i<nnodes-1;++i)  
    {
      //
      file2 << idata;
      file2 << " ";
      file2 << i;
      file2 << " ";
      file2 << i+1;
      file2 << endl;
      //
    }
  //
  file2 << idata;
  file2 << " ";
  file2 << noElem-1;
  file2 << " ";
  file2 << 0;
  file2 << endl;
  //
  file2 << "CELL_DATA ";
  file2 << noElem;
  file2 << endl;
  file2 << "SCALARS ";
  file2 << "Components ";
  file2 << "int";
  file2 << endl;
  file2 << "LOOKUP_TABLE ";
  file2 << "default";
  file2 << endl;
  //stipulate which elements(segments) are on each surface 
  //elements in(on) surface 1
  for (int f=0;f<surf1divisions-1;++f) 
    {
      file2 << 1;
      file2 << endl;
    }
  //elements in(on) surface 2
  for (int f=0;f<surf2divisions;++f) 
    {                          
      file2 << 2;              
      file2 << endl;           
    }                          
  //elements in(on) surface 3  
  for (int f=0;f<surf3divisions;++f) 
    {                          
      file2 << 3;              
      file2 << endl;          
    }                          
  //elements in(on) surface 4  
  for (int f=0;f<surf4divisions;++f) 
    {                          
      file2 << 4;              
      file2 << endl;           
    }                          
  //elements in(on) surface 5  
  for (int f=0;f<surf5divisions;++f) 
    {                          
      file2 << 5;              
      file2 << endl;           
    }                          
  //elements in(on) surface 6  
  for (int f=0;f<surf6divisions;++f) 
    {                          
      file2 << 6;             
      file2 << endl;           
    }                          
  //elements in(on) surface 7  
  for (int f=0;f<surf7divisions;++f) 
    {                         
      file2 << 7;              
      file2 << endl;           
    }                          
  //elements in(on) surface 8  
  for (int f=0;f<surf8divisions;++f) 
    {                          
      file2 << 8;              
      file2 << endl;           
    }                          
  //elements in(on) surface 9  
  for (int f=0;f<surf9divisions;++f) 
    {
      file2 << 9;
      file2 << endl;
    }
  //the last element is on surface 1 for some reason, just manually computed.
  file2 << 1;
  file2 << endl;
  //
  file2.close();
  //
}
