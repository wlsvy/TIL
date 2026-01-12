-- [nvim-telescopetelescope-symbols.nvim](https://github.com/nvim-telescope/telescope-symbols.nvim)
return {
    'nvim-telescope/telescope-symbols.nvim',
    config = function ()

        vim.api.nvim_set_keymap('n', '<leader>fs', '<cmd>lua require("telescope.builtin").symbols{ sources = {"emoji", "kaomoji", "gitmoji"}}<CR>', { noremap = true, silent = true })

    end
}
