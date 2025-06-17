function status = CallPetsc(np, N1, N2)

command = sprintf('mpirun -np %d ~/Projects/PetscEmbedding/build/vecrng -N %d,%d', np, N1, N2);
status = system(command);

end