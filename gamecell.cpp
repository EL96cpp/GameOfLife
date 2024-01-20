#include "gamecell.h"

GameCell::GameCell(const qreal &x, const qreal &y, const QBrush& brush) {

    setRect(0, 0, 10, 10);
    setPos(x, y);
    setBrush(brush);

}

bool GameCell::GetState() {

    return is_alive;

}

void GameCell::UpdateCell(const bool &is_alive, const QBrush& brush) {

    this->is_alive = is_alive;
    setBrush(brush);

}


void GameCell::PaintCell(const QBrush& brush) {

    setBrush(brush);

}


void GameCell::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    is_alive = !is_alive;
    emit FlipCellState(x(), y());

}
