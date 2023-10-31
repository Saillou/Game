# Game
You lost it.

# Build
## Requirements:
- `Powershell`, enable scripts with `Set-ExecutionPolicy RemoteSigned`.
- `CMake`, has to be in the path, version 3.6 at least.
- `Visual Studio` 2022.

## How to:
Use the command `./generate.ps1` and hope for the best.

## Generation:
- Visual Studio solution in `./build/Game.sln`.
- Binary executables in `./build/Output/{mode}/Game.exe`.

# Dependencies:
- `GLM`  (OpenGL Mathematics)                                        | Clone: https://github.com/g-truc/glm
- `Glad` (Get entry points for `opengl32.dll`'s methods) | Generated at: https://glad.dav1d.de/
- `Glfw` (Windows and inputs helper)                              | Official website: https://www.glfw.org/