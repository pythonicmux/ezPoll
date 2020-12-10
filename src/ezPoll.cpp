#include <ezPoll.hpp>

namespace ezPoll {

tcpListener::tcpListener(int port) {
    // Attempt to create a socket.
    if ((this->listenerSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw std::runtime_error{"Creating socket failed"};
    }

    // Attempt to attach the socket to the port specified by the user.
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    // Note that this will bind the socket to all interfaces in addition to localhost. 
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = port;

    if (bind(this->listenerSocketFd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        throw std::runtime_error{"Binding socket failed"};
    }

    // Start listening on this port, allowing for MAX_EVENTS pending connections to accept, i.e. the length of the epoll event array (the choice of length seems arbitrary though, as long as it's not just one client waiting).
    if (listen(this->listenerSocketFd, tcpListener::MAX_EVENTS) < 0) { 
        throw std::runtime_error{"Listening socket failed"};
    }

    // Create an epoll instance to process new connections and incoming data.
    if ((this->epollFd = epoll_create1(0)) < 0) {
        throw std::runtime_error{"Creating epoll structure failed"};
    }

    // Register the listening socket to epoll to monitor for new connections.
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = this->listenerSocketFd;
    if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, this->listenerSocketFd, &ev) == -1) {
        throw std::runtime_error{"Adding the listener socket to the epoll structure failed"};
    }
}

tcpListener::~tcpListener() {
        // Here, instead of throwing an exception we just disregard the error code for the syscalls in-case this destructor is called during stack unwinding while processing another exception. 
    close(this->epollFd);
    close(this->listenerSocketFd);
}


} // namespace ezPoll

