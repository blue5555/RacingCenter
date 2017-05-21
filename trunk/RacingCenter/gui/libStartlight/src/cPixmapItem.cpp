#include "cPixmapItem.h"

cPixmapItem::cPixmapItem(QGraphicsView *parent) : 
 QGraphicsView(parent)
,scene(NULL)
{
	int width = this->geometry().width();
	int height = this->geometry().height();
	// QMessageBox::information(this, tr("WIDTH HEIGHT"), tr("Width= %1 Height= %2").arg(QString::number(width, 10), QString::number(height, 10)));
	scene = new QGraphicsScene(QRectF(0, 0, width, height), 0);

	this->setScene(scene);
	this->show();
}

cPixmapItem::~cPixmapItem()
{

}

void cPixmapItem::UpdateImage(const QString& i_QSFilename)
{
	//QImage tempImage(i_QSFilename);
	//QImage tempImage("C:/Users/Fabian/Documents/Carrera/NewCarrera/trunk/CPP/gui/startlight/forms/images/State_1.jpg");
	//if (tempImage.isNull()) {
	//	//QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
	//	//return;
	//}
	//QImage image = tempImage.convertToFormat(QImage::Format_RGB32);
	//QPixmap pixmap = QPixmap::fromImage(image);
		
	QPixmap pixmap(i_QSFilename);

	qDebug() << i_QSFilename;

	int width = this->geometry().width();
	int height = this->geometry().height();

	QGraphicsPixmapItem *item = scene->addPixmap(pixmap.scaled(QSize(
		(int)scene->width(), (int)scene->height()),
		Qt::KeepAspectRatio, Qt::SmoothTransformation));
	this->fitInView(QRectF(0, 0, width, height),
		Qt::KeepAspectRatio);

	fitInView(QRectF(0,0,scene->width(),scene->height()), Qt::IgnoreAspectRatio);

}

void cPixmapItem::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	fitInView(QRectF(0,0,scene->width(),scene->height()), Qt::IgnoreAspectRatio);
}

void cPixmapItem::drawBackground(QPainter *painter, const QRectF &rect)
{
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	QRectF r;

	//r.setRect(0,0,image->width(),image->height());
	//painter->drawImage(r,*image);
}