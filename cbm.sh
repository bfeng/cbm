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
  *)
    echo "Usuage: $0 {cpu|mem|disk|client|server}"
    exit 1
esac
