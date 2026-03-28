#!/usr/bin/env sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
GUI_DIR="$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)"
SRC="$GUI_DIR/AppIcon.ppm"
OUT="$GUI_DIR/AppIcon.icns"
ICONSET="$GUI_DIR/AppIcon.iconset"

if [ ! -f "$SRC" ]; then
  echo "missing source icon: $SRC" >&2
  exit 1
fi

rm -rf "$ICONSET"
mkdir -p "$ICONSET"

for sz in 16 32 128 256 512; do
  sips -z "$sz" "$sz" "$SRC" --out "$ICONSET/icon_${sz}x${sz}.png" >/dev/null
  dbl=$((sz * 2))
  sips -z "$dbl" "$dbl" "$SRC" --out "$ICONSET/icon_${sz}x${sz}@2x.png" >/dev/null
done

iconutil -c icns "$ICONSET" -o "$OUT"
rm -rf "$ICONSET"

echo "generated $OUT"
