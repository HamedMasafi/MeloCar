#include "light_dancer.h"

void basic_light_dancer::step()
{
}

void police_light_dancer::step()
{
    if (_step)
    {
        pixels->Color(0, 0, 150);
        _step = 0;
    }
    else
    {
        pixels->Color(150, 0, 0);
        _step = 1;
    }
}