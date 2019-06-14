// The lengths of lines 1, 3, and 4 can be easily set in lines 41-46. Line 5 is actually 
// recalculated so dont worry about it. Line 6 is set to equal line 4. To set the position
// of the bump, you need to modify red, rad, h, and k. Modifying red will automatically 
// modify h and k as well as rad. Basically, red sets the size of the bubble, while 
// the position can be amnipulated using the lengths of lines 1 and 3. The equations for
// h and k can also be modified so that the bubble sits differently on the channel. The 
// current h and k equations were pretty much just a random set that I thought would work.
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
  //                             2  
  //             1               _         3
  //         ___________________( )____________________
  //        |                                          |
  //        |                                          |
  //        |                                          |
  // origin-|-  - - - - - - - - - - - - - - - - - - - -|- - -       setup with dimensionless groups is horizontal
  //    6   |                                          | 4
  //        |                                          |
  //        |__________________________________________|
  //
  //                            5               
  //
  //  
  //
int main()    
{
  //pick use custom assignment or literature assignment: for now use lit(=1), the other is unsupported
  double rad                          = 0;              //raduis of circle
  double red                          = 0;              //raduis of circle, position finder, not actual
  double h                            = 0;              //center x or y point
  double k                            = 0;              //center x or y point
  int defineDimensionlessLength       = 1;           // stipulated, does not change... defines everything in terms of the literature notation 
  double surf1Length                  = 5.;
  double surf2Length                  = 2.;
  double surf3Length                  = 20.;
  double surf4Length                  = 4.;
  double surf5Length                  = 10;
  double surf6Length                  = surf4Length;
  //
  int surf1divisions      = 100;
  int surf2divisions      = 1000;
  int surf3divisions      = 100;
  int surf4divisions      = 100;
  int surf5divisions      = 100;
  int surf6divisions      = 100;
  int nnodes              = surf1divisions+surf2divisions+surf3divisions+surf4divisions+surf5divisions+surf6divisions; 
  //
  int noElem                 = nnodes;
  string filename3           = "testTrap2D2.vtk";
  //
  double surf1Delta       = surf1Length / surf1divisions;
  double surf2Delta       = surf2Length / surf2divisions;
  double surf3Delta       = surf3Length / surf3divisions;
  double surf4Delta       = surf4Length / surf4divisions;
  double surf5Delta       = surf5Length / surf5divisions;
  double surf6Delta       = surf6Length / surf6divisions;
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
  double xCoord = 0.;                              //start at the origin
  double yCoord = 0.;                              //start at the origin
  double zCoord = 0.;                              //start at the origin  
  //
  double pi = 3.1415926535897932384626433;
  red = surf1Length/8;
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
  h   = xCoord + red / 2;                                     //defined center of circle x value
  k   = yCoord + red * 3 / 4;                                 //defined center of circle y value 
  rad = sqrt((h-xCoord)*(h-xCoord)+(k-yCoord)*(k-yCoord));
  double firstAngle   = 180/pi*atan2((yCoord-k),(xCoord-h));
  double totalDegrees = abs(360 + firstAngle + firstAngle + 180);
  double degreeChange = totalDegrees/surf2divisions;
  double currentAngle = firstAngle;
  for (int i=0;i<surf2divisions;++i)
    { 
      currentAngle = currentAngle - degreeChange  ;
      xCoord= h + rad * cos((currentAngle)*pi/180) ;
      yCoord= k + rad * sin((currentAngle)*pi/180) ;
      file3 << xCoord;
      file3 << " ";
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
  surf5Length = surf1Length + red + surf3Length;
  surf5Delta = surf5Length / surf5divisions;
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
      xCoord = xCoord;
      file3 << xCoord;
      file3 << " ";
      yCoord = yCoord + surf6Delta;
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
  //the last element is on surface 1 for some reason, just manually computed.
  file3 << 1;
  file3 << endl;
  //
  file3.close();
  //    
}





 
