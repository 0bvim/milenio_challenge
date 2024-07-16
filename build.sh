#!/bin/sh

install_dependencies() {
  apk update && apk upgrade;
  apk add --update alpine-sdk;
  apk add --no-cache cmake g++ make clang neovim bash git;
}

install_google_test() {
  mkdir -p ~/gtest && cd ~/gtest;
  git clone https://github.com/google/googletest.git;
  cd googletest;
  mkdir build; cd build; cmake .. && make;
  make install
}

build_tests() {
  mkdir -p /app/build
  cd /app/build
  cmake ..
  make
}

make_shared() {
  cd /app;
  make so;
}

install_dependencies
install_google_test
make_shared
build_tests
