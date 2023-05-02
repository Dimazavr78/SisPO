#include "TcpSocketClient.h"
#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
  std::string remote_address = "127.0.0.1";
  uint16_t remote_port = atoi("6666");

  TcpSocketClient client(remote_address, remote_port);
  client.init();

  std::thread client_thread (
    [&client]() {
      std::string buf;

      while (true)
      {
        std::cin >> buf;

        client.send(buf);
      }
    }
  );

  client_thread.join();

  return 0;
};