#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QObject>

class CustomView : public QGraphicsView {

public:
    CustomView(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent* event);

    double scale_factor = 1.2;
    double current_scale = 1.0;  // stores the current scale value.
    double scale_min = 0.32; // defines the min scale limit.
    double scale_max = 5;

};


#endif // CUSTOMVIEW_H
