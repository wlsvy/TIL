return {
    "stevearc/aerial.nvim",
    config = function() 
        require("aerial").setup({
            on_attach = function(bufnr)
                -- Jump forwards/backwards with '{' and '}'
                vim.api.nvim_set_keymap("n", "{", "<cmd>AerialPrev<CR>", { buffer = bufnr })
                vim.api.nvim_set_keymap("n", "}", "<cmd>AerialNext<CR>", { buffer = bufnr })
            end,

        })
    end
}
