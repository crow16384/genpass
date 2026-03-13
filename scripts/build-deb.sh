#!/usr/bin/env sh

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_DIR=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
BUILD_DIR=${BUILD_DIR:-"$PROJECT_DIR/build-deb"}
BUILD_TYPE=${BUILD_TYPE:-Release}

echo "==> Configuring in $BUILD_DIR"
cmake -S "$PROJECT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

echo "==> Building"
cmake --build "$BUILD_DIR"

echo "==> Packaging Debian artifact"
cmake --build "$BUILD_DIR" --target package

echo "==> Generated packages"
find "$BUILD_DIR" -maxdepth 1 -type f -name '*.deb' -print