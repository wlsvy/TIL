return  {
    {
        "nvim-telescope/telescope.nvim",
        requires = { { "nvim-lua/plenary.nvim" } },
        dependencies = {"scottmckendry/pick-resession.nvim"},

        config = function()

            local builtin = require('telescope.builtin')

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
                    resession = {
                        prompt_title = "Find Sessions", -- telescope prompt title
                        dir = "session", -- directory where resession stores sessions
                        layout = nil -- telescope picker layout, defaults to dropdown if not set
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
            vim.api.nvim_set_keymap('n', '<leader>fr', '<cmd>Telescope registers<CR>', { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fd', '<cmd>Telescope diagnostics<CR>', { noremap = true, silent = true })

            -- [kickstart.nvim/init.lua at master · nvim-lua/kickstart.nvim](https://github.com/nvim-lua/kickstart.nvim/blob/master/init.lua)
            -- This runs on LSP attach per buffer (see main LSP attach function in 'neovim/nvim-lspconfig' config for more info,
            -- it is better explained there). This allows easily switching between pickers if you prefer using something else!
            vim.api.nvim_create_autocmd('LspAttach', {
                group = vim.api.nvim_create_augroup('telescope-lsp-attach', { clear = true }),
                callback = function(event)
                    local buf = event.buf

                    -- Find references for the word under your cursor.
                    vim.keymap.set('n', 'grr', builtin.lsp_references, { buffer = buf, desc = '[G]oto [R]eferences' })

                    -- Jump to the implementation of the word under your cursor.
                    -- Useful when your language has ways of declaring types without an actual implementation.
                    vim.keymap.set('n', 'gri', builtin.lsp_implementations, { buffer = buf, desc = '[G]oto [I]mplementation' })

                    -- Jump to the definition of the word under your cursor.
                    -- This is where a variable was first declared, or where a function is defined, etc.
                    -- To jump back, press <C-t>.
                    vim.keymap.set('n', 'grd', builtin.lsp_definitions, { buffer = buf, desc = '[G]oto [D]efinition' })

                    -- Fuzzy find all the symbols in your current document.
                    -- Symbols are things like variables, functions, types, etc.
                    vim.keymap.set('n', 'gO', builtin.lsp_document_symbols, { buffer = buf, desc = 'Open Document Symbols' })

                    -- Fuzzy find all the symbols in your current workspace.
                    -- Similar to document symbols, except searches over your entire project.
                    vim.keymap.set('n', 'gW', builtin.lsp_dynamic_workspace_symbols, { buffer = buf, desc = 'Open Workspace Symbols' })

                    -- Jump to the type of the word under your cursor.
                    -- Useful when you're not sure what type a variable is and you want to see
                    -- the definition of its *type*, not where it was *defined*.
                    vim.keymap.set('n', 'grt', builtin.lsp_type_definitions, { buffer = buf, desc = '[G]oto [T]ype Definition' })
                end,
            })
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
        -- [LukasPietzschmann/telescope-tabs: Fly through your tabs in NeoVim ✈️](https://github.com/LukasPietzschmann/telescope-tabs)
        'LukasPietzschmann/telescope-tabs',
        dependencies = { "nvim-telescope/telescope.nvim" },

        config = function()
            vim.api.nvim_set_keymap('n', '<leader>ft', "<cmd>lua require('telescope-tabs').list_tabs()<CR>", { noremap = true, silent = true })
            vim.api.nvim_set_keymap('n', '<leader>fT', "<cmd>lua require('telescope-tabs').go_to_previous()<CR>", { noremap = true, silent = true })
        end
    },
    {
        "jvgrootveld/telescope-zoxide",
        dependencies = { "nvim-telescope/telescope.nvim", "nvim-lua/plenary.nvim", "nvim-lua/popup.nvim" },

        config = function()

            vim.api.nvim_set_keymap('n', '<leader>fz', '<cmd>Telescope zoxide list<CR>', { noremap = true, silent = true })

            -- Useful for easily creating commands
            local z_utils = require("telescope._extensions.zoxide.utils")
            local builtin = require("telescope.builtin")

            require('telescope').setup{
                -- (other Telescope configuration...)
                extensions = {
                    zoxide = {
                        prompt_title = "[ Zoxide List ]",
                        list_command = "zoxide query -ls",
                        mappings = {
                            default = {
                                action = function(selection)
                                    vim.cmd.cd(selection.path)
                                end,
                                after_action = function(selection)
                                    vim.notify("Directory changed to " .. selection.path)
                                end,
                            },
                            ["<C-s>"] = { action = z_utils.create_basic_command("split") },
                            ["<C-v>"] = { action = z_utils.create_basic_command("vsplit") },
                            ["<C-e>"] = { action = z_utils.create_basic_command("edit") },
                            ["<C-f>"] = {
                                keepinsert = true,
                                action = function(selection)
                                    builtin.find_files({ cwd = selection.path })
                                end,
                            },
                            ["<C-t>"] = {
                                action = function(selection)
                                    vim.cmd.tcd(selection.path)
                                end,
                            },
                        }
                    }
                }
            }
        end
    }
}
