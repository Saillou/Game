# Generate solution
New-Item -ItemType Directory -Path "./.tmp"
Set-Location -Path  "./.tmp"

cmake .. -G "Visual Studio 17 2022" -A x64