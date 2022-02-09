#!/bin/sh

echo "run 'make load' on command prompt"
# https://developers.ledger.com/docs/nano-app/load/
sudo docker run --rm -ti -v "/dev/bus/usb:/dev/bus/usb" -v "$(realpath .):/app"  --privileged ledger-app-builder:latest
