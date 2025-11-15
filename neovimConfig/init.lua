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

-- Insert 모드에서 Ctrl + (h|j|k|l)가 노멀 모드에서 화살표 키와 동일하게 동작하도록 설정
vim.api.nvim_set_keymap('i', '<C-h>', '<Left>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-j>', '<Down>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-k>', '<Up>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-l>', '<Right>', {noremap = true, silent = true})

-- <C-b> (Backward)를 단어 단위 '뒤로' 이동으로 설정
-- <C-f> (Forward)를 단어 단위 '앞으로' 이동으로 설정
vim.api.nvim_set_keymap('i', '<C-b>', '<C-Left>', {noremap = true, silent = true})
vim.api.nvim_set_keymap('i', '<C-f>', '<C-Right>', {noremap = true, silent = true})

-- Insert/Normal/Visual 모드에서 Alt + j/k를 사용하여 라인을 아래/위로 이동시키기
vim.api.nvim_set_keymap('i', '<A-j>', '<Esc>:m .+1<CR>gi', { noremap = true, silent = true })
vim.api.nvim_set_keymap('i', '<A-k>', '<Esc>:m .-2<CR>gi', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '<A-j>', ':m .+1<CR>', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '<A-k>', ':m .-2<CR>', { noremap = true, silent = true })
vim.api.nvim_set_keymap('v', '<A-j>', ":m '>+1<CR>gv=gv", { noremap = true, silent = true })
vim.api.nvim_set_keymap('v', '<A-k>', ":m '<-2<CR>gv=gv", { noremap = true, silent = true })

-- Insert/Normal/Visual 모드에서 Leader + y/p 로 시스템 클립보드에 복사/붙여넣기
-- vim.api.nvim_set_keymap('i', '<A-c>', '<Esc>V"+ygi', { noremap = true, silent = true }) -- 라인 전체 복사
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

vim.api.nvim_set_keymap('n', '<leader>vw', ":lua ToggleTextWrap()<CR>", { noremap = true, silent = true }) 

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

    { import = "plugins" },

})

local is_windows = vim.loop.os_uname().sysname == "Windows_NT"
local is_macos = vim.fn.has("macunix") == 1

if is_windows then -- Windows 특정 설정
     require('windows-settings')
     print("windows Os Recognized...")
elseif is_macos then -- macOS 특정 설정
     require('macos-settings')
     print("mac OS Recognized...")
else
    print("any predefined os found...")
end

