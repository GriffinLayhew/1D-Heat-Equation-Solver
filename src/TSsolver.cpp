#include "TSsolver.hpp"

/*=================================
    Member Function Definitions
  ================================*/

// Typical Constructor
TSsolver::TSsolver(int T, double Diff, double dt, Mesh& cM) : numSteps{T}, Diffusion{Diff}, timeStep{dt}, currentState{cM}, nextState{cM}
{
  std::cout << "[SOLVER] Solver Generated with " << numSteps << " TimeSteps." << std::endl;
}
// Default Constructor
const TSsolver& defaultTimeSolver()
{
  double      dtimeStep   = .01;
  double      dDiffusion  = 1.0;
  int         dnumSteps   = 100;
  Mesh        dcurrentState;
  Mesh        dnextState;

  static TSsolver dSolver {dnumSteps, dDiffusion, dtimeStep, dcurrentState};
  return dSolver;

}

TSsolver::TSsolver() : timeStep         {defaultTimeSolver().getTimeStep()}, 
                       Diffusion        {defaultTimeSolver().getDiffusion()}, 
                       numSteps         {defaultTimeSolver().getNumSteps()}, 
                       currentState     {defaultTimeSolver().getCurrentState()},
                       nextState        {defaultTimeSolver().getNextState()}
{
    std::cout << "[SOLVER]  --Default SOLVER Generated" << std::endl;
}

// Check to ensure Time Step satisfies Stability
void TSsolver::OverrideTimeStep()
{
  double dx = currentState.getGridSpacing();
  double dt = timeStep;

  double checkSize = (dt * Diffusion / (dx * dx));
  if (checkSize > 0.5)
  {
    timeStep /= 2;
    this->OverrideTimeStep();
  }
  else
    return;
}

// Member Function to Solve the System 
void TSsolver::SolveSystem()
{
  this->OverrideTimeStep();
  std::cout << "[SOLVER] Solving the System with dt = " << timeStep << std::endl;
  for (int i=0; i<=(*this).getNumSteps(); i++)
    ++*(this);
}

/*=================================
       Overloaded Definitions
  ================================*/

// std::cout << 
std::ostream& operator<<(std::ostream& os, const TSsolver& TS)
{
    os << "Time-Solver (" << TS.getNumSteps() << " Steps):\n";
    os << "---Current State: \n";
    os << TS.getCurrentState();
    os << std::endl;
    return os;
}

// ++
TSsolver& operator++(TSsolver& TS)
{
    auto& current = TS.getCurrentState();
    auto& next    = TS.getNextState();

    const auto& u = current.getData();
    std::size_t N = u.size();

    double dx = current.getGridSpacing();
    double alpha = (TS.getTimeStep() * TS.getDiffusion()) / (dx * dx);

    for (std::size_t i = 1; i < N - 1; ++i)
    {
        next.setData(
            u[i] + alpha * (u[i - 1] - 2.0 * u[i] + u[i + 1]),
            i
        );
    }

    for (std::size_t i = 1; i < N - 1; ++i)
    {
        current.setData(next.getData()[i], i);
    }

    return TS;
}

/*=================================
    Helper Function Definitions
  ================================*/

