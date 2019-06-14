#
# compile with -r8 or set MPI_DOUBLE to MPI_FLOAT
#
EXECUTABLE = artGen.x
#

FLAGS = -O0 -std=c++11 -g -cpp -w 
#-fcheck=all -fbacktrace  -fbounds-check  -fdefault-real-8 -fdefault-double-8
FCOMPL = mpic++ 
LIBS   =  
#
.SUFFIXES: .cc
.cc.o:
	$(FCOMPL) -c $(FLAGS) $< 
#
FOBJECTS = artGen.o
#
OBJECTS = $(FOBJECTS) $(COBJECTS)
#
APPLIC:	$(OBJECTS)
	$(FCOMPL) $(FLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)
#
clean:
	rm -f $(OBJECTS)

#
