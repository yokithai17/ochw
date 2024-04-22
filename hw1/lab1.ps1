param(
    [string]$Path = ""
)

if (-not (Test-Path $Path)) { exit }

$files = Get-ChildItem -Path $Path -Filter *.jpg | Sort-Object -Property CreationTime

$i = 1

foreach ($file in $files) {
    $newName = "IMG_" + $i.ToString("D6") + ".jpg"
    Rename-Item -Path $file.FullName -NewName $newName
    $i++
}

