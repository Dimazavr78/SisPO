#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Socket.h"


class TcpSocket : public Socket
{
public:
  TcpSocket();

  virtual bool isOpened() const = 0;
  virtual void open()  = 0;
  virtual void close() = 0;
  virtual void send    (std::string message)                   override;
  virtual void receive (std::string &buf, uint16_t max_length) override;

  virtual ~TcpSocket();
};

#endif // TCPSOCKET_H