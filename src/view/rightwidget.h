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
    MC_talker *mcTalker;

    //for changing dinamicallhy the info :
    QComboBox *destComboBox;
    QComboBox *reachableLevelComboBox;
    QLabel *labelName;
    QLabel *labelAltitude;

    //condition
    TypeRoute trCondition=TypeRoute::NONE;
signals:

public slots:
    void assignRouteCondition(int);
    void assignReachableNode(int);
    void assignReachableNodeWithCondition(int/*,TypeRoute*/);
    void setInfoName(int);
    void setInfoAltitude(int);
};

#endif // RIGHTWIDGET_H
