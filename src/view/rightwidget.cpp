#include "rightwidget.h"
#include <QtGui>
#include <iostream>
RightWidget::RightWidget(MC_talker *mc,QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(150,10);
    this->mcTalker=mc;
    //QVBoxLayout *layout = new QHBoxLayout();
    layout = new QVBoxLayout();

    constructLevelGroup();
    constructPathGroup();
    constructInfoGroup();
    constructOptionGroup();

    //layout->addWidget(new QLabel("Starting Node :"),3,1,1,1);
    //layout->addWidget(new QPushButton("test"));
    this->setLayout(layout);

}

void RightWidget::constructLevelGroup()
{
    QGroupBox *levelGroupBox = new QGroupBox("Reachable place with a level :");

    QComboBox *levelComboBox = new QComboBox();
    levelComboBox->addItem("Green");
    levelComboBox->addItem("Blue");
    levelComboBox->addItem("Red");
    levelComboBox->addItem("Black");
    //levelComboBox->addItem("None");
    levelComboBox->setCurrentIndex(-1);
    connect(levelComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(sendAResetElectionSig()));
    connect(levelComboBox,SIGNAL(activated(int)),
            this,SLOT(assignRouteCondition(int)));

    QComboBox *sourceComboBox = new QComboBox();
    for(int id:mcTalker->getNodeIDList())
    {
        sourceComboBox->addItem(
                             QString::number(id).append(" | ").append(
                             QString::fromStdString(
                             mcTalker->getNodeNameFromId(
                             id
                             ))));
    }

    sourceComboBox->setCurrentIndex(-1);


    reachableLevelList = new QListWidget();
    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(sendAResetElectionSig()));
    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(assignReachableNodeWithCondition(int)));

    QGridLayout *groupBoxLayout = new QGridLayout();
    groupBoxLayout->addWidget(new QLabel("Level :"),0,1,1,1);
    groupBoxLayout->addWidget(levelComboBox,0,2,1,2);
    groupBoxLayout->addWidget(new QLabel("Start point :"),1,1,1,1);
    groupBoxLayout->addWidget(sourceComboBox,1,2,1,2);
    groupBoxLayout->addWidget(new QLabel("Reachable point :"),2,1,1,1);
    groupBoxLayout->addWidget(reachableLevelList,2,2,1,2);

    levelGroupBox->setLayout(groupBoxLayout);


    layout->addWidget(levelGroupBox);
}

void RightWidget::constructPathGroup()
{
    QGroupBox *pathGroupBox = new QGroupBox("Compute a shortest path :");

    QComboBox *sourceComboBox = new QComboBox();
    for(int id:mcTalker->getNodeIDList())
    {
        sourceComboBox->addItem(
                             QString::number(id).append(" | ").append(
                             QString::fromStdString(
                             mcTalker->getNodeNameFromId(
                             id
                             ))));
    }
    sourceComboBox->setCurrentIndex(-1);

    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(sendAResetElectionSig()));
    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(assignReachableNode(int)));
    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(assignSourceNodeId(int)));
    destComboBox = new QComboBox();

    connect(destComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(assignDestNodeId(int)));

    QGridLayout *groupBoxLayout = new QGridLayout();
    groupBoxLayout->addWidget(new QLabel("Start point :"),1,1,1,1);
    groupBoxLayout->addWidget(sourceComboBox,1,2,1,2);
    groupBoxLayout->addWidget(new QLabel("End point :"),2,1,1,1);
    groupBoxLayout->addWidget(destComboBox,2,2,1,2);

    computeButton=new QPushButton("Compute !\n(will do something only on reachable place)");
    computeButton->setEnabled(false);
    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(deactivatePathButton()));
    connect(destComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(activatePathButton()));
    connect(computeButton,SIGNAL(clicked()),this,SLOT(startShortestPath()));
    connect(computeButton,SIGNAL(clicked()),this,SLOT(deactivatePathButton()));
    groupBoxLayout->addWidget(computeButton,3,1,1,3);

    pathGroupBox->setLayout(groupBoxLayout);

    layout->addWidget(pathGroupBox);
}

