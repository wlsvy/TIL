
-- [GitHub - olimorris/codecompanion.nvim: ✨ AI Coding, Vim Style](https://github.com/olimorris/codecompanion.nvim)
return {
    "olimorris/codecompanion.nvim",
    cond = vim.fn.has('macunix') == 1, -- mac 에서 실행
    dependencies = {
        "nvim-lua/plenary.nvim",
        "nvim-treesitter/nvim-treesitter",
    },

    config = function ()
        require("codecompanion").setup({

            strategies = {
                chat = {
                    -- adapter = "openai",
                    -- model = "gpt-4o"

                    adapter = "gemini",
                    model = "gemini-2.5-flash:generateContent",
                },
                inline = {
                    adapter = "gemini",
                },
            },

            -- NOTE: The log_level is in `opts.opts`
            opts = {
                log_level = "DEBUG", -- or "TRACE"
            },

            adapters = {
                http = {
                    gemini = function()
                        return require("codecompanion.adapters").extend("gemini", {
                            env = {
                                api_key = "FIX_HERE", -- fix here
                            },
                        })
                    end,
                }
            }
        })
    end
}
