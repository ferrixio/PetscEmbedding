# Petsc Embedding
How to embed a petsc code (executable or functions) inside another programming language

:dragon: Author: Samuele Ferri (@ferrixio)


## Structure
This library serves as collection of templates of "how to" to embed a PETSc executable in another programming language. At the moment only MATLAB is implemented.

The PETSc code stored in `src` generates a structured grid (called DMDA) and a (local) vector on it. Then, it populates it with random values 100 times and saves its norm 1 and norm 2 in a formatted string. Finally, it creates a .csv file containing the results. Each row is formatted as follows

```
iteration number;output rank;norm 1;norm 2
```

The `Matlab` folder contains a basic script that runs the petsc code (it is supposed it is already compiled), read the output .csv and plot the mean values of the vectors of all norm 1 and norm 2.

## Known issues

+ In **Windows**, Matlab can't run the PETSc code from its terminal, since it uses **cdm.exe**.