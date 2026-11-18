-- [nvim-neo-tree/neo-tree.nvim: Neovim plugin to manage the file system and other tree like structures.](https://github.com/nvim-neo-tree/neo-tree.nvim)
return {
    "nvim-neo-tree/neo-tree.nvim",
    branch = "v3.x",
    dependencies = {
        "nvim-lua/plenary.nvim",
        "MunifTanjim/nui.nvim",
        "nvim-tree/nvim-web-devicons",
    },
    cmd = "Neotree",
    keys = {
        { "<leader>e", "<cmd>Neotree toggle<CR>", desc = "Neo-tree toggle" },
        { "<leader>E", "<cmd>Neotree reveal<CR>", desc = "Neo-tree reveal current file" },
    },
    opts = {},
}
