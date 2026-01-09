-- [nvim-lualinelualine.nvim A blazing fast and easy to configure neovim statusline plugin written in pure lua.](https://github.com/nvim-lualine/lualine.nvim)
return {
    'nvim-lualine/lualine.nvim',
    dependencies = { 'nvim-tree/nvim-web-devicons' },

    config = function()
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
                lualine_b = {'branch', 'diff', 'diagnostics'},
                lualine_c = {'filename'},
                lualine_x = {'encoding', 'fileformat', 'filetype'},
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
