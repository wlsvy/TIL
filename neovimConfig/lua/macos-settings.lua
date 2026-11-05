-- macos-settings.lua


-- Cmd+Shift+방향키/hjkl 로 분할 창 이동
for dir, keys in pairs({
  h = { "<D-S-h>", "<D-S-Left>" },
  j = { "<D-S-j>", "<D-S-Down>" },
  k = { "<D-S-k>", "<D-S-Up>" },
  l = { "<D-S-l>", "<D-S-Right>" },
}) do
  for _, key in ipairs(keys) do
    vim.keymap.set({ "n", "i", "v", "t" }, key, "<Cmd>wincmd " .. dir .. "<CR>", { silent = true })
  end
end
