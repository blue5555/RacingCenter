#include "cSVGView.h"

#include <QFile>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <qmath.h>

#ifndef QT_NO_OPENGL
#include <QGLWidget>
#endif

cSvgView::cSvgView(QWidget *parent)
    : QGraphicsView(parent)
    , m_renderer(Native)
    //, m_svgItem(0)
	//, m_svgItemRot(0)
    , m_backgroundItem(0)
    , m_outlineItem(0)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);

    //// Prepare background check-board pattern
    //QPixmap tilePixmap(64, 64);
    //tilePixmap.fill(Qt::white);
    //QPainter tilePainter(&tilePixmap);
    //QColor color(220, 220, 220);
    //tilePainter.fillRect(0, 0, 32, 32, color);
    //tilePainter.fillRect(32, 32, 32, 32, color);
    //tilePainter.end();

    //setBackgroundBrush(tilePixmap);
}

void cSvgView::drawBackground(QPainter *p, const QRectF &)
{
    p->save();
    p->resetTransform();
    p->drawTiledPixmap(viewport()->rect(), backgroundBrush().texture());
    p->restore();
}

void cSvgView::openFile(const tBool i_bClear, const QString &fileName, QGraphicsSvgItem** o_oppGraphicsSvgItem )
{
    //if (!file.exists())
    //    return;

    QGraphicsScene *s = scene();

	s->setBackgroundBrush(QBrush(QColor(0,0,0),Qt::SolidPattern));

    bool drawBackground = (m_backgroundItem ? m_backgroundItem->isVisible() : false);
    bool drawOutline = (m_outlineItem ? m_outlineItem->isVisible() : true);

	if(i_bClear) {
	    m_oSvgItems.clear();
		s->clear();
		//resetTransform();
		if(m_backgroundItem) {
			//delete m_backgroundItem;
			m_backgroundItem = NULL;
		}
		if(m_outlineItem) {
			//delete m_outlineItem;
			m_outlineItem = NULL;
		}
	}

    QGraphicsSvgItem* m_svgItem = new QGraphicsSvgItem(fileName);
	if(o_oppGraphicsSvgItem) {
		*o_oppGraphicsSvgItem = m_svgItem;
	}
	m_oSvgItems.push_back(m_svgItem);

    m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    m_svgItem->setCacheMode(QGraphicsItem::NoCache);
    m_svgItem->setZValue(0);

    if(!m_backgroundItem) {
		m_backgroundItem = new QGraphicsRectItem(m_svgItem->boundingRect());
		m_backgroundItem->setBrush(Qt::white);
		m_backgroundItem->setPen(Qt::NoPen);
		m_backgroundItem->setVisible(drawBackground);
		m_backgroundItem->setZValue(-1);
		s->addItem(m_backgroundItem);
	}

	if(!m_outlineItem) {
		m_outlineItem = new QGraphicsRectItem(m_svgItem->boundingRect());
		QPen outline(Qt::black, 2, Qt::DashLine);
		outline.setCosmetic(true);
		m_outlineItem->setPen(outline);
		m_outlineItem->setBrush(Qt::NoBrush);
		m_outlineItem->setVisible(drawOutline);
		m_outlineItem->setZValue(1);
		s->addItem(m_outlineItem);
	}

    s->addItem(m_svgItem);
    
    s->setSceneRect(m_outlineItem->boundingRect().adjusted(-10, -10, 10, 10));

}

void cSvgView::updateOutline()
{
	QGraphicsScene *s = scene();
	m_outlineItem->setRect( s->sceneRect() );
}

void cSvgView::setRenderer(RendererType type)
{
    m_renderer = type;

    if (m_renderer == OpenGL) {
#ifndef QT_NO_OPENGL
        setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif
    } else {
        setViewport(new QWidget);
    }
}

void cSvgView::setHighQualityAntialiasing(bool highQualityAntialiasing)
{
#ifndef QT_NO_OPENGL
    setRenderHint(QPainter::HighQualityAntialiasing, highQualityAntialiasing);
#else
    Q_UNUSED(highQualityAntialiasing);
#endif
}

void cSvgView::setViewBackground(bool enable)
{
    if (!m_backgroundItem)
          return;

    m_backgroundItem->setVisible(enable);
}

void cSvgView::setViewOutline(bool enable)
{
    if (!m_outlineItem)
        return;

    m_outlineItem->setVisible(enable);
}

void cSvgView::paintEvent(QPaintEvent *event)
{
    if (m_renderer == Image) {
        if (m_image.size() != viewport()->size()) {
            m_image = QImage(viewport()->size(), QImage::Format_ARGB32_Premultiplied);
        }

        QPainter imagePainter(&m_image);
        QGraphicsView::render(&imagePainter);
        imagePainter.end();

        QPainter p(viewport());
        p.drawImage(0, 0, m_image);

    } else {
        QGraphicsView::paintEvent(event);
    }
}

//void cSvgView::wheelEvent(QWheelEvent *event)
//{
//    qreal factor = qPow(1.2, event->delta() / 240.0);
//    scale(factor, factor);
//    event->accept();
//}

void cSvgView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	fitInView(QRectF(0,0,scene()->width(),scene()->height()), Qt::IgnoreAspectRatio);
}