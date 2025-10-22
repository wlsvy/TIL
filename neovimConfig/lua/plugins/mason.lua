-- [williamboman/mason-lspconfig.nvim: Extension to mason.nvim that makes it easier to use lspconfig with mason.nvim.](https://github.com/williamboman/mason-lspconfig.nvim)
return {
    "williamboman/mason.nvim",
    "williamboman/mason-lspconfig.nvim",
    "neovim/nvim-lspconfig",

    config = function()
        require("mason-lspconfig").setup_handlers {
            -- 기본 설정 핸들러
            function(server_name)
                require("lspconfig")[server_name].setup {}
            end,
            -- 특정 LSP에 대한 커스텀 설정을 하고 싶다면 여기에 추가
            ["lua_ls"] = function()
                require("lspconfig").lua_ls.setup {
                    settings = {
                        Lua = {
                            diagnostics = {
                                globals = { "vim" },
                            },
                        },
                    },
                }
            end
        }

        require("mason").setup()
        require("mason-lspconfig").setup{
            ensure_installed = { "lua_ls",},
        }

        local on_attach = function(client, bufnr)
            -- 아래 키맵들은 이 파일에 연결된 LSP 서버가 지원하는 경우에만 작동합니다.
            local opts = { buffer = bufnr, noremap = true, silent = true }

            -- 리팩토링 및 주요 기능 키맵
            vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
            vim.keymap.set('n', 'K', vim.lsp.buf.hover, opts)
            vim.keymap.set('n', 'gi', vim.lsp.buf.implementation, opts)
            vim.keymap.set('n', 'gr', vim.lsp.buf.references, opts)
            vim.keymap.set('n', 'rn', vim.lsp.buf.rename, opts)
            vim.keymap.set('n', '<leader>ca', vim.lsp.buf.code_action, opts)
            vim.keymap.set('n', '<leader>f', function() vim.lsp.buf.format { async = true } end, opts)

            -- 진단(오류) 관련 키맵
            vim.keymap.set('n', '[d', vim.diagnostic.goto_prev, opts)
            vim.keymap.set('n', ']d', vim.diagnostic.goto_next, opts)
        end

        -- 각 LSP 서버를 설정할 때 on_attach 함수를 연결해줍니다-- .
        require('lspconfig').pyright.setup({
            on_attach = on_attach,
            -- ... other settings
        })


    end
}
