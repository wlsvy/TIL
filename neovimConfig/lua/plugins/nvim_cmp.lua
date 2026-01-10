return {
    "hrsh7th/nvim-cmp",
    dependencies = {
        "hrsh7th/cmp-nvim-lsp", -- LSP를 자동완성 소스로 사용
        "hrsh7th/cmp-buffer",   -- 현재 버퍼의 텍스트를 소스로 사용
        "hrsh7th/cmp-path",     -- 파일 경로를 소스로 사용
        'L3MON4D3/LuaSnip',
        'saadparwaiz1/cmp_luasnip',
    },
    config = function()
        local cmp = require("cmp")
        local luasnip = require("luasnip")

        cmp.setup({
            -- ... (스니펫, UI 설정 등) ...
            sources = cmp.config.sources({
                { name = "nvim_lsp" }, -- LSP 소스 등록
                { 
                    name = "buffer" ,
                    option = {
                        --  점(.)과 골뱅이(@)가 포함된 단어도 하나로 인식하도록 설정
                        keyword_pattern = [[\%(\k\|[.@]\)\+]],

                        -- 모든 버퍼를 가져오는 함수를 지정
                        get_bufnrs = function()
                            -- 현재 열려있는 모든 버퍼 목록을 반환
                            return vim.api.nvim_list_bufs()
                        end
                    }
                },
                { name = "path" },
                { name = "luasnip" },
            }),

            snippet = {
                expand = function(args)
                    luasnip.lsp_expand(args.body)
                end,
            },

            -- 키매핑 설정 (Tab, Enter 등으로 자동완성 선택)
            mapping = cmp.mapping.preset.insert({
                ['<C-b>'] = cmp.mapping.scroll_docs(-4),
                ['<C-f>'] = cmp.mapping.scroll_docs(4),
                ['<C-Space>'] = cmp.mapping.complete(),
                ['<C-e>'] = cmp.mapping.abort(),
                ['<CR>'] = cmp.mapping.confirm({ select = true }),
                ['<Tab>'] = cmp.mapping(function(fallback)
                    if cmp.visible() then
                        cmp.select_next_item()
                    elseif luasnip.expand_or_jumpable() then
                        luasnip.expand_or_jump()
                    else
                        fallback()
                    end
                end, { 'i', 's' }),
                ['<S-Tab>'] = cmp.mapping(function(fallback)
                    if cmp.visible() then
                        cmp.select_prev_item()
                    elseif luasnip.jumpable(-1) then
                        luasnip.jump(-1)
                    else
                        fallback()
                    end
                end, { 'i', 's' }),
            }),
        })
    end,
}
