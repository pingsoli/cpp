#### boost::asio::io_service play what role ?

boost::asio::io_service - proactor
std::thread - io_service dispatchs the completion handler to thread
boost::asio::io_service::strand

asynchronous operations - such as async_read, async_write from socket.  

completion handler  
It's a callback function, it will be called when the task is finished.  

### References
[1] https://www.youtube.com/watch?v=rwOv_tw2eA4  
