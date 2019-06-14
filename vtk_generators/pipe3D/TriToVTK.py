#!/usr/bin/env python
#  This converts an ascii tri file to a vtk file

import sys
import os
from pylab import *

print "This script converts a tri file to a vtk"
print "Input  i.tri file = " + sys.argv[1]
print "Output vtk   file = " + sys.argv[2]

tri_in  = open(sys.argv[1],'r')
tri_out = open(sys.argv[2],'w')


#Process header
string = tri_in.readline()
nverts = int(string.split()[0])
nfaces = int(string.split()[1])
print "nverts = " + str(nverts)
print "nfaces = " + str(nfaces)

#write header info
tri_out.write("# vtk DataFile Version 3.0\n")
tri_out.write("vtk output\n")
tri_out.write("ASCII\n")
tri_out.write("DATASET POLYDATA\n")
tri_out.write("POINTS ")
tri_out.write(str(nverts))
tri_out.write(" float\n")

#process verts
for ivert in range(0,nverts):
    string = tri_in.readline()
    tri_out.write(string)
    
#write the connectivity data
tri_out.write("POLYGONS "+str(nfaces)+" "+str(nfaces*4)+"\n")

#process faces (three verts)
for iface in range(0,nfaces):
    string = tri_in.readline()
    face0 = int(string.split()[0])-1#-1 because faces in vtk are zero based
    face1 = int(string.split()[1])-1
    face2 = int(string.split()[2])-1
    tri_out.write("3 " + str(face0) + " " + str(face1) + " " + str(face2) + "\n")

#write the connectivity data
tri_out.write("CELL_DATA "+str(nfaces)+"\n")
tri_out.write("SCALARS Components int\n")
tri_out.write("LOOKUP_TABLE default\n")

#get the components at each face, and write it to vtk file
for iface in range(0,nfaces):
    string = tri_in.readline()
    tri_out.write(string)
