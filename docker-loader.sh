#!/bin/sh

echo "run 'make load' on command prompt"
# https://developers.ledger.com/docs/nano-app/load/
sudo docker run --rm -ti -v "/dev/bus/usb:/dev/bus/usb" -v "$(realpath .):/app" --privileged ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder:1d9f741e9bc969b072e2de53762b64993536c0f7

