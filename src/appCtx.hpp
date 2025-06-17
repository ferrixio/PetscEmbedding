#ifndef appCtx
#define appCtx

#include <petscsys.h>
#include <petscdm.h>
#include <petscdmda.h>
#include <petscvec.h>
#include <iostream>
#include <vector>

typedef struct {
    PetscInt cpuRank;                   // processor used
    DM dmdaGrid;                        // id to the current DM
    DM coordDM;                         // id to the coordinate DM
    PetscInt nPoints[2];                // no. of points of the grid
    PetscScalar dx[2];                  // cell size
    PetscInt start[2], end[2];          // indexes of grid points
    PetscInt len[2];                    // length of grid

    PetscScalar bboxMin[2] = {-1., 1.};
    PetscScalar bboxMax[2] = {-1., 1.};

    Vec v;

    std::vector<std::string> collector;

    PetscRandom rng;                    // rng on this process

    // DEBUG MODE
    PetscBool debug = PETSC_FALSE;
} AppCtx;


#endif