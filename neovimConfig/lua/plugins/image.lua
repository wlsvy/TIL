-- [GitHub - 3rd/image.nvim: 🖼️ Bringing images to Neovim.](https://github.com/3rd/image.nvim)
return {
    '3rd/image.nvim',
    cond = vim.fn.has('macunix') == 1,
    config = function()
        require("image").setup({
            backend = "kitty", -- or "ueberzug" or "sixel"
            processor = "magick_cli", -- or "magick_rock"
            integrations = {
                markdown = {
                    enabled = true,
                    clear_in_insert_mode = false,
                    download_remote_images = true,
                    only_render_image_at_cursor = false,
                    only_render_image_at_cursor_mode = "popup", -- or "inline"
                    floating_windows = false, -- if true, images will be rendered in floating markdown windows
                    filetypes = { "markdown", "vimwiki" }, -- markdown extensions (ie. quarto) can go here
                },
                html = {
                    enabled = false,
                },
                css = {
                    enabled = false,
                },
            },
            max_width = nil,
            max_height = nil,
            max_width_window_percentage = nil,
            max_height_window_percentage = nil,
            scale_factor = 1.0,
            window_overlap_clear_enabled = true, -- toggles images when windows are overlapped
            window_overlap_clear_ft_ignore = { "cmp_menu", "cmp_docs", "snacks_notif", "scrollview", "scrollview_sign" },
            editor_only_render_when_focused = true, -- auto show/hide images when the editor gains/looses focus
            tmux_show_only_in_active_window = false, -- auto show/hide images in the correct Tmux window (needs visual-activity off)
            -- hijack_file_patterns = { "*.png", "*.jpg", "*.jpeg", "*.gif", "*.webp", "*.avif" }, -- render image files as images when opened
            hijack_file_patterns = {}, -- render image files as images when opened
        })

        local image = require("image")

        -- upstream 핸들러는 이벤트당 1개만 지우므로 전체를 다시 훑는다
        local function clear_stale_images()
            local tab_wins = {}
            for _, win in ipairs(vim.api.nvim_tabpage_list_wins(0)) do tab_wins[win] = true end
            for _, img in ipairs(image.get_images()) do
                local win, buf = img.window, img.buffer
                if win and (not tab_wins[win]
                        or (buf and (not vim.api.nvim_buf_is_valid(buf) or vim.api.nvim_win_get_buf(win) ~= buf))) then
                    img:clear()
                end
            end
        end

        vim.api.nvim_create_autocmd({ "BufLeave", "WinClosed", "TabEnter" }, {
            group = vim.api.nvim_create_augroup("image.nvim:stale", { clear = true }),
            callback = function() vim.schedule(clear_stale_images) end,
        })

        -- image.disable()은 is_rendered인 이미지만 지우므로, 기록에 없는 잔상까지 kitty 전체 삭제로 지운다
        local function wipe_images()
            for _, img in ipairs(image.get_images()) do img:clear() end
            image.clear()
        end

        local function redraw_images()
            for _, win in ipairs(vim.api.nvim_tabpage_list_wins(0)) do
                vim.api.nvim_exec_autocmds("BufEnter", {
                    group = "image.nvim:markdown",
                    buffer = vim.api.nvim_win_get_buf(win),
                })
            end
        end

        vim.api.nvim_create_user_command("ImageClear", wipe_images, { desc = "Clear all images" })

        vim.api.nvim_create_user_command("ImageReset", function()
            wipe_images()
            redraw_images()
        end, { desc = "Reset image.nvim" })

        vim.api.nvim_create_user_command("ImageToggle", function()
            if image.is_enabled() then
                image.disable()
                wipe_images()
            else
                image.enable()
                redraw_images()
            end
            vim.notify("image.nvim " .. (image.is_enabled() and "on" or "off"))
        end, { desc = "Toggle image.nvim" })
    end
}
