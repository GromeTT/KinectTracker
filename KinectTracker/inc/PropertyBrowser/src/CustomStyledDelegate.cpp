#include "../inc/CustomStyledDelegate.h"
#include "../inc/FixedPropertyVector.h"
#include "../inc/FloatEditor.h"
#include "../../Kinect/inc/SkeletonData.h"
#include <opencv2/opencv.hpp>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QComboBox>
#include <QPainter>
#include <QDebug>

Q_DECLARE_METATYPE( cv::Size )
Q_DECLARE_METATYPE( FixedPropertyVector )

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
    else if ( value.canConvert<FixedPropertyVector>() )
    {
        FixedPropertyVector vec = qvariant_cast<FixedPropertyVector>( value );
        QString text ( "{" );
        for ( int i = 0; i < vec.size()-1; ++i )
        {
            text.append( QString::number( vec.at( i ) ) );
            text.append( ", " );
        }
        text.append( QString::number( vec.last() ) );
        text.append( "}" );
        return text;
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

/*!
   \brief CustomStyledDelegate::createEditor
 */
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
    else if ( index.data().canConvert<FixedPropertyVector>() )
    {
        QLineEdit* editor = new QLineEdit( parent );
        QRegularExpression rx ( "{\\d(, \\d)*}" );
        QRegularExpressionValidator* validator = new QRegularExpressionValidator( rx, editor );
        editor->setValidator( validator );
        return editor;
    }
    else if ( index.data( Qt::EditRole ).type() == QMetaType::Int )
    {
        QString typeName ( index.data( Qt::EditRole ).typeName() );
        if ( typeName == "SkeletonData::Joints" )
        {
            QComboBox* editor = new QComboBox( parent );
            editor->addItem( "Hip" );
            editor->addItem( "Spine" );
            editor->addItem( "ShoulderCenter" );
            editor->addItem( "ShoulderLeft" );
            editor->addItem( "ElbowLeft" );
            editor->addItem( "WristLeft" );
            editor->addItem( "HandLeft" );
            editor->addItem( "ShoulderRight" );
            editor->addItem( "ElbowRight" );
            editor->addItem( "WristRight" );
            editor->addItem( "HandRight" );
            editor->addItem( "HipLeft" );
            editor->addItem( "KneeLeft" );
            editor->addItem( "AnkleLeft" );
            editor->addItem( "FootLeft" );
            editor->addItem( "HipRight" );
            editor->addItem( "KneeRight" );
            editor->addItem( "AnkleRight" );
            editor->addItem( "FootRight" );
            return editor;
        }
        else
        {
            QSpinBox* editor = static_cast<QSpinBox*>( QStyledItemDelegate::createEditor( parent,
                                                                                          option,
                                                                                          index ) );
            connect( editor, SIGNAL( valueChanged(int) ), this, SLOT( commit() ) );
            return editor;
        }

    }
    else if ( index.data( Qt::EditRole ).type() == QMetaType::Float )
    {
        FloatEditor* editor  = static_cast<FloatEditor*>( QStyledItemDelegate::createEditor( parent,
                                                                                             option,
                                                                                             index ) );
        editor->setRange( -999999, 999999 );
        connect( editor, SIGNAL( valueChanged(double) ), this, SLOT( commit() ) );
        return editor;
    }
    else if ( index.data( Qt::EditRole ).type() == QMetaType::Double )
    {
        QDoubleSpinBox* editor = static_cast<QDoubleSpinBox*>( QStyledItemDelegate::createEditor( parent,
                                                                                                  option,
                                                                                                  index ) );
        connect( editor, SIGNAL( valueChanged(double) ), this, SLOT( commit() ) );
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
    else if ( index.data().canConvert<FixedPropertyVector>() )
    {
        FixedPropertyVector vec = qvariant_cast<FixedPropertyVector>( index.data() );
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>( editor );
        QString text ( "{" );
        for ( int i = 0; i < vec.size()-1; ++i )
        {
            text.append( QString::number( vec.at( i ) ) );
            text.append( ", " );
        }
        text.append( QString::number( vec.last() ) );
        text.append( "}" );
        lineEdit->setText( text );
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
    else if ( index.data().canConvert<FixedPropertyVector>() )
    {
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>( editor );
        QString tmp ( lineEdit->text() );
        tmp.remove( 0, 1 );
        tmp.remove( tmp.length()-1, 1 );
        QStringList list = tmp.split( "," );
        FixedPropertyVector vec ( list.count() );
        for ( int i = 0; i < list.count(); ++i )
        {
            vec.setData( i, list.at( i ).toFloat() );
        }
        QVariant v = QVariant::fromValue( vec );
        model->setData( index, v );
    }
    else
    {
        QStyledItemDelegate::setModelData( editor,
                                           model,
                                           index );
    }
}

void CustomStyledDelegate::commit()
{
    QWidget* widget = qobject_cast<QWidget*>( QObject::sender() );
    emit commitData( widget );
}

