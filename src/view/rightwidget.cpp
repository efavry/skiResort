#include "rightwidget.h"
#include <QtGui>

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

    //layout->addWidget(new QLabel("Starting Node :"),3,1,1,1);
    //layout->addWidget(new QPushButton("test"));
    this->setLayout(layout);

}

void RightWidget::constructLevelGroup()
{
    QGroupBox *levelGroupBox = new QGroupBox("Level :");

    QComboBox *levelComboBox = new QComboBox();
    levelComboBox->addItem("Green");
    levelComboBox->addItem("Blue");
    levelComboBox->addItem("Red");
    levelComboBox->addItem("Black");

    levelGroupBox->setLayout(new QVBoxLayout());
    levelGroupBox->layout()->addWidget(levelComboBox);

    layout->addWidget(levelGroupBox);
}

void RightWidget::constructPathGroup()
{
    QGroupBox *pathGroupBox = new QGroupBox("Compute a path :");

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

    connect(sourceComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(assignReachableNode(int)));
    destComboBox = new QComboBox();
    destComboBox->addItem("ipsum");
    destComboBox->addItem("quia");
    destComboBox->addItem("dolor");
    destComboBox->addItem("sit");
    destComboBox->addItem("amet");

    QGridLayout *groupBoxLayout = new QGridLayout();
    groupBoxLayout->addWidget(new QLabel("Start point :"),1,1,1,1);
    groupBoxLayout->addWidget(sourceComboBox,1,2,1,2);
    groupBoxLayout->addWidget(new QLabel("End point :"),2,1,1,1);
    groupBoxLayout->addWidget(destComboBox,2,2,1,2);
    groupBoxLayout->addWidget(new QPushButton("Compute !"),3,1,1,3);

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


//slots

void RightWidget::assignReachableNode(int i)
{
    destComboBox->clear();
    list<int> listOfReachedNode = mcTalker->getReachableNode(i);
    for(int id:listOfReachedNode)
        destComboBox->addItem(
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
