#include "stdafx.hpp"

using boost::asio::ip::udp;

void server_worker(udp::socket *socket)
{
  for (;;)
  {
    char recv_buf[128];
    udp::endpoint remote_endpoint;
    boost::system::error_code error;
    socket->receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);

    if (error && error != boost::asio::error::message_size)
      throw boost::system::system_error(error);

    std::string message = "SVR RPL";

    boost::system::error_code ignored_error;
    socket->send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
  }
}

void server(int port, int n_thread)
{
  try
  {
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), port));

    boost::thread worker[n_thread];
    for(int i=0;i<n_thread;++i)
      worker[i] = boost::thread(server_worker, &socket);
      
    for(int i=0;i<n_thread;++i)
      worker[i].join();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int main()
{
  server(13000, 4);
  return 0;
}
