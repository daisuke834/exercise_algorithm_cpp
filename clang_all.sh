#!/bin/bash

set -e
ROOT_PATH=$(
  cd $(dirname "$0")
  pwd
)

CLANGTARGETS=$(find ./ -iname "*.hpp" -or -iname "*.cc" -or -iname "*.cpp" -or -iname "*.c" -or -iname "*.cu" -or -iname "*.h" | grep -v googletest)
for CCLANGTARGET in ${CLANGTARGETS[@]}; do
  echo "  clang-format-10 -i ${CCLANGTARGET}"
  clang-format-10 -style=file -i "${CCLANGTARGET}"
done
