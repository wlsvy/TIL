return {
    "jamessan/vim-gnupg",
    config = function ()
        vim.cmd("autocmd User GnuPG setl textwidth=72")
    end
}
