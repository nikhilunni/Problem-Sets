#ifndef COUNTER_H
#define COUNTER_H

class Counter {
public:
  void increment() { ++_count; }
  uint32_t get_count() const { return _count; }
private:
  uint32_t _count = 0;
};

#endif
