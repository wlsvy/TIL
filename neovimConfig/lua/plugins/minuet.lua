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
    end,
}
