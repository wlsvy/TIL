-- [williamboman/mason-lspconfig.nvim: Extension to mason.nvim that makes it easier to use lspconfig with mason.nvim.](https://github.com/williamboman/mason-lspconfig.nvim)
return {
    "williamboman/mason.nvim",

    config = function()
        require("mason").setup()
    end
}
