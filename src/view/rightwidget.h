#ifndef GRAPH_RIGHTWIDGET_H
#define GRAPH_RIGHTWIDGET_H

#include <QWidget>

class RightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RightWidget(QWidget *parent = 0);

private :
    QGridLayout *layout;
signals:

public slots:

};

#endif // RIGHTWIDGET_H
