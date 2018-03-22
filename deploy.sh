
#!/bin/bash

OUT=app.wast
ACCOUNT=acmv
LOG_FILE=deploy.log
alias lc='eosioc -H leclevn -p 8888 --wallet-host leclevn --wallet-port 8888'
lc set contract $ACCOUNT $OUT app.abi > $LOG_FILE
cat $LOG_FILE

lc get code -a detail.api $ACCOUNT
