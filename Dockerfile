FROM alpine:latest

ARG CMAKE_BUILD_TYPE=Debug

RUN apk add --no-cache gcc g++ clang clang++ make cmake boost boost-dev gtest gtest-dev
ADD . tui
WORKDIR tui

RUN mkdir build
WORKDIR build

RUN cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} ..
RUN make

CMD ["./test"]
