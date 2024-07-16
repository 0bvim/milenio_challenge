FROM --platform=linux/amd64 alpine:3.20.1

WORKDIR /app

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

COPY . .

RUN ./build.sh

CMD ["/app/test_libcsv"]
