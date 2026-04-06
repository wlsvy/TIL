return {
    "nvim-treesitter/nvim-treesitter",
    lazy = false,
    build = ":TSUpdate",
    branch = "main",
    opts = {
        -- ensure_installed = { "c", "lua", "markdown", "markdown_inline", "query", "vim", "vimdoc", "c_sharp" ,"python" },
        indent = { enable = true },
        folding = { enable = true, },
    },
}
