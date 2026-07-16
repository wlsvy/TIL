-- [arnauKLsouth.nvim Port of the emacs south theme.](https://github.com/arnauKL/south.nvim)
return {
    'arnauKL/south.nvim',
    lazy = false,
    priority = 1000,
    config = function()
        -- Optional configuration goes here
        require('south').setup({
            transparent = false,
            -- ...
        })
        vim.cmd.colorscheme('south')
    end
}
