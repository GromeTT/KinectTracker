#include "../inc/CustomStyledDelegate.h"
#include <opencv2/opencv.hpp>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPainter>
#include <QDebug>

Q_DECLARE_METATYPE( cv::Size )


CustomStyledDelegate::CustomStyledDelegate( QObject* parent )
    : QStyledItemDelegate( parent )
{

}

CustomStyledDelegate::~CustomStyledDelegate()
{

}

QString CustomStyledDelegate::displayText( const QVariant& value,
                                           const QLocale& locale ) const
{
    if ( value.canConvert<cv::Size>() )
    {
        cv::Size size = qvariant_cast<cv::Size>( value );
        return QString( "{%1, %2}" ).arg( size.width )
                                    .arg( size.height );
    }
    else
    {
        return QStyledItemDelegate::displayText( value, locale );
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
    if ( index.data().canConvert<cv::Size>() )
    {
        QLineEdit* editor = new QLineEdit( parent );
        QRegularExpression rx ( "{\\d+, \\d+}" );
        QRegularExpressionValidator* validator = new QRegularExpressionValidator( rx, editor );
        editor->setValidator( validator );
        return editor;
    }
    else
    {
        return QStyledItemDelegate::createEditor( parent,
                                                  option,
                                                  index );
    }
}

void CustomStyledDelegate::setEditorData( QWidget* editor,
                                          const QModelIndex& index ) const
{
    if ( index.data().canConvert<cv::Size>() )
    {
        cv::Size size = qvariant_cast<cv::Size>( index.data() );
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>( editor );
        lineEdit->setText( QString( "{%1, %2}" ).arg( size.width )
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

