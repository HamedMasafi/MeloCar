#include "Arduino.h"
#include "smooth_reader.h"
#include "avg_list.h"

void smooth_reader::attach(int port)
{
  _port = port;
}

int smooth_reader::read()
{
  return _buffer.put_and_get(analogRead(_port));
}

bool smooth_reader::read(int *n)
{
  auto buffer = _buffer.put_and_get(analogRead(_port));

  if (buffer == _vlast_value)
    return false;

  _vlast_value = buffer;
  return true;
}