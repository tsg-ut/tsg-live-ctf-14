#!/bin/sh
SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
export HOME=/home/sage
cd $SCRIPTPATH
timeout 3m sage ./problem.sage
