#ifndef cPixmapItem_H
#define cPixmapItem_H

#include <stdafx.h>
#include <QGraphicsView>
#include <QPainter>

class cPixmapItem: public QGraphicsView
{
	Q_OBJECT

	QGraphicsScene *scene;
	QPixmap		   *image;

public:
	cPixmapItem(QGraphicsView *parent=0);
	~cPixmapItem();

	void UpdateImage(const QString& i_QSFilename);

public:

protected:
	void resizeEvent(QResizeEvent *event);
	void drawBackground(QPainter *painter, const QRectF &rect);

};

#endif // cPixmapItem_H