#include "mc/mc_node.h"
#include "mc/mc_graph.h"
#include "iostream"
#include "stdlib.h" //for abs on int value

MC_graph::MC_graph()
{
}

void MC_graph::addNode(MC_node *n)
{
    this->listOfNodes.push_back(n);
    emit nodeCreated(n->id,n->name,n->altitude);
}


void MC_graph::connectNode(MC_node *from,MC_node *to,int id,string name,TypeRoute typeRoute)
{//can be used later on to use edges defined by a class
    cout << "Connecting " << from->id << "to" << to->id << endl;
    //TODO ajouter info dans le modele
    int distance = abs(from->altitude - to->altitude);
    int temps;
    int distanceCalc= distance/100;
    switch (typeRoute)
    {
        case TypeRoute::V:
            temps=5*distanceCalc;
            break;
        case TypeRoute::B:
            temps=4*distanceCalc;
            break;
        case TypeRoute::R:
            temps=3*distanceCalc;
            break;
        case TypeRoute::N:
            temps=2*distanceCalc;
            break;
        case TypeRoute::KL:
            temps=0.166*distanceCalc; //(10 sec ie 1/6 minutes for 100m)
            break;
        case TypeRoute::SURF:
            temps=10*distanceCalc;
            break;
        case TypeRoute::TPH:
            temps=4 + 2*distanceCalc;
            break;
        case TypeRoute::TC:
            temps=2 + 3*distanceCalc;
            break;
        case TypeRoute::TSD:
            temps=1 + 3*distanceCalc;
            break;
        case TypeRoute::TS:
            temps=1 + 4*distanceCalc;
            break;
        case TypeRoute::TK:
            temps=1 + 4*distanceCalc;
            break;
        case TypeRoute::BUS: //assuming we know a lot
            //TODO : TEMPS BUS
            temps=35;
            break;
        default:
            temps=distanceCalc;
    }
    from->addNeighbor(new MC_edge(from,to,id,distance,temps,typeRoute));
    emit edgeCreated(from->id,to->id,id,name,distance,temps,typeRoute);
}


void MC_graph::unmarkAll()
{
    for(MC_node* n : this->listOfNodes)
        n->unmarkNode();
}

list<MC_node*> MC_graph::dfs(MC_node* n,TypeRoute tr)
{
    list<MC_node *> reachableNodeList;
    this->unmarkAll();
    //for(MC_node* m:this->listOfNodes) //for each unreached node we dfs it (yes the above line is usless)
    this->dfsRec(/*m*/n,&reachableNodeList,tr);
    return reachableNodeList;
}

void MC_graph::dfsRec(MC_node* n,list<MC_node *> *reachableNodeList,TypeRoute tr)
{
    if(!n->isMarkedNode())
    {
        reachableNodeList->push_back(n);
        n->markNode();
        //cout << "DFS : I'm " << n->id << endl;
        for(MC_edge* edge:n->l_successors)
            if(tr==edge->typeRoute || tr == TypeRoute::NONE) //if a color is conditioned are no condition for the dfs
                this->dfsRec(edge->dest,reachableNodeList,tr);
    }
}


MC_graph::~MC_graph()
{
    for(MC_node* n: this->listOfNodes)
        for(MC_edge* edge: n->l_successors)
            delete edge;
    while(!this->listOfNodes.empty())
    {
        delete this->listOfNodes.front();
        this->listOfNodes.pop_front();
    }
}

//singals
/*
void MC_graph::nodeCreated(int id,string name,int altitude)
{
    Q_UNUSED(id);
    Q_UNUSED(name);
    Q_UNUSED(altitude);
    return;
}
void MC_graph::edgeCreated(int fromId,int destId,int id,string name,int distance,int temps,TypeRoute typeRoute)
{
    Q_UNUSED(fromId);
    Q_UNUSED(destId);
    Q_UNUSED(id);
    Q_UNUSED(name);
    Q_UNUSED(distance);
    Q_UNUSED(temps);
    Q_UNUSED(typeRoute);
    return;
}
*/
