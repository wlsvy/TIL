-- [olimorris/codecompanion.nvim: ✨ AI Coding, Vim Style](https://github.com/olimorris/codecompanion.nvim)
return {
    "olimorris/codecompanion.nvim",
    dependencies = {
        "nvim-lua/plenary.nvim",
        "nvim-treesitter/nvim-treesitter",
    },
    cond = vim.fn.has('macunix') == 1, -- mac 에서 실행
    opts = {
        -- NOTE: The log_level is in `opts.opts`
        opts = {

            log_level = "DEBUG", -- or "TRACE"
            interactions = {
                chat = {
                    adapter = "anthropic",
                    model = "claude-sonnet-4-20250514"
                },
            },
        },
    },
    config = function ()
        require("codecompanion").setup({
            interactions = {
                chat = {
                    -- You can specify an adapter by name and model (both ACP and HTTP)
                    adapter = {
                        name = "anthropic",
                        model = "claude-sonnet-4-20250514",
                    },
                    opts = {
                        completion_provider = "cmp", -- blink|cmp|coc|default
                    }
                },
                -- Or, just specify the adapter by name
                inline = {
                    adapter = "anthropic",
                },
                cmd = {
                    adapter = "anthropic",
                },
                cli = {
                    agent = "claude_code",
                    agents = {
                        claude_code = {
                            cmd = "claude",
                            args = {},
                            description = "Claude Code CLI",
                            provider = "terminal",
                        },
                    },
                },
                background = {
                    adapter = {
                        name = "anthropic",
                        -- model = "qwen-7b-instruct",
                    },
                },
            },
            adapters = {
                http = {
                    anthropic = function()
                        return require("codecompanion.adapters").extend("anthropic", {
                            env = {
                                api_key = "CODE_COMPANION_ANTHROPIC_API_KEY",
                            },
                        })
                    end,
                },
            },

            display = {
                chat = {
                    icons = {
                        buffer_sync_all = "󰪴 ",
                        buffer_sync_diff = " ",
                        chat_context = "📎️", -- You can also apply an icon to the fold
                        chat_fold = " ",
                        tool_pending = "  ",
                        tool_in_progress = "  ",
                        tool_failure = "  ",
                        tool_success = "  ",
                    },
                    fold_context = true,
                    window = {
                        buflisted = true, -- List the chat buffer in the buffer list?
                        sticky = true, -- Chat window follows when switching tabs
                        layout = "vertical", -- float|vertical|horizontal|tab|buffer
                        full_height = true, -- for vertical layout
                        position = "right", -- left|right|top|bottom (nil will default depending on
                    }
                },
            },
        })
    end
}
