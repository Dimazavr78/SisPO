#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Base class for both TCP and UDP non-threaded sockets
class Socket
{
protected:
  ::sockaddr_in    m_remote;
  int              m_sock_fd;
  bool             m_notif_allowed;

  void notify(const std::string &message, bool show_error = false);

public:
  Socket();

  virtual void init()            = 0;
  virtual void shutdown()        = 0;
  virtual bool isInited() const  = 0;
  virtual void send       (std::string message)                   = 0;
  virtual void receive    (std::string &buf, uint16_t max_length) = 0;
  void allowNotifications (bool notif_allowed = true);

  virtual ~Socket();
};

#endif // SOCKET_H