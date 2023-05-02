#include "TcpSocket.h"

TcpSocket::TcpSocket()
  : Socket()
{};


void TcpSocket::send(std::string message)
{
  open();

  if (::send(m_sock_fd, message.data(), message.length(), MSG_NOSIGNAL) < 0
      || ::recv(m_sock_fd, message.data(), 1, MSG_NOSIGNAL) <= 0 // ACK alive
  ) {
    notify("|!| Cannot send", true);
    close();
  }
};


void TcpSocket::receive(std::string &buf, uint16_t max_length)
{
  open();

  buf.resize(max_length);
  int length = ::recv(m_sock_fd, buf.data(), max_length, MSG_NOSIGNAL);
  if (length > 0)
  {
    buf.resize(length);

    char ready_receive[] = "+";
    if (::send(m_sock_fd, ready_receive, 1, MSG_NOSIGNAL) > 0) // ACK alive
      return;
  }

  notify("|!| Cannot receive", true);
  close();
};


TcpSocket::~TcpSocket()
{};