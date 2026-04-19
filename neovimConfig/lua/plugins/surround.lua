-- [kylechui/nvim-surround: Add/change/delete surrounding delimiter pairs with ease. Written with in Lua.](https://github.com/kylechui/nvim-surround)
return {
    "kylechui/nvim-surround",
    version = "^4.0.0", -- Use for stability; omit to use `main` branch for the latest features
    event = "VeryLazy",
    -- Optional: See `:h nvim-surround.configuration` and `:h nvim-surround.setup` for details
    -- config = function()
    --     require("nvim-surround").setup({
    --         -- Put your configuration here
    --     })
    -- end
    config = function ()
        require("nvim-surround").setup({
            surrounds = {
                -- Markdown bold (**text**)
                ["*"] = {
                    add = { "**", "**" },
                    find = "%*%*.--%*%*",
                    delete = "^(%*%*)().-()(%*%*)$",
                },
            },
            -- 추가 키맵핑
            keymaps = {
                insert = "<C-g>s",
                insert_line = "<C-g>S",
                normal = "ys",
                normal_cur = "yss",
                normal_line = "yS",
                normal_cur_line = "ySS",
                visual = "S",
                visual_line = "gS",
                delete = "ds",
                change = "cs",
            },
        })

    end
}
