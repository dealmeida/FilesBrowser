#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H


#include <QAbstractItemView>
#include <QTreeView>
#include <QTableView>
#include <QListView>


class ViewFactory
{
public:
    enum viewType { LIST, TREE, TABLE };
    static QAbstractItemView *createView( viewType aType, QWidget *parent = Q_NULLPTR );
};


#endif // VIEWFACTORY_H
