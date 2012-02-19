#include "stdafx.hpp"

using boost::asio::ip::udp;

void client_worker(char host[], char port[], const unsigned int buf_size, long *size, double *dur)
{
  boost::asio::io_service io_service;

  udp::socket socket(io_service, udp::endpoint(udp::v4(), 0));

  udp::resolver resolver(io_service);
  udp::resolver::query query(udp::v4(), host, port);
  udp::resolver::iterator iterator = resolver.resolve(query);

  int times = 100*1024/buf_size + ((100*1024%buf_size==0)?0:1);

  *size = 0;
  *dur = 0.0;

  for(int i=0;i<times;++i)
  {
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
}

void client(char host[], char port[], const unsigned int buf_size, int n_thread)
{
  try
  {
    long size[n_thread];
    double dur[n_thread];
    boost::thread worker[n_thread];
    for(int i=0;i<n_thread;++i)
      worker[i] = boost::thread(client_worker, host, port, buf_size, &size[i], &dur[i]);

    for(int i=0;i<n_thread;++i)
      worker[i].join();

    long t_size = 0;
    double t_dur = 0.0;

    for(int i=0;i<n_thread;++i)
    {
      t_size += size[i];
      t_dur += dur[i];
    }

    std::cout << "Time: " << t_dur << " s" << std::endl;
    std::cout << "Size: " << t_size << "B" << std::endl;
    std::cout << "Speed: " << ((double)t_size)*8/1024/1024/(t_dur) << "Mbps" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usuage: <host> <port>" << std::endl;
    return 1;
  }
  srand(time(0));
  for(int i=0;i<10;++i)
    client(argv[1], argv[2], 1024, 4);
  return 0;
}

