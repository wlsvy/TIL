-- [snacks.nvim/docs/image.md at main · folke/snacks.nvim](https://github.com/folke/snacks.nvim/blob/main/docs/image.md)
return {
    "folke/snacks.nvim",
    ---@type snacks.Config
    opts = {
        -- your configuration comes here
        -- or leave it empty to use the default settings
        -- refer to the configuration section below
        bigfile = { enabled = true },
        dashboard = { 
            enabled = true, 
            sections = {
                { section = "header" },
                { icon = " ", title = "Keymaps", section = "keys", indent = 2, padding = 1 },
                { icon = " ", title = "Recent Files", section = "recent_files", indent = 2, padding = 1 },
                { icon = " ", title = "Projects", section = "projects", indent = 2, padding = 1 },
                { section = "startup" },
            },
        },
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
        image = {
            doc = {
                -- enable image viewer for documents
                -- a treesitter parser must be available for the enabled languages.
                enabled = true,
                -- render the image inline in the buffer
                -- if your env doesn't support unicode placeholders, this will be disabled
                -- takes precedence over `opts.float` on supported terminals
                inline = true,
                -- render the image in a floating window
                -- only used if `opts.inline` is disabled
                float = true,
                max_width = 80,
                max_height = 40,
                backend = 'iterm',
                -- Set to `true`, to conceal the image text when rendering inline.
                -- (experimental)
                ---@param lang string tree-sitter language
                ---@param type snacks.image.Type image type
                conceal = function(lang, type)
                    -- only conceal math expressions
                    return type == "math"
                end,
            },
        },
    },
    priority=1000,

    config = function()

        vim.api.nvim_set_keymap('n', '<leadek>;', ':lua Snacks.explorer()<CR>', { noremap = true, silent = true }) -- 파일 찾기 
        vim.api.nvim_set_keymap('n', '<C-p>', ':lua Snacks.picker.pickers()<CR>', { noremap = true, silent = true }) -- Snacks.picker 리스트
        vim.api.nvim_set_keymap('n', '<C-f>', ':lua Snacks.picker.lines()<CR>', { noremap = true, silent = true }) -- 버퍼 목록 보기 
        vim.api.nvim_set_keymap('n', '<leader>b', ':lua Snacks.picker.grep_buffers()<CR>', { noremap = true, silent = true }) -- 현재 파일 텍스트 검색 
        vim.api.nvim_set_keymap('n', '<leader>q', ':lua Snacks.picker.autocmds()<CR>', { noremap = true, silent = true }) -- 명령어 탐색 키맵핑
        vim.api.nvim_set_keymap('n', '<leader>Q', ':lua Snacks.picker.command_history()<CR>', { noremap = true, silent = true }) -- 명령어 히스토리
        vim.api.nvim_set_keymap('n', '<leader>t', ':lua Snacks.picker.files()<CR>', { noremap = true, silent = true }) -- find_files
        vim.api.nvim_set_keymap('n', '<leader>T', ':lua Snacks.picker.treesitter()<CR>', { noremap = true, silent = true }) -- treesitter
        vim.api.nvim_set_keymap('n', '<leader>g', ':lua Snacks.picker.grep()<CR>', { noremap = true, silent = true }) -- grep / text 검색
        vim.api.nvim_set_keymap('n', '<leader>G', ':lua Snacks.picker.grep_word()<CR>', { noremap = true, silent = true }) -- grep_word / 정확한 단어 검색

    end
}
