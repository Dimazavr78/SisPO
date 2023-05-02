#include "TcpSocketServer.h"


TcpSocketServer::TcpSocketServer (uint16_t local_port)
  : TcpSocket(),
    m_listener_sock_fd(-1)
{
  setOptions(local_port);
};


void TcpSocketServer::setOptions(uint16_t local_port)
{
  close();

  m_local.sin_family = PF_INET;
  m_local.sin_addr.s_addr = INADDR_ANY;
  m_local.sin_port = ::htons(local_port);
};


inline bool TcpSocketServer::isInited() const {
  return m_listener_sock_fd >= 0;
};


inline bool TcpSocketServer::isOpened() const {
  return m_sock_fd >= 0;
};


void TcpSocketServer::init()
{
  if (!isInited())
  {
    m_listener_sock_fd = ::socket(m_local.sin_family, SOCK_STREAM, 0);
    if (m_listener_sock_fd < 0)
    {
      notify("|!| Cannot create socket", true);
      exit(1);
    }

    if (::bind(m_listener_sock_fd, (sockaddr*)&m_local, sizeof(m_local)) < 0)
    {
      notify("|!| Cannot bind port", true);

      shutdown();
      exit(1);
    }
  }
};


void TcpSocketServer::open()
{
  if (!isOpened())
  {
    if (::listen(m_listener_sock_fd, 1) < 0)
    {
      notify("|!| Cannot listen this port", true);

      shutdown();
      exit(1);
    }

    ::socklen_t sock_len = sizeof(m_remote);

    m_sock_fd = (
      ::accept (m_listener_sock_fd, (::sockaddr*)&m_remote, &sock_len)
    );
    if (m_sock_fd < 0)
    {
      notify("|!| Cannot create socket", true);

      shutdown();
      exit(1);
    }
  }
};


void TcpSocketServer::close()
{
  if (isOpened())
  {
    ::send(m_sock_fd, nullptr, 0, MSG_NOSIGNAL); // CLOSE request

    if (::close(m_sock_fd) >= 0)
        m_sock_fd = -1;
    else
      notify("|!| Cannot close socket", true);
  }
};


void TcpSocketServer::shutdown()
{
  close();

  if (isInited())
  {
    if (::close(m_listener_sock_fd) >= 0)
      m_listener_sock_fd = -1;
    else notify("|!| Cannot close socket", true);
  }
};


TcpSocketServer::~TcpSocketServer() {
  shutdown();
};