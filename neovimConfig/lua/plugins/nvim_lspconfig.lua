return {
    "neovim/nvim-lspconfig",

    config = function()

        vim.notify("LSP config function started!", vim.log.levels.INFO, { title = "LazyVim" })

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
        vim.lsp.config('pyright', {
            on_attach = on_attach,
            -- ... other settings
        })


    end
}
