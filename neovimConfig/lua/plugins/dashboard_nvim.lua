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
                        desc = ' Apps',
                        group = 'DiagnosticHint',
                        action = 'Telescope app',
                        key = 'a',
                    },
                    {
                        desc = ' dotfiles',
                        group = 'Number',
                        action = 'Telescope dotfiles',
                        key = 'd',
                    },
                },
                packages = { enable = true }, -- show how many plugins neovim loaded
                project = { enable = true, limit = 8, icon = 'your icon', label = '', action = 'Telescope find_files cwd=' },
            },       
        }
    end,
    dependencies = { {'nvim-tree/nvim-web-devicons'}}
}
