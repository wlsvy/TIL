return  {
    {
        "nvim-telescope/telescope.nvim",
        requires = { { "nvim-lua/plenary.nvim" } },

        config = function()

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
                        mappings = {
                            ["i"] = {
                                ["<C-s>"] = "select_vertical"
                            },
                            ["n"] = {
                                ["<C-s>"] = "select_vertical"
                            },
                        },
                    },
                    buffers = {
                        mappings = {
                            ["i"] = {
                                ["<C-s>"] = "select_vertical",
                                ["<C-q>"] = "delete_buffer",
                            },
                            ["n"] = {
                                ["<C-s>"] = "select_vertical",
                                ["<C-q>"] = "delete_buffer",
                            },
                        },
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
                    },
                }
            }

            vim.api.nvim_set_keymap('n', '<leader>ff', '<cmd>Telescope find_files<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fb', '<cmd>Telescope buffers<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fn', '<cmd>Telescope notify<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fc', '<cmd>Telescope command_history<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fm', '<cmd>Telescope marks<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fj', '<cmd>Telescope jumplist<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fh', '<cmd>Telescope help_tags<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader><Tab>', '<cmd>Telescope oldfiles<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fk', '<cmd>Telescope keymaps<CR>', { noremap = true, silent = true })

        end
    },
    {
        "nvim-telescope/telescope-file-browser.nvim",
        dependencies = { "nvim-telescope/telescope.nvim", "nvim-lua/plenary.nvim" },

        config = function()

            -- To get telescope-file-browser loaded and working with telescope,
            -- you need to call load_extension, somewhere after setup function:
            require("telescope").load_extension "file_browser"
        end
    },
    {
        'LukasPietzschmann/telescope-tabs',
        dependencies = { "nvim-telescope/telescope.nvim" },

        config = function()
            vim.api.nvim_set_keymap('n', '<leader>ft', "<cmd>lua require('telescope-tabs').list_tabs()<CR>", { noremap = true, silent = true })
        end
    }
}
