-- colorschemes

return {
    {
        "catppuccin/nvim", name = "catppuccin", priority = 1000 ,
        config = function()

            require("catppuccin").setup({
                flavour = "auto", -- latte, frappe, macchiato, mocha
                background = { -- :h background
                    light = "latte",
                    dark = "mocha",
                },
                transparent_background = false, -- disables setting the background color.
                show_end_of_buffer = true, -- shows the '~' characters after the end of buffers
                term_colors = false, -- sets terminal colors (e.g. `g:terminal_color_0`)
                dim_inactive = {
                    enabled = true, -- dims the background color of inactive window
                    shade = "dark",
                    percentage = 0.15, -- percentage of the shade to apply to the inactive window
                },
                no_italic = false, -- Force no italic
                no_bold = false, -- Force no bold
                no_underline = false, -- Force no underline
                styles = { -- Handles the styles of general hi groups (see `:h highlight-args`):
                    comments = { "italic" }, -- Change the style of comments
                    conditionals = { "italic" },
                    loops = {},
                    functions = {"italic"},
                    keywords = {"bold"},
                    strings = {"italic"},
                    variables = {},
                    numbers = {"italic"},
                    booleans = {"italic"},
                    properties = {"bold"},
                    types = {"bold"},
                    operators = {"bold"},
                    -- miscs = {}, -- Uncomment to turn off hard-coded styles
                },
                color_overrides = {
                    latte = {
                        -- 기본 배경색(base)을 더 밝은 흰색 계열로 변경
                        -- (기본값: #eff1f5)
                        base = "#F8F9FA",

                        -- 텍스트 색상(text)을 더 진하게 변경하여 가독성 향상
                        -- (기본값: #4c4f69)
                        text = "#43465A",
                    },
                },
                custom_highlights = {},
                default_integrations = true,
                integrations = {
                    cmp = true,
                    gitsigns = true,
                    nvimtree = true,
                    treesitter = true,
                    notify = false,
                    mini = {
                        enabled = true,
                        indentscope_color = "",
                    },
                    -- For more plugins integrations please scroll down (https://github.com/catppuccin/nvim#integrations)
                },
            })

            vim.cmd.colorscheme("catppuccin")
            vim.o.background = "light"
        end

    },
    { "marko-cerovac/material.nvim", name = "material", priority = 1000 },
    { "rmehri01/onenord.nvim", name = "onenord", priority = 1000 },
    { "sainnhe/edge", name = "edge", priority = 1000 },
}
