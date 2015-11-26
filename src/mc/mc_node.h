#ifndef MC_NODE_H
#define MC_NODE_H
#include <list>
#include <string>
#include <QObject>
using namespace std;
class MC_edge;
class MC_node :QObject
{
    Q_OBJECT
private:
    friend class MC_talker;
    friend class MC_graph;
    int id; //id
    string name;
    int altitude;
    bool b_mark;
    list<MC_edge*> l_successors;
    MC_node* predecessor;
    MC_node (const MC_node&); //copy constructor
    void addNeighbor(MC_edge * edge);
public:
    MC_node(int,string,int);

    bool isMarkedNode();
    void selectNode(){emit selectedSignal(id);}
    void markNode();
    void unmarkNode();
    void addOutCommingEdge(MC_node*); //more like add son
    void depthFirsSearchRecursive(int id);
    //MC_node &operator=(const MC_node&); // operator =: not coded because WE WANT to comapre the adress of the pointer
    ~MC_node();

signals:
    void selectedSignal(int);
}
;


#endif // MC_NODE_H
