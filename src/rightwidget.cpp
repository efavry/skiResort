#include "rightwidget.h"
#include <QtGui>

RightWidget::RightWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(150,10);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(new QPushButton("test"));
    this->setLayout(layout);

}
