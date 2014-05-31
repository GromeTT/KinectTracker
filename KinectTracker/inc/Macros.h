#ifndef MACROS_H
#define MACROS_H

#define SAFE_DELETE( x ) \
{                        \
    if ( x )             \
    {                    \
        delete x;        \
        x = nullptr;     \
    }                    \
}                        \

#endif // MACROS_H
