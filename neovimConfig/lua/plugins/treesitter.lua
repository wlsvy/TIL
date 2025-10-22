return {
    "nvim-treesitter/nvim-treesitter",
    run = ":TSUpdate",
    dependencies = { "OXY2DEV/markview.nvim",},
    opts = { 
        ensure_installed = { "c", "lua", "markdown", "markdown_inline", "query", "vim", "vimdoc", "c_sharp" ,"python" },
        indent = { enable = true },
        folding = { enable = true, },
    },
}
