-- [GitHub - akinshotoggleterm.nvim A neovim lua plugin to help easily manage multiple terminal windows](https://github.com/akinsho/toggleterm.nvim)
return {
    "akinsho/toggleterm.nvim", 
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
            direction = 'vertical', -- 'vertical' | 'horizontal' | 'tab' | 'float',
            shell = vim.o.shell,
        }
    end
}
