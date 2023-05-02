#include "TcpSocketServer.h"
#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
  uint16_t local_port = atoi("6666");

  TcpSocketServer server(local_port);
  server.init();

  std::thread server_thread (
    [&server]() {
      std::cout << std::endl
                << "Waiting for incoming connections..."
                << std::endl
                << "(Input any key to SHUTDOWN)"
                << std::endl
                << std::endl;

      std::string buf;

      while (server.isInited())
      {
        server.receive(buf, 1000);

        if (buf.length())
          std::cout << buf << std::endl;
      }
    }
  );

  server_thread.detach();

  std::getchar();
  server.shutdown();
  std::cin.clear();

  return 0;
};