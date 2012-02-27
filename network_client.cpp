#include "stdafx.hpp"

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

void print_result(long size[], double dur[], int n_thread)
{
  long t_size = 0;
  double t_dur = 0.0;
  for(int i=0;i<n_thread;++i)
  {
    t_size += size[i];
    t_dur += dur[i];
  }

  std::cout << "Time, " << t_dur << " s, ";
  std::cout << "Size, " << t_size << "B, ";
  std::cout << "Speed, " << ((double)t_size)*8/1024/1024/(t_dur) << "Mbps" << std::endl;
}

void udp_client_worker(char host[], char port[], const unsigned int buf_size, long *size, double *dur)
{
  boost::asio::io_service io_service;

  udp::socket socket(io_service, udp::endpoint(udp::v4(), 0));

  udp::resolver resolver(io_service);
  udp::resolver::query query(udp::v4(), host, port);
  udp::resolver::iterator iterator = resolver.resolve(query);

  *size = 0;
  *dur = 0.0;

  char arr[buf_size];
  cbm::rand_char_array(arr, buf_size);
  const char * request = arr;

  auto start = NOW();
  socket.send_to(boost::asio::buffer(request, buf_size), *iterator);

  char recv_buf[buf_size];
  udp::endpoint sender_endpoint;
  size_t len = socket.receive_from(boost::asio::buffer(recv_buf, buf_size), sender_endpoint);

  auto end = NOW();
  *dur += DURATION(end, start);
  *size += buf_size + len;
}

void udp_client(char host[], char port[], const unsigned int buf_size, int n_thread)
{
  try
  {
    long size[n_thread];
    double dur[n_thread];
    boost::thread worker[n_thread];
    for(int i=0;i<n_thread;++i)
      worker[i] = boost::thread(udp_client_worker, host, port, buf_size, &size[i], &dur[i]);

    for(int i=0;i<n_thread;++i)
      worker[i].join();

    print_result(size, dur, n_thread);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void tcp_client_worker(char host[], char port[], const unsigned int buf_size, long *size, double *dur)
{
  boost::asio::io_service io_service;

  tcp::resolver resolver(io_service);
  tcp::resolver::query query(tcp::v4(), host, port);

  tcp::resolver::iterator iterator = resolver.resolve(query);
  tcp::socket socket(io_service);
  socket.connect(*iterator);

  *size = 0;
  *dur = 0.0;

  char arr[buf_size];
  cbm::rand_char_array(arr, buf_size);
  const char * request = arr;

  auto start = NOW();
  boost::asio::write(socket, boost::asio::buffer(request, buf_size));

  char recv_buf[buf_size];
  size_t len = boost::asio::read(socket, boost::asio::buffer(recv_buf, buf_size));

  auto end = NOW();
  *dur += DURATION(end, start);
  *size += buf_size + len;
}

void tcp_client(char host[], char port[], const unsigned int buf_size, int n_thread)
{
  try
  {
    long size[n_thread];
    double dur[n_thread];
    boost::thread worker[n_thread];
    for(int i=0;i<n_thread;++i)
      worker[i] = boost::thread(tcp_client_worker, host, port, buf_size, &size[i], &dur[i]);

    for(int i=0;i<n_thread;++i)
      worker[i].join();

    print_result(size, dur, n_thread);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Usuage: <tcp/udp> <host> <port> <buf_size> <n_thread>" << std::endl;
    return 1;
  }
  srand(time(0));
  int buf_size = atoi(argv[4]);
  int n_thread = atoi(argv[5]);
  if(strcmp(argv[1], "udp")==0)
    udp_client(argv[2], argv[3], buf_size, n_thread);
  else
    tcp_client(argv[2], argv[3], buf_size, n_thread);
  return 0;
}

