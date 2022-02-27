#!/usr/bin/env bash

set -o errexit -o nounset -o pipefail

function apply_clang_format() {
  local CLANG_FORMAT="clang-format-10"
  local tool_version
  tool_version=$(${CLANG_FORMAT} --version)
  echo "started ${CLANG_FORMAT}: version=${tool_version}"

  local cfolder="${1}"
  local targets
  mapfile -t targets < <(
    find "${cfolder}/" \
      \( \
      -path "${cfolder}/.*" -o \
      -path "${cfolder}/bazel-*" \
      \) -prune -false \
      -o \( -iname "*.hpp" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.c" -o -iname "*.cu" -o -iname "*.h" \)
  )

  for ctarget in "${targets[@]}"; do
    echo "  ${CLANG_FORMAT} -style=file -i ${ctarget}"
    ${CLANG_FORMAT} -style=file -i "${ctarget}"
  done

  echo "ended ${CLANG_FORMAT}"
  echo ""
}

function apply_shell_format() {
  local SHFMT="shfmt"
  local tool_version
  tool_version=$(${SHFMT} --version)
  echo "started ${SHFMT}: version=${tool_version}"

  local cfolder="${1}"
  local targets
  mapfile -t targets < <(
    find "${cfolder}/" \
      \( \
      -path "${cfolder}/.*" -o \
      -path "${cfolder}/bazel-*" \
      \) -prune -false \
      -o \( -iname "*.sh" \)
  )

  for ctarget in "${targets[@]}"; do
    echo "  ${SHFMT} -i 2 -d ${ctarget}"
    ${SHFMT} -i 2 -d "${ctarget}"
  done

  echo "ended ${SHFMT}"
  echo ""
}

function apply_bazel_format() {
  local BUILDIFIER="buildifier"
  local tool_version
  tool_version=$(${BUILDIFIER} --version)
  echo "started ${BUILDIFIER}: version=${tool_version}"

  local cfolder="${1}"
  local targets
  mapfile -t targets < <(
    find "${cfolder}/" \
      \( \
      -path "${cfolder}/.*" -o \
      -path "${cfolder}/bazel-*" \
      \) -prune -false \
      -o \( -iname "*.bazel" -o -iname "*.bzl" \)
  )

  for ctarget in "${targets[@]}"; do
    echo "  ${BUILDIFIER} --mode fix ${ctarget}"
    ${BUILDIFIER} --mode fix "${ctarget}"
  done

  echo "ended ${BUILDIFIER}"
  echo ""
}

function main() {
  local root_path
  root_path=$(
    cd $(dirname "$0")
    pwd
  )
  apply_clang_format "${root_path}"
  apply_shell_format "${root_path}"
  apply_bazel_format "${root_path}"
}

main
