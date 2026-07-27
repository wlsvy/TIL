-- [jakewvincent/mkdnflow.nvim: Fluent navigation and management of markdown notebooks](https://github.com/jakewvincent/mkdnflow.nvim#list-management)
return {
    'jakewvincent/mkdnflow.nvim',
    ft = { 'markdown', 'rmd' },  -- Add custom filetypes here if configured
    config = function()
        require('mkdnflow').setup({
            -- Your config
            mappings = {
                MkdnCreateLinkFromClipboard = false,
                MkdnFoldSection = { 'n', '<leader>vf' },
                MkdnUnfoldSection = { 'n', '<leader>vF' },
            },

            path_resolution = {
                primary = 'current',
                fallback = 'current',
                root_marker = false,
                sync_cwd = false,
                update_on_navigate = false,
            },
        })
    end
}
