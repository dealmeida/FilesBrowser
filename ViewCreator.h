#ifndef VIEWCREATORTEMPLATE_H
#define VIEWCREATORTEMPLATE_H

#include "MainWindow.h"

#include <QWidget>

class ViewCreator
{
public:
    template <class T>
    static T *createView( QWidget *parent = Q_NULLPTR )
    {
        return new T( parent );
    }
};

#endif // VIEWCREATORTEMPLATE_H
