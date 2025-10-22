return  {
    {
        "nvim-telescope/telescope.nvim",
        requires = { { "nvim-lua/plenary.nvim" } },
    },
    {
        "nvim-telescope/telescope-file-browser.nvim",
        dependencies = { "nvim-telescope/telescope.nvim", "nvim-lua/plenary.nvim" }
    },

    config = function()
        -- To get telescope-file-browser loaded and working with telescope,
        -- you need to call load_extension, somewhere after setup function:
        require("telescope").load_extension "file_browser"
        vim.api.nvim_set_keymap('n', '<leader><Tab>', ':Telescope oldfiles<CR>', { noremap = true, silent = true })

        require('telescope').setup{
            defaults = {
                -- telescope 기본 설정 옵션들
                vimgrep_arguments = {
                    'rg',
                    '--color=never',
                    '--no-heading',
                    '--with-filename',
                    '--line-number',
                    '--column',
                    '--smart-case'
                },
                prompt_prefix = "🔍 ",
                selection_caret = " ",
                path_display = { "smart" },
                file_ignore_patterns = {"node_modules", ".git/"},
                layout_strategy = 'horizontal',
                layout_config = {
                    horizontal = {
                        preview_width = 0.5,
                    },
                },
            },
            pickers = {
                -- 기본 픽커 설정
                find_files = {
                },
                live_grep = {
                    theme = "ivy",
                    layout_strategy = 'horizontal',
                    layout_config = {
                        horizontal = {
                            preview_width = 0.5,
                        },
                    },
                },
            },
            extensions = {
                -- 추가 확장기능 설정
                file_browser = {
                    theme = "ivy",
                    -- disables netrw and use telescope-file-browser in its place
                    hijack_netrw = true,
                    mappings = {
                        ["i"] = {
                            -- your custom insert mode mappings
                        },
                        ["n"] = {
                            -- your custom normal mode mappings
                        },
                    },
                },
            }
        }

    end
}
