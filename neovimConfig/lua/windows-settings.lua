--windows-settings.lua

vim.o.shell = 'powershell'

-- Alt+Shift+hjkl 로 분할 창 이동 (Win 키 조합은 OS가 가로챔)
for _, dir in ipairs({ "h", "j", "k", "l" }) do
  vim.keymap.set({ "n", "i", "v", "t" }, "<A-S-" .. dir .. ">", "<Cmd>wincmd " .. dir .. "<CR>", { silent = true })
end
