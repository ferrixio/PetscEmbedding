#ifndef library
#define library

#include "appCtx.hpp"
#include <fstream>

PetscErrorCode ReadTerminal(AppCtx& ctx);
PetscErrorCode CreateRandomVector(AppCtx& ctx, PetscInt iter);
PetscErrorCode Export(AppCtx& ctx);

#endif