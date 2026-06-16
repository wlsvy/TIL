return {
    "hrsh7th/nvim-cmp",
    dependencies = {
        "hrsh7th/cmp-nvim-lsp", -- LSP를 자동완성 소스로 사용
        "hrsh7th/cmp-buffer",   -- 현재 버퍼의 텍스트를 소스로 사용
        "hrsh7th/cmp-path",     -- 파일 경로를 소스로 사용
        'L3MON4D3/LuaSnip',
        'saadparwaiz1/cmp_luasnip',
        "folke/lazydev.nvim",
    },
    config = function()

        -- Enum 정의
        local BufferMode = {
            ALL = "all",
            CURRENT = "current",
            TABPAGE = "tabpage",
            NONE = "none"
        }

        -- 버퍼 소스 설정을 위한 함수들
        local current_cmp_source_frombuffer_mode = BufferMode.CurrentBuffer

        vim.api.nvim_create_user_command('CmpBuffer', function(opts)

                    local mode = opts.args:upper()

                    if BufferMode[mode] then
                        current_cmp_source_frombuffer_mode = BufferMode[mode]

                        local messages = {
                            ALL = "모든 버퍼를 자동완성 소스로 사용",
                            CURRENT = "현재 버퍼만 자동완성 소스로 사용",
                            TABPAGE = "현재 탭의 버퍼들을 자동완성 소스로 사용",
                            NONE = "버퍼 자동완성 비활성화"
                        }

                        print("CMP: " .. messages[mode])
                    else
                        print("CMP: 유효하지 않은 모드. 사용 가능: ALL, CURRENT, TABPAGE, NONE")
                    end
                end, {
            nargs = 1,
            complete = function()
                    return { "ALL", "CURRENT", "TABPAGE", "NONE" }
                end,
            desc = "CMP 버퍼 소스 모드 변경"
        })

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
                        get_bufnrs = function()
                            if current_cmp_source_frombuffer_mode == BufferMode.ALL then
                                -- 현재 열려있는 모든 버퍼 목록을 반환
                                return vim.api.nvim_list_bufs()
                            elseif current_cmp_source_frombuffer_mode == BufferMode.TABPAGE then
                                -- 현재 탭의 모든 윈도우에서 버퍼 ID 수집
                                local buffers = {}
                                for _, win in ipairs(vim.api.nvim_tabpage_list_wins(0)) do
                                    table.insert(buffers, vim.api.nvim_win_get_buf(win))
                                end
                                return buffers
                            elseif current_cmp_source_frombuffer_mode == BufferMode.CURRENT then
                                return {vim.api.nvim_get_current_buf()}
                            elseif current_cmp_source_frombuffer_mode == BufferMode.NONE then
                            else
                                return {}
                            end
                        end
                    }
                },
                { name = "path" },
                { name = "luasnip" },
                {
                    name = "lazydev", 
                    group_index = 0, -- set group index to 0 to skip loading LuaLS completions
                }
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
