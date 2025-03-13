# Minishell

## Introduction
`minishell` is a 42 project that aims to create a simple shell, replicating the behavior of `bash` in a minimalistic way.

## Features
- Prompt display.
- Command execution (including absolute, relative, and environment path resolution).
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Handling of environment variables.
- Input/output redirections (`>`, `>>`, `<`).
- Pipes (`|`).
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Command history using `readline` library.
- Proper handling of exit statuses.

## Installation
### Prerequisites
Make sure you have the following installed:
- `gcc` (or another C compiler).
- `make`.
- `readline` library.

### Steps
```sh
git clone https://github.com/serg-backend-developer/minishell.git
cd minishell
make
```

## Usage
Run the shell with:
```sh
./minishell
```

You can now enter commands as you would in a basic shell.

## Built-in Commands
| Command   | Description                   |
|-----------|-------------------------------|
| `echo`    | Print arguments to stdout     |
| `cd`      | Change the current directory  |
| `pwd`     | Print the current directory   |
| `export`  | Set an environment variable   |
| `unset`   | Remove an environment variable|
| `env`     | Display environment variables |
| `exit`    | Exit the shell                |

## Signals
- `Ctrl+C`: Interrupt the current command
- `Ctrl+D`: Exit the shell
- `Ctrl+\`: Quit (ignore in interactive mode)
