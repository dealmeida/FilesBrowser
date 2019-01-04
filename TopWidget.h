#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QAbstractScrollArea>

class TopWidget : public QAbstractScrollArea
{
public:
    TopWidget(QWidget *parent = nullptr):QAbstractScrollArea(parent){}
    void setTransparent( const int percentage )
    {
        QAbstractScrollArea::setVisible( !visible );
    }

protected:
    void paintEvent( QPaintEvent *event ) override
    {
        QAbstractScrollArea::paintEvent( event );
        QPainter painter( viewport() );
        painter.setBrush( QColor(0, 0, 0, 90) );
        painter.drawRect( viewport()->rect() );
    }
private:
};

#endif // TOPWIDGET_H
