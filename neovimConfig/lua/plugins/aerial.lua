-- [GitHub - stevearcaerial.nvim Neovim plugin for a code outline window](https://github.com/stevearc/aerial.nvim)
return {
    "stevearc/aerial.nvim",
    dependencies = {
        "nvim-treesitter/nvim-treesitter",
        "nvim-tree/nvim-web-devicons"
    },
    config = function() 
        require("aerial").setup({

            backends = { "treesitter", "lsp", "markdown", },

            -- Determines how the aerial window decides which buffer to display symbols for
            --   window - aerial window will display symbols for the buffer in the window from which it was opened
            --   global - aerial window will display symbols for the current window
            attach_mode = "window",

            -- Disable aerial on files with this many lines
            disable_max_lines = 20000,

            -- Disable aerial on files this size or larger (in bytes)
            disable_max_size = 5000000, -- 5MB

            on_attach = function(bufnr)
                vim.api.nvim_set_keymap("n", "<leader>a", "<cmd>AerialToggle right<CR>", { noremap = true, silent = true })
                vim.api.nvim_set_keymap("n", "<leader><leader>h", "<cmd>AerialPrev<CR>", { noremap = true, silent = true })
                vim.api.nvim_set_keymap("n", "<leader><leader>l", "<cmd>AerialNext<CR>", { noremap = true, silent = true })
                vim.api.nvim_set_keymap("n", "<leader>A", "<cmd>AerialNavToggle<CR>", { noremap = true, silent = true })
            end,

        })
    end
}

--[[
Command	Args	Description
AerialToggle[!]	left/right/float	Open or close the aerial window. With ! cursor stays in current window
AerialOpen[!]	left/right/float	Open the aerial window. With ! cursor stays in current window
AerialOpenAll		Open an aerial window for each visible window.
AerialClose		Close the aerial window.
AerialCloseAll		Close all visible aerial windows.
[count]AerialNext		Jump forwards {count} symbols (default 1).
[count]AerialPrev		Jump backwards [count] symbols (default 1).
[count]AerialGo[!]		Jump to the [count] symbol (default 1).
AerialInfo		Print out debug info related to aerial.
AerialNavToggle		Open or close the aerial nav window.
AerialNavOpen		Open the aerial nav window.
AerialNavClose		Close the aerial nav window.
--]]
