#pragma once

#include "avg_list.h"

class smooth_reader {
  avg_list<10> _buffer;
  int _port;
  int _vlast_value = -1;
public:
  void attach(int port);
  int read();
  bool read(int *n);
};