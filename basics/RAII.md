### RAII - Resource Acquisition Is Initialization

keyword: Scoped-Bound Resource Management - SBRM  

I perfer use Scoped-Bound Resource Management, It's clear and unmisleading.
```
RawResourceHandle* handle = createNewResource();
handle->performInvalidOperation(); // Ooops, throws exception.
...
deleteResource(handle); // never gets called, so the resource leaks.
```

```
class ManageResourceHandle {
public:
  ManageResourceHandle(RawResourceHandle* rawHandle_) : rawHandle(rawHandle_) {};
  ~ManageResourceHandle() { delete rawHandle; }

  ... // other stuff

private:
  RawResourceHandle* rawHandle;
};

ManageResourceHandle handle(createNewResource());
handle->performInvalidOperation();
```

RAII classes are prevalent in STL, such as mutex. here is the example.

```
std::mutex m;

void bad() {
  m.lock();                     // acquire the mutex
  f();                          // if f() throws an exception, the mutex is never
  if (!everything_ok()) return; // released early return, the mutex is never released.
  m.unlock();                   // if bad() reaches this statement, the mutex is released.
}

void good() {
  std::lock_guard<std::mutex> lock(m); // RAII class: mutex acquisition is initialization.
  f();                          // if f() throws an exception, the mutex is released.
  if(!everything_ok()) return;  // early return, the mutex is released.
                                // if good() return normally, the mutex is released.
}

```

### References
[1] https://en.cppreference.com/w/cpp/language/raii  
[2] https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii  
