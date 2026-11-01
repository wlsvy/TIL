-- 한국어 nvim-cmp 소스: 버퍼의 한글 단어에서 조사를 떼어낸 어간을 빈도순으로 제안
local source = {}

local JOSA = {
    "에서는", "으로는", "에게는", "에서", "에게", "으로", "까지", "부터", "처럼", "보다", "이나", "이랑",
    "이", "가", "을", "를", "은", "는", "의", "에", "로", "와", "과", "도", "만",
}
-- 긴 조사부터 검사해야 "에서는"이 "는"보다 먼저 잘린다
table.sort(JOSA, function(a, b) return #a > #b end)

local MIN_BYTES = 6 -- 한글 2음절(UTF-8 3바이트 x 2)

local function strip(word)
    for _, josa in ipairs(JOSA) do
        if #word - #josa >= MIN_BYTES and word:sub(-#josa) == josa then
            return word:sub(1, -#josa - 1)
        end
    end
    return word
end

-- 어간이 2가지 이상 형태(맨몸 포함)로 등장할 때만 조사로 인정한다.
-- "고양이"만 있으면 "고양"+"이"로 오인하지 않고, "고양이"+"고양이가"가 있으면 "고양이"로 합친다.
function source.extract(lines)
    local count, variants = {}, {}
    for _, line in ipairs(lines) do
        -- shortcut: 줄마다 vim.fn 호출, 큰 버퍼에서 느려지면 버퍼별 캐시 도입
        for _, w in ipairs(vim.fn.split(line, [[[^가-힣]\+]])) do
            count[w] = (count[w] or 0) + 1
            local s = strip(w)
            variants[w] = variants[w] or {}
            variants[w][w] = true
            variants[s] = variants[s] or {}
            variants[s][w] = true
        end
    end

    local freq = {}
    for w, n in pairs(count) do
        local s = strip(w)
        local key = vim.tbl_count(variants[s]) >= 2 and s or w
        if #key >= MIN_BYTES then
            freq[key] = (freq[key] or 0) + n
        end
    end

    local words = vim.tbl_keys(freq)
    table.sort(words, function(a, b) return freq[a] > freq[b] end)
    return words
end

function source:get_keyword_pattern()
    return [[[가-힣]\+]]
end

function source:complete(params, callback)
    local bufnrs = params.option.get_bufnrs and params.option.get_bufnrs() or { vim.api.nvim_get_current_buf() }
    local lines = {}
    for _, b in ipairs(bufnrs) do
        if vim.api.nvim_buf_is_loaded(b) then
            vim.list_extend(lines, vim.api.nvim_buf_get_lines(b, 0, -1, false))
        end
    end
    -- shortcut: 빈도순은 cmp 기본 comparator의 마지막 tiebreak(order)에만 반영됨, 부족하면 custom comparator 추가
    local items = {}
    for i, w in ipairs(source.extract(lines)) do
        items[i] = { label = w }
    end
    callback(items)
end

return source
