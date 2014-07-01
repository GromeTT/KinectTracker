#include "../inc/ImageWidget.h"
#include "ui_ImageWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

/*!
   \brief ImageWidget::ImageWidget
   Standardconstructor.
 */
ImageWidget::ImageWidget( QWidget* parent )
    : QWidget( parent )
    , ui ( new Ui::ImageWidget )
    , m_leftMousePressed( false )
    , m_startPoint( 0,0 )
    , m_endPoint( 0,0 )
{
    ui->setupUi( this );
    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    ui->image->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    ui->image->setMouseTracking( true );
    setMouseTracking( true );

    ui->image->installEventFilter( this );
}

/*!
   \brief ImageWidget::~ImageWidget
   Destroyes the object.
 */
ImageWidget::~ImageWidget()
{

}

/*!
   \brief ImageWidget::setImage
    Displays \a image.
 */
void ImageWidget::setImage( const QImage& image )
{
    m_image     = QImage( image );
    ui->image->setPixmap( QPixmap::fromImage( m_image ) );
    this->resize( m_image.size() );
    ui->image->resize( m_image.size() );
}

/*!
   \brief ImageWidget::eventFilter
   Displayes informations in the statusbar.
 */
bool ImageWidget::eventFilter( QObject* object, QEvent* event )
{
    if ( object == ui->image )
    {
        if ( QMouseEvent* e = dynamic_cast<QMouseEvent*>( event ) )
        {
            QString text;
            text.append( "x:" );
            text.append( QString::number( e->pos().x() ) );
            text.append( " ");
            text.append( "y:" );
            text.append( QString::number( e->pos().y() ) );
            ui->statusbar->setText( text );
            if ( e->button() == Qt::LeftButton )
            {
                if ( ( e->buttons() & Qt::LeftButton ) == Qt::LeftButton )
                {
                    // case: Left mouse pressed.
                    m_startPoint = e->pos();
                    m_endPoint   = e->pos();
                    m_leftMousePressed = true;
                    emit leftMousePressed( e->pos() );
                }
                else
                {
                    // case: Left mouse released.
                    m_leftMousePressed = false;
                    m_endPoint = e->pos();
                    if ( m_startPoint == m_endPoint )
                    {
                        // case: Start and end position are equal.
                        //       Draw the original image. And reset the rectangle.
                        ui->image->setPixmap( QPixmap::fromImage( m_image ) );
                        m_startPoint = QPoint( 0, 0 );
                        m_endPoint = QPoint( 0, 0 );
                    }
                    emit leftMouseReleased( e->pos() );
                }
            }
            else
            {
                // case: Mouse moved.
                emit mouseMoved( e->pos() );
                if ( m_leftMousePressed )
                {
                    // case: Left mouse button is  pressed.
                    //       Update the end position.
                    m_endPoint = e->pos();
                    if ( m_endPoint != m_startPoint )
                    {
                        // case: Start and end position are different.
                        //       Update the rectangle.
                        qDebug() << "Startpos: " << m_startPoint.x() << " " << m_startPoint.y();
                        qDebug() << "Endpos: "   << m_endPoint.x() << " "   << m_endPoint.y();
                        QImage tmp = m_image;
                        QPainter painter( &tmp );
                        painter.setPen( Qt::red );
                        painter.drawRect( QRect( m_startPoint, m_endPoint ) );
                        painter.end();
                        ui->image->setPixmap( QPixmap::fromImage( tmp ) );
                    }
                }
            }

        }
        return false;
    }
    return true;
}

/*!
   \brief ImageWidget::rect
   Returns the rectangle painted by the user.
 */
QRect ImageWidget::rect() const
{
    return QRect( m_startPoint, m_endPoint );
}
