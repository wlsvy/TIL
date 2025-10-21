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

        vim.keymap.set('', 'f', function()
            hop.hint_char1({ direction = directions.AFTER_CURSOR, current_line_only = true })
        end, {remap=true})
        vim.keymap.set('', 'F', function()
            hop.hint_char1({ direction = directions.BEFORE_CURSOR, current_line_only = true })
        end, {remap=true})
        vim.keymap.set('', 't', function()
            hop.hint_char1({ direction = directions.AFTER_CURSOR, current_line_only = true, hint_offset = -1 })
        end, {remap=true})
        vim.keymap.set('', 'T', function()
            hop.hint_char1({ direction = directions.BEFORE_CURSOR, current_line_only = true, hint_offset = 1 })
        end, {remap=true})

        vim.keymap.set('', '<leader><leader>l', function()
            hop.hint_lines_skip_whitespace({ multi_windows = true })
        end, {remap=true})
        vim.keymap.set('', '<leader><leader>w', function()
            hop.hint_words({ current_line_only = true, })
        end, {remap=true})
        vim.keymap.set('', '<leader><leader>W', function()
            hop.hint_words({ current_line_only = false, })
        end, {remap=true})

        vim.keymap.set('', '<leader><leader>p', function()
            hop.hint_patterns()
        end, {remap=true})

    end
}
