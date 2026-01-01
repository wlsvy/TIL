_G.gemini_prompt_preset_default = [[

** 전체적으로 표현 방식은**

* 표로 정리 가능하면 표 사용 (빠르게 살펴보기 위해)
* 적당한 이모지 많이 넣어줘
* 개조식 문장을 사용해줘. 읽기 쉽게 ]]

_G.gemini_prompt_preset_youtube = [[

내용 정리해줘.
** 전체적으로 표현 방식은**

* 표로 정리 가능하면 표 사용 (빠르게 살펴보기 위해)
* 적당한 이모지 많이 넣어줘
* 개조식 문장을 사용해줘. 읽기 쉽게

**아래 순서로 대답해줘**

1. 제작자의 의도와 주요 부분을 쭉 나열해주고,
2. 내용을 뒷받침하는 사례가 있다면 중요하지 않아도 괜찮으니 가급적 나열
3. 주요 구간의 실제 자막 텍스트 출력 - 맞춤법 틀려도 괜찮고 원문 그대로, 이때 한 구간마다 최소 4~5 문장 분량으로 

---

위 과정을 영어로 진행해주고, 그 다음에 한글로 번역. 필요해보인다면 영어로 자료 조사진행할 것.]]

function append_text_to_clipboard_for_aiprompt(text)

    local prevClipboard = vim.fn.getreg('+')
    local newText = prevClipboard .. text
    vim.fn.setreg('+', newText)

    vim.notify("✅ 클립보드가 수정되었습니다.".."\n"..newText)
end

-- [jesseleitenvim-macroni 🤌 Save your macros for future use](https://github.com/jesseleite/nvim-macroni)
return {
    'jesseleite/nvim-macroni',

    config = function()
        vim.keymap.set({'n', 'v'}, '<Leader>m', function ()
            require('telescope').extensions.macroni.saved_macros()
        end)

        require('macroni').setup {
            macros = {
                make_todo_list_item = {
                    macro = '^i-<Space>[<Space>]<Space>',
                    mode = { 'n', 'v' }, -- By default, macros will be mapped to both normal & visual modes
                    desc = '^i-<Space>[<Space>]<Space>',
                },

                tabularize_markdown_table = {
                    macro = ":'<,'>Tabularize /|<CR>",
                    mode = {'v'},
                    desc = ":'<,'>Tabularize /|<CR>",
                },

                check_health = {
                    macro = ":checkhealth<CR>",
                    mode = { 'n'},
                    desc = ":checkhealth<CR>",
                },

                toggle_text_wrap = {
                    macro = ":ToggleTextWrap<CR>",
                    mode = {'n', 'v'},
                    desc = ":ToggleTextWrap<CR>",
                },

                reset_markdown_numbered_list_rank = {
                    macro = ":\'<,\'>s/^1/\\=line(\'.\') + 1 - line(\"\'<\")/g<CR>",
                    mode = {'n', 'v'},
                    desc = ":\'<,\'>s/^1/\\=line(\'.\') + 1 - line(\"\'<\")/g<CR>",
                },

                copy_current_file_path_to_clipboard = {
                    macro = ":let @+ = expand(\'%\')<CR>",
                    mode = {'n', 'v'},
                    desc = ":let @+ = expand(\'%\')<CR>",
                },

                write_date_with_markdown_caption = {
                    macro = ":execute \"normal i\" . strftime(\"# %y.%m.%d\")<CR>",
                    mode = {'n'},
                    desc = ":execute \"normal i\" . strftime(\"# %y.%m.%d\")<CR>",
                },

                copy_multiline_with_any_keyword = {
                    macro = ":g/keyword1\\|keyword2/normal Vj\"Ay<CR>",
                    mode = {'n'},
                    desc = ":g/keyword1\\|keyword2/normal Vj\"Ay<CR>",
                },

                flush_register_at_abcde = {
                    macro = ":let @a='' | let @b = '' | let @c = ''| let @d = ''| let @e = ''<CR>",
                    mode = {'n'},
                    desc = ":let @a='' | let @b = '' | let @c = ''| let @d = ''| let @e = ''<CR>",
                },

                gemini_prompt_preset_00 = {
                    macro = ":lua append_text_to_clipboard_for_aiprompt(_G.gemini_prompt_preset_default)<CR>",
                    mode = {'n'},
                    desc = "표로 정리할 수 있으면 표 사용해줘, 적당한 이모지 많이 넣어줘. 표현은 개조식 문장으로. ",
                },

                gemini_prompt_preset_00_youtube = {
                    macro = ":lua append_text_to_clipboard_for_aiprompt(_G.gemini_prompt_preset_youtube)<CR>",
                    mode = {'n'},
                    desc = "표로 정리할 수 있으면 표 사용해줘, 적당한 이모지 많이 넣어줘, 표현은 개조식 문장으로, \\n 대답할 때에는 1. 제작자의 의도와 주요 부분을 쭉 나열, 2. 내용을 뒷받침하는 사례 예시가 있다면 중요도에 관계없이 나열. 3. 주요 구간의 실제 자막 텍스트 출력- 맞춤법 틀려도 괜찮으니 원문 그대로.",
                },

                vim_messages = {
                    macro = ":messages",
                    mode = {'n'},
                    desc = ":messages"
                },

                -- 무명레지스터에 등록 후 붙여넣는 방식
                add_line_summarized_by_gemini = {
                    macro = ":put = '**Summarized By Gemini**'<CR>",
                    mode = {'n'},
                    desc = ":let @@ = '**Summarized By Gemini**'<CR>"
                },

                put_current_absolute_file_path = {
                    macro = ":put = expand('%:p')<CR>",
                    mode = {'n'},
                    desc = ":put = expand('%:p')<CR>"
                },

                refresh_all_windows_in_tab = {
                    macro = ":windo e!<CR>",
                    mode = {'n'},
                    desc = ":windo e!<CR>"
                },
            },
        }
    end
}
