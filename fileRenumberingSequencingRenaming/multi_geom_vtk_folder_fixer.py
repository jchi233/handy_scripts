#! /usr/bin/env python
#
# This script is to take a lot of similarly named files in a directory and renumber
# them. Say you have files numbered 1 to 60, but number 31 is missing. This routine
# will renumber all of them 1-59, keeping them in the same order. This works, even
# if most of the files are missing. You have to have somewhat of a structure to the
# file names, something like "basefile_name_here_0078.vtk". This can quickly be
# edited in the script though. It is set up for vkt files, but could be modified
# for any file type. It can also rename the files, which can be quickly edited. It
# only works properly if the only files in the directory are the ones that we want
# to edit, due to numbering implementation.
#==================================================================================
# This routine takes 3 arguments
# 1.) directory where these files reside, including the backslash
# 2.) base name of the files to be affected (basefile_name_here_)
# 3.) number of digits in the file numbering (4)
#
#==================================================================================
#          ----------------------- EDIT HISTORY----------------------
#  
#  Created and pushed by JCH, 6/14/19, jchi233@g.uky.edy 
#
#
#
#
#
#
#
#
#
import os
import sys
import numpy as np
from math import log
from numpy import loadtxt,zeros
import subprocess
import fileinput


filler = int(sys.argv[3])

# make sure the directory exists
exists = os.path.isdir(str(sys.argv[1]))
if not exists:
    print "Specified directory (argument 1) "+str(sys.argv[1])+" does not exist."
    sys.exit(1)
sys.stdout.flush()

# see how many documents are in the directory. 
docs = os.listdir(str(sys.argv[1]))
number_docs = len(docs)
print "There are "+str(number_docs)+" documents inside of "+str(sys.argv[1]) 

# see how many files are in the directory
onlyfiles = next(os.walk(str(sys.argv[1])))[2]
number_files = len(onlyfiles)
print "There are "+str(number_files)+" files inside of "+str(sys.argv[1]) 

# process info to pass/fail the check
if (number_docs == number_files):
    print "Passes check, the directory contains "+str(number_files)
else:
    print "Fails check, the directory has extra files that void the logic."
    sys.exit(1)

print "Using basefile name "+str(sys.argv[2])+" to get the files ordered."

#cycle through expected number of files to get a map.
print str(number_files)
j = 0
i = 0
mapp = np.zeros(number_files,dtype=int)
while (j<number_files):
    print "i"
    print str(i)
    exists = os.path.isfile(str(sys.argv[1])+"/"+str(sys.argv[2])+str(i).zfill(filler)+".vtk")
    if (exists):
        mapp[j] = i
        j = j+1
    else:
        #print "file does not exist for this i:"
        #print str(sys.argv[2])+str(i).zfill(filler)+".vtk"
    i=i+1

# set length so that we can remove the backslash
lenn = len(str(sys.argv[1])) -1

# check to see if the directory already exists. If it does, prompt that we will overwrite files, else, create it.
exists = os.path.isdir(str(sys.argv[1])[:lenn]+"_fixed")
if not exists:
    cmd = "mkdir "+str(sys.argv[1])[:lenn]+"_fixed"
    subprocess.call(cmd, shell=True)    
else:
    remove = input("Do you really want to remove "+str(sys.argv[1])+"_fixed? All data inside will be lost.(y/n).\n Any other response will just write the data into existing directory, if the files exist, they will be overwritten.")
    if(remove == "y"):
        cmd = "rm -r "+str(sys.argv[1])[:lenn]+"_fixed"
        subprocess.call(cmd, shell=True)    
        cmd = "mkdir "+str(sys.argv[1])[:lenn]+"_fixed"
        subprocess.call(cmd, shell=True)    
    elif(remove == "n"):
        sys.exit(1)

# mv the files to the new location, with a new name.
i = 0
while (i<number_files):
    cmd = "mv "+str(sys.argv[1])+"/"+str(sys.argv[2])+str(mapp[i]).zfill(filler)+".vtk "+str(sys.argv[1])[:lenn]+"_fixed/"+str(sys.argv[2])+"-"+str(i).zfill(filler)+".vtk"
    subprocess.call(cmd, shell=True)
    i=i+1

print "all files have been moved"
sys.exit()


