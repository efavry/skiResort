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
            temps=(int)(10/60*((float)distanceCalc)); //(10 sec ie 1/6 minutes for 100m)
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
            if(id == 57 || id == 58)
                temps=30;
            else if (id==59 || id ==60)
                temps=40;
            //else
                //temps=35;
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

void MC_graph::dijkstra(MC_node *startPoint, MC_node *endPoint)
{
    //verifions si le noued est ateignable


    std::cout << "MC_Graph : dijkstra"<< startPoint->id << " to " << endPoint->id << std::endl;
    int mini=INT_MAX; //thisvar will help to find the minimum weight
    list<MC_node*> l_opened;
    //the actual structure of the graph give a list of node whichi will be used extensively with the mark
    //initialisation
    unmarkAll(); //well unmark all node and setup all node to infinity (INT_MAX)
    startPoint->weight=0; //we setup the source node as fixed and weighted at 0
    startPoint->fixed=true;
    MC_node * electedNode=startPoint;

    //the predecessor of startpoint is logically NULL
    //while destnode weight is not fixed definitly
    while(endPoint->fixed == false)
    {
        //we search all the unfixed node adjacent to the previously elected node
        for(MC_edge* edge:electedNode->l_successors)
        {
            if(edge->dest->fixed==false)
            {
                if(edge->dest->b_mark == false)
                    l_opened.push_back(edge->dest);
                edge->dest->predecessor=electedNode; //we temporary mark them with the previous weight + the edge weight
                edge->dest->weight=electedNode->weight + edge->temps;
            }
        }
        std::cout << "Mid dijk\n";



        //welcome toC++ ! when removing  with a foreach logically make a segfault but  you must iterate anyway so you use this :
        /*list<MC_node*>::iterator minimalWeightNode = std::begin(l_opened);
        while (minimalWeightNode != std::end(l_opened))
        {
            if ((*minimalWeightNode)->weight<=mini)
            {
                electedNode = *minimalWeightNode; //an iterator "feel like a pointer"
                electedNode->fixed=true;
                mini=electedNode->weight;
                minimalWeightNode = l_opened.erase(minimalWeightNode);
                //l_opened.remove(electedNode); //will call the destructor of the pointer but not of the actual object because we use ptr
            }
            else
                ++minimalWeightNode;
        }*/
        //now in the non definitly fixed node that we visited we find the minimal weight and we elc this node
        for(MC_node * minimalWeightNodeIter : l_opened)
            if(minimalWeightNodeIter->weight<=mini)
            {
                electedNode = minimalWeightNodeIter;
                mini=electedNode->weight;
            }
        //we fix the node that have this minimal weight
        electedNode->fixed=true;
        //we remove it from opened
        l_opened.remove(electedNode);
        mini=INT_MAX;
    }
    //reconstruct the path
    MC_node* iter=endPoint; //our "iterator"
    if(iter->weight >0)
        iter->weight+=10;
    std::cout << "time" << iter->weight << std::endl;
    while(iter!=NULL)
    {
        iter->selectNode(); //signal that he is part of the path
        std::cout << iter->name << std::endl;

        iter=iter->predecessor;

    }
    //cleanup the mess
    unmarkAll();
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
