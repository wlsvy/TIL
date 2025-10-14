-- init.lua

-- Basic settings
vim.o.number = true -- Enable line numbers
vim.o.relativenumber = true -- Enable relative line numbers
vim.o.tabstop = 4 -- Number of spaces a tab represents
vim.o.shiftwidth = 4 -- Number of spaces for each indentation
vim.o.expandtab = true -- Convert tabs to spaces
vim.o.smartindent = true -- Automatically indent new lines
vim.o.wrap = false -- Disable line wrapping
vim.o.cursorline = true -- Highlight the current line
vim.o.termguicolors = true -- Enable 24-bit RGB colors
vim.o.ignorecase = true
vim.o.smartcase = true -- 패턴에 대문자가 포함되어 있다면 대소문자 구분
vim.o.encoding = 'utf-8'
vim.o.incsearch = true
vim.o.hlsearch = true
vim.opt.guicursor = "n-v-c-sm:block,i-ci:ver30-iCursor-blinkwait300-blinkon200-blinkoff150,r-cr-o:hor20" 

-- Syntax highlighting and filetype plugins
vim.cmd("syntax enable")
vim.cmd("filetype plugin indent on")

-- Leader key
vim.g.mapleader = " " -- Space as the leader key


-- Normal 모드에서 커서 위치 기준으로 NewLine
vim.keymap.set("n", "<S-CR>", "a<CR><Esc>", { noremap = true, silent = true })

-- Insert 모드에서 Ctrl + (h|j|k|l)가 노멀 모드에서 화살표 키와 동일하게 동작하도록 설정
vim.api.nvim_set_keymap('i', '<C-h>', '<Left>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-j>', '<Down>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-k>', '<Up>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-l>', '<Right>', {noremap = true, silent = true})

-- insert 모드에서 Ctrl + w -> 단어 선택
vim.api.nvim_set_keymap('i', '<C-w>', '<ESC>viw', {noremap = true, silent = true})

-- Insert/Normal/Visual 모드에서 Alt + j/k를 사용하여 라인을 아래/위로 이동시키기
vim.api.nvim_set_keymap('i', '<A-j>', '<Esc>:m .+1<CR>gi', { noremap = true, silent = true })
vim.api.nvim_set_keymap('i', '<A-k>', '<Esc>:m .-2<CR>gi', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '<A-j>', ':m .+1<CR>', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '<A-k>', ':m .-2<CR>', { noremap = true, silent = true })
vim.api.nvim_set_keymap('v', '<A-j>', ":m '>+1<CR>gv=gv", { noremap = true, silent = true })
vim.api.nvim_set_keymap('v', '<A-k>', ":m '<-2<CR>gv=gv", { noremap = true, silent = true })

-- Insert/Normal/Visual 모드에서 Leader + y/p 로 시스템 클립보드에 복사/붙여넣기
-- vim.api.nvim_set_keymap('i', '<A-c>', '<Esc>V"+ygi', { noremap = true, silent = true }) -- 라인 전체 복사
vim.api.nvim_set_keymap('i', '<C-v>', '<Esc>"+pgi', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '<leader>y', '"+y', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '<leader>p', '"+p', { noremap = true, silent = true })
vim.api.nvim_set_keymap('v', '<leader>y', '"+y', { noremap = true, silent = true })
vim.api.nvim_set_keymap('v', '<leader>p', '"+p', { noremap = true, silent = true })

vim.api.nvim_set_keymap('n', '<A-Left>', '<C-w>h', { noremap = true, silent = true }) -- 창 탐색 (왼쪽)
vim.api.nvim_set_keymap('n', '<A-Right>', '<C-w>l', { noremap = true, silent = true }) -- 창 탐색 (오른쪽)
vim.api.nvim_set_keymap('n', '<A-Up>', '<C-w>k', { noremap = true, silent = true }) -- 창 탐색 (오른쪽)
vim.api.nvim_set_keymap('n', '<A-Down>', '<C-w>j', { noremap = true, silent = true }) -- 창 탐색 (오른쪽)

