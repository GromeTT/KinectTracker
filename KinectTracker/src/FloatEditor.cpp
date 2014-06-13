#include "../inc/FloatEditor.h"


FloatEditor::FloatEditor(QWidget* parent)
    : QDoubleSpinBox( parent )
{
}

FloatEditor::~FloatEditor()
{
}

float FloatEditor::data() const
{
    return static_cast<float>( value() );
}

void FloatEditor::setData( const float number )
{
    setValue( number );
}
