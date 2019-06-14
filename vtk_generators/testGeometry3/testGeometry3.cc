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
//                                 3
//                             _________  
//             1           2  |  _______| 4,G4       
//                            | |    5
//                            | |6
//                            | |                7
//         ___________________| |____________________
//        |                   G1                     |
//        |                                          |
//        |                                          |
//        |                                          |      
//    10  |                                          | 8
//        |                                          |
//        |__________________________________________|
//
//                            9               
//
//  

int main()    
{
  //user input here:
  int computeSegment9        = 1;    //set this to 1 to autocompute segment 9. Otherwise, set it to anything else.
  //
  double surf1Length          = 5.;
  double surf2Length          = 2.; //must be equal to 6+4
  double surf3Length          = 3.; //must be larger than 5
  double surf4Length          = 1.;
  double surf5Length          = 1.;
  double surf6Length          = 1.;
  double surf7Length          = 5.;
  double surf8Length          = 2.;
  double surf9Length          = 10.;
  double surf10Length         = 10.;
  //to only establish the gaps and respective heights,use input below. Else, comment this out.   
  double G1Width              = 0.2;
  double G4Width              = 0.2;
  double G1Depth              = 1.;
  double G4Depth              = 1.;
  surf2Length = G1Depth;
  surf4Length = G4Width;
  surf6Length = surf2Length - G4Width;
  surf5Length = surf3Length - G1Width;
  //for symmetry, I have modified some below. comment this out if you don't want symmetry.
  //
  surf10Length = surf8Length;
  surf9Length  = surf1Length + surf7Length + surf3Length - surf5Length;
  surf10Length = surf8Length;
  //
  //depending on preference, you can specify the divisions of each segment here.
  //this is good for odd geometries, like circles, but no so much for straight lines.
  //surface forces are only ocmputed at each segment, so to have accurate surface forces,
  //you would want many divisions in the applicable segments.
  //
  int surf1divisions       = 10;
  int surf2divisions       = 10;
  int surf3divisions       = 2;
  int surf4divisions       = 10;
  int surf5divisions       = 10;
  int surf6divisions       = 2;
  int surf7divisions       = 10;
  int surf8divisions       = 10;
  int surf9divisions       = 2;
  int surf10divisions      = 2;
  int nnodes               = surf1divisions+surf2divisions+surf3divisions+surf4divisions+surf5divisions+surf6divisions+surf7divisions+surf8divisions+surf9divisions+surf10divisions;
  //
  // These are the angles from horizontal positive x-axis at the beginnning of each segment.
  double angle1            = 0.;
  double angle2            = 90.;
  double angle3            = 0.;
  double angle4            = -90.;
  double angle5            = 180.;
  double angle6            = -90.;
  double angle7            = 0.;
  double angle8            = -90.;
  double angle9            = 180.;
  double angle10           = 90.;
  //
  int noElem               = nnodes;
  string filename2         = "testGeometry3.vtk";
  //
  double surf1Delta        = surf1Length / surf1divisions;
  double surf2Delta        = surf2Length / surf2divisions;
  double surf3Delta        = surf3Length / surf3divisions;
  double surf4Delta        = surf4Length / surf4divisions;
  double surf5Delta        = surf5Length / surf5divisions;
  double surf6Delta        = surf6Length / surf6divisions;
  double surf7Delta        = surf7Length / surf7divisions;
  double surf8Delta        = surf8Length / surf8divisions;
  double surf9Delta        = surf9Length / surf9divisions;
  double surf10Delta       = surf10Length / surf10divisions;
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
  //Starting at the origin
  double xCoord = 0.;
  double yCoord = 0.;
  double zCoord = 0.;
  //
  double pi = 3.1415926535897932384626433;
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
  //if(xCoord < 0) cout << "Reconsider Inputs, xCoord < 1" << endl;;
  //if(yCoord > 0.000001) cout << "Reconsider Inputs, yCoord !=0, yCoord=" << yCoord <<endl;;
  //if(yCoord < -0.000001) cout << "Reconsider Inputs, yCoord !=0, yCoord=" << yCoord <<endl;;
  //double surf9Length = sqrt(xCoord*xCoord + yCoord*yCoord);
  //cout << "surf9Length= " << surf9Length << endl;;
  //double angle9 = atan2(xCoord,yCoord);
  //cout << "angl9= " << angle9 << "  in radians, measured from the positive x axis" <<endl;;
  //double surf9Delta=surf9Length / surf9divisions;
  //
  //Run nodes for Surface 9
  for (int i=0;i<surf9divisions;++i)
    { 
      xCoord = xCoord + surf9Delta * cos(pi*angle9/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf9Delta * sin(pi*angle9/180);
      file2 << yCoord;
      file2 << " ";
      file2 << zCoord;
      file2 << endl;
    }
  //Run nodes for Surface 10
  for (int i=0;i<surf10divisions;++i)
    { 
      xCoord = xCoord + surf10Delta * cos(pi*angle10/180);
      file2 << xCoord;
      file2 << " ";
      yCoord = yCoord + surf10Delta * sin(pi*angle10/180);
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
  //elements in(on) surface 10  
  for (int f=0;f<surf10divisions;++f) 
    {
      file2 << 10;
      file2 << endl;
    }
  //the last element is on surface 1 for some reason, just manually computed.
  file2 << 1;
  file2 << endl;
  //
  file2.close();
  //
}
