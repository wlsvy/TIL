return {
    'chrishrb/gx.nvim',
    -- keys = { { 'gx', '<cmd>Browse<CR>', mode = { 'n', 'x' } } },
    cmd = { 'Browse' },
    init = function()
        vim.g.netrw_nogx = 1 -- nvim 기본 gx 기능 비활성화
    end,
    config = true, -- 또는 config = function() require('gx').setup() end
}
