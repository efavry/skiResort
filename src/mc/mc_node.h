#ifndef MC_NODE_H
#define MC_NODE_H
#include <list>
#include <string>
using namespace std;
class MC_node
{
private:
    friend class MC_talker;
    friend class MC_graph;
    int id; //id
    string name;
    int altitude;
    bool b_mark;
    list<MC_node*> l_successors;
    MC_node* predecessor;
    MC_node (const MC_node&); //copy constructor
    void addNeighbor(MC_node * n);
public:
    MC_node(int,string,int);

    bool isMarkedNode();
    void markNode();
    void unmarkNode();
    void addOutCommingEdge(MC_node*); //more like add son
    void depthFirsSearchRecursive(int id);
    //MC_node &operator=(const MC_node&); // operator =: not coded because WE WANT to comapre the adress of the pointer
    ~MC_node(); //detructor
}
;


#endif // MC_NODE_H
