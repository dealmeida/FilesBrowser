#ifndef INTEGEREDITORDELEGATE_H
#define INTEGEREDITORDELEGATE_H

#include <QItemDelegate>

class IntegerEditorDelegate : public QItemDelegate
{
    Q_OBJECT
    enum dataFormat { number=0, name=1 };
public:
    IntegerEditorDelegate( QObject *parent=0 );

    QWidget* createEditor( QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const override;

    void setEditorData( QWidget *editor,
                        const QModelIndex &index ) const override;

    void setModelData( QWidget *editor,
                       QAbstractItemModel *model,
                       const QModelIndex &index ) const override;

    void updateEditorGeometry( QWidget *editor,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index ) const override;


private:
    template <typename T>
    T* getEditor( QWidget *parent ) const
    {
        return new T(parent);
    }

};

#endif // INTEGEREDITORDELEGATE_H
