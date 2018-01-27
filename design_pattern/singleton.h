#ifndef SINGLETON_H_
#define SINGLETON_H_

// NOTE: Not thread safe
class Singleton
{
public:
  static Singleton& getInstance()
  {
    static Singleton instance;  // Guaranteed to be destroyed
    return instance;            // Instantiated on first use
  }

private:
  Singleton() {}

  // C++ 03
//  Singleton(Singleton const&);       // Don't implement
//  void operator=(Singleton const&);  // Don't implement

public:
  Singleton(Singleton const&)      = delete;
  void operator=(Singleton const&) = delete;
};

#endif /* SINGLETON_H_ */
