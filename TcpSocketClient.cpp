#include "TcpSocketClient.h"


TcpSocketClient::TcpSocketClient (
  const std::string &remote_addr,
  uint16_t          remote_port
) : TcpSocket(),
    m_is_connected(false)
{
  setOptions(remote_addr, remote_port);
};


void TcpSocketClient::setOptions (
  const std::string &remote_addr,
  uint16_t          remote_port
) {
  close();

  m_remote.sin_family = PF_INET;
  m_remote.sin_addr.s_addr = ::inet_addr(remote_addr.data());
  m_remote.sin_port = ::htons(remote_port);
};


inline bool TcpSocketClient::isInited() const {
  return m_sock_fd >= 0;
};


inline bool TcpSocketClient::isOpened() const {
  return m_is_connected;
};


void TcpSocketClient::init()
{
  if (!isInited())
  {
    m_sock_fd = ::socket(m_remote.sin_family, SOCK_STREAM, 0);
    if (m_sock_fd < 0)
      notify("|!| Cannot create socket");
  }
};


void TcpSocketClient::open()
{
  if (!isOpened()
      && (
        m_is_connected = ::connect (
          m_sock_fd, (::sockaddr*)&m_remote,
          sizeof(m_remote)
        )
      ) < 0
  ) notify("|!| Cannot connect to server", true);
};


void TcpSocketClient::close()
{
  if (isOpened())
  {
    ::send(m_sock_fd, nullptr, 0, MSG_NOSIGNAL); // CLOSE request
    m_is_connected = false;
  }
};


void TcpSocketClient::shutdown()
{
  close();

  if (isInited())
  {
    if (::close(m_sock_fd) >= 0)
      m_sock_fd = -1;
    else
      notify("|!| Cannot close socket", true);
  }
};


TcpSocketClient::~TcpSocketClient() {
  shutdown();
};