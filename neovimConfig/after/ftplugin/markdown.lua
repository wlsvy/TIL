-- ============================================================
-- after/ftplugin/markdown.lua
--
-- [ftplugin 이란?]
--   filetype plugin의 약자. 특정 파일타입을 열 때만 실행되는 설정 파일.
--   nvim은 파일을 열면 filetype을 감지하고, 해당 이름의 ftplugin을 자동 로드한다.
--   예) markdown 파일 열기 → ftplugin/markdown.lua 실행
--
-- [after/ 디렉토리의 역할]
--   nvim 기본 ftplugin이 먼저 로드된 뒤, after/ftplugin/이 로드된다.
--   기본 설정을 덮어쓰거나 추가할 때 after/를 사용한다.
--
-- [syntax/markdown.vim 대신 이 파일을 쓰는 이유]
--   treesitter가 활성화된 filetype은 vim의 regex syntax 레이어를 비활성화한다.
--   syntax region / syntax match 같은 명령이 무시된다.
--   matchadd()는 syntax/treesitter와 별개인 "match 하이라이트 레이어"에 작동하므로
--   treesitter 활성 여부와 관계없이 항상 동작한다.
-- ============================================================

-- vim.fn.matchadd(그룹명, 패턴)
--   현재 버퍼에 패턴 매칭 하이라이트를 추가한다.
--   그룹명: 기존 highlight 그룹 이름 (여기서는 bold 속성을 가진 htmlBold)
--   패턴:   Vimscript 정규식
--     <strong>   : 리터럴 태그
--     \_.        : 줄바꿈을 포함한 임의의 한 문자 (. 의 멀티라인 버전)
--     \{-}       : non-greedy 반복 (가장 짧은 범위로 매칭)
--     </strong>  : 리터럴 닫는 태그
--   Lua 문자열에서는 \ 를 \\ 로 이스케이프해야 한다.
-- 전용 highlight 그룹 정의
-- nvim_set_hl(namespace, group, opts): 0 = 전역 namespace
-- catppuccin latte 팔레트 기준: Mauve(#8839ef) + bold
vim.api.nvim_set_hl(0, "MarkdownStrong", { fg = "#8839ef", bold = true })

vim.fn.matchadd("MarkdownStrong", "<strong>\\_.\\{-}</strong>")
