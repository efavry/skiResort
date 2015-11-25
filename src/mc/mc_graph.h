#ifndef MC_GRAPH_H
#define MC_GRAPH_H
#include "mc_edge.h"
#include "mc_node.h"
#include "list"
#include "vector"
using namespace std;
class MC_graph //in fact it is a digraph
{
private:
    list<MC_node *> listOfNodes; //will usefull for unmark or things like that
    void dfsRec(MC_node* n,list<MC_node *>*);
    MC_graph();
    MC_graph(const MC_graph&);
public:
    MC_graph(vector<vector<unsigned int>>,int);
    void addNode(MC_node *);
    void connectNode(MC_node *,MC_node *);
    list<MC_node *> dfs(MC_node* source);
    vector<vector<unsigned int>>  tarjan();
    void unmarkAll();
    list<MC_node *> dijkstra(MC_node* startPoint, MC_node* endPoint); //return the ordered path from start node to end node

    ~MC_graph();
}
;
#endif // MC_GRAPH_H
