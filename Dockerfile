FROM alpine:latest

ARG CMAKE_BUILD_TYPE=Debug

RUN apk add --no-cache gcc g++ clang make cmake gtest gtest-dev
ADD . kui
WORKDIR kui

RUN mkdir build
WORKDIR build

RUN cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} ..
RUN make

CMD ["./kui_test"]
