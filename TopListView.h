#ifndef TOPLISTVIEW_H
#define TOPLISTVIEW_H

#include <QListView>
#include <QPainter>

//ToplistView inheriths QListView and overrides paintEvent() in order to paint a transluscent foreground
class TopListView: public QListView
{
public:
    TopListView( QWidget *parent = nullptr ):QListView( parent ){}
    virtual void publicPaint( QPaintEvent *event )
    {
        paintEvent( event );
    }
protected:
    void paintEvent( QPaintEvent *event ) override
    {
        QListView::paintEvent( event );
        QPainter painter( viewport() );
        painter.setBrush( QColor(0, 0, 255, 90) );
        painter.drawRect( viewport()->rect() );
    }
};

#endif // TOPLISTVIEW_H
