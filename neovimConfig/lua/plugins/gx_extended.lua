return {
  'rmagatti/gx-extended.nvim',

  keys = { 'gx' },
  opts = {
    open_fn = require'lazy.util'.open,
  },
  config = function()
    require("gx-extended").setup {
      extensions = { },
    }
  end
}
