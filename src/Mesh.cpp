#include "Mesh.hpp"

/*=================================
    Member Function Definitions
  ================================*/

// Typical Constructor
Mesh::Mesh(int nN, double lL) : MeshPoints{nN}, Length{lL}, dx{(double) lL / (nN - 1.0)}
{
    for (int it = 0; it < nN; it++)        // Initialize all Constructed Meshes with 0's
        Data.push_back(0.0);
    
    std::cout << "[MESH] Mesh Generated with " << MeshPoints << " Nodes." << std::endl;
}

// Default Constructor
const Mesh& defaultMesh()
{
    int DefaultSize = 10;
    static Mesh dMesh {DefaultSize, 1.0};
    for (int it = 0; it < DefaultSize; it++)        // Initialize all Constructed Meshes with 0's
        dMesh.getData().push_back(0.0);
    return dMesh;

}

Mesh::Mesh() : MeshPoints{defaultMesh().getMeshPointNumber()}, 
               Length    {defaultMesh().getDomainLength()}, 
               dx        {defaultMesh().getGridSpacing()}, 
               Data      {defaultMesh().getData()} 
{
    std::cout << "[MESH]    --Default Mesh Generated" << std::endl;
}

// Function to Modify the Data in the Mesh
void Mesh::setData(double INPUT, int LOC)
{
    Data[LOC] = INPUT;
}

/*=================================
       Overloaded Definitions
  ================================*/

// std::cout << 
std::ostream& operator<<(std::ostream& os, const Mesh& M)
{
    os << "Mesh (" << M.getMeshPointNumber() << " points):\n";

    for (const auto& val : M.getData())
    {
        os << val << " ";
    }
    os << std::endl;
    return os;
}



/*=================================
    Helper Function Definitions
  ================================*/

double initialFunction(double INPUT)
{
    return std::sin(M_PI * INPUT);
}


void applyInitialCondition(Mesh& M, std::function<double(double)> func)
{
    int count = 0;
    for (auto& val : M.getData())
    {
        double x = count * M.getGridSpacing();
        val = func(x);
        M.setData(val, count);
        count++;
    }

    M.setData(M.getLeft(), 0);                            // Left Dirichlet
    M.setData(M.getRight(), M.getData().size()-1);        // Right Dirichlet
}