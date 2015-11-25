#include "rightwidget.h"
#include <QtGui>

RightWidget::RightWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(150,10);
    //QHBoxLayout *layout = new QHBoxLayout();
    layout = new QGridLayout();

    //layout->addWidget(new QLabel("Level :"),1,1,1,1);

    layout->addWidget(new QLabel("Starting Node :"),3,1,1,1);
    //layout->addWidget(new QPushButton("test"));
    this->setLayout(layout);

}

void RightWidget::constructLevelGroup()
{
    QGroupBox *levelGroupBox = new QGroupBox("Level : ");
    QComboBox *levelComboBox = new QComboBox();
    levelComboBox->addItem("ipsum");
    levelComboBox->addItem("quia");
    levelComboBox->addItem("dolor");
    levelComboBox->addItem("sit");
    levelComboBox->addItem("amet");

    levelGroupBox->setLayout(new QVBoxLayout());
    levelGroupBox->layout()->addWidget(levelComboBox);
    layout->addWidget(levelGroupBox,1,1,2,2);
}
