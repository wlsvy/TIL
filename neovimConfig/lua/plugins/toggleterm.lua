-- [GitHub - akinshotoggleterm.nvim A neovim lua plugin to help easily manage multiple terminal windows](https://github.com/akinsho/toggleterm.nvim)
return {
    "akinsho/toggleterm.nvim", 

    cond = vim.fn.has('macunix') == 1, -- mac 에서 실행

    config = function()
        require("toggleterm").setup{
            -- size can be a number or function which is passed the current terminal
            size = function(term)
                if term.direction == "horizontal" then
                    return 15
                elseif term.direction == "vertical" then
                    return vim.o.columns * 0.4
                end
            end,

            shade_terminals = true, -- NOTE: this option takes priority over highlights specified so if you specify Normal highlights you should set this to false
            direction = 'float', -- 'vertical' | 'horizontal' | 'tab' | 'float',
            shell = vim.o.shell,

            open_mapping = [[<c-\>]], -- or { [[<c-\>]], [[<c-¥>]] } if you also use a Japanese keyboard.

            float_opts = {
                -- The border key is *almost* the same as 'nvim_open_win'
                -- see :h nvim_open_win for details on borders however
                -- the 'curved' border is a custom border type
                -- not natively supported but implemented in this plugin.
                border = 'curved', -- 'single' | 'double' | 'shadow' | 'curved' | ... other options supported by win open
                -- like `size`, width, height, row, and col can be a number or function which is passed the current terminal
                -- width = <value>,
                -- height = <value>,
                -- row = <value>,
                -- col = <value>,
                -- winblend = 3,
                -- zindex = <value>,
                title_pos = 'center', -- 'left' | 'center' | 'right', position of the title of the floating window
            },
        }
    end
}
