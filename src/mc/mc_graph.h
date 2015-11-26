#ifndef MC_GRAPH_H
#define MC_GRAPH_H
#include "mc_edge.h"
#include "mc_node.h"
#include "list"
#include "vector"
#include "mc_type.h"
#include <QObject>
class MC_talker;
using namespace std;
class MC_graph : public QObject//in fact it is a digraph
{
    Q_OBJECT
friend MC_talker;
private:
    list<MC_node *> listOfNodes; //will usefull for unmark or things like that
    void dfsRec(MC_node* n,list<MC_node *>*);
    MC_graph(const MC_graph&);
public:
    MC_graph();
    void addNode(MC_node *);
    void connectNode(MC_node *,MC_node *);
    list<MC_node *> dfs(MC_node* source);
    void unmarkAll();
    list<MC_node *> dijkstra(MC_node* startPoint, MC_node* endPoint); //return the ordered path from start node to end node
    list<MC_node *>& getListOfNodes(){return listOfNodes;}
    ~MC_graph();
signals:
    void nodeCreated(int id,string name,int altitude);
    void edgeCreated(int fromId,int destId,int id,int distance,int temps,TypeRoute typeRoute); //distance(slope : source.alt -dest.alt
}
;
#endif // MC_GRAPH_H
