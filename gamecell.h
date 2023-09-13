#ifndef GAMECELL_H
#define GAMECELL_H

#include <QDebug>

#include <QObject>
#include <QGraphicsRectItem>

class GameCell : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    GameCell(const qreal& x, const qreal& y, const QBrush& brush);

    bool GetState();
    void UpdateCell(const bool& is_alive, const QBrush& brush);

public slots:
    void PaintCell(const QBrush& brush);

signals:
    void FlipCellState(const qreal& x, const qreal& y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool is_alive = false;
};

#endif // GAMECELL_H
