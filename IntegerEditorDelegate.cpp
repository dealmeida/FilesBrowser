#include "IntegerEditorDelegate.h"

#include <QLineEdit>
#include <QSpinBox>

IntegerEditorDelegate::IntegerEditorDelegate( QObject *parent )
    :QItemDelegate(parent)
{

}


QWidget* IntegerEditorDelegate::createEditor( QWidget* parent,
                                              const QStyleOptionViewItem&,
                                              const QModelIndex& index ) const
{
    if( index.column() == number )
    {
        QSpinBox* tmpEdt = getEditor<QSpinBox>( parent );
        return tmpEdt;
    }
    else
    {
        return getEditor<QLineEdit>( parent );
    }
}

void IntegerEditorDelegate::setEditorData( QWidget *editor,
                                           const QModelIndex &index ) const
{
    const QVariant currentValue = index.data( Qt::EditRole );
    if( index.column() == number )
    {
        static_cast<QSpinBox*>( editor )->setValue( currentValue.toInt() );
    }
    else
    {
        static_cast<QLineEdit*>( editor )->setText( currentValue.toString() );
    }
}

void IntegerEditorDelegate::setModelData( QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index ) const
{
    QVariant newValue;
    if( index.column() == number )
    {
        newValue = static_cast<QSpinBox*>( editor )->value();
    }
    else
    {
        newValue = static_cast<QLineEdit*>( editor )->text();
    }
    model->setData( index, QVariant( newValue ), Qt::EditRole );
}

void IntegerEditorDelegate::updateEditorGeometry( QWidget *editor,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex& ) const
{
    QRect tempRect(option.rect);
    tempRect.setY( tempRect.y()-4 );
    tempRect.setHeight( tempRect.height()+4 );
    editor->setGeometry( tempRect );
}


