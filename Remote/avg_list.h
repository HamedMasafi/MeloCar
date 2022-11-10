#pragma once
 
template <int size>
class avg_list
{
  int _numbers[size];
  int _total = 0;
  int _index = 0;
public:

  avg_list() {
    _total = _index = 0;
    for (int i = 0; i < _total; i++) {
      _numbers[i] = 0;
    }
  }
  int put_and_get(int new_value)
  {
    _total -= _numbers[_index];
    _numbers[_index] = new_value;

    if (++_index >= size)
      _index = 0;
    _total += new_value;
    return _total / size;
  }
};
