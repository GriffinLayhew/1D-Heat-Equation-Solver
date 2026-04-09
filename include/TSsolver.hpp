#ifndef TSOLVE
#define TSOLVE

#include "Utilities.hpp"
#include "Mesh.hpp"

class TSsolver
{
    public:
    // Constructors
        TSsolver();                                             // Default Constructor
        TSsolver(int T, double dt, double Diff, Mesh& cM);                   // Typical Constructor

    // NonModifying Operations
        double                  getTimeStep()       const {return timeStep;     }
        double                  getDiffusion()      const {return Diffusion;    }
        int                     getNumSteps()       const {return numSteps;     }
        Mesh&                   getCurrentState()   const {return currentState; }
        Mesh&                   getNextState()      const {return nextState;    }

    // Modifying Operations


    // Member Functions
        void                SolveSystem();
        void                OverrideTimeStep();



    private:
        double      timeStep;
        double      Diffusion;
        int         numSteps;
        Mesh&        currentState;
        Mesh&        nextState;


};

// Overloaded Operators
std::ostream& operator<<(std::ostream& os, const TSsolver& TS);
TSsolver&     operator++(TSsolver& TS);


// Helper Functions



#endif