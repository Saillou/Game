# Create solution in a temporary folder
if (-Not(Test-Path -Path "./.build")) 
{
    New-Item -ItemType Directory -Path "./.build"
}

Push-Location -Path  "./.build"

# Generate it
cmake .. -G "Visual Studio 17 2022" -A x64

# Compile it
cmake --build . --config Debug
cmake --build . --config Release

Pop-Location