#ifndef MESH
#define MESH

#include "Utilities.hpp"

class Mesh
{
    public:
    // Constructors
        Mesh();                                 // Default Constructor
        Mesh(int N, double L);                  // Typical Constructor

    // NonModifying Operations
    int                  getMeshPointNumber() const {return MeshPoints; }
    double               getDomainLength()    const {return Length;     }
    double               getGridSpacing()     const {return dx;         }
    std::vector<double>  getData()            const {return Data;       }
    double               getLeft()            const {return Tleft;      }
    double               getRight()           const {return Tright;     }

    // Modifying Operations
    void                setData(double, int);

    // Member Functions
    



    private:
        int         MeshPoints;     // Number of Mesh Points in the 1D Grid
        double      Length;         // Total Length of the Domain
        double      dx;             // Computed Spacing of Grid Points

        double      Tleft;          // Dirichlet Boundary Condition on the Left
        double      Tright;         // Dirichlet Boundary Condition on the Right

        std::vector<double> Data;

};

// Overloaded Operators
std::ostream& operator<<(std::ostream& os, const Mesh& M);


// Helper Functions
double initialFunction(double INPUT);
void applyInitialCondition(Mesh& M, std::function<double(double)> func);


#endif