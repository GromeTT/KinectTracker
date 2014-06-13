#ifndef CUSTOMSTYLEDDELEGATE_H
#define CUSTOMSTYLEDDELEGATE_H

#include <QStyledItemDelegate>



class CustomStyledDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CustomStyledDelegate( QObject* parent );
    virtual ~CustomStyledDelegate();

    void paint( QPainter* painter,
                const QStyleOptionViewItem& option,
                const QModelIndex& index ) const;
    QSize sizeHint( const QStyleOptionViewItem& option,
                    const QModelIndex& index ) const;
    QWidget* createEditor( QWidget* parent,
                           const QStyleOptionViewItem& option,
                           const QModelIndex &index ) const;
    void setEditorData( QWidget* editor,
                        const QModelIndex& index ) const;
    void setModelData( QWidget* editor,
                       QAbstractItemModel* model,
                       const QModelIndex& index ) const;

private:
};

#endif // CUSTOMSTYLEDDELEGATE_H
