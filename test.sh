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

ACCOUNT=acmv
ACTION=rnw

$cmd push action $ACCOUNT $ACTION '
  {
    "w_add": "a2",
    "w_type": "50",
    "a_name": "acmv"
  }
' -p $ACCOUNT@active

$cmd push action $ACCOUNT gwwallet '
  {
    "w_add": "a2"
  }
' -p $ACCOUNT@active


$cmd push action $ACCOUNT inwinfo '
  {
    "a_name": "acmv",
    "tx_type": "20",
    "tx_id": "txid1",
    "tx_desc": "test saving tx info"
  }
' -p $ACCOUNT@active

$cmd push action $ACCOUNT gwinfo '
  {
    "a_name": "acmv",
    "tx_id": "txid1"
  }
' -p $ACCOUNT@active

# view tables
MY_CMD="$cmd get table $ACCOUNT $ACCOUNT wwallet"
echo $MY_CMD
$MY_CMD

MY_CMD="$cmd get table $ACCOUNT $ACCOUNT winfo"
echo $MY_CMD
$MY_CMD