#ifndef GRAPH_RIGHTWIDGET_H
#define GRAPH_RIGHTWIDGET_H

#include <QtGui>
#include "../mc/mc_talker.h"
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
    QLabel *labelName;
    QLabel *labelAltitude;
signals:

public slots:
    void assignReachableNode(int);
    void setInfoName(int);
    void setInfoAltitude(int);
};

#endif // RIGHTWIDGET_H
