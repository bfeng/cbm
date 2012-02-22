memtest() {
  rw_arr=("read" "write")
  is_random=("true" "false")
  block_size=(1 10 100 1024 10240 102400 1024000)
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
  test)
    case "$2" in
      cpu)
        ;;
      mem)
        memtest
        ;;
      *)
        echo "Usuage: $0 $1 {cpu|mem|disk|client|server}"
        exit 1
    esac
    ;;
  *)
    echo "Usuage: $0 {cpu|mem|disk|client|server|test}"
    exit 1
esac
