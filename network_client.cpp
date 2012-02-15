#include "stdafx.hpp"

using boost::asio::ip::udp;

int main()
{
  try
  {

    boost::asio::io_service io_service;

    udp::endpoint receiver_endpoint = udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 13000);

    udp::socket socket(io_service);
    socket.open(udp::v4());
    socket.bind(receiver_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

