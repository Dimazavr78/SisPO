#ifndef TCPSOCKETCLIENT_H
#define TCPSOCKETCLIENT_H

#include "TcpSocket.h"


class TcpSocketClient final : public TcpSocket
{
protected:
  ::sockaddr_in m_remote;
  bool          m_is_connected;

public:
  TcpSocketClient(const std::string  &server_addr, uint16_t server_port);
  TcpSocketClient(TcpSocketClient &) = delete;
  TcpSocketClient(TcpSocketClient &&) = delete;

  virtual void setOptions(const std::string  &server_addr, uint16_t server_port);
  virtual bool isInited() const override;
  virtual bool isOpened() const override;
  virtual void init()           override;
  virtual void open()           override;
  virtual void close()          override;
  virtual void shutdown()       override;

  virtual ~TcpSocketClient();
};

#endif // TCPSOCKETCLIENT_H