vim.api.nvim_set_keymap('n', '<C-Left>', ':vertical resize -3<CR>', { noremap = true, silent = true }) -- 창 탐색 (왼쪽)
vim.api.nvim_set_keymap('n', '<C-Right>', ':vertical resize +3<CR>', { noremap = true, silent = true }) -- 창 탐색 (오른쪽)
vim.api.nvim_set_keymap('n', '<C-Up>', ':horizontal resize +3<CR>', { noremap = true, silent = true }) -- 창 탐색 (오른쪽)
vim.api.nvim_set_keymap('n', '<C-Down>', ':horizontal resize -3<CR>', { noremap = true, silent = true }) -- 창 탐색 (오른쪽)

-- terminal
vim.api.nvim_set_keymap('t', '<ESC>', "<C-\\><C-n>", { noremap = true, silent = true }) 

-- text wrap toggle
function ToggleTextWrap() -- 텍스트 줄 바꿈 토글하는 함수 정의
    vim.o.wrap = not vim.o.wrap
    if vim.o.wrap then
        -- wrap이 켜졌을 때 'j', 'k'를 'gj', 'gk'로 매핑
        vim.api.nvim_set_keymap('n', 'j', 'gj', { noremap = true, silent = true })
        vim.api.nvim_set_keymap('n', 'k', 'gk', { noremap = true, silent = true })
        print("Text wrap enabled. Mapped 'j' to 'gj' and 'k' to 'gk'")
    else
        -- wrap이 꺼졌을 때 기본 'j', 'k'로 복원
        vim.api.nvim_set_keymap('n', 'j', 'j', { noremap = true, silent = true })
        vim.api.nvim_set_keymap('n', 'k', 'k', { noremap = true, silent = true })
        print("Text wrap disabled. Restored default 'j' and 'k'")
    end
end

-- Markdown 파일에서만 적용되는 하이라이트 설정
vim.api.nvim_create_autocmd("FileType", {
  pattern = "markdown",
  callback = function()
    -- **로 감싸진 텍스트를 하이라이트
    vim.cmd [[
      syntax match markdownBold /\*\*.\{-}\*\*/
      highlight markdownBold cterm=bold gui=bold guifg=purple
    ]]
  end
})

vim.api.nvim_create_user_command( -- 명령어 등록
    'ToggleTextWrap',
    'lua ToggleTextWrap()',
    { nargs = 0 }
)
-- 'lazy.nvim' 설치 및 경로 설정
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
    vim.fn.system({
        "clone",
        "--filter=blob:none",
        "https://github.com/folke/lazy.nvim.git",
        "--branch=stable", -- latest stable release
        lazypath,
    })
end
vim.opt.rtp:prepend(lazypath)

