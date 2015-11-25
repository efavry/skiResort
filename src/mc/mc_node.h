#ifndef MC_NODE_H
#define MC_NODE_H
#include <list>
using namespace std;
class MC_node
{
private:
    friend class MC_graph;
    unsigned int uint_name;
    bool b_mark;
    list<MC_node*> l_successors;
    MC_node* predecessor;

    MC_node (const MC_node&); //copy constructor
public:
    MC_node(unsigned int name);

    bool isMarkedNode();
    void markNode();
    void unmarkNode();
    void addOutCommingEdge(MC_node*); //more like add son
    void depthFirsSearchRecursive(unsigned int name);
    //MC_node &operator=(const MC_node&); // operator =: not coded because WE WANT to comapre the adress of the pointer
    ~MC_node(); //detructor
}
;


#endif // MC_NODE_H
