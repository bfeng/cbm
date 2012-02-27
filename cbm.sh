cputest() {
  thread=(1 2 4 8)
  
  for l in "${thread[@]}"
  do
    ./cpu $l
  done
}

memtest() {
  rw_arr=("read" "write")
  is_random=("true" "false")
  block_size=(1 1024 1048576)
  thread=(1 2 4 8)

  for i in "${rw_arr[@]}"
  do
    for j in "${is_random[@]}"
    do
      for k in "${block_size[@]}"
      do
        for l in "${thread[@]}"
        do
          ./mem $i $j $k $l
        done
      done
    done
  done
}

disktest() {
  rw_arr=("read" "write")
  is_random=("true" "false")
  block_size=(1 1024 1048576 1073741824)
  thread=(1 2 4 8)

  for i in "${rw_arr[@]}"
  do
    for j in "${is_random[@]}"
    do
      for k in "${block_size[@]}"
      do
        for l in "${thread[@]}"
        do
          ./disk $i $j $k $l
        done
      done
    done
  done
}

## buggy here
loopbacktest() {
  protocol=("tcp" "udp")
  buf_size=(1 1024 1048576)
  thread=(1 2 4 8)

  for i in "${protocol[@]}"
  do
    for j in "${buf_size[@]}"
    do
      for k in "${thread[@]}"
      do
        eval "./network_server $i 13000 $j $k &"
        pid=$!
        ./network_client $i localhost 13000 $j $k
        sleep 1
        kill $pid
      done
    done
  done
}

case "$1" in
  cpu)
    echo "cpu testing"
    ./cpu $2
    ;;
  mem)
    echo "memory testing"
    ./mem $2 $3 $4 $5
    ;;
  disk)
    echo "disk testing"
    ./disk $2 $3 $4 $5
    ;;
  client)
    echo "client starting"
    ./network_client $2 $3 $4 $5 $6 
    ;;
  server)
    echo "server starting"
    ./network_server $2 $3 $4 $5
    ;;
  loopback)
    ./network_server $2 $3 $4 $5 &
    ./network_client $2 localhost $3 $4 $5
    ;;
  test)
    case "$2" in
      cpu)
        for i in 1 2 3
        do
          cputest
        done
        ;;
      mem)
        for i in 1 2 3
        do
          memtest
        done
        ;;
      disk)
        for i in 1 2 3
        do
          disktest
        done
        ;;
      loopback)
        for i in 1 2 3
        do
          loopbacktest
        done
        ;;
      *)
        echo "Usuage: $0 $1 {cpu|mem|disk|loopback}"
        exit 1
    esac
    ;;
  *)
    echo "Usuage: $0 {cpu|mem|disk|client|server|test}"
    exit 1
esac
