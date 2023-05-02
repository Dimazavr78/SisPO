#include "Socket.h"


Socket::Socket()
  : m_notif_allowed(true),
    m_sock_fd(-1)
{};


void Socket::allowNotifications(bool notif_allowed) {
  m_notif_allowed = notif_allowed;
};


void Socket::notify(const std::string &message, bool show_error)
{
  if (m_notif_allowed)
  {
    std::cout << message
              << (show_error ?
                    " ("
                    + std::error_code {
                      errno, std::generic_category()
                    }.message()
                    + ")"
                    : ""
              )
              << std::endl;
  }
};

Socket::~Socket()
{};