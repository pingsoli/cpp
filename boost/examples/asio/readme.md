# Boost.Asio library

## synchronous operation
What's that mean ?  
Blocking to wait the return result.  

## asynchronous operation
It means that you don't need to wait, just give the callback function, if
the operations comlete, asio will invoke the callback automatically.  

NOTE: the asynchronous support is based on the Proactor design pattern(is what?)  
The most important thing, synchronization is not equal to blocking.

sync blocking, sync non-blocking and async non-blocking ?  
