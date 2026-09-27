-- [GitHub - hakonharnes/img-clip.nvim: Embed images into any markup language, like LaTeX, Markdown or Typst](https://github.com/hakonharnes/img-clip.nvim)
return {
    "HakonHarnes/img-clip.nvim",
    event = "VeryLazy",
    opts = {
        -- add options here
        -- or leave it empty to use the default settings
        --
        default = {
            dir_path = "img", ---@type string | fun(): string
            extension = "png", ---@type string | fun(): string
            file_name = "%Y-%m-%d-%H-%M-%S", ---@type string | fun(): string
        },

        filetypes = {
            markdown = {
                dir_path = "img", ---@type string | fun(): string
                extension = "png", ---@type string | fun(): string
                file_name = "%Y-%m-%d-%H-%M-%S", ---@type string | fun(): string
                use_absolute_path = false, ---@type boolean | fun(): boolean
                relative_to_current_file = true, ---@type boolean | fun(): boolean
                url_encode_path = false, ---@type boolean | fun(): boolean
                template = "![$FILE_NAME_NO_EXT]($FILE_PATH)$CURSOR", ---@type string | fun(context: table): string
                download_images = true, ---@type boolean | fun(): boolean
            },

            html = {
                template = '<img src="$FILE_PATH" alt="$CURSOR">', ---@type string | fun(context: table): string
            },
        }
    },
}
