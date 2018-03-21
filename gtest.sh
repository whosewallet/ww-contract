#!/bin/bash

# CMD="eosioc -H leclevn -p 8888 --wallet-host leclevn --wallet-port 8888"
CMD="eosioc"
ACTION=gwinfo

$CMD push action acmv $ACTION '
  {
    "owner": "acmv"
  }
' -p acmv@active