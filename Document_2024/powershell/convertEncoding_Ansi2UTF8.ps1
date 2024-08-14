## 사용 예시 : `.\<filename.ps1> -directoryPath .\logs\`
param (
    [string]$directoryPath = "C:\default\directory\path"  # 기본 경로 설정
)

# 인자로 받은 디렉토리 경로 확인
if (-not (Test-Path -Path $directoryPath)) {
    Write-Host "The specified directory does not exist. Please provide a valid directory path. [$directoryPath]"
    exit
}

# 디렉토리 내의 모든 파일 가져오기
$files = Get-ChildItem -Path $directoryPath -File

# 각 파일에 대해 작업 수행
foreach ($file in $files) {

    # 파일 스트림을 열고 인코딩을 확인
    $reader = [System.IO.StreamReader]::new($file.FullName, [System.Text.Encoding]::Default, $true)
    $null = $reader.Peek()  # Force the StreamReader to detect encoding
    $encoding = $reader.CurrentEncoding
    $reader.Close()

    # ANSI 인코딩인지 확인
    if ($encoding.BodyName -eq "us-ascii" -or $encoding.BodyName -eq "iso-8859-1") {    
        Write-Host "File $($file.FullName) is detected as ANSI."

        # 파일 내용을 ANSI로 읽기
        $content = Get-Content -Path $file.FullName -Encoding Default

        # UTF-8로 다시 쓰기
        Set-Content -Path $file.FullName -Value $content -Encoding UTF8

        Write-Host "Converted $($file.FullName) to UTF-8 encoding"
    } else {
        Write-Host "File $($file.FullName) is not ANSI or already UTF-8. Skipping conversion."
    }
}

Write-Host "Processing complete."

