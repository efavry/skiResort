#ifndef MC_EDGE_H
#define MC_EDGE_H
#include <string>
using namespace std;
class MC_node;
class MC_edge
{
public:
    MC_edge(MC_node* sourceNode,MC_node destNode);
    MC_edge(const MC_edge&);
    ~MC_edge();

private :
    MC_node* source;
    MC_node* dest;
    int routeNumber;
    string routeName;
type

};

#endif // MC_EDGE_H
