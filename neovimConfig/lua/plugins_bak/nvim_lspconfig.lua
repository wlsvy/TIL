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
            -- vim.keymap.set('n', 'gr', vim.lsp.buf.references, opts)
            vim.keymap.set('n', 'rn', vim.lsp.buf.rename, opts)
            vim.keymap.set('n', '<leader>ca', vim.lsp.buf.code_action, opts)
            vim.keymap.set('n', 'grf', function() vim.lsp.buf.format { async = true } end, opts)

            -- 진단 키맵 (누락된 부분 추가)
            vim.keymap.set('n', '<leader>de', vim.diagnostic.open_float, opts)
            vim.keymap.set('n', '<leader>dq', vim.diagnostic.setloclist, opts)

        end

        -- 기본 capabilities 설정
        local capabilities = vim.lsp.protocol.make_client_capabilities()
        if pcall(require, 'cmp_nvim_lsp') then
            capabilities = require('cmp_nvim_lsp').default_capabilities(capabilities)
        end

        -- Python LSP
        vim.lsp.config.pyright = {
            cmd = { 'pyright-langserver', '--stdio' },
            filetypes = { 'python' },
            root_markers = { 'pyproject.toml', 'setup.py', 'setup.cfg', 'requirements.txt', 'Pipfile', 'pyrightconfig.json' },
            on_attach = on_attach,
            capabilities = capabilities,
        }

        -- C# OmniSharp LSP
        vim.lsp.config.omnisharp = {
            cmd = { 'omnisharp', '--languageserver', '--hostPID', tostring(vim.fn.getpid()) },
            filetypes = { 'cs', 'vb' },
            root_markers = { '*.sln', '*.csproj', 'omnisharp.json', 'function.json' },
            on_attach = on_attach,
            capabilities = capabilities,
            settings = {
                FormattingOptions = {
                    EnableEditorConfigSupport = true,
                    OrganizeImports = true,
                },
                MsBuild = {
                    LoadProjectsOnDemand = false,
                },
                RoslynExtensionsOptions = {
                    EnableAnalyzersSupport = true,
                    EnableImportCompletion = true,
                    AnalyzeOpenDocumentsOnly = false,
                },
            },
        }

        -- TypeScript/JavaScript LSP
        vim.lsp.config.ts_ls = {
            cmd = { 'typescript-language-server', '--stdio' },
            filetypes = { 'javascript', 'javascriptreact', 'typescript', 'typescriptreact' },
            root_markers = { 'package.json', 'tsconfig.json', 'jsconfig.json' },
            on_attach = on_attach,
            capabilities = capabilities,
        }

        -- Lua LSP
        vim.lsp.config.lua_ls = {
            cmd = { 'lua-language-server' },
            filetypes = { 'lua' },
            root_markers = { '.luarc.json', '.luarc.jsonc', '.luacheckrc', '.stylua.toml', 'stylua.toml', 'selene.toml', 'selene.yml' },
            on_attach = on_attach,
            capabilities = capabilities,
            settings = {
                Lua = {
                    runtime = { version = 'LuaJIT' },
                    diagnostics = { globals = { 'vim' } },
                    workspace = {
                        library = vim.api.nvim_get_runtime_file("", true),
                        checkThirdParty = false,
                    },
                    telemetry = { enable = false },
                },
            },
        }

        -- 진단 표시 설정
        vim.diagnostic.config({
            virtual_text = true,
            signs = true,
            underline = true,
            update_in_insert = false,
            severity_sort = true,
        })
    end
}
