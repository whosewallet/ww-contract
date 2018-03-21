#!/bin/bash
# deploy local

OUT=app.wast
ACCOUNT=acmv
LOG_FILE=deploy.log
cmd='eosioc'
$cmd set contract $ACCOUNT $OUT app.abi > $LOG_FILE
cat $LOG_FILE

$cmd get code -a detail.api $ACCOUNT
