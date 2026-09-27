-- [preservim/nerdtree: A tree explorer plugin for vim.](https://github.com/preservim/nerdtree)
return {
    "preservim/nerdtree",
    dependencies = { 'nvim-tree/nvim-web-devicons' },
    config = function()
        vim.g.NERDTreeUseDevIcons = true,
        vim.api.nvim_set_keymap("n", "<leader>n", "<cmd>NERDTree<CR>", { noremap = true, silent = true })
        vim.api.nvim_set_keymap("n", "<leader>N", "<cmd>NERDTreeFind<CR>", { noremap = true, silent = true })
    end
}
