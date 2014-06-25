#ifndef FLOATEDITOR_H
#define FLOATEDITOR_H

#include <QDoubleSpinBox>

class FloatEditor : public QDoubleSpinBox
{
    Q_OBJECT

public:
    FloatEditor( QWidget* parent );
    ~FloatEditor();

    float data() const;
    void  setData( const float number );

private:
    Q_PROPERTY( float data
                READ data
                WRITE setData
                USER true )
};

#endif // FLOATEDITOR_H
