#!/usr/bin/env bash
set -euo pipefail

TEMPLATE="include/CostantSettings.hpp.in"
OUT_HDR="include/CostantSettings.hpp"

BUILD_DIR="build"          # cambia se serve
EXEC="./build/MyExecutable"  # cambia col tuo eseguibile

mkdir -p "$BUILD_DIR"

for f in $(seq 0 48); do
  out="/home/abrau/code/data/fulltrack_${f}.txt"

  # genera header da template
  sed \
    -e "s|@FRAME@|$f|g" \
    -e "s|@OUT_FILE@|$out|g" \
    "$TEMPLATE" > "$OUT_HDR"

  # build (scegli il tuo comando)
  cmake --build "$BUILD_DIR" -j

  # run
  "$EXEC"
done
