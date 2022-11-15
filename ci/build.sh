#!/bin/bash

if [[ -z "${OUTPUT_PKG_NAME}" ]]; then
  OUTPUT_PKG_NAME="app-accumulate"
fi

cd /app
rm -rf bin obj debug dep output-scan-build
mkdir -p dist
make scan-build
cp bin/app.elf "dist/${OUTPUT_PKG_NAME}.elf"
cp bin/app.sha256 "dist/${OUTPUT_PKG_NAME}.sha256"
cp bin/app.hex "dist/${OUTPUT_PKG_NAME}.hex"
cp bin/app.apdu "dist/${OUTPUT_PKG_NAME}.apdu"

zip -r dist/output-scan-build.zip output-scan-build/*


