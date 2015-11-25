#include "mc/mc_node.h"
#include "mc/mc_graph.h"
#include "iostream"

MC_graph::MC_graph()
{
}

void MC_graph::addNode(MC_node *n)

{
    this->listOfNodes.push_back(n);
}


void MC_graph::connectNode(MC_node *from,MC_node *to)
{//can be used later on to use edges defined by a class
    cout << "Connecting " << from->uint_name << "to" << to->uint_name << endl;
    from->addNeighbor(to);
}


void MC_graph::unmarkAll()
{
    for(MC_node* n : this->listOfNodes)
        n->unmarkNode();
}

list<MC_node*> MC_graph::dfs(MC_node* n)
{
    list<MC_node *> reachableNodeList;
    this->unmarkAll();
    //for(MC_node* m:this->listOfNodes) //for each unreached node we dfs it (yes the above line is usless)
        this->dfsRec(/*m*/n,&reachableNodeList);
    return reachableNodeList;
}

void MC_graph::dfsRec(MC_node* n,list<MC_node *> *reachableNodeList)
{
    if(!n->isMarkedNode())
    {
        reachableNodeList->push_back(n);
        n->markNode();
        cout << "DFS : I'm " << n->uint_name << endl;
        for(MC_node* m:n->l_successors)
                this->dfsRec(m,reachableNodeList);
    }
}


MC_graph::~MC_graph()
{
    while(!this->listOfNodes.empty())
    {
        delete this->listOfNodes.front();
        this->listOfNodes.pop_front();
    }
}
