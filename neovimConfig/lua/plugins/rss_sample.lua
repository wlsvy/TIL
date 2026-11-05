-- rss reader learning sample (local, PersonalToolsWithAI/rss/nvim-sample)
-- token: env RSS_TOKEN (keep secrets out of this file)
return {
    dir = '~/Desktop/Workspace/PersonalToolsWithAI/rss/nvim-sample',
    name = 'rss_sample',
    main = 'rss_sample',
    cmd = { 'RssSample', 'RssSampleUnread', 'RssSampleAdd', 'RssSampleRefresh' },
    opts = {
        url = vim.env.RSS_URL or 'http://127.0.0.1:8080',
    },
}
