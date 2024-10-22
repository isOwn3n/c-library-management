#!/bin/sh

remove_build_dir() {
  if [ -d "build" ]; then
    rm -rf build
  fi
}

create_build_dir() {
  mkdir build
}

build_project() {
  local is_remove="$1"
  if [[ $is_remove == "yes" ]]; then
    remove_build_dir
    create_build_dir
  fi
  cd build
  cmake ..
  make
}

remove_confirmation() {
  printf "Removing existing build directory. Confirm (Y/n/r (rebuild)) "
  read -r remove_build
  if [ -z "$remove_build" ] || [[ "$remove_build" == [yY] ]]; then
    build_project "yes"
  elif [[ "$remove_build" == [nN] ]];then
    echo "You can use cmake and make."
  elif [[ "$remove_build" == [rR] ]];then
    build_project
  else
    echo "Invalid input."
    exit 1
  fi

}

if [ -f "CMakeLists.txt" ];then
  if [ -d "build" ];then
    remove_confirmation
  else
    build_project
  fi
fi
