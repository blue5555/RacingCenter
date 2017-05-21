/***************************************************************************
 *   Copyright (C) 2010 by Tn                                              *
 *   thenobody@poczta.fm                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QPainter>
#include "qledindicator.h"

//const qreal QLedIndicator::scaledSize = 20000; /* Visual Studio static const mess */

QLedIndicator::QLedIndicator(const qreal& i_scale, QGraphicsItem *parent) : QGraphicsItem  (parent)
{
    /*setMinimumSize(24,24);*/
    /*setCheckable(true);*/
    onColor1 =  QColor(0,255,0);
    onColor2 =  QColor(0,192,0);
    offColor1 = QColor(0,28,0);
    offColor2 = QColor(0,128,0);

	realSize = 0.05 * i_scale;

	m_bState = false;

	/*this->setAttribute( Qt::WA_OpaquePaintEvent, true);*/
}

void QLedIndicator::resizeEvent(QResizeEvent *event) 
{
    update();
}

QRectF QLedIndicator::boundingRect() const
{
	return QRectF(0, 0, 1000 * realSize, 1000 * realSize);
}

void QLedIndicator::setState(const bool i_bState)
{
	m_bState = i_bState;
	update();
}

void QLedIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
//void QLedIndicator::paintEvent(QPaintEvent *event) 
{
     //qMin(boundingRect().width(), boundingRect().height());

    QRadialGradient gradient;
    //QPainter painter(painter);
    QPen     pen(Qt::black);
             pen.setWidth(1);

	//setBackgroundMode(Qt::);
    painter->setRenderHint(QPainter::Antialiasing);
    //painter->translate(boundingRect().width()/2, boundingRect().height()/2);
    painter->scale(realSize, realSize);

	gradient = QRadialGradient (QPointF(-500,-500), 1500, QPointF(-500,-500));
	gradient.setColorAt(0, QColor(224,224,224));
	gradient.setColorAt(1, QColor(28,28,28));
	painter->setPen(pen);
	painter->setBrush(QBrush(gradient));
	painter->drawEllipse(QPointF(0,0), 500, 500);

	gradient = QRadialGradient (QPointF(500,500), 1500, QPointF(500,500));
	gradient.setColorAt(0, QColor(224,224,224));
	gradient.setColorAt(1, QColor(28,28,28));
	painter->setPen(pen);
	painter->setBrush(QBrush(gradient));
	painter->drawEllipse(QPointF(0,0), 450, 450);

	painter->setPen(pen);
	if( m_bState ) {
		gradient = QRadialGradient (QPointF(-500,-500), 1500, QPointF(-500,-500));
		gradient.setColorAt(0, onColor1);
		gradient.setColorAt(1, onColor2);
	} else {
		gradient = QRadialGradient (QPointF(500,500), 1500, QPointF(500,500));
		gradient.setColorAt(0, offColor1);
		gradient.setColorAt(1, offColor2);
	}
	painter->setBrush(gradient);
	painter->drawEllipse(QPointF(0,0), 400, 400);
}

