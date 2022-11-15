#!/bin/bash
cd /app

echo uploading assets to package to "${PACKAGE_REGISTRY_URL}/${APP_VERSION}/"
curl --header "JOB-TOKEN: $CI_JOB_TOKEN" --upload-file "dist/$OUTPUT_PKG_NAME.elf" "${PACKAGE_REGISTRY_URL}/${APP_VERSION}/${OUTPUT_PKG_NAME}.elf"
curl --header "JOB-TOKEN: $CI_JOB_TOKEN" --upload-file "dist/$OUTPUT_PKG_NAME.sha256" "${PACKAGE_REGISTRY_URL}/${APP_VERSION}/${OUTPUT_PKG_NAME}.sha256"
curl --header "JOB-TOKEN: $CI_JOB_TOKEN" --upload-file "dist/$OUTPUT_PKG_NAME.hex" "${PACKAGE_REGISTRY_URL}/${APP_VERSION}/${OUTPUT_PKG_NAME}.hex"
curl --header "JOB-TOKEN: $CI_JOB_TOKEN" --upload-file "dist/$OUTPUT_PKG_NAME.apdu" "${PACKAGE_REGISTRY_URL}/${APP_VERSION}/${OUTPUT_PKG_NAME}.apdu"
curl --header "JOB-TOKEN: $CI_JOB_TOKEN" --upload-file "dist/output-scan-build.zip" "${PACKAGE_REGISTRY_URL}/${APP_VERSION}/output-scan-build.zip"