void RightWidget::constructInfoGroup()
{
    QGroupBox *infoGroupBox = new QGroupBox("Information :");
    infoGroupBox->setLayout(new QVBoxLayout());
    QComboBox *nodeComboBox = new QComboBox();
    for(int id:mcTalker->getNodeIDList())
    {
        nodeComboBox->addItem(
                             QString::number(id).append(" | ").append(
                             QString::fromStdString(
                             mcTalker->getNodeNameFromId(
                             id
                             ))));
    }
    nodeComboBox->setCurrentIndex(-1);
    labelName = new QLabel("Name : ");
    labelAltitude = new QLabel("Elevation : ");
    connect(nodeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(setInfoName(int)));
    connect(nodeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(setInfoAltitude(int)));

    infoGroupBox->layout()->addWidget(nodeComboBox);
    infoGroupBox->layout()->addWidget(labelName);
    infoGroupBox->layout()->addWidget(labelAltitude);

    layout->addWidget(infoGroupBox);
}

void RightWidget::constructOptionGroup()
{
    QGroupBox *optionGroupBox = new QGroupBox("Graph Visualiser Option :");
    optionGroupBox->setLayout(new QVBoxLayout());
    QCheckBox *checkShowName = new QCheckBox("Show the name of the path");
    connect(checkShowName,SIGNAL(stateChanged(int)),mcTalker->graphWidget,SLOT(setStateOfShowableNameForEdges(int)));
    optionGroupBox->layout()->addWidget(checkShowName);
    QCheckBox *checkShowDist =new QCheckBox("Show the distance of the path");
    connect(checkShowDist,SIGNAL(stateChanged(int)),mcTalker->graphWidget,SLOT(setStateOfShowableDistanceForEdges(int)));
    optionGroupBox->layout()->addWidget(checkShowDist);
    QCheckBox *checkShowTime =new QCheckBox("Show the time of the path");
    connect(checkShowTime,SIGNAL(stateChanged(int)),mcTalker->graphWidget,SLOT(setStateOfShowableTimeForEdges(int)));
    optionGroupBox->layout()->addWidget(checkShowTime);

    layout->addWidget(optionGroupBox);
}

//slots
void RightWidget::assignRouteCondition(int i)
{   std::cout<< "View : Level : Route condition : " << i << std::endl;
    switch (i)
    {
        case 0:
            trCondition=TypeRoute::V;
            break;
        case 1:
            trCondition=TypeRoute::B;
            break;
        case 2:
            trCondition=TypeRoute::R;
            break;
        case 3:
            trCondition=TypeRoute::N;
            break;
        default:
            trCondition=TypeRoute::NONE;

    }
    return;
}

void RightWidget::assignReachableNode(int i)
{
    destComboBox->clear();
    list<int> listOfReachedNode = mcTalker->getReachableNode(i);
    int j=0;
    QString text;
    for(int id:mcTalker->getNodeIDList())
    {

        text.append(QString::number(id));
        text.append(" | ");
        text.append(QString::fromStdString(mcTalker->getNodeNameFromId(id)));
        for(int comparator:listOfReachedNode)
        {
            if(comparator == j)
            {
                text.append(" Reachable");
            }
        }
        destComboBox->addItem(QString(text));
        text.clear();
        ++j;
    }



/*
    for(int id:listOfReachedNode)
        destComboBox->itemData()


        destComboBox->addItem(
                    QString::number(id).append(" | ").append(
                    QString::fromStdString(
                    mcTalker->getNodeNameFromId(
                    id
                    ))));*/
}

void RightWidget::assignReachableNodeWithCondition(int i/*,TypeRoute type*/)
{

    std::cout<<"View : Level DFS : Places selected " << i << " tr : " << trCondition << std::endl;
    reachableLevelList->clear();
    list<int> listOfReachedNode = mcTalker->getReachableNodeWithCondition(i,trCondition);
    for(int id:listOfReachedNode)
        reachableLevelList->addItem(
                            QString::number(id).append(" | ").append(
                            QString::fromStdString(
                            mcTalker->getNodeNameFromId(
                            id
                            ))));
}


void RightWidget::setInfoName(int i)
{
    labelName->setText(
                QString("Name : ").append(
                    QString::fromStdString(mcTalker->getNodeNameFromId(i))));
}


void RightWidget::setInfoAltitude(int i)
{
    labelAltitude->setText(
                QString("Elevation : ").append(
                        QString::number(mcTalker->getNodeAltitudeFromId(i))));
}
