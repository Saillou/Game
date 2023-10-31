# Solution creation
if (-Not(Test-Path -Path "./.build")) 
{
    New-Item -ItemType Directory -Path "./.build"
}
Push-Location -Path  "./.build"

# Generate
cmake .. -G "Visual Studio 17 2022" -A x64

Pop-Location

# -----------

# Link and compile
if (-Not(Test-Path -Path "./Output")) 
{
    New-Item -ItemType Directory -Path "./Output"
}
Push-Location -Path  "./Output"

# Generate
cmake --build .

Pop-Location