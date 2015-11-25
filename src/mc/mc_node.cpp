#include "mc/mc_edge.h"
#include "mc/mc_node.h"

MC_node::MC_node(int inId, string inName, int inAltitude)
{
    this->id= inId;
    this->name = inName;
    this->altitude = inAltitude;
}

bool MC_node::isMarkedNode()
{
    return this->b_mark;
}
void MC_node::markNode()
{
    this->b_mark=true;
}
void MC_node::unmarkNode()
{
    this->b_mark=false;
    this->predecessor=NULL;
}
void MC_node::addNeighbor(MC_node * n)
{
    this->l_successors.push_back(n);
}
/*
void node::addParent(node * n)
{
    this->parentList.push_back(n);
}
*/
MC_node::~MC_node()
{

}
