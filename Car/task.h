class AbstractTask {
protected:
  void *(*_cb)();
public:
  void setCallback(void *(cb)());
};

class Elapsed : public AbstractTask {
  int _timeout{ 0 };
  int _startTime;
public:
  Elapsed(int timeout);

  void check();
  void reset();
};

class Timer : public AbstractTask {
public:
};

class CommandWithSpace : public AbstractTask {
  int _timeout;
  int _lastExec;
public:
  CommandWithSpace(int timeout = 200);
  void tryExec();
};