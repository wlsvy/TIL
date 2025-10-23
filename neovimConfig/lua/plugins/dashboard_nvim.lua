-- [GitHub - nvimdevdashboard-nvim vim dashboard](https://github.com/nvimdev/dashboard-nvim)
return {
    'nvimdev/dashboard-nvim',
    event = 'VimEnter',
    config = function()
        require('dashboard').setup {

            theme = 'hyper',    -- theme is doom and hyper default is hyper
            config = { -- config used for theme
                week_header = { enable = true, },
                shortcut = {
                    {
                        desc = '󰊳 Update', group = '@property', action = 'Lazy update', key = 'u' 
                    },
                    {
                        icon = ' ',
                        icon_hl = '@variable',
                        desc = 'Files',
                        group = 'Label',
                        action = 'Telescope find_files',
                        key = 'f',
                    },
                    {
                        desc = ' Sessions',
                        group = 'DiagnosticHint',
                        action = 'lua require("nvim-possession").list()',
                        key = 's',
                    },
                },
                packages = { enable = true }, -- show how many plugins neovim loaded
                mru = {
                    enable = true,
                    limit = 10,
                    icon = '  ',
                    label = 'Recent',
                    cwd_only = false -- 현재 디렉터리가 아닌, nvim 전체의 최근 파일을 보여줌
                },
            },       
        }
    end,
    dependencies = { {'nvim-tree/nvim-web-devicons'}}
}
