-- [snacks.nvim/docs/image.md at main · folke/snacks.nvim](https://github.com/folke/snacks.nvim/blob/main/docs/image.md)
return {
    "folke/snacks.nvim",
    ---@type snacks.Config
    opts = {
        -- your configuration comes here
        -- or leave it empty to use the default settings
        -- refer to the configuration section below
        bigfile = { enabled = true },
        dashboard = { enabled = false, },
        explorer = { enabled = true },
        indent = { enabled = true },
        input = { enabled = true },
        picker = { enabled = true },
        notifier = { enabled = true },
        quickfile = { enabled = true },
        scope = { enabled = true },
        scroll = { enabled = true },
        statuscolumn = { enabled = true },
        words = { enabled = true },
        lazygit = { },
        image = { enabled = false, },
    },
    priority=1000,

    config = function()

        vim.api.nvim_set_keymap('n', '<leader>s;', ':lua Snacks.explorer()<CR>', { noremap = true, silent = true }) -- 파일 찾기 
        vim.api.nvim_set_keymap('n', '<leader>t', ':lua Snacks.picker.files()<CR>', { noremap = true, silent = true }) -- 파일 찾기 
        vim.api.nvim_set_keymap('n', '<C-f>', ':lua Snacks.picker.lines()<CR>', { noremap = true, silent = true }) -- 버퍼 목록 보기 
        vim.api.nvim_set_keymap('n', '<leader>g', ':lua Snacks.picker.grep()<CR>', { noremap = true, silent = true }) -- grep / text 검색
        vim.api.nvim_set_keymap('n', '<leader>G', ':lua Snacks.picker.grep_word()<CR>', { noremap = true, silent = true }) -- grep_word / 정확한 단어 검색

    end
}
