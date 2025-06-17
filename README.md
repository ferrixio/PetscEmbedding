# PETSc Embedding
How to embed a PETSc code (executable or functions) inside another programming language

:dragon: Author: Samuele Ferri (@ferrixio)


## Structure
This library serves as collection of templates of "how to" to embed a PETSc executable in another programming language. At the moment only MATLAB is implemented.

The PETSc code stored in `/src` generates a structured grid (called DMDA) and a (local) vector on it. Then, it populates it with random values and saves its norm 1 and norm 2 in a formatted string. This process is repeated 100 times. Finally, it creates a .csv file containing the results. Each row is formatted as follows

```
iteration;output rank;norm 1;norm 2
```

The `/Matlab` folder contains a basic script that runs the PETSc code, read the output .csv and plot the mean values of the vectors of all norm 1 and norm 2.

## How to use

The following things are supposed to be true:

1. in the `/build` folder there is a file named _localDefs.make_ where the paths of PETSc are stored;
2. Matlab and this code are on the same operating systems;
3. the PETSc code is already compiled.

To compile the PETSc source you can run `make vecrng` from the `/build` folder. Moreover, parallel execution is supported.

To run the matlab code you can use call `matlab -batch "main"` from a terminal pointing to the `/Matlab` folder of this repository.

If you encounter some problems of "command not found" try changing the paths inside _CallPetsc.m_ or _ProcessOutput.m_.

## Known issue

+ In Windows, Matlab can't run the PETSc code from its terminal, since it uses cdm.exe.