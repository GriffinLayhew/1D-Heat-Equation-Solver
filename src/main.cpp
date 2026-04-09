/*
    AUTHOR:                     Griffin Layhew

    DATE:                       03/28/26
    PROGRAM TITLE:              1D Heat Equation Solver
    PROGRAM DESCRIPTION:
            " This program solves the 1D Heat Equation in Serial. The
              Central Difference method is used in space, while the explicit
              Euler method is used for time-stepping."


*/

#include "Mesh.hpp"
#include "TSsolver.hpp"

// Standard Function to Calculate Amount of Memory Being Used
long GetProgramMemoryUsage() 
{
    struct rusage usage;
    int ret = getrusage(RUSAGE_SELF, &usage);
    if (ret == -1) {
        perror("getrusage error");
        return -1;
    }
    return usage.ru_maxrss; 
}

            //===============================//
            //      MAIN STARTS HERE //
            //===============================//
int main(int argc, char* argv[])
{
    /*
    =============================================
                Input Space for Constants
    =============================================
    */
    double dt           = 0.01;
    double Diffusion    = 1.0;
    int GridElements    = 5000;
    double Domain       = 1.0;
    int TimeSteps       = 50;

    /*
    =============================================
                Intiialize Mesh and Solver
    =============================================
    */
    Mesh FiniteDiffGrid(GridElements, Domain);
    applyInitialCondition(FiniteDiffGrid, initialFunction);
    std::cout << FiniteDiffGrid;
    
    TSsolver EulerTimeSolver{TimeSteps, Diffusion, dt, FiniteDiffGrid};

    /*
    =============================================
                Solve the System
    =============================================
    */
    EulerTimeSolver.SolveSystem();
    long currentMem = GetProgramMemoryUsage();
    std::cout << "Current memory usage: " << currentMem << " KB" << std::endl;
 
    /*
    =============================================
                Output the Results
    =============================================
    */
   std::cout << EulerTimeSolver << std::endl;

   return 0;
}