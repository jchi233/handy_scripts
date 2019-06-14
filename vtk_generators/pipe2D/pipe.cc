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
// The general pipe shape is shown below with the original settings. Each segment can have a stipulated length and angle. The anlges 
// can be quickly adjusted so that the flow goes at any angle. In principle, just adjust "pipe_angle" variable, which adjusts the
// angle of all of the walls so that they remain perpendicular. This "pipe_angle" variable adjusts from the positive x-axis, 
// counterclockwise. Additionally, in the case with flow toward the positive x-axis, 1 is the inflow, while 3 is set as the ouflow. 
// NOTE: The atan2 function(near line 238) has not been exhaustively tested and may or may not be robust.
//                            
//                            2                                                                                                
//                ___________________________                                                                                                            
//               |                           |                                                                   
//            1  |                           | 3                                                                       
//               |___________________________|                                                                    
//                             4                                                                                  
//                                                                                                                                                                                                             
//                                                                                                           
int main()    
{
  double pi = 3.1415926535897932384626433;
  //user input here
  double pipe_angle          = 0.0;
  //
  double surf1Length         = 1.;
  double surf2Length         = 3.*pi;
  double surf3Length         = surf1Length;
  double surf4Length         = surf2Length;
  //
  int surf1divisions      = 10;
  int surf2divisions      = 10;
  int surf3divisions      = 2;
  int surf4divisions      = 10;
  int nnodes              = surf1divisions+surf2divisions+surf3divisions+surf4divisions;
  //
  //If symmetric, 1=-3, 2=-4
  // 
  double angle1              = 90. + pipe_angle;
  double angle2              = 0. + pipe_angle;
  double angle3              = -90. + pipe_angle;
  double angle4              = 180. + pipe_angle;
  //
  int noElem                 = nnodes;
  string filename            = "pipe_00deg_3pi.vtk";
  //
  double surf1Delta       = surf1Length / surf1divisions;
  double surf2Delta       = surf2Length / surf2divisions;
  double surf3Delta       = surf3Length / surf3divisions;
  double surf4Delta       = surf4Length / surf4divisions;
  //                                          FOR VISIT
  //////////////////////////////////////////////////////////////////////////////////////////////
  //assign file
  ofstream file2;
  file2.open(filename);
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
  // Starting position 
  double xCoord = 0.;
  double yCoord = 0.;
  double zCoord = 0.;
  xCoord = -(surf1Length*cos(pi*angle1/180))/2 ; 
  yCoord = -(surf1Length*sin(pi*angle1/180))/2 ; 
  //
  //writing nodal locations
  //Run nodes for Surface 1
  //
  //WRITE A COUT COMMAND HERE AND AFTER SURFACE 1 AND THEN DETERMINE WHERE THE CENTER IS FOR THE INFLOW CONDITION AND SET THIS POSITION IN THE USER FILE.
  //
  //cout << "start x position " << xCoord << endl;;
  //cout << "start y position " << yCoord << endl;;
  //double differencex = xCoord;  
  //double differencey = yCoord;
  //
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
  //
  //cout << "end x position " << xCoord << endl;;
  //cout << "end y position " << yCoord << endl;;
  //differencex = xCoord - differencex;
  //differencey = yCoord - differencey;
  //cout << "differencex " << differencex/2 << endl;;
  //cout << "differencey " << differencey/2 << endl;;
  //
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
  //the last element is on surface 1 for some reason, just manually computed.
  file2 << 1;
  file2 << endl;
  //
  file2.close();
  //
}
