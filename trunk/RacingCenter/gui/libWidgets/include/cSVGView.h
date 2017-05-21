#ifndef SVGVIEW_H
#define SVGVIEW_H

#include <stdafx.h>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>

QT_BEGIN_NAMESPACE
class QWheelEvent;
class QPaintEvent;
class QFile;
QT_END_NAMESPACE

class cSvgView : public QGraphicsView
{
    Q_OBJECT

public:
    enum RendererType { Native, OpenGL, Image };

    cSvgView(QWidget *parent = 0);

    void openFile(const tBool i_bClear, const QString &fileName, QGraphicsSvgItem** o_oppGraphicsSvgItem );
    void setRenderer(RendererType type = Native);
    void drawBackground(QPainter *p, const QRectF &rect);

	void updateOutline();

public slots:
    void setHighQualityAntialiasing(bool highQualityAntialiasing);
    void setViewBackground(bool enable);
    void setViewOutline(bool enable);

protected:
    //virtual void wheelEvent(QWheelEvent *event);
    virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

private:
    RendererType m_renderer;

    std::vector<QGraphicsItem*> m_oSvgItems;
    
	QGraphicsRectItem *m_backgroundItem;
    QGraphicsRectItem *m_outlineItem;

    QImage m_image;
};

#endif