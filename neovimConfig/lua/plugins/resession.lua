-- [GitHub - stevearc/resession.nvim: A replacement for mksession with a better API · GitHub](https://github.com/stevearc/resession.nvim)
return {
    'stevearc/resession.nvim',
    opts = {},
    keys = {

        { "<leader>ss", function() require("resession").save() end, desc = "📌save sessions", },
        { "<leader>sd", function() require("resession").delete() end, desc = "📌delete current session", },
        { "<leader>sl", function() require("telescope").extensions.resession.resession() end, desc = "📌list session", },
    },

    config = function()

        local resession = require("resession")
        resession.setup()

        vim.api.nvim_create_autocmd("VimLeavePre", {
            callback = function()
                -- Always save a special session named "last"
                resession.save("last")
            end,
        })
    end

}

