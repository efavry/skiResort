#include "mc/mc_readdb.h"
#include <iostream>
#include <fstream>
#include <string.h> //c style string
MC_ReadDB::MC_ReadDB(string filename)
{
    this->readFile(filename);
}

void MC_ReadDB::readFile(string filename)
{
    std::cout << std::endl;
    ifstream file;
    string temp;
    file.open(filename);
    //first line is number of node
    file >> temp;
    int nbNode = atoi(temp.c_str());
    temp.clear();
    for(int i=0;i<nbNode;++i)
    {
        db_node tempDbNode;
        file >> temp; //id = osef
        tempDbNode.id = i;
        file >> temp; //name
        tempDbNode.name = temp;
        file >> temp; //altirude
        tempDbNode.altitude = atoi(temp.c_str());
        dbNodes.push_back(tempDbNode);
        std::cout << "Node is : " << tempDbNode.id << " " << tempDbNode.name << " " << tempDbNode.altitude << std::endl;
        temp.clear();
    }
    file >> temp; //nummber of edge
    int nbEdge = atoi(temp.c_str());
    for(int j=0;j<nbEdge;++j)
    {
        db_edge tempDbEdge;
        file >> temp; //osef
        tempDbEdge.id = j;
        file >> temp;
        tempDbEdge.name = temp;
        file >> temp;
        tempDbEdge.tr=this->getTypeRoutr(temp);
        file >> temp;
        tempDbEdge.idSourcePoint =atoi(temp.c_str())-1;
        file >> temp;
        tempDbEdge.idDestPoint =atoi(temp.c_str())-1;
        dbEdges.push_back(tempDbEdge);
        std::cout << "Edge is : " << tempDbEdge.id << " " << tempDbEdge.name << " " << tempDbEdge.tr << " " << tempDbEdge.idSourcePoint << " " << tempDbEdge.idDestPoint << std::endl;
        temp.clear();
        //ne pas oiublié de moins moin les ID !!!
    }
    temp.clear();
    file.close(); //now that the import is finished we close the file
}

TypeRoute MC_ReadDB::getTypeRoutr(string stringTr)
{
    //c++ can't switch on string (espacially because string is stl and not the language
    if (!strcmp(stringTr.c_str(), "TK"))
      return TypeRoute::TK;
    else if (!strcmp(stringTr.c_str(), "TS"))
      return TypeRoute::TS;
    else if (!strcmp(stringTr.c_str(), "TSD"))
      return TypeRoute::TSD;
    else if (!strcmp(stringTr.c_str(), "TC"))
      return TypeRoute::TC;
    else if (!strcmp(stringTr.c_str(), "TPH"))
      return TypeRoute::TPH;
    else if (!strcmp(stringTr.c_str(), "BUS"))
      return TypeRoute::BUS;
    else if (!strcmp(stringTr.c_str(), "V"))
      return TypeRoute::V;
    else if (!strcmp(stringTr.c_str(), "B"))
      return TypeRoute::B;
    else if (!strcmp(stringTr.c_str(), "R"))
      return TypeRoute::R;
    else if (!strcmp(stringTr.c_str(), "N"))
      return TypeRoute::N;
    else if (!strcmp(stringTr.c_str(), "KL"))
      return TypeRoute::KL;
    else if (!strcmp(stringTr.c_str(), "SURF"))
      return TypeRoute::SURF;
    else
      return TypeRoute::NONE;
}
