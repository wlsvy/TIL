return {
    'Vigemus/iron.nvim',

    config = function ()

        local iron = require("iron.core")

        iron.setup {
            config = {
                -- 언어별 실행할 REPL 명령 정의
                repl_definition = {
                    python = { command = { "python3" } },
                    powershell = { command = { "pwsh" } },
                },
                -- REPL 터미널이 열릴 위치 (오른쪽 40% 너비)
                repl_open_cmd = "vertical botright 40split"
            },
            -- 단축키 설정
            keymaps = {
                toggle_repl = "<space>rr", -- toggles the repl open and closed.
                restart_repl = "<space>rR", -- calls `IronRestart` to restart the repl
                send_motion = "<space>rc", -- 동작(motion)으로 보내기
                visual_send = "<space>rc", -- 비주얼 모드에서 선택 영역 보내기
                send_line = "<space>rl",   -- 현재 줄 보내기
                interrupt = "<space>ri",   -- 실행 중단 (Ctrl+C)
                clear = "<space>rx",       -- 화면 지우기
            }
        }
    end
}
