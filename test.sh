#!/bin/bash

ACCOUNT=acmv
CMD="eosioc -H leclevn -p 8888 --wallet-host leclevn --wallet-port 8888"
#CMD="eosioc"
ACTION=rnw

$CMD push action $ACCOUNT $ACTION '
  {
    "nickname": "acmv",
    "wtype": "50",
    "wadd": "add",
    "ctype": "50",
    "cvalue": "valuee"
  }
' -p $ACCOUNT@active