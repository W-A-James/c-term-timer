# C Term Timer

A port of [https://github.com/W-A-James/term-timer](term-timer). Originally written in Typescript for use with Node.js.
This port was written to give a more responsive terminal experience. This port currently only supports unix-like systems and is currently only tested on an x86 Ubuntu 22.04 machine.

## Features

- Simple terminal-based UI
- Alarm sound using native terminal bell

## Installation

```bash
git clone git@github.com:W-A-James/c-term-timer.git
cd c-term-timer
make -j
```
Feel free to add a soft-link to the `./build/release/term-timer` binary to a directory in your `$PATH` or add the `./build/release` directory directly to your `$PATH`.

## Usage

```
Usage:
    term-timer [<hours>h] [<minutes>m] [<seconds>s?]
    Must specify at least one of [<hours>h], [<minutes>m], [<seconds>s?]
    If only one argument is specified with no suffix, defaults to interpreting as seconds
```

Use `Ctrl-C` or `Ctrl-Q` to close the timer.

### Example

```
$ term-timer 5m
╭──────────╮
│ 00:05:00 |
╰──────────╯
```

## Tests

After building the binaries in the installation step, the test binaries will live in `./test/build`.
