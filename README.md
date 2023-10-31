# Game
You lost it.

# Build
## Requirements:
- `Powershell`, enable scripts with `Set-ExecutionPolicy RemoteSigned`
- `CMake`, has to be in the path, version 3.14
- `Visual Studio`, here hardcoded 2022, but 2015 shall be fine

## How to:
Use the command `./generate.ps1` and hope for the best.

## Generation:
- Visual Studio solution in `./build/Game.sln`.
- Binary executables in `./build/Output/{mode}/Game.exe`.