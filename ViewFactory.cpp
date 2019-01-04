#include "ViewFactory.h"

QAbstractItemView *ViewFactory::createView( viewType aType, QWidget *parent)
{
    switch( aType )
    {
    case TABLE:
        return new QTableView( parent );
        break;
    case TREE:
        return new QTreeView( parent );
        break;
    case LIST:
        return new QListView( parent );
        break;
    default:
        return Q_NULLPTR;
        break;
    }
}
