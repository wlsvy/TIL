-- [MeanderingProgrammer/render-markdown.nvim: Plugin to improve viewing Markdown files in Neovim](https://github.com/MeanderingProgrammer/render-markdown.nvim)
return {
    'MeanderingProgrammer/render-markdown.nvim',
    dependencies = { 'nvim-treesitter/nvim-treesitter', 'nvim-tree/nvim-web-devicons' }, -- if you prefer nvim-web-devicons

    ---@module 'render-markdown'
    ---@type render.md.UserConfig
    opts = {},
    config = function()
        require('render-markdown').setup({
            enabled = true,
            file_types = { 'markdown', 'codecompanion' },
        })

        vim.keymap.set('n', '<leader>vm', function()
            local ok, rm = pcall(require, 'render-markdown')
            if not ok then
                vim.notify('render-markdown plugin not found', vim.log.levels.WARN)
                return
            end
            rm.toggle()
        end, { desc = 'Toggle render-markdown' })

    end
}
