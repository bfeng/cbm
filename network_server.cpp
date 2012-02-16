#include "stdafx.hpp"

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  time_t now = std::time(0);
  return std::ctime(&now);
}

void server()
{
  try
  {
    boost::asio::io_service io_service;

    udp::socket socket(io_service, udp::endpoint(udp::v4(), 13000));

    for (;;)
    {
      char recv_buf[128];
      udp::endpoint remote_endpoint;
      boost::system::error_code error;
      size_t len = socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);
      std::cout.write(recv_buf, len);
      std::cout << std::endl;

      if (error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);

      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;
      socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int main()
{
  server();
  return 0;
}
