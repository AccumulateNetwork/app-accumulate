#!/bin/sh
# Setup docker builder using these instructions: https://developers.ledger.com/docs/nano-app/build/
sudo docker run --rm -ti -v "$(realpath .):/app" ledger-app-builder:latest
#sudo docker cp ledger-app-builder:
