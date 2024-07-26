using DotnetToyConsole;

public static class Shell
{
    public async static Task<string> Execute(string command)
    {
        // 프로세스 정보 설정
        ProcessStartInfo psi = new ProcessStartInfo
        {
            FileName = "C:\\Program Files\\Git\\bin\\bash.exe", // Git Bash 경로 (Windows)
            RedirectStandardInput = true,
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            UseShellExecute = false,
            CreateNoWindow = true,
            Arguments = "-c \"" + command + "\""
        };

        // 프로세스 생성
        Process process = new Process
        {
            StartInfo = psi
        };

        try
        {
            // 프로세스 시작
            process.Start();

            // 명령어 출력 읽기
            string output = await process.StandardOutput.ReadToEndAsync();
            string error = await process.StandardError.ReadToEndAsync();

            // 프로세스가 종료될 때까지 대기
            await process.WaitForExitAsync();

            // 오류가 있으면 오류 메시지를 포함한 출력 반환
            if (!string.IsNullOrEmpty(error))
            {
                return $"Error: {error}";
            }

            // 출력 결과 반환
            return output;
        }
        catch (Exception ex)
        {
            return $"Exception: {ex.Message}";
        }
    }
}
