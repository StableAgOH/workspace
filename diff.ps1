$ErrorActionPreference = "Stop"

function ExitIfNotZero {
    param ($Message)

    if ($LASTEXITCODE) {
        Write-Error $Message
    }
}

$Program1 = $args[0]
if (!$Program1) {
    $Program1 = "temp.cpp"
}
$Program2 = $args[1]
if (!$Program2) {
    $Program2 = "test.cpp"
}

Write-Output "[INFO] Compiling $Program1"
g++ $Program1 -o temp -O2 -std=c++20
ExitIfNotZero "[CE] $Program1"

Write-Output "[INFO] Compiling $Program2"
g++ $Program2 -o test -O2 -std=c++20
ExitIfNotZero "[CE] $Program2"

for ($i = 1; ; $i++) {
    Write-Output "[INFO] Testcase No.$i"

    python data.py > in.txt
    ExitIfNotZero "[RE] data.py"

    Get-Content in.txt | ./temp > out.txt
    ExitIfNotZero "[RE] $Program1"

    Get-Content in.txt | ./test > out2.txt
    ExitIfNotZero "[RE] $Program2"

    fc.exe /W out.txt out2.txt
    ExitIfNotZero "[ERROR] Two results do not match"

    Start-Sleep 0.5
}
