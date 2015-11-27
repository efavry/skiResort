#ifndef MC_READDB_H
#define MC_READDB_H
#include <list>
#include "mc_type.h"
using namespace std;
class MC_ReadDB
{

public:
    MC_ReadDB(string filename);
    list<db_node> getDbNodes(){return dbNodes;}
    list<db_edge> getDbEdges(){return dbEdges;}
private :
    void readFile(string filename);
    TypeRoute getTypeRoutr(string);
    list<db_node> dbNodes;
    list<db_edge> dbEdges;
};



#endif // MC_READDB_H
