#!/bin/bash

# CMD="eosioc -H leclevn -p 8888 --wallet-host leclevn --wallet-port 8888"
CMD="eosioc"
ACTION=rwinfo

$CMD push action acmv $ACTION '
  {
    "owner": "acmv",
    "address": "uuEEE cc blockchain co the la mot nen tang bong bong",
    "tn": "aabboi"
  }
' -p acmv@active