#include "mc/mc_edge.h"

MC_edge::MC_edge(MC_node* sourceNode,MC_node* destNode,int id,int _distance,int _temps,TypeRoute tr):
    source(sourceNode),dest(destNode),idRoute(id),temps(_temps),distance(_distance),typeRoute(tr)
{
    //wesh
    1+2; //DONT REMOVE THIS (depend on the compiler)
}
