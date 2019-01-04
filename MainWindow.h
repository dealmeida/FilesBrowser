#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TopListView.h"

#include <QMainWindow>
#include <QSharedPointer>

class QFileSystemModel;
class QItemSelection;
class QSplitter;
class QTableView;
class QTreeView;
class QAbstractItemView;
class PaintedView;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateWindowTitle(const QItemSelection & selected, const QItemSelection & deselected);
    void toggleViewVisibility(const QItemSelection & selected, const QItemSelection & deselected);
    void treeSelectionChanged(const QItemSelection&, const QItemSelection&);
private:
    QFileSystemModel *_model;
    QSharedPointer<QSplitter> _splitter;
    QAbstractItemView *_table;
    TopListView *_list;
    QTreeView *_tree;
    PaintedView* _decoratedList;
    QStandardItemModel* _customModel;

    QStandardItemModel* getPopulatedModel();

};

#endif // MAINWINDOW_H
