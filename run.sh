#!/bin/sh

app_name="tui-library"
if [ -f "CMakeLists.txt" ];then
  if [ -d "build" ];then
    cd  build
    ./"$app_name"
  else
    echo "Please Run make.sh file"
  fi
else
  echo "Please go to a valid project."
fi
