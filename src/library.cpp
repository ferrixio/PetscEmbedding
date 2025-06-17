#include "library.hpp"

/* Read the terminal and gets the parameters for the grid and the methods */
PetscErrorCode ReadTerminal(AppCtx& ctx){
    PetscFunctionBegin;

    PetscBool isGiven = PETSC_FALSE;    // boolean used for mandatory data
    PetscInt dim = 2;

    // Get the number of points
    PetscCall(PetscOptionsGetIntArray(NULL, NULL, "-N", ctx.nPoints, &dim, &isGiven));
    PetscCheck(isGiven, PETSC_COMM_WORLD, PETSC_ERR_USER_INPUT, "Usage: -N N_x,N_y");
    PetscCall(PetscPrintf(PETSC_COMM_WORLD, " N points used: %d, %d\n", ctx.nPoints[0], ctx.nPoints[1]));

    // Get the box boundary
    PetscCall(PetscOptionsGetScalarArray(NULL, NULL, "-bboxmin", ctx.bboxMin, &dim, NULL));
    PetscCall(PetscPrintf(PETSC_COMM_WORLD, " BboxMin: %f, %f\n", ctx.bboxMin[0], ctx.bboxMin[1]));

    PetscCall(PetscOptionsGetScalarArray(NULL, NULL, "-bboxmax", ctx.bboxMax, &dim, NULL));
    PetscCall(PetscPrintf(PETSC_COMM_WORLD, " BboxMax: %f, %f\n", ctx.bboxMax[0], ctx.bboxMax[1]));

    // Get the debug mode
    PetscBool _debug = PETSC_FALSE;
    PetscCall(PetscOptionsGetBool(NULL, NULL, "-debug", &_debug, NULL));
    PetscCall(PetscPrintf(PETSC_COMM_WORLD, " debug mode: %d\n", _debug));

    // create the grid
    PetscCall(DMDACreate2d(PETSC_COMM_WORLD, DM_BOUNDARY_NONE, DM_BOUNDARY_NONE, DMDA_STENCIL_BOX, ctx.nPoints[0], ctx.nPoints[1], PETSC_DECIDE, PETSC_DECIDE, 1, 4, NULL, NULL, &ctx.dmdaGrid));
    PetscCall(DMSetFromOptions(ctx.dmdaGrid));
    PetscCall(DMSetUp(ctx.dmdaGrid));
    PetscCall(DMDASetUniformCoordinates(ctx.dmdaGrid, ctx.bboxMin[0], ctx.bboxMax[0], ctx.bboxMin[1], ctx.bboxMax[1], 0, 0));
    PetscCall(DMGetCoordinateDM(ctx.dmdaGrid, &ctx.coordDM));

    PetscCall(DMView(ctx.dmdaGrid, PETSC_VIEWER_STDOUT_WORLD));

    PetscCall(DMDAGetCorners(ctx.dmdaGrid, &ctx.start[0], &ctx.start[1], NULL, &ctx.len[0], &ctx.len[1], NULL));
    for (PetscInt i = 0; i < dim; i++)
    {
        ctx.dx[i] = (ctx.bboxMax[i]-ctx.bboxMin[i])/ctx.nPoints[i];
        ctx.end[i] = ctx.start[i] + ctx.len[i];
    }

    // Get the MPI rank
    PetscCall(MPI_Comm_size(PETSC_COMM_WORLD, &ctx.cpuRank));

    // Create the random number generator
    PetscCall(PetscRandomCreate(PETSC_COMM_WORLD, &ctx.rng));
    PetscRandomSetType(ctx.rng, PETSCRAND);

    // Create the random vector
    PetscCall(DMCreateLocalVector(ctx.dmdaGrid, &ctx.v));
    PetscCall(VecSetFromOptions(ctx.v));

    PetscFunctionReturn(PETSC_SUCCESS);
}


/* Creates a local random vector */
PetscErrorCode CreateRandomVector(AppCtx& ctx, PetscInt iter){
    PetscFunctionBegin;

    PetscCall(VecZeroEntries(ctx.v));
    PetscCall(VecSetRandom(ctx.v, ctx.rng));

    PetscScalar norm1, norm2;
    PetscCall(VecNorm(ctx.v, NORM_1, &norm1));
    PetscCall(VecNorm(ctx.v, NORM_2, &norm2));
    
    char buffer[100];
    sprintf(buffer, "%d;%d;%e;%.12f\n", iter, ctx.cpuRank, norm1, norm2);
    ctx.collector.push_back(buffer);

    PetscFunctionReturn(PETSC_SUCCESS);
}


/* Exports the data in .csv format */
PetscErrorCode Export(AppCtx& ctx){
    PetscFunctionBegin;

    std::ofstream outputFile;
    outputFile.open("../output/results.csv");

    for (PetscInt i = 0; i < static_cast<int>(ctx.collector.size()); i++)
    {
        outputFile << ctx.collector[i];
    }
    outputFile.close();

    PetscCall(PetscPrintf(PETSC_COMM_WORLD, ">> Created .csv from rank %d\n", ctx.cpuRank));

    PetscFunctionReturn(PETSC_SUCCESS);
}