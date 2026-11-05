-- Folo client wrapping the folo CLI (local, PersonalToolsWithAI/folo/nvim)
-- auth: `folo login` or env FOLO_TOKEN (keep secrets out of this file)
return {
    dir = '~/Desktop/Workspace/PersonalToolsWithAI/folo/nvim',
    name = 'folo',
    main = 'folo',
    cmd = { 'Folo', 'FoloUnread', 'FoloCategory', 'FoloStarred' },
    opts = {},
}
