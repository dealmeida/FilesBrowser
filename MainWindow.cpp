#include "MainWindow.h"

#include "IntegerEditorDelegate.h"
#include "DecoratedView.h"
#include "Helper.h"
#include "ViewCreator.h"
//#include "ViewFactory.h"

#include <QApplication>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QListView>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>

#include <iostream>
#include <memory>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), _customModel(nullptr)
{
    //Tests on Move Constructors and Move Assignement Operators
    {
        //Helper::Base base("First Base");
        Helper::Derived derived("First Derived");

        Helper::Derived derivedTwo = derived;
        derivedTwo.setBigString("Test Derived Two Big String");

        Helper::Derived derivedThree;
        derivedThree = derived;
        derivedThree.setBigString("Test Derived THREE BS");

        std::cout<<"Big String 1: "<<derived.getBigString()<<std::endl;
        std::cout<<"Big String 2: "<<derivedTwo.getBigString()<<std::endl;
        std::cout<<"Big String 3: "<<derivedThree.getBigString()<<std::endl;

        Helper::Derived derivedFour = std::move( derivedThree );
        Helper::Derived derivedFive;
        derivedFive = std::move( derivedTwo );

        //std::unique_ptr<Helper::Base> basePtr( new Helper::Base( "Rodrigo", "Almeida" ) );
        //std::unique_ptr<int[]> basePtr(new int[3]());
//        basePtr.get()[1]=2;
//        basePtr.get()[2]=3;
//        basePtr.get()[3]=4;

                //QSharedPointer<Helper::Base>(new Helper::Base("Shared Base"));
        //std::cout<<"Base Name: "<<basePtr.get()[2] <<std::endl;

    }

    //_splitter = new QSplitter( this );
    _splitter = QSharedPointer<QSplitter>(new QSplitter(this), &QObject::deleteLater);

    /*
    table = ViewFactory::createView( ViewFactory::TABLE, splitter );
    tree = ViewFactory::createView( ViewFactory::TREE, splitter );
    list = ViewFactory::createView( ViewFactory::LIST, splitter );
    */
    _table = ViewCreator::createView<QTableView>( _splitter.data() );
    _list = ViewCreator::createView<TopListView>( _splitter.data() );
    _tree = ViewCreator::createView<QTreeView>( _splitter.data() );

    _model = new QFileSystemModel;
    _model->setRootPath( "/Users/rodrigoalmeida/" );
    _table->setModel( _model );
    _table->setRootIndex( _model->index( "/Users/rodrigoalmeida/" ) );
    qobject_cast<QTableView *>(_table)->horizontalHeader()->setSortIndicatorShown(true);
    qobject_cast<QTableView *>(_table)->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
    qobject_cast<QTableView *>(_table)->setSortingEnabled( true );

    //Create a custom model populating it with calendar tree data (years, months, days)
    _customModel = Helper::getPopulatedModel();
    _tree->setModel( _customModel );
    _customModel->setHorizontalHeaderLabels(
                QStringList() << QApplication::translate("Dates", "Number")
                << QApplication::translate("Dates", "Name"));

    _tree->setItemDelegate( new IntegerEditorDelegate( this ) );

    //_tree->setRootIndex( _model->index( "/Users/rodrigoalmeida/" ) );


    _list->setModel( _model);
    _list->setAlternatingRowColors( true );
    _list->setRootIndex( _model->index( "/Users/rodrigoalmeida/" ) );
    //The decoratedList only works when calling the setVisible() method
    _decoratedList = new PaintedView( _list );

    setCentralWidget( _splitter.data() );
    setFixedSize( 900, 500 );

    connect( _table->selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
             this,
             SLOT(updateWindowTitle(const QItemSelection&, const QItemSelection&) ));

    connect( _tree->selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
             this,
             SLOT(toggleViewVisibility(const QItemSelection&, const QItemSelection&) ));

    connect( _tree->selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
             this,
             SLOT(treeSelectionChanged(const QItemSelection&, const QItemSelection&) ));


    this->setWindowTitle("File Explorer");
}

MainWindow::~MainWindow()
{
    delete _model;
    delete _tree;
    delete _table;
    delete _list;
    //delete _splitter;
    delete _customModel;
}

void MainWindow::updateWindowTitle(const QItemSelection&, const QItemSelection&)
{
    QString newText = _table->currentIndex().data( Qt::DisplayRole ).toString();
    this->setWindowTitle( newText );
}

void MainWindow::toggleViewVisibility(const QItemSelection &, const QItemSelection &)
{
    std::cout<<"Starting operation"<<std::endl;
    long int total = 0;
    for(long int i=0; i<100000000; i++)
        total += i;
    //_decoratedList->setVisible( false );
    std::cout<<"Finishing operation: "<<total<<std::endl;
}

void MainWindow::treeSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    const QModelIndex index = _tree->selectionModel()->currentIndex();
    const QString selectionText = index.data( Qt::DisplayRole ).toString();
    int level = 0;
    QModelIndex isRoot = index;
    while( isRoot.parent() != QModelIndex() )
    {
        level++;
        isRoot = isRoot.parent();
    }
    setWindowTitle( selectionText + " Level "+ QString::number(level));
}

