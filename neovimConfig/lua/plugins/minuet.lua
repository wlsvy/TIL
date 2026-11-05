-- [milanglacier/minuet-ai.nvim: 💃 Dance with Intelligence in Your Code](https://github.com/milanglacier/minuet-ai.nvim)
return {
    "milanglacier/minuet-ai.nvim",
    event = "InsertEnter",
    cmd = "Minuet",
    config = function()
        require("minuet").setup({
            provider = "claude",
            provider_options = {
                -- ANTHROPIC_API_KEY 를 쓰면 Claude Code CLI 도 API 키로 인증하므로 전용 변수를 사용
                claude = {
                    api_key = "MINUET_ANTHROPIC_API_KEY",
                    -- Haiku 5.5 는 thinking 이 기본으로 켜져 있어, 짧은 시간·토큰 제한 안에 텍스트가 나오지 않음
                    optional = { thinking = { type = "disabled" } },
                },
            },
            virtualtext = {
                -- 버퍼 내용이 자동 전송되지 않도록 자동 트리거는 끔. :Minuet virtualtext toggle 로 버퍼별로 켬
                auto_trigger_ft = {},
                keymap = {
                    accept = "<A-A>",
                    accept_line = "<A-a>",
                    prev = "<A-[>",
                    next = "<A-]>",
                    dismiss = "<A-e>",
                },
            },
        })

        -- 요청 중 현재 줄 끝에 스피너 표시
        -- shortcut: 요청이 여러 개면 첫 완료 시점에 멈춤, 여러 요청을 쓰게 되면 request_idx/n_requests 로 집계
        local ns = vim.api.nvim_create_namespace("minuet_spinner")
        local frames = { "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏" }
        local timer, buf, mark

        local function stop()
            if timer then timer:stop(); timer:close(); timer = nil end
            if buf and vim.api.nvim_buf_is_valid(buf) then vim.api.nvim_buf_clear_namespace(buf, ns, 0, -1) end
            mark = nil
        end

        vim.api.nvim_create_autocmd("User", { pattern = "MinuetRequestStartedPre", callback = function()
            stop()
            buf = vim.api.nvim_get_current_buf()
            local row, i = vim.api.nvim_win_get_cursor(0)[1] - 1, 0
            timer = vim.uv.new_timer()
            timer:start(0, 80, vim.schedule_wrap(function()
                if not timer or not vim.api.nvim_buf_is_valid(buf) or row >= vim.api.nvim_buf_line_count(buf) then return stop() end
                i = i % #frames + 1
                mark = vim.api.nvim_buf_set_extmark(buf, ns, row, 0, { id = mark, virt_text = { { frames[i], "Comment" } }, virt_text_pos = "eol" })
            end))
        end })

        vim.api.nvim_create_autocmd("User", { pattern = "MinuetRequestFinished", callback = stop })
    end,
}
