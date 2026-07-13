-- 각 쉘(ex: .zshrc, .bashrc 등) 환경에서 GPG 사전 설정 필요
-- # GPG가 현재 TTY를 인식하도록 설정 — 없으면 pinentry 실패                                                
-- export GPG_TTY=$(tty)                               

return {
    "jamessan/vim-gnupg",
    lazy = false,
}
