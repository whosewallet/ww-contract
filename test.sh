#!/bin/bash
ACCOUNT=whosewallet

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

    -st|--setup)
    echo "${i#*=}"
    # create whosewallet account
    
    $cmd create account eosio $ACCOUNT EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2
    # create test account
    $cmd create account whosewallet acmv EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2
    $cmd create account whosewallet haiz EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2

    shift # past argument=value
    ;;
    *)
          # unknown option
    echo unknown option
    ;;
esac
done

$cmd push action whosewallet inrnw '{ "w_add": "0x1a4C8627eeCf38d7392B7637123a899ff559f0A0", "w_type": "100", "a_name": "acmv" }' -p whosewallet@active -p acmv@active
$cmd push action whosewallet inrnw '{ "w_add": "12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq", "w_type": "50", "a_name": "haiz" }' -p whosewallet@active -p haiz@active

$cmd get table whosewallet acmv mywallet
$cmd get table whosewallet haiz mywallet
$cmd get table whosewallet whosewallet alwallet
