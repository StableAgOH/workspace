$ErrorActionPreference = "Stop"

function ExitIfNotZero {
    param ($Message)

    if ($LASTEXITCODE) {
        Write-Error $Message
    }
}

Write-Output "[INFO] Compiling temp.cpp"
clang++ temp.cpp -o temp -O2 -std=c++20
ExitIfNotZero "[CE] temp.cpp"

Write-Output "[INFO] Compiling test.cpp"
clang++ test.cpp -o test -O2 -std=c++20
ExitIfNotZero "[CE] test.cpp"

for ($i = 1; ; $i++) {
    Write-Output "[INFO] Testcase No.$i"

    python data.py > .\in.in
    ExitIfNotZero "[RE] data.py"

    Get-Content in.in | .\temp > .\out.out
    ExitIfNotZero "[RE] temp.cpp"

    Get-Content in.in | .\test > .\out2.out
    ExitIfNotZero "[RE] test.cpp"

    fc.exe /W .\out.out .\out2.out
    ExitIfNotZero "[ERROR] Two results do not match"

    Start-Sleep 0.5
}
