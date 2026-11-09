-- wlsvy/PersonalToolsWithAI: folo (folo/nvim) + rss_sample (rss/nvim-sample)
-- one spec: lazy merges specs that share a url
-- folo auth: `folo login` or env FOLO_TOKEN / rss token: env RSS_TOKEN (keep secrets out of this file)
local subdirs = {
    { dir = 'folo/nvim', main = 'folo', opts = {} },
    { dir = 'rss/nvim-sample', main = 'rss_sample', opts = { url = vim.env.RSS_URL or 'http://127.0.0.1:8080' } },
}

return {
    'wlsvy/PersonalToolsWithAI',
    name = 'personal_tools',
    cmd = {
        'Folo', 'FoloUnread', 'FoloCategory', 'FoloStarred',
        'RssSample', 'RssSampleUnread', 'RssSampleAdd', 'RssSampleRefresh',
    },
    -- lazy only loads a repo root, so put each subdir on rtp ourselves
    config = function(plugin)
        for _, s in ipairs(subdirs) do
            local dir = plugin.dir .. '/' .. s.dir
            vim.opt.rtp:append(dir)
            vim.cmd.source(dir .. '/plugin/' .. s.main .. '.lua')
            require(s.main).setup(s.opts)
        end
    end,
}
