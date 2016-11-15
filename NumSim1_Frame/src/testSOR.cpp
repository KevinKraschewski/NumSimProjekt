#include <iostream>
#include "typedef.hpp"
#include "compute.hpp"
#include "geometry.hpp"
#include "iterator.hpp"
#include "parameter.hpp"
#include "visu.hpp"
#include "vtk.hpp"
#include "grid.hpp"
#include "solver.hpp"


int main(int argc, char *argv[]) {
Parameter param;
Geometry geom;
Renderer visu(geom.Length(), geom.Mesh());

Grid grid(&geom);
grid.Initialize(0);

Grid rhs(&geom);
rhs.Initialize(0);

Iterator it(&geom,8*18+8);
grid.Cell(it) = 1;

visu.Init(800, 800);



visu.Render(&grid);

SOR sor(&geom,1.7);

while(true){
   sor.Cycle(&grid,&rhs);
   visu.Render(&grid);
   std::cin.get();
}



return 0;

}
