#ifndef MC_TYPE_H
#define MC_TYPE_H
#include <string>
using namespace std;

enum TypeRoute{
    TK, //fo ski lift
    TS, //for chair lift
    TSD, //Special char lift
    TC, //for cabin
    TPH, //for telepheric
    BUS, //for shuttle bus
    V, //for green piste
    B, //for blue piste
    R, //for red psite
    N, //for black piste
    KL, //for track skiing
    SURF, //area reserved for surfing
    NONE
};

typedef struct DBNODE {   // Declare PERSON struct type
    int id; //point number
    string name;
    int altitude;
} db_node;

typedef struct DBEDGE {   // Declare PERSON struct type
    int id; //route number
    string name; //route name
    TypeRoute tr;//type
    int idSourcePoint;//startingpoint
    int idDestPoint;//arrivalpoint
} db_edge;



#endif // MC_TYPE_H
