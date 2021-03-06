
#!/bin/bash

cmd='cleos -H leclevn -p 8888 --wallet-host leclevn --wallet-port 8888'

for i in "$@"
do

echo "---- params -- $i"

case $i in
    -lc|--local)
    echo "${i#*=}"
    cmd=cleos
    shift # past argument=value
    ;;
    *)
          # unknown option
    echo unknown option
    ;;
esac
done

OUT=main.wast
ACCOUNT=whosewallet
LOG_FILE=deploy.log

echo command =  $cmd

$cmd set contract $ACCOUNT ./ $OUT main.abi > $LOG_FILE
cat $LOG_FILE

$cmd get code -a detail.api $ACCOUNT
