function status = CallPetsc(np, N1, N2)

command = sprintf('~/Software/petsc/arch-linux-c-opt/bin/mpirun -np %d ~/Projects/PetscEmbedding/build/vecrng -N %d,%d', np, N1, N2);
status = system(command);

end