-- 플러그인 설정
require("lazy").setup({
    -- Treesitter
    {
        "nvim-treesitter/nvim-treesitter",
        run = ":TSUpdate",
    },
    -- Telescope
    {
        "nvim-telescope/telescope.nvim",
        requires = { { "nvim-lua/plenary.nvim" } },
    },
    {
        "nvim-telescope/telescope-file-browser.nvim",
        dependencies = { "nvim-telescope/telescope.nvim", "nvim-lua/plenary.nvim" }
    },
    { "folke/which-key.nvim", requires = {{"which-key"}}, },
    { "akinsho/toggleterm.nvim", },
    { "img-paste-devs/img-paste.vim" }, -- paste image in clipboard

    { import = "plugins" },

    -- 일부 폰트는 플러그인에서 활용하는 아이콘들을 지원하지 않아서 '?' 물음표 박스가 뜨는 경우가 있음. chatGPT 한테 물어보니까 NerdFont 쓰라고 해서 그거 쓰니까 해결되더라 
    { "preservim/nerdtree", }, -- [preservim/nerdtree: A tree explorer plugin for vim.](https://github.com/preservim/nerdtree)
    {"ryanoasis/vim-devicons", requires = "preservim/nerdtree"}, -- [ryanoasis/vim-devicons: Adds file type icons to Vim plugins such as: NERDTree, vim-airline, CtrlP, unite, Denite, lightline, vim-startify and many more](https://github.com/ryanoasis/vim-devicons) 
    {"nvim-mini/mini.icons"}, -- [GitHub - nvim-mini/mini.icons: Icon provider. Part of 'mini.nvim' library.](https://github.com/nvim-mini/mini.icons)
    { "nvim-tree/nvim-web-devicons", opts = {} }, -- [GitHub - nvim-tree/nvim-web-devicons: Provides Nerd Font icons (glyphs) for use by neovim plugins](https://github.com/nvim-tree/nvim-web-devicons)

    -- [williamboman/mason-lspconfig.nvim: Extension to mason.nvim that makes it easier to use lspconfig with mason.nvim.](https://github.com/williamboman/mason-lspconfig.nvim)
    {
        "williamboman/mason.nvim",
        "williamboman/mason-lspconfig.nvim",
        "neovim/nvim-lspconfig",
    },

    {
        "hrsh7th/nvim-cmp",
        dependencies = {
            "hrsh7th/cmp-nvim-lsp", -- LSP를 자동완성 소스로 사용
            "hrsh7th/cmp-buffer",   -- 현재 버퍼의 텍스트를 소스로 사용
            "hrsh7th/cmp-path",     -- 파일 경로를 소스로 사용
        },
        config = function()
            local cmp = require("cmp")
            cmp.setup({
                -- ... (스니펫, UI 설정 등) ...
                sources = cmp.config.sources({
                    { name = "nvim_lsp" }, -- LSP 소스 등록
                    { name = "buffer" },
                    { name = "path" },
                }),
            })
        end,
    },

    -- [junegunn/fzf: :cherry_blossom: A command-line fuzzy finder](https://github.com/junegunn/fzf)
    { "junegunn/fzf", },
    { "junegunn/fzf.vim", },

    { "godlygeek/tabular" },

    -- [easymotion/vim-easymotion: Vim motions on speed!](https://github.com/easymotion/vim-easymotion)
    { "easymotion/vim-easymotion"},

    -- [atiladefreitaslazyclip The laziest clipboard manager for Neovim](https://github.com/atiladefreitas/lazyclip)
    { "atiladefreitas/lazyclip",
    config = function()
        require("lazyclip").setup({
            -- your custom config here (optional)
        })
    end,
    keys = {
        { "Cw", desc = "Open Clipboard Manager" },
    },
    -- Optional: Load plugin when yanking text
    event = { "TextYankPost" },
},

-- [echasnovskimini.icons Icon provider. Part of 'mini.nvim' library.](https://github.com/echasnovski/mini.icons)
{ 'echasnovski/mini.nvim', version = '*' },

-- [rcarriganvim-notify A fancy, configurable, notification manager for NeoVim](https://github.com/rcarriga/nvim-notify)
{ 'rcarriga/nvim-notify'},

-- [folkenoice.nvim 💥 Highly experimental plugin that completely replaces the UI for messages, cmdline and the popupmenu.](https://github.com/folke/noice.nvim)
{
    "folke/noice.nvim",
    event = "VeryLazy",
    opts = {
        -- add any options here
    },
    dependencies = {
        -- if you lazy-load any plugin below, make sure to add proper `module="..."` entries
        "MunifTanjim/nui.nvim",
        -- OPTIONAL:
        --   `nvim-notify` is only needed, if you want to use the notification view.
        --   If not available, we use `mini` as the fallback
        "rcarriga/nvim-notify",
    },
},

-- [jesseleitenvim-macroni 🤌 Save your macros for future use](https://github.com/jesseleite/nvim-macroni)
{
    'jesseleite/nvim-macroni',
    opts = {
        -- All of your `setup(opts)` and saved macros will go here
    },
},

-- [nvim-lualinelualine.nvim A blazing fast and easy to configure neovim statusline plugin written in pure lua.](https://github.com/nvim-lualine/lualine.nvim)
{
    'nvim-lualine/lualine.nvim',
    dependencies = { 'nvim-tree/nvim-web-devicons' },
},

-- [GitHub - lukas-reinekeindent-blankline.nvim Indent guides for Neovim](https://github.com/lukas-reineke/indent-blankline.nvim)
{
    "lukas-reineke/indent-blankline.nvim",
    main = "ibl",
    ---@module "ibl"
    ---@type ibl.config
    opts = {},
},

-- [GitHub - RRethyvim-illuminate illuminate.vim - (Neo)Vim plugin for automatically highlighting other uses of the word under the cursor using either LSP, Tree-sitter, or regex matching.](https://github.com/RRethy/vim-illuminate)
{
    "RRethy/vim-illuminate",
    config = function()
        require("illuminate").configure({
            delay = 100, -- 하이라이트 적용 시간 (ms)
            under_cursor = true, -- 커서 아래 단어 강조
            filetypes_denylist = { "NvimTree", "TelescopePrompt" } -- 특정 파일 타입 제외
        })
    end
},

-- [snacks.nvim/docs/image.md at main · folke/snacks.nvim](https://github.com/folke/snacks.nvim/blob/main/docs/image.md)
{
    "folke/snacks.nvim",
    ---@type snacks.Config
    opts = {
        -- your configuration comes here
        -- or leave it empty to use the default settings
        -- refer to the configuration section below
        bigfile = { enabled = true },
        dashboard = { 
            enabled = true, 
            sections = {
                { section = "header" },
                { icon = " ", title = "Keymaps", section = "keys", indent = 2, padding = 1 },
                { icon = " ", title = "Recent Files", section = "recent_files", indent = 2, padding = 1 },
                { icon = " ", title = "Projects", section = "projects", indent = 2, padding = 1 },
                { section = "startup" },
            },
        },
        explorer = { enabled = true },
        indent = { enabled = true },
        input = { enabled = true },
        picker = { enabled = true },
        notifier = { enabled = true },
        quickfile = { enabled = true },
        scope = { enabled = true },
        scroll = { enabled = true },
        statuscolumn = { enabled = true },
        words = { enabled = true },
        lazygit = { },
        image = {
            doc = {
                -- enable image viewer for documents
                -- a treesitter parser must be available for the enabled languages.
                enabled = true,
                -- render the image inline in the buffer
                -- if your env doesn't support unicode placeholders, this will be disabled
                -- takes precedence over `opts.float` on supported terminals
                inline = true,
                -- render the image in a floating window
                -- only used if `opts.inline` is disabled
                float = true,
                max_width = 80,
                max_height = 40,
                backend = 'iterm',
                -- Set to `true`, to conceal the image text when rendering inline.
                -- (experimental)
                ---@param lang string tree-sitter language
                ---@param type snacks.image.Type image type
                conceal = function(lang, type)
                    -- only conceal math expressions
                    return type == "math"
                end,
            },
        },
    },
    priority=1000,
},

-- [GitHub - OXY2DEV/markview.nvim: A hackable markdown, Typst, latex, html(inline) & YAML previewer for Neovim](https://github.com/OXY2DEV/markview.nvim)
{
    "OXY2DEV/markview.nvim",
    lazy = false,

    -- For `nvim-treesitter` users.
    priority = 49,

    config = function()
        require("markview").setup({
            preview = {
                icon_provider = "internal", -- "mini" or "devicons"
            },
            markdown = {
                -- [Markdown · OXY2DEV/markview.nvim Wiki · GitHub](https://github.com/OXY2DEV/markview.nvim/wiki/Markdown)
                enable = true,
                block_quotes = {
                    enable = true,
                    wrap = true,

                    default = {
                        border = "▋",
                        hl = "MarkviewBlockQuoteDefault"
                    },

                    ["ABSTRACT"] = {
                        preview = "󱉫 Abstract",
                        hl = "MarkviewBlockQuoteNote",

                        title = true,
                        icon = "󱉫",

                    },
                    ["SUMMARY"] = {
                        hl = "MarkviewBlockQuoteNote",
                        preview = "󱉫 Summary",

                        title = true,
                        icon = "󱉫",
                    },
                },
                code_blocks = {
                    enable = true,

                    style = "block",

                    label_direction = "right",

                    border_hl = "MarkviewCode",
                    info_hl = "MarkviewCodeInfo",

                    min_width = 60,
                    pad_amount = 2,
                    pad_char = " ",

                    sign = true,

                    default = {
                        block_hl = "MarkviewCode",
                        pad_hl = "MarkviewCode"
                    },

                    ["diff"] = {
                        block_hl = function (_, line)
                            if line:match("^%+") then
                                return "MarkviewPalette4";
                            elseif line:match("^%-") then
                                return "MarkviewPalette1";
                            else
                                return "MarkviewCode";
                            end
                        end,
                        pad_hl = "MarkviewCode"
                    }
                },

                headings = {
                    enable = true,

                    heading_1 = {
                        style = "icon",
                        sign = "󰌕 ", sign_hl = "MarkviewHeading1Sign",

                        icon = "󰼏  ", hl = "MarkviewHeading1",
                    },
                    heading_2 = {
                        style = "icon",
                        sign = "󰌖 ", sign_hl = "MarkviewHeading2Sign",

                        icon = "󰎨  ", hl = "MarkviewHeading2",
                    },
                    heading_3 = {
                        style = "icon",

                        icon = "󰼑  ", hl = "MarkviewHeading3",
                    },
                    heading_4 = {
                        style = "icon",

                        icon = "󰎲  ", hl = "MarkviewHeading4",
                    },
                    heading_5 = {
                        style = "icon",

                        icon = "󰼓  ", hl = "MarkviewHeading5",
                    },
                    heading_6 = {
                        style = "icon",

                        icon = "󰎴  ", hl = "MarkviewHeading6",
                    },

                    setext_1 = {
                        style = "decorated",

                        sign = "󰌕 ", sign_hl = "MarkviewHeading1Sign",
                        icon = "  ", hl = "MarkviewHeading1",
                        border = "▂"
                    },
                    setext_2 = {
                        style = "decorated",

                        sign = "󰌖 ", sign_hl = "MarkviewHeading2Sign",
                        icon = "  ", hl = "MarkviewHeading2",
                        border = "▁"
                    },

                    shift_width = 1,

                    org_indent = false,
                    org_indent_wrap = true,
                    org_shift_char = " ",
                    org_shift_width = 1,
                },

                tables = {
                    enable = false,
                    strict = true,

                    col_min_width = 10,
                    block_decorator = true,
                    use_virt_lines = false,

                    parts = {
                        top = { "╭", "─", "╮", "┬" },
                        header = { "│", "│", "│" },
                        separator = { "├", "─", "┤", "┼" },
                        row = { "│", "│", "│" },
                        bottom = { "╰", "─", "╯", "┴" },

                        overlap = { "┝", "━", "┥", "┿" },

                        align_left = "╼",
                        align_right = "╾",
                        align_center = { "╴", "╶" }
                    },

                    hl = {
                        top = { "TableHeader", "TableHeader", "TableHeader", "TableHeader" },
                        header = { "TableHeader", "TableHeader", "TableHeader" },
                        separator = { "TableHeader", "TableHeader", "TableHeader", "TableHeader" },
                        row = { "TableBorder", "TableBorder", "TableBorder" },
                        bottom = { "TableBorder", "TableBorder", "TableBorder", "TableBorder" },

                        overlap = { "TableBorder", "TableBorder", "TableBorder", "TableBorder" },

                        align_left = "TableAlignLeft",
                        align_right = "TableAlignRight",
                        align_center = { "TableAlignCenter", "TableAlignCenter" }
                    }
                },
            },

        })
    end
},

-- [GitHub - neo451/feed.nvim: Neovim feed reader, rss, atom and jsonfeed, all in lua](https://github.com/neo451/feed.nvim)
{
    "neo451/feed.nvim",
    dependencies = { "OXY2DEV/markview.nvim", "nvim-lua/plenary.nvim" },
    cmd = "Feed",
    ---@module 'feed'
    ---@type feed.config
    opts = {},
},


})

-- 현재 init.lua의 디렉토리 위치를 가져오는 방법
local function get_current_directory()
  local str = debug.getinfo(1, "S").source:sub(2)
  
  -- 운영체제에 따른 경로 구분 처리
  if vim.loop.os_uname().sysname == "Windows_NT" then
    return str:match("(.*\\)")  -- Windows에서는 백슬래시(\) 사용
  else
    return str:match("(.*/)")   -- Unix 계열에서는 슬래시(/) 사용
  end
end

local current_directory = get_current_directory()
local is_windows = vim.loop.os_uname().sysname == "Windows_NT"
local is_macos = vim.fn.has("macunix") == 1

-- 결과 확인용 출력 (디버깅에 사용 가능)
-- print("init.lua Directory: " .. current_directory)

if is_windows then -- Windows 특정 설정
     require('windows-settings')
     print("windows Os Recognized...")
elseif is_macos then -- macOS 특정 설정
     require('macos-settings')
     print("mac OS Recognized...")
else
    print("any predefined os found...")
end

-- 기본 설정 및 확장 기능 로드
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

-- To get telescope-file-browser loaded and working with telescope,
-- you need to call load_extension, somewhere after setup function:
require("telescope").load_extension "file_browser"

-- 키맵핑 설정
local builtin = require('telescope.builtin')
local opts = { noremap = true, silent = true }

-- telescope & snacks
vim.api.nvim_set_keymap('n', '<leader>;', ':lua Snacks.explorer()<CR>', opts) -- 파일 찾기 
vim.api.nvim_set_keymap('n', '<C-p>', ':lua Snacks.picker.pickers()<CR>', opts) -- Snacks.picker 리스트
vim.api.nvim_set_keymap('n', '<C-f>', ':lua Snacks.picker.lines()<CR>', opts) -- 버퍼 목록 보기 
vim.api.nvim_set_keymap('n', '<leader>b', ':lua Snacks.picker.grep_buffers()<CR>', opts) -- 현재 파일 텍스트 검색 
vim.api.nvim_set_keymap('n', '<leader>q', ':lua Snacks.picker.autocmds()<CR>', opts) -- 명령어 탐색 키맵핑
vim.api.nvim_set_keymap('n', '<leader>Q', ':lua Snacks.picker.command_history()<CR>', opts) -- 명령어 히스토리
vim.api.nvim_set_keymap('n', '<leader>t', ':lua Snacks.picker.files()<CR>', { noremap = true, silent = true }) -- find_files
vim.api.nvim_set_keymap('n', '<leader>T', ':lua Snacks.picker.treesitter()<CR>', opts) -- treesitter
vim.api.nvim_set_keymap('n', '<leader>g', ':lua Snacks.picker.grep()<CR>', opts) -- grep / text 검색
vim.api.nvim_set_keymap('n', '<leader>G', ':lua Snacks.picker.grep_word()<CR>', opts) -- grep_word / 정확한 단어 검색
vim.api.nvim_set_keymap('n', '<leader><Tab>', ':Telescope oldfiles<CR>', opts) -- 최근 파일

--mason
require("mason").setup()

local on_attach = function(client, bufnr)
  -- 아래 키맵들은 이 파일에 연결된 LSP 서버가 지원하는 경우에만 작동합니다.
  local opts = { buffer = bufnr, noremap = true, silent = true }

  -- 리팩토링 및 주요 기능 키맵
  vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
  vim.keymap.set('n', 'K', vim.lsp.buf.hover, opts)
  vim.keymap.set('n', 'gi', vim.lsp.buf.implementation, opts)
  vim.keymap.set('n', 'gr', vim.lsp.buf.references, opts)
  vim.keymap.set('n', 'rn', vim.lsp.buf.rename, opts)
  vim.keymap.set('n', '<leader>ca', vim.lsp.buf.code_action, opts)
  vim.keymap.set('n', '<leader>f', function() vim.lsp.buf.format { async = true } end, opts)

  -- 진단(오류) 관련 키맵
  vim.keymap.set('n', '[d', vim.diagnostic.goto_prev, opts)
  vim.keymap.set('n', ']d', vim.diagnostic.goto_next, opts)
end

-- 각 LSP 서버를 설정할 때 on_attach 함수를 연결해줍니다-- .
-- require('lspconfig').omnisharp.setup({
--   on_attach = on_attach,
--   -- ... other settings
-- })

require('lspconfig').pyright.setup({
  on_attach = on_attach,
  -- ... other settings
})

-- 자동 완성 트리거
vim.api.nvim_set_keymap('i', '<Tab>', 'pumvisible() ? "\\<C-n>" : "\\<Tab>"', { noremap = true, expr = true })
vim.api.nvim_set_keymap('i', '<S-Tab>', 'pumvisible() ? "\\<C-p>" : "\\<S-Tab>"', { noremap = true, expr = true })

-- [jesseleitenvim-macroni 🤌 Save your macros for future use](https://github.com/jesseleite/nvim-macroni)
vim.keymap.set({'n', 'v'}, '<Leader>m', function ()
  require('telescope').extensions.macroni.saved_macros()
end)

_G.gemini_prompt_preset_default = [[

** 전체적으로 표현 방식은**

* 표로 정리 가능하면 표 사용 (빠르게 살펴보기 위해)
* 적당한 이모지 많이 넣어줘
* 개조식 문장을 사용해줘. 읽기 쉽게 ]]

_G.gemini_prompt_preset_youtube = [[

내용 정리해줘.
** 전체적으로 표현 방식은**

* 표로 정리 가능하면 표 사용 (빠르게 살펴보기 위해)
* 적당한 이모지 많이 넣어줘
* 개조식 문장을 사용해줘. 읽기 쉽게

**아래 순서로 대답해줘**

1. 제작자의 의도와 주요 부분을 쭉 나열해주고,
2. 내용을 뒷받침하는 사례가 있다면 중요하지 않아도 괜찮으니 가급적 나열
3. 주요 구간의 실제 자막 텍스트 출력 - 맞춤법 틀려도 괜찮고 원문 그대로, 이때 한 구간마다 최소 4~5 문장 분량으로 

---

위 과정을 영어로 진행해주고, 그 다음에 한글로 번역. 필요해보인다면 영어로 자료 조사진행할 것.]]

function append_text_to_clipboard_for_aiprompt(text)

  local prevClipboard = vim.fn.getreg('+')
  local newText = prevClipboard .. text
  vim.fn.setreg('+', newText)
  
  vim.notify("✅ 클립보드가 수정되었습니다.".."\n"..newText)
end

require('macroni').setup {
    macros = {
      make_todo_list_item = {
        macro = '^i-<Space>[<Space>]<Space>',
        mode = { 'n', 'v' }, -- By default, macros will be mapped to both normal & visual modes
        desc = '^i-<Space>[<Space>]<Space>',
      },

      tabularize_markdown_table = {
        macro = ":'<,'>Tabularize /|<CR>",
        mode = {'v'},
        desc = ":'<,'>Tabularize /|<CR>",
      },

      check_health = {
        macro = ":checkhealth<CR>",
        mode = { 'n'},
        desc = ":checkhealth<CR>",
      },

      toggle_text_wrap = {
        macro = ":ToggleTextWrap<CR>",
        mode = {'n', 'v'},
        desc = ":ToggleTextWrap<CR>",
      },

      reset_markdown_numbered_list_rank = {
        macro = ":\'<,\'>s/^1/\\=line(\'.\') + 1 - line(\"\'<\")/g<CR>",
        mode = {'n', 'v'},
        desc = ":\'<,\'>s/^1/\\=line(\'.\') + 1 - line(\"\'<\")/g<CR>",
      },

      copy_current_file_path_to_clipboard = {
        macro = ":let @+ = expand(\'%\')<CR>",
        mode = {'n', 'v'},
        desc = ":let @+ = expand(\'%\')<CR>",
      },

      write_date_with_markdown_caption = {
        macro = ":execute \"normal i\" . strftime(\"## %y.%m.%d\")<CR>",
        mode = {'n'},
        desc = ":execute \"normal i\" . strftime(\"## %y.%m.%d\")<CR>",
      },

      copy_multiline_with_any_keyword = {
          macro = ":g/keyword1\\|keyword2/normal Vj\"Ay<CR>",
          mode = {'n'},
          desc = ":g/keyword1\\|keyword2/normal Vj\"Ay<CR>",
      },

      flush_register_at_abcde = {
          macro = ":let @a='' | let @b = '' | let @c = ''| let @d = ''| let @e = ''<CR>",
          mode = {'n'},
          desc = ":let @a='' | let @b = '' | let @c = ''| let @d = ''| let @e = ''<CR>",
      },

      gemini_prompt_preset_00 = {
          macro = ":lua append_text_to_clipboard_for_aiprompt(_G.gemini_prompt_preset_default)<CR>",
          mode = {'n'},
          desc = "표로 정리할 수 있으면 표 사용해줘, 적당한 이모지 많이 넣어줘. 표현은 개조식 문장으로. ",
      },

      gemini_prompt_preset_00_youtube = {
          macro = ":lua append_text_to_clipboard_for_aiprompt(_G.gemini_prompt_preset_youtube)<CR>",
          mode = {'n'},
          desc = "표로 정리할 수 있으면 표 사용해줘, 적당한 이모지 많이 넣어줘, 표현은 개조식 문장으로, \\n 대답할 때에는 1. 제작자의 의도와 주요 부분을 쭉 나열, 2. 내용을 뒷받침하는 사례 예시가 있다면 중요도에 관계없이 나열. 3. 주요 구간의 실제 자막 텍스트 출력- 맞춤법 틀려도 괜찮으니 원문 그대로.",
      },

      vim_messages = {
          macro = ":messages",
          mode = {'n'},
          desc = ":messages"
      },

      -- 무명레지스터에 등록 후 붙여넣는 방식
      add_line_summarized_by_gemini = {
          macro = ":let @@ = '**Summarized By Gemini**'<CR>p",
          mode = {'n'},
          desc = ":let @@ = '**Summarized By Gemini**'<CR>p"
      },
    },
  }

-- Set the image directory and image name (if you want to change the defaults)
vim.g.mdip_imgdir = 'img'
vim.g.mdip_imgname = 'image'

-- Define the :mdip command to call the MarkdownClipboardImage function
vim.api.nvim_create_user_command('Mdip', function()
    vim.cmd('call mdip#MarkdownClipboardImage()')
end, {})

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
  sections = {
    lualine_a = {'mode'},
    lualine_b = {'branch', 'diff', 'diagnostics'},
    lualine_c = {'filename'},
    lualine_x = {'encoding', 'fileformat', 'filetype'},
    lualine_y = {'progress'},
    lualine_z = {'location'}
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

local highlight = {
    "RainbowRed",
    "RainbowYellow",
    "RainbowBlue",
    "RainbowOrange",
    "RainbowGreen",
    "RainbowViolet",
    "RainbowCyan",
}

local hooks = require "ibl.hooks"
-- create the highlight groups in the highlight setup hook, so they are reset
-- every time the colorscheme changes
hooks.register(hooks.type.HIGHLIGHT_SETUP, function()
    vim.api.nvim_set_hl(0, "RainbowRed", { fg = "#E06C75" })
    vim.api.nvim_set_hl(0, "RainbowYellow", { fg = "#E5C07B" })
    vim.api.nvim_set_hl(0, "RainbowBlue", { fg = "#61AFEF" })
    vim.api.nvim_set_hl(0, "RainbowOrange", { fg = "#D19A66" })
    vim.api.nvim_set_hl(0, "RainbowGreen", { fg = "#98C379" })
    vim.api.nvim_set_hl(0, "RainbowViolet", { fg = "#C678DD" })
    vim.api.nvim_set_hl(0, "RainbowCyan", { fg = "#56B6C2" })
end)

require("ibl").setup { 
    indent = { highlight = highlight },
    scope = { enabled = false },
}

vim.cmd.colorscheme("catppuccin")
vim.o.background = "light"
