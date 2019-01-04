#ifndef DECORATEDVIEW_H
#define DECORATEDVIEW_H

#include "TopListView.h"

#include <QAbstractItemView>
#include <QPainter>

//Decorate Patern
class DecoratedView: public TopListView
{
public:
    DecoratedView( TopListView* trueView ):_trueView(trueView)
    {
    }

    virtual void setVisible( bool visible ) override
    {
        _trueView->setVisible( visible );
    }

private:
    TopListView* _trueView;

};

//Concrete Decorated View
class PaintedView: public DecoratedView
{
public:
    PaintedView( TopListView* trueView ):DecoratedView(trueView), _visible(true)
    {
    }
    //Set visible will ignore whatever visibility parameter used by the client
    // and will work as a toggleVisibility func
    virtual void setVisible( bool visible ) override
    {
        Q_UNUSED( visible );
        _visible = !_visible;
        DecoratedView::setVisible( _visible );
    }
private:
    bool _visible;
};

#endif // DECORATEDVIEW_H
