-- [GitHub - hadronized/hop.nvim: Neovim motions on speed!](https://github.com/hadronized/hop.nvim)
return {
    "hadronized/hop.nvim",
    config = function()
        -- you can configure Hop the way you like here; see :h hop-config
        local hop = require('hop')
        local directions = require('hop.hint').HintDirection

        hop.setup ({
            keys = 'etovxqpdygfblzhckisuran',
            case_insensitive = false,
            multi_windows = true,
        })

        vim.keymap.set('', '<leader>l', function()
            hop.hint_lines_skip_whitespace({ multi_windows = true })
        end, {remap=true})
        vim.keymap.set('', '<leader>w', function()
            hop.hint_words({ current_line_only = true, })
        end, {remap=true})
        vim.keymap.set('', '<leader>W', function()
            hop.hint_words({ current_line_only = false, })
        end, {remap=true})

        vim.keymap.set('', '<leader>p', function()
            hop.hint_patterns()
        end, {remap=true})

    end
}
