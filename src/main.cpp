static char help[] = "Generates 100 random vectors and saves its norm 1 and 2\n\n\n";

#include "library.hpp"

int main(int argc, char **argv){

    PetscFunctionBeginUser;
    PetscCall(PetscInitialize(&argc, &argv, NULL, help));

    AppCtx ctx;
    PetscCall(ReadTerminal(ctx));

    for (PetscInt i = 0; i < 100; i++)
    {
        PetscCall(CreateRandomVector(ctx, i+1));
    }

    // export results
    PetscCall(Export(ctx));

    PetscCall(DMDestroy(&ctx.dmdaGrid));
    PetscCall(PetscRandomDestroy(&ctx.rng));
    PetscCall(PetscFinalize());
    PetscFunctionReturn(PETSC_SUCCESS);
}