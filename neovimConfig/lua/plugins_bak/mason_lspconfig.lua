return {
    "williamboman/mason-lspconfig.nvim",

    dependencies = {
        { "mason-org/mason.nvim", opts = {} },
        "neovim/nvim-lspconfig",
    },

    config = function()

        vim.notify("mason-lspconfig config function started!", vim.log.levels.INFO, { title = "LazyVim" })


        require("mason-lspconfig").setup{
            ensure_installed = { "lua_ls", "pyright",},
        }

    end

}
