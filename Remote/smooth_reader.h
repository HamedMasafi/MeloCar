#pragma once

#include "avg_list.h"

class smooth_reader {
  avg_list<10> _buffer;
  int _port;
  int _vlast_value = -1;

  int _min;
  int _max;

public:
  smooth_reader(int min, int max, int telo = 1);
  void attach(int port);
  int read();
  bool read(int *n);
};