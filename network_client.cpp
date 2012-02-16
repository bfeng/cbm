#include "stdafx.hpp"

using boost::asio::ip::udp;

int main(int argc, char * argv[])
{
  try
  {

    if (argc != 3)
    {
      std::cerr << "Usuage: <host> <port>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;

    udp::socket socket(io_service, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[1], argv[2]);
    udp::resolver::iterator iterator = resolver.resolve(query);

    for(int i=0;i<10;++i)
    {
      std::string s;
      std::stringstream out;
      out << "NO. " << i << " This is the message from client.";
      const char * request = out.str().data();
      socket.send_to(boost::asio::buffer(request, strlen(request)), *iterator);

      boost::array<char, 128> recv_buf;
      udp::endpoint sender_endpoint;
      size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

      std::cout.write(recv_buf.data(), len);
      std::cout << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

