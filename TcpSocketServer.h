#ifndef TCPSOCKETSERVER_H
#define TCPSOCKETSERVER_H

#include "TcpSocket.h"


class TcpSocketServer : public TcpSocket
{
protected:
  ::sockaddr_in m_local;
  int           m_listener_sock_fd;

public:
  TcpSocketServer(uint16_t local_port);
  TcpSocketServer(TcpSocketServer &) = delete;
  TcpSocketServer(TcpSocketServer &&) = delete;

  virtual void setOptions(uint16_t local_port);
  virtual bool isInited() const override;
  virtual bool isOpened() const override;
  virtual void init()           override;
  virtual void open()           override;
  virtual void close()          override;
  virtual void shutdown()       override;

  virtual ~TcpSocketServer();
};

#endif // TCPSOCKETSERVER_H