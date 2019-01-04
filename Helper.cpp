#include "Helper.h"

#include <QDate>
#include <QHash>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Helper
{
// ToDO
// make it RECURSIVE
// GetNbOfLevels
// For each level, inject:
// 1. the nb Min of the Loop
// 2. the nb Max of the Loop
// 3. a rule specifying how to display the Date Name
QStandardItemModel* getPopulatedModel()
{
    QStandardItemModel* aModel = new QStandardItemModel;
    QStandardItem* invisibleItem = aModel->invisibleRootItem();
    const QHash<int, QString> years = {{2017,"Chicken"}, {2018,"Dog"}, {2019, "Pig"},
                                       {2020,"Rat"}, {2021,"Ox"}, {2022, "Tiger"}};
    const int yearMin = 2017;
    const int yearMax = 2022;
    const int monthMin = 1;
    const int monthMax = 12;
    const int dayMin = 1;
    //
    for(int y=yearMin; y<=yearMax; y++)
    {
        QDate tmpDate = QDate(y, monthMin, dayMin);
        QList<QStandardItem*> thisYear( QList<QStandardItem*>() << new QStandardItem( tmpDate.toString( "yyyy" ) ) << new QStandardItem( years[y] ) << new QStandardItem( "Extra" ) );
        //QList<QStandardItem*> thisYear( QList<QStandardItem*>() << new QStandardItem( tmpDate.toString( "yyyy" ) ) );
        invisibleItem->appendRow( thisYear );
        for(int m=monthMin; m<=monthMax; m++)
        {
            tmpDate = QDate(y, m, dayMin);
            QList<QStandardItem*> thisMonth( QList<QStandardItem*>() << new QStandardItem( tmpDate.toString( "M" ) ) << new QStandardItem( tmpDate.toString( "MMMM" ) ) );
            thisYear.first()->appendRow( thisMonth );
            for(int d=dayMin; d<=tmpDate.daysInMonth(); d++)
            {
                tmpDate = QDate(y, m, d);
                QList<QStandardItem*> thisDay( QList<QStandardItem*>() << new QStandardItem( tmpDate.toString( "d" ) ) << new QStandardItem( tmpDate.toString( "dddd" ) ) );
                thisMonth.first()->appendRow( thisDay );
            }
        }
    }
    return aModel;
}
}
