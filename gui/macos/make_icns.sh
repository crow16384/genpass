#!/usr/bin/env sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
OUT="${1:-$SCRIPT_DIR/../AppIcon.icns}"
ICONSET="$(dirname "$OUT")/AppIcon.iconset"

if ! command -v sips >/dev/null 2>&1; then
  echo "sips not found" >&2
  exit 1
fi

if ! command -v iconutil >/dev/null 2>&1; then
  echo "iconutil not found" >&2
  exit 1
fi

mkdir -p "$(dirname "$OUT")"

rm -rf "$ICONSET"
mkdir -p "$ICONSET"

make_png() {
  out_file="$1"
  size="$2"
  tmp_ppm="$(mktemp -t genpass_icon_XXXXXX).ppm"

  awk -v n="$size" '
  BEGIN {
    print "P3"
    print n " " n
    print 255

    cx = (n - 1) / 2.0
    sh_cy = n * 0.34
    sh_outer = n * 0.20
    sh_inner = n * 0.13

    bx0 = int(n * 0.24)
    bx1 = int(n * 0.76)
    by0 = int(n * 0.42)
    by1 = int(n * 0.82)

    kh_cy = n * 0.58
    kh_r = n * 0.055
    ks0 = int(n * 0.54)
    ks1 = int(n * 0.70)

    for (y = 0; y < n; ++y) {
      line = ""
      for (x = 0; x < n; ++x) {
        # Background: soft blue-gray
        r = 206; g = 218; b = 226

        # Lock body
        if (x >= bx0 && x <= bx1 && y >= by0 && y <= by1) {
          r = 242; g = 201; b = 76
        }

        # Shackle ring (upper half)
        dx = x - cx
        dy = y - sh_cy
        d2 = dx * dx + dy * dy
        if (y <= by0 && d2 <= sh_outer * sh_outer && d2 >= sh_inner * sh_inner) {
          r = 242; g = 201; b = 76
        }

        # Keyhole head
        dx2 = x - cx
        dy2 = y - kh_cy
        if (dx2 * dx2 + dy2 * dy2 <= kh_r * kh_r) {
          r = 30; g = 30; b = 46
        }

        # Keyhole stem
        if (x >= int(cx - n * 0.018) && x <= int(cx + n * 0.018) && y >= ks0 && y <= ks1) {
          r = 30; g = 30; b = 46
        }

        line = line sprintf("%d %d %d ", r, g, b)
      }
      print line
    }
  }
  ' > "$tmp_ppm"

  sips -s format png "$tmp_ppm" --out "$out_file" >/dev/null
  rm -f "$tmp_ppm"
}

for sz in 16 32 128 256 512; do
  make_png "$ICONSET/icon_${sz}x${sz}.png" "$sz"
  dbl=$((sz * 2))
  make_png "$ICONSET/icon_${sz}x${sz}@2x.png" "$dbl"
done

iconutil -c icns "$ICONSET" -o "$OUT"
rm -rf "$ICONSET"

echo "generated $OUT"
