class Elapsed {
  int _timeout{ 0 };
  int _startTime;
  void *(*_cb)();

public:
  Elapsed(int timeout);
  
  void setCallback(void *(cb)());

  void check();
  void reset();
};