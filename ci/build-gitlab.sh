#!/bin/bash
apt update && apt install zip wget -y
. ${0%/*}/build.sh
. ${0%/*}/upload.sh
