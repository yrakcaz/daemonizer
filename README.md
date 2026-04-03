[![CI](https://github.com/yrakcaz/daemonizer/actions/workflows/ci.yml/badge.svg)](https://github.com/yrakcaz/daemonizer/actions/workflows/ci.yml)
[![MIT License](https://img.shields.io/github/license/yrakcaz/daemonizer?color=blue)](./LICENSE)

# daemonizer

A command-line daemon manager for Linux. `daemonizer` daemonizes processes by forking and redirecting I/O to `/dev/null`, and provides commands to list, kill, restart, stop, and continue running daemons by index. Daemons are detected by scanning `/proc` for processes whose parent PID is 1.

## Build

```
./configure && make
```

Options:

- `--with-debug` — enable debug symbols (`-g3`)
- `--with-clang` — compile with clang instead of gcc
- `--prefix=DIR` — set install directory (default: `/usr/local`)

## Install

```
make install
```

Installs `daemonizer` to `/usr/local/bin` by default. Override with `--prefix`:

```
./configure --prefix=/usr && make install
```

To uninstall:

```
make uninstall
```

## Usage

```
daemonizer [option] [command] ...
```

| Option | Description |
|---|---|
| `[command]` | Daemonize a command |
| `-c, --cmd` | Daemonize multiple commands (use before each) |
| `-k, --kill <index>` | Kill the daemon at the given index |
| `-r, --restart <index>` | Restart the daemon at the given index |
| `-s, --stop <index>` | Stop (SIGSTOP) the daemon at the given index |
| `-cont, --continue <index>` | Continue (SIGCONT) a stopped daemon |
| `-j, --jobs` | Display running daemons with their index and PID |
| `-h, --help` | Show help |

## Examples

Daemonize a command:

```
daemonizer my-server --port 8080
```

Daemonize multiple commands:

```
daemonizer -c server-a -c server-b --flag
```

List running daemons:

```
daemonizer --jobs
```

Kill daemon at index 2:

```
daemonizer --kill 2
```
