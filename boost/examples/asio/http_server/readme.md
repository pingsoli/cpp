server             accept incoming clinets
connection         represent every connection from a clinet
connection_manager connection container, manager all connections
request            request from client, include http method, uri and other info
request_parser     parse http request
request_handler    handle request and produce reply
reply              reply datagram, status code, headers, content
