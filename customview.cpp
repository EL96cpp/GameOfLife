#include "customview.h"

#include <QDebug>

CustomView::CustomView(QWidget* parent) : QGraphicsView(parent) {

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(2, 2);

}

void CustomView::wheelEvent(QWheelEvent *event) {

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    if(event->angleDelta().y() > 0) {

        if (current_scale * scale_factor <= scale_max) {

            scale(scale_factor, scale_factor);
            current_scale *= scale_factor;

        }

    } else if (current_scale * scale_factor >= scale_min) {

        scale(1 / scale_factor, 1 / scale_factor);
        current_scale /= scale_factor;

    }
}
