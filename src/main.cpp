#include <QtGui>
#include <QObject>

#include "view/graphwidget.h"
#include "view/graphpathwidget.h"
#include "view/rightwidget.h"
#include "mc/mc_talker.h"
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MC_talker *mc=new MC_talker();

    QGridLayout *layout = new QGridLayout();


    GraphWidget *widget = new GraphWidget();
    mc->setGraphWidget(widget);
    //widget->populate();

    mc->populate();

    layout->addWidget(widget,1,1,20,20);

    GraphPathWidget *pathWidget = new GraphPathWidget();
    //pathWidget->populate();
    layout->addWidget(pathWidget,21,1,1,20);

    RightWidget *rwidget = new RightWidget(mc);
    layout->addWidget(rwidget,1,21,1,1);
    QObject::connect(rwidget,SIGNAL(resetElectionSig()),widget,SLOT(resetElection()));
    QWidget mainWindow;
    mainWindow.setLayout(layout);
    mainWindow.showMaximized();

    return app.exec();
}
