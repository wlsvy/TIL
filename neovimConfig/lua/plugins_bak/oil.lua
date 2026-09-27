-- [stevearc/oil.nvim: Neovim file explorer: edit your filesystem like a buffer](https://github.com/stevearc/oil.nvim)
return {
    'stevearc/oil.nvim',
    ---@module 'oil'
    ---@type oil.SetupOpts
    opts = {},
    -- Optional dependencies
    dependencies = { 
        { "nvim-mini/mini.icons", opts = {} },
        { "nvim-tree/nvim-web-devicons" },
    },

    -- Lazy loading is not recommended because it is very tricky to make it work correctly in all situations.
    lazy = false,

    config = function()
        require("oil").setup()

        vim.keymap.set("n", "<space>o", "<CMD>Oil<CR>", { desc = "Open parent directory" })

        vim.api.nvim_create_user_command('OilSave', function()
            require("oil").save()
        end, {})

    end
}
