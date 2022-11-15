#!/bin/sh
# Setup docker builder using these instructions: https://developers.ledger.com/docs/nano-app/build/
sudo docker run --rm -ti -v "$(realpath .):/app" ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder:latest
#sudo docker cp ledger-app-builder:
