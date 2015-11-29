#ifndef GRAPH_RIGHTWIDGET_H
#define GRAPH_RIGHTWIDGET_H

#include <QtGui>
#include "../mc/mc_talker.h"
#include "mc_type.h"
class RightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RightWidget(MC_talker*,QWidget *parent = 0);
private :
    QVBoxLayout *layout;
    void constructLevelGroup();
    void constructPathGroup();
    void constructInfoGroup();
    void constructOptionGroup();
    MC_talker *mcTalker;

    //for changing dinamicallhy the info :
    QComboBox *destComboBox;
    QListWidget *reachableLevelList;
    QLabel *labelName;
    QLabel *labelAltitude;

    //condition
    TypeRoute trCondition=TypeRoute::NONE;

    //path
    int idSource;
    int idDest;
    QPushButton *computeButton;
signals:
    void resetElectionSig();
public slots:
    void sendAResetElectionSig(){emit resetElectionSig();}
    void assignRouteCondition(int);
    void assignReachableNode(int);
    void assignReachableNodeWithCondition(int/*,TypeRoute*/);
    void setInfoName(int);
    void setInfoAltitude(int);
    void assignSourceNodeId(int id){idSource=id;}
    void assignDestNodeId(int id){idDest=id;}
    void startShortestPath()
    {
        //checking if the path exist before calling shortest path
        for(int i:mcTalker->getReachableNode(idSource))
            if(i==idDest)
            {
                mcTalker->startShortestPath(idSource,idDest);
                break;
            }
    }
    void deactivatePathButton(){computeButton->setEnabled(false);}
    void activatePathButton(){computeButton->setEnabled(true);}

};

#endif // RIGHTWIDGET_H
