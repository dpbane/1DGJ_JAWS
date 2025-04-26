# pragma once

namespace pattern {

template<typename T>
class Singleton {
public:
  Singleton(const Singleton &obj) = delete;
  Singleton &operator=(const Singleton &obj) = delete;
  Singleton(Singleton &&) = delete;
  Singleton &operator=(Singleton &&) = delete;

  static inline T &Instance() {
    static T instance;
    return instance;
  }

protected:
  Singleton() = default;
  virtual ~Singleton() = default;
};

}
