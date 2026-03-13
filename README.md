# genpass

Readable and pronounceable password generator written in C++.

`genpass` creates passwords from a compact template format and can remember
the last template you used.

## Usage

```text
genpass [options] [format]
```

### Options

- `-h`, `--help` Print help and exit.
- `-v`, `--version` Print version and exit.
- `-n`, `--number <N>` Number of passwords to generate (default: `3`).
- `-l`, `--last` Reuse the last remembered format from `~/.genpass_memory`.

`format` is required unless you use `--last`.

## Format Reference

The format is a sequence of `type + length` pairs with no separators:

- `W` Uppercase word (randomly plain or pronounceable, first letter capitalized)
- `w` Lowercase word (randomly plain or pronounceable)
- `d` Digits (`0-9`)
- `s` Special symbols (`!@#$%^&*~><(),\=/;:+-.[]_`)

Only `W`, `w`, `d`, and `s` are valid type letters.

Examples of parts:

- `w4` -> 4 lowercase word characters
- `W8` -> 8 uppercase readable characters
- `d2` -> 2 digits

If no number is given after a type, length defaults to `1` (for example `W`).

## Examples

```bash
# Generate 3 passwords (default count)
genpass W4s2w3d5

# Generate 5 readable passwords, each w8 + d2
genpass w8d2 -n 5

# Reuse the last format
genpass --last -n 2
```

Sample output:

```text
Rofo#her68314
Bozo-[bid18278
```

## Build

Requirements:

- CMake >= 3.25
- C++20 compiler
- Boost `program_options`

Build steps:

```bash
cmake -S . -B build
cmake --build build
```

To build a Debian package:

```bash
./scripts/build-deb.sh
```

The script configures a fresh package build directory, builds the project, and
produces the `.deb` artifact in the build directory.

Binary path:

```text
build/app/genpass
```

## Install

```bash
cmake --install build
```

To install to user-local prefix:

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="$HOME/.local"
cmake --build build
cmake --install build
```

## Man Page

Install includes `genpass(1)` under `share/man/man1`.

```bash
man genpass
```

## License

This project is licensed under the GNU General Public License v3.0.
See the `LICENSE` file for the full text.
