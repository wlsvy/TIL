-- [GitHub - RRethyvim-illuminate illuminate.vim - (Neo)Vim plugin for automatically highlighting other uses of the word under the cursor using either LSP, Tree-sitter, or regex matching.](https://github.com/RRethy/vim-illuminate)
return {
    "RRethy/vim-illuminate",
    config = function()
        require("illuminate").configure({
            delay = 100, -- 하이라이트 적용 시간 (ms)
            under_cursor = true, -- 커서 아래 단어 강조
            filetypes_denylist = { "NvimTree", "TelescopePrompt" } -- 특정 파일 타입 제외
        })
    end
}
