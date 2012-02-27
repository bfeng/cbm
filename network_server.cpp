#include "stdafx.hpp"

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

void udp_server_worker(udp::socket *socket, int buf_size)
{
  for (;;)
  {
    char recv_buf[buf_size];
    udp::endpoint remote_endpoint;
    boost::system::error_code error;
    int recv_len = socket->receive_from(boost::asio::buffer(recv_buf, buf_size), remote_endpoint, 0, error);

    if (error && error != boost::asio::error::message_size)
      throw boost::system::system_error(error);

    boost::system::error_code ignored_error;
    socket->send_to(boost::asio::buffer(recv_buf, recv_len), remote_endpoint, 0, ignored_error);
  }
}

void udp_server(int port, int buf_size, int n_thread)
{
  try
  {
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), port));

    boost::thread worker[n_thread];
    for(int i=0;i<n_thread;++i)
      worker[i] = boost::thread(udp_server_worker, &socket, buf_size);
      
    for(int i=0;i<n_thread;++i)
      worker[i].join();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void tcp_server_worker(tcp::acceptor *acceptor, int buf_size)
{
  boost::asio::io_service io_service;
  for(;;)
  {
    tcp::socket socket(io_service);
    acceptor->accept(socket);

    char recv_buf[buf_size];
    boost::system::error_code error;
    int recv_len = socket.read_some(boost::asio::buffer(recv_buf, buf_size), error);

    if (error == boost::asio::error::eof)
      break;
    else if(error)
      throw boost::system::system_error(error);

    boost::asio::write(socket, boost::asio::buffer(recv_buf, recv_len));
  }
}

void tcp_server(int port, int buf_size, int n_thread)
{
  try
  {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

    boost::thread worker[n_thread];
    for(int i=0;i<n_thread;++i)
      worker[i] = boost::thread(tcp_server_worker, &acceptor, buf_size);

    for(int i=0;i<n_thread;++i)
      worker[i].join();
  }
  catch (std::exception & e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int main(int argc, char *argv[])
{
  if(argc!=5)
  {
    std::cerr << "Usuage: <tcp/udp> <port> <buf_size> <n_thread>" << std::endl;
    return 1;
  }
  int port = atoi(argv[2]);
  int buf_size = atoi(argv[3]);
  int n_thread = atoi(argv[4]);
  if(strcmp(argv[1], "udp")==0)
    udp_server(port, buf_size, n_thread);
  else
    tcp_server(port, buf_size, n_thread);
  return 0;
}
