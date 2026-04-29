-- [nvim-lualinelualine.nvim A blazing fast and easy to configure neovim statusline plugin written in pure lua.](https://github.com/nvim-lualine/lualine.nvim)
return {
    'nvim-lualine/lualine.nvim',
    dependencies = { 'nvim-tree/nvim-web-devicons' },

    config = function()

        local cwdGetter = function()
            return '🏠'..vim.fn.getcwd()
        end

        local relativePathGetter = function()
            local current_file = vim.fn.expand('%:p')
            if current_file == '' then
                return '📁'
            end

            -- CWD를 제외한 상대 경로 계산
            local relative_path = vim.fn.fnamemodify(current_file, ':~:.')
            -- 파일명만 있는 경우 (현재 디렉토리) 빈 문자열 반환
            if relative_path == vim.fn.expand('%:t') then
                return '📁'
            end

            -- 디렉토리 경로만 반환 (파일명 제외)
            local dir_path = vim.fn.fnamemodify(relative_path, ':h')
            return dir_path ~= '.' and '📁 ' .. dir_path or '📁 '
        end

        require('lualine').setup {
            options = {
                icons_enabled = true,
                theme = 'ayu_light',
                component_separators = { left = '', right = ''},
                section_separators = { left = '', right = ''},
                disabled_filetypes = {
                    statusline = {},
                    winbar = {},
                },
                ignore_focus = {},
                always_divide_middle = true,
                always_show_tabline = true,
                globalstatus = false,
                refresh = {
                    statusline = 1000,
                    tabline = 1000,
                    winbar = 1000,
                    refresh_time = 16, -- ~60fps
                    events = {
                        'WinEnter',
                        'BufEnter',
                        'BufWritePost',
                        'SessionLoadPost',
                        'FileChangedShellPost',
                        'VimResized',
                        'Filetype',
                        'CursorMoved',
                        'CursorMovedI',
                        'ModeChanged',
                    },
                }
            },

            --[[
            +-------------------------------------------------+
            | A | B | C                             X | Y | Z |
            +-------------------------------------------------+
            ]]
            sections = {
                lualine_a = {'mode'},
                lualine_b = {'filename', 'branch', },
                lualine_c = { relativePathGetter,   'diagnostics' },
                lualine_x = { cwdGetter, 'encoding', 'fileformat', 'filetype', 'diff', 'filesize', 'lsp_status' },
                lualine_y = {'progress'},
                lualine_z = {
                    'location',
                    function()
                        if not package.loaded["korean_ime"] then
                            return ""
                        end
                        local mode = require("korean_ime").get_mode()
                        if mode == "en" then
                            return "A "
                        elseif mode == "ko" then
                            return "한"
                        end
                    end,
                }
            },
            inactive_sections = {
                lualine_a = {},
                lualine_b = {},
                lualine_c = {'filename'},
                lualine_x = {'location'},
                lualine_y = {},
                lualine_z = {}
            },
            tabline = {},
            winbar = {},
            inactive_winbar = {},
            extensions = {}
        }
    end
}
