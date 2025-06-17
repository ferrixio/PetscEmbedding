# Create a localDefs.make file with the appropriate defines to find the
# libraries. Make sure PETSC_DIR, PETSC_ARCH and EIGEN_INCL are defined
# as environment variables or in the localDefs.make file.

include localDefs.make

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules

CFLAGS  = -g3
CXXFLAGS= -g3

SRCDIR = ../src
OBJS = gridLibrary.o MGLibrary.o
SRCDIR_OBJS := $(OBJS:%=${SRCDIR}/%)
HEADERS=$(SRCDIR_OBJS:.o=.hpp)


ghostMG: ghostMG.o $(OBJS) $(HEADERS)
	${CXXLINKER} -o $@ ghostMG.o $(OBJS) ${PETSC_DM_LIB} ${PETSC_SYS_LIB}

ghostMG.o: ${SRCDIR}/main.cpp $(HEADERS)
	${PETSC_CXXCOMPILE_SINGLE} -I${SRCDIR} -o $@ ${SRCDIR}/main.cpp

%.o: ${SRCDIR}/%.cpp ${SRCDIR}/%.hpp
	${PETSC_CXXCOMPILE_SINGLE} -o $@ ${SRCDIR}/$*.cpp


# clean output folder
folder:
	rm -r ${SRCDIR}/../output/*