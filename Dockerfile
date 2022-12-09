FROM ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder:latest as build

WORKDIR /app
ENV DEBIAN_FRONTEND=noninteractive
RUN  apk add zip wget curl 
COPY . .
#CMD chmod +x /app/ci/build-gitlab.sh && chmod +x /app/ci/build.sh && chmod +x /app/ci/upload.sh
#ENTRYPOINT ["/app/ci/build-gitlab.sh"]
