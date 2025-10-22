-- [GitHub - gennaro-tedesconvim-possession 📌 the no-nonsense session manager](https://github.com/gennaro-tedesco/nvim-possession)
return {
    "gennaro-tedesco/nvim-possession",
    dependencies = {
        "ibhagwan/fzf-lua",
    },
    keys = {
        { "<leader>sl", function() require("nvim-possession").list() end, desc = "📌list sessions", },
        { "<leader>sn", function() require("nvim-possession").new() end, desc = "📌create new session", },
        { "<leader>su", function() require("nvim-possession").update() end, desc = "📌update current session", },
        { "<leader>sd", function() require("nvim-possession").delete() end, desc = "📌delete selected session"},
    },
    config = function()

        require("nvim-possession").setup({
            sessions = {
                sessions_path = vim.fn.stdpath("data") .. "\\session\\", -- folder to look for sessions, must be a valid existing path
                sessions_variable = "nvim_possession_sessions", -- defines vim.g[sessions_variable] when a session is loaded
                sessions_icon = '🦆', -- string: shows icon both in the prompt and in the statusline
                -- sessions_prompt = ... -- fzf prompt string
            },

            autoload = false, -- whether to autoload sessions in the cwd at startup
            autosave = false, -- whether to autosave loaded sessions before quitting
            autoswitch = {
                enable = false,-- whether to enable autoswitch
                exclude_ft = {}, -- list of filetypes to exclude from autoswitch
            },

            save_hook = nil, -- callback, function to execute before saving a session
            -- useful to update or cleanup global variables for example
            post_hook = nil, -- callback, function to execute after loading a session
            -- useful to restore file trees, file managers or terminals
            -- function()
            --     require('FTerm').open()
            --     require("nvim-tree.api").tree.toggle()
            -- end

            ---@type possession.Hls
            fzf_hls = { -- highlight groups for the sessions and preview windows
                normal = "Normal",
                preview_normal = "Normal",
                border = "Todo",
                preview_border = "Constant",
            },
            ---@type possession.Winopts
            fzf_winopts = {
                -- any valid fzf-lua winopts options, for instance
                width = 0.5,
                preview = {
                    vertical = "right:30%"
                }
            },
            ---@type possession.Mapopts
            mappings = { -- configure action keymaps on possession.list() picker
                action_delete = "ctrl-x",
                action_rename = "ctrl-r",
                action_new = "ctrl-n",
            },
        })
    end,
}
