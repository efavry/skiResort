#ifndef MC_EDGE_H
#define MC_EDGE_H
#include <string>
#include "mc_type.h"
using namespace std;
class MC_node;
class MC_graph;
class MC_edge
{
    friend MC_node;
    friend MC_graph;
public:
    MC_edge(MC_node* sourceNode,MC_node* destNode,int id,int distance,int temps,TypeRoute tr);
    ~MC_edge(){}

private :
    MC_edge(const MC_edge&);
    MC_node* source;
    MC_node* dest;
    int idRoute;
    //string routeName;
    int distance=0;
    int temps=0;
    TypeRoute typeRoute;


};

#endif // MC_EDGE_H
