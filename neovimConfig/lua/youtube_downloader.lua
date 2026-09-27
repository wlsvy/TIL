local function ProcessYoutubeSubtitleLines(lines)
    local clean = {}
    local seen = {} -- 1. seen 테이블 초기화
    for _, line in ipairs(lines) do -- 2. 변수명 lin -> line 으로 통일
        -- SRT 파일의 불필요한 요소 제거
        if not line:match("^%d%d:%d%d")       -- 타임스탬프 (00:00:...)
            and not line:match("^%d+$")       -- SRT 순번 (숫자만 있는 줄)
            and not line:match("^WEBVTT")     -- WEBVTT 헤더
            and not line:match("^%s*$")       -- 빈 줄
            and not line:match("<[^>]+>")     -- HTML 태그
            and not seen[line] then           -- 중복 체크
            
            seen[line] = true -- 3. 중복 방지 마킹
            table.insert(clean, line)
        end
    end
    return clean
end


function fetch_youtube_subtitle(url)

    -- URL 유효성 검사
    if not url or url == "" then
        vim.notify("❌ URL을 입력해주세요.", vim.log.levels.ERROR)
        return
    end

    local lang = "ko"
    local timestamp = os.date("%Y%m%d_%H%M%S")
    local output = "/tmp/youtube_subtitle_" .. timestamp
    local ext = "vtt"
    local sub_path = output .. "." .. lang .. "." .. ext

    -- Automatic cleanup: Delete files starting with 'youtube_subtitle_' older than 24 hours
    local uv = vim.uv or vim.loop
    local tmp_dir = "/tmp"
    local handle = uv.fs_scandir(tmp_dir)
    if handle then
        local now = os.time()
        local one_day_sec = 86400

        while true do
            local name, _ = uv.fs_scandir_next(handle)
            if not name then break end

            if name:match("^youtube_subtitle_") then
                local full_path = tmp_dir .. "/" .. name
                local stat = uv.fs_stat(full_path)
                
                if stat and (now - stat.mtime.sec > one_day_sec) then
                    os.remove(full_path)
                end
            end
        end
    end

    local cmd = {
        "yt-dlp",
        "--skip-download",
        "--write-auto-subs",
        "--sub-langs", lang,
        "--sub-format",ext,
        "--output", output,
        url
    }

    vim.notify("⏳ 자막 다운로드 중... " .. url .. "\n" .. table.concat(cmd, " "), vim.log.levels.INFO)

    local job_id = nil
    local done = false  -- 완료 여부 플래그
    local stderr_lines = {}

    local current_buf = vim.api.nvim_get_current_buf()
    local current_row = vim.api.nvim_win_get_cursor(0)[1] -- 현재 커서 줄 번호 (1-based)

    job_id = vim.fn.jobstart(cmd, {
        stderr_buffered = true,

        on_stderr = function(_, data)
            if data then
                vim.list_extend(stderr_lines, data)
            end
        end,

        on_exit = function(_, exit_code)

            done = true

            -- yt-dlp 실패
            if exit_code ~= 0 then
                local err_msg = table.concat(stderr_lines, "\n")
                vim.notify("❌ yt-dlp 실패 (exit: " .. exit_code .. ")\n" .. err_msg, vim.log.levels.ERROR)
                return
            end

            -- 자막 파일 존재 여부 확인
            if vim.fn.filereadable(sub_path) == 0 then
                vim.notify("❌ 자막 파일을 찾을 수 없습니다: " .. sub_path .. "\n(한국어 자막이 없는 영상일 수 있습니다.)", vim.log.levels.WARN)
                return
            end

            -- 자막 파일 읽기
            local ok, lines = pcall(vim.fn.readfile, sub_path)
            if not ok or not lines then
                vim.notify("❌ 자막 파일 읽기 실패: " .. sub_path, vim.log.levels.ERROR)
                return
            end

            -- 타임스탬프/태그 제거 (순수 텍스트만)
            local clean = ProcessYoutubeSubtitleLines(lines)

            -- 정제된 내용이 없는 경우
            if #clean == 0 then
                vim.notify("⚠️ 자막 내용이 비어 있습니다.", vim.log.levels.WARN)
                return
            end

            -- 현재 버퍼에 출력
            local ok_buf, err_buf = pcall(function()
                -- row, row를 사용하면 현재 줄 바로 다음에 삽입됩니다.
                -- (현재 줄 윗줄에 삽입하려면 row - 1, row - 1 사용)
                vim.api.nvim_buf_set_lines(current_buf, current_row, current_row, false, clean)
            end)

            if not ok_buf then
                vim.notify("❌ 버퍼 출력 실패: " .. tostring(err_buf), vim.log.levels.ERROR)
                return
            end

            vim.notify("✅ " .. url .. " 자막 다운로드 완료 (" .. #clean .. "줄)", vim.log.levels.INFO)
        end
    })

    -- 타임아웃: 30초 후 job 강제 종료
    vim.defer_fn(function()
        if not done then
            vim.fn.jobstop(job_id)
            vim.notify("⏰ 타임아웃: 30초 초과로 작업 취소", vim.log.levels.WARN)
        end
    end, 30000)  -- 30000ms = 30초
end

vim.api.nvim_create_user_command("YoutubeSubtitle", function(opts)
    fetch_youtube_subtitle(opts.args)
end, { nargs = 1 })
