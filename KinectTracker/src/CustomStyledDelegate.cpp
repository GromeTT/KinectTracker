#include "../inc/CustomStyledDelegate.h"
#include <opencv2/opencv.hpp>
#include <QLineEdit>
#include <QPainter>

Q_DECLARE_METATYPE( cv::Size )


CustomStyledDelegate::CustomStyledDelegate( QObject* parent )
    : QStyledItemDelegate( parent )
{

}

CustomStyledDelegate::~CustomStyledDelegate()
{

}

void CustomStyledDelegate::paint( QPainter* painter,
                                  const QStyleOptionViewItem& option,
                                  const QModelIndex& index ) const
{
    //       Unwrap data and display it.
    //       If this step is not done, the QTableWidgetItem
    //       will not have any caption for costume types.

    if ( index.data().canConvert<cv::Size>() )
    {
        // case: QVariant contains an object from type cv::Size
        if ( option.state & QStyle::State_Selected )
            painter->fillRect(option.rect, option.palette.highlight());
        cv::Size size = qvariant_cast<cv::Size>( index.data() );
        painter->drawText( option.rect ,QString( "{ %1, %2}" ).arg( size.width )
                                                               .arg( size.height )  );
    }
    else
    {
        QStyledItemDelegate::paint( painter,
                                    option,
                                    index );
    }
}

QSize CustomStyledDelegate::sizeHint( const QStyleOptionViewItem& option,
                                      const QModelIndex& index ) const
{
    return QStyledItemDelegate::sizeHint( option,
                                          index );
}


QWidget* CustomStyledDelegate::createEditor( QWidget* parent,
                                             const QStyleOptionViewItem& option,
                                             const QModelIndex& index ) const
{
    return QStyledItemDelegate::createEditor( parent,
                                              option,
                                              index );
}

void CustomStyledDelegate::setEditorData( QWidget* editor,
                                          const QModelIndex& index ) const
{
    if ( index.data().canConvert<cv::Size>() )
    {
        cv::Size size = qvariant_cast<cv::Size>( index.data() );
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>( editor );
        lineEdit->setText( QString( "{ %1, %2 }" ).arg( size.width )
                                                  .arg( size.height ) );
    }
    else
    {
        QStyledItemDelegate::setEditorData( editor,
                                            index );
    }
}


void CustomStyledDelegate::setModelData( QWidget* editor,
                                         QAbstractItemModel* model,
                                         const QModelIndex& index ) const
{
    if ( index.data().canConvert<cv::Size>() )
    {
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>( editor );
        QString tmp ( lineEdit->text() );
        tmp.remove( 0, 1 );
        tmp.remove( tmp.length()-1, 1 );
        QStringList list = tmp.split( "," );
        cv::Size size;
        size.width = list.at( 0 ).toFloat();
        size.height = list.at( 1 ).toFloat();
        model->setData( index, QVariant::fromValue( size ) );

    }
    else
    {
        QStyledItemDelegate::setModelData( editor,
                                           model,
                                           index );
    }
}

