#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdexcept>
#include <unistd.h>

namespace ezPoll {

// tcpListener listens and processes data from TCP connections on a specified port.
class tcpListener {
public:
    // Construct a listener that will monitor a TCP connection on a port. Throws an exception if creating the listener fails for any reason.
    tcpListener(int port);

    // Close the tcpListener.
    ~tcpListener();

    // The listener sleeps until some data comes from any senders to the socket. Will automatically accept new connections. Upon receiving data from any sender, loop will call processData(int fd) with the file descriptor for any ready sender's data to let processData process the data. processData could potentially be called multiple times for multiple events/senders in one call to loop. Once it is done processing the ready data, loop returns to the user. Returns -1 if there is an error, or 0 if processData was applied successfully on the data. 
    template <typename F>
    int loop(F processData);

    // The listener loops forever and continually process incoming data with processData. Throws an exception if there is any error.
    template <typename F>
    void serve(F processData);

private:
    static const int MAX_EVENTS = 10; 

    // An array of events that epoll will add ready file descriptors with available data to.
    struct epoll_event arrivedEvents[MAX_EVENTS];
    // The file descriptor for the listening socket.
    int listenerSocketFd;
    // File descriptor for the epoll struct.
    int epollFd;
}; 


} // namespace ezPoll
