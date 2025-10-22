-- [GitHub - OXY2DEV/markview.nvim: A hackable markdown, Typst, latex, html(inline) & YAML previewer for Neovim](https://github.com/OXY2DEV/markview.nvim)
return {
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

                        icon = "I  ", hl = "MarkviewHeading1",
                    },
                    heading_2 = {
                        style = "icon",
                        sign = "󰌖 ", sign_hl = "MarkviewHeading2Sign",

                        icon = "II  ", hl = "MarkviewHeading2",
                    },
                    heading_3 = {
                        style = "icon",

                        icon = "III  ", hl = "MarkviewHeading3",
                    },
                    heading_4 = {
                        style = "icon",

                        icon = "IV  ", hl = "MarkviewHeading4",
                    },
                    heading_5 = {
                        style = "icon",

                        icon = "V  ", hl = "MarkviewHeading5",
                    },
                    heading_6 = {
                        style = "icon",

                        icon = "VI  ", hl = "MarkviewHeading6",
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
    end
}
