
local M = {}

-- 1. Python + requests + BeautifulSoup 활용 (가장 강력)
local function fetch_with_python(url)
  local python_script = string.format([[
import requests
from bs4 import BeautifulSoup
import json
import re

try:
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36',
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Language': 'ko-KR,ko;q=0.9,en;q=0.8'
    }
    
    response = requests.get('%s', headers=headers, timeout=30)
    response.raise_for_status()
    
    soup = BeautifulSoup(response.text, 'html.parser')
    article_data = {}
    
    # 제목 추출
    title_selectors = ['h1.headline', '.article-head h1', 'h1[class*="title"]', 'h1']
    for selector in title_selectors:
        elem = soup.select_one(selector)
        if elem and len(elem.get_text(strip=True)) > 5:
            article_data['title'] = elem.get_text(strip=True)
            break
    
    # 본문 추출
    content_selectors = ['.article-text', '.article_txt', '.news_text', '.article-body', 'article']
    for selector in content_selectors:
        elem = soup.select_one(selector)
        if elem:
            for unwanted in elem.select('script, style, .ad, .advertisement'):
                unwanted.decompose()
            content = re.sub(r'\s+', ' ', elem.get_text(strip=True))
            if len(content) > 200:
                article_data['content'] = content
                break
    
    # 작성자 추출
    author_selectors = ['.reporter', '.byline', '[class*="author"]']
    for selector in author_selectors:
        elem = soup.select_one(selector)
        if elem:
            article_data['author'] = elem.get_text(strip=True)
            break
    
    # 날짜 추출
    date_selectors = ['time[datetime]', '.date', '[class*="date"]']
    for selector in date_selectors:
        elem = soup.select_one(selector)
        if elem:
            article_data['date'] = elem.get('datetime') or elem.get_text(strip=True)
            break
    
    print(json.dumps(article_data, ensure_ascii=False))
    
except Exception as e:
    print(json.dumps({'error': str(e)}, ensure_ascii=False))
]], url)

  return execute_script("python3", python_script, "py")
end

-- 2. wget 활용 (curl 대안)
local function fetch_with_wget(url)
  local wget_cmd = string.format([[wget -q -O - \
    --user-agent="Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36" \
    --header="Accept-Language: ko-KR,ko;q=0.9,en;q=0.8" \
    --timeout=30 \
    '%s']], url)
  
  local handle = io.popen(wget_cmd)
  if not handle then return nil end
  
  local html_content = handle:read("*a")
  local success, _, exit_code = handle:close()
  
  if success and exit_code == 0 and html_content and html_content ~= "" then
    return extract_hankyung_article(html_content)
  end
  return nil
end

-- 3. httpie 활용 (현대적인 HTTP 클라이언트)
local function fetch_with_httpie(url)
  local http_cmd = string.format([[http --timeout=30 --follow \
    User-Agent:"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36" \
    Accept-Language:"ko-KR,ko;q=0.9,en;q=0.8" \
    '%s']], url)
  
  local handle = io.popen(http_cmd .. " 2>/dev/null")
  if not handle then return nil end
  
  local html_content = handle:read("*a")
  handle:close()
  
  if html_content and html_content ~= "" then
    return extract_hankyung_article(html_content)
  end
  return nil
end

-- 스크립트 실행 헬퍼 함수
local function execute_script(interpreter, script, extension)
  local temp_file = string.format("/tmp/hankyung_%d.%s", os.time(), extension)
  
  local file = io.open(temp_file, "w")
  if not file then return nil end
  
  file:write(script)
  file:close()
  
  local handle = io.popen(interpreter .. " " .. temp_file .. " 2>/dev/null")
  if not handle then
    os.remove(temp_file)
    return nil
  end
  
  local result = handle:read("*a")
  handle:close()
  os.remove(temp_file)
  
  local success, json_data = pcall(function()
    return vim.fn.json_decode(result)
  end)
  
  if success and json_data and not json_data.error then
    return json_data
  end
  return nil
end

-- 개선된 HTML 파싱 함수
local function extract_hankyung_article(html_content)
  if not html_content or html_content == "" then
    return nil
  end

  local article_data = { title = "", content = "", author = "", date = "" }

  -- 제목 추출
  local title_patterns = {
    '<h1[^>]*class="[^"]*headline[^"]*"[^>]*>([^<]+)</h1>',
    '<div[^>]*class="[^"]*article%-head[^"]*"[^>]*>.-<h1[^>]*>([^<]+)</h1>',
    '<h1[^>]*class="[^"]*title[^"]*"[^>]*>([^<]+)</h1>',
    '<title>([^|<]+)%s*|',
    '<h1[^>]*>([^<]+)</h1>'
  }
  
  for _, pattern in ipairs(title_patterns) do
    local title = html_content:match(pattern)
    if title then
      title = title:gsub("&[^;]+;", ""):gsub("^%s*", ""):gsub("%s*$", "")
      if #title > 5 then
        article_data.title = title
        break
      end
    end
  end

  -- 본문 추출
  local content_patterns = {
    '<div[^>]*class="[^"]*article%-text[^"]*"[^>]*>(.-)</div>',
    '<div[^>]*class="[^"]*article_txt[^"]*"[^>]*>(.-)</div>',
    '<div[^>]*class="[^"]*news_text[^"]*"[^>]*>(.-)</div>',
    '<div[^>]*class="[^"]*article%-body[^"]*"[^>]*>(.-)</div>',
    '<article[^>]*>(.-)</article>'
  }

  for _, pattern in ipairs(content_patterns) do
    local content = html_content:match(pattern)
    if content then
      content = content:gsub("<script[^>]*>.-</script>", "")
      content = content:gsub("<style[^>]*>.-</style>", "")
      content = content:gsub("<[^>]*>", "")
      content = content:gsub("&[^;]+;", " ")
      content = content:gsub("%s+", " ")
      content = content:gsub("^%s*", ""):gsub("%s*$", "")
      
      if #content > 200 then
        article_data.content = content
        break
      end
    end
  end

  -- 작성자 추출
  local author_patterns = {
    '<span[^>]*class="[^"]*reporter[^"]*"[^>]*>([^<]+)</span>',
    '<div[^>]*class="[^"]*byline[^"]*"[^>]*>([^<]+)</div>',
    '([^<\n]+)%s*기자'
  }

  for _, pattern in ipairs(author_patterns) do
    local author = html_content:match(pattern)
    if author then
      article_data.author = author:gsub("^%s*", ""):gsub("%s*$", "")
      break
    end
  end

  -- 날짜 추출
  local date_patterns = {
    '<time[^>]*datetime="([^"]+)"',
    '<span[^>]*class="[^"]*date[^"]*"[^>]*>([^<]+)</span>',
    '(%d%d%d%d%.%d%d%.%d%d)',
    '(%d%d%d%d%-%d%d%-%d%d)'
  }

  for _, pattern in ipairs(date_patterns) do
    local date = html_content:match(pattern)
    if date then
      article_data.date = date
      break
    end
  end

  return article_data
end

-- 통합 스크래핑 함수
function M.scrape_hankyung_article(url)
  if not url or not url:match("hankyung%.com") then
    vim.notify("Invalid Hankyung URL", vim.log.levels.ERROR)
    return nil
  end

  local strategies = {
    { name = "Python + BeautifulSoup", func = fetch_with_python },
    { name = "wget", func = fetch_with_wget },
    { name = "httpie", func = fetch_with_httpie }
  }

  for _, strategy in ipairs(strategies) do
    vim.notify("Trying " .. strategy.name .. "...", vim.log.levels.INFO)
    
    local result = strategy.func(url)
    if result and (result.content or result.title) and #(result.content or "") > 100 then
      vim.notify("Success with " .. strategy.name, vim.log.levels.INFO)
      return result
    end
  end

  vim.notify("All scraping strategies failed", vim.log.levels.ERROR)
  return nil
end

-- 결과를 새 버퍼에 표시
function M.display_article(article_data)
  if not article_data then return end

  vim.cmd('new')
  local lines = {}
  
  table.insert(lines, "# " .. (article_data.title or "제목 없음"))
  table.insert(lines, "")
  
  if article_data.author and article_data.author ~= "" then
    table.insert(lines, "**작성자:** " .. article_data.author)
  end
  
  if article_data.date and article_data.date ~= "" then
    table.insert(lines, "**날짜:** " .. article_data.date)
  end
  
  table.insert(lines, "")
  table.insert(lines, "---")
  table.insert(lines, "")
  
  -- 본문을 80자 단위로 줄바꿈
  local content = article_data.content or ""
  local words = {}
  for word in content:gmatch("%S+") do
    table.insert(words, word)
  end
  
  local current_line = ""
  for _, word in ipairs(words) do
    if #current_line + #word + 1 > 80 then
      if current_line ~= "" then
        table.insert(lines, current_line)
      end
      current_line = word
    else
      current_line = current_line == "" and word or current_line .. " " .. word
    end
  end
  
  if current_line ~= "" then
    table.insert(lines, current_line)
  end

  vim.api.nvim_buf_set_lines(0, 0, -1, false, lines)
  vim.bo.filetype = 'markdown'
  vim.bo.readonly = true
end

-- 통합 함수
function M.fetch_and_display(url)
  vim.notify("Fetching article from Hankyung...", vim.log.levels.INFO)
  
  local article_data = M.scrape_hankyung_article(url)
  if article_data then
    M.display_article(article_data)
    vim.notify("Article loaded successfully!", vim.log.levels.INFO)
  else
    vim.notify("Failed to fetch article", vim.log.levels.ERROR)
  end
end

-- 디버깅용 함수
function M.debug_html(url)
  local wget_cmd = string.format([[wget -q -O - \
    --user-agent="Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36" \
    '%s']], url)
  
  local handle = io.popen(wget_cmd)
  local content = handle:read("*a")
  handle:close()
  
  vim.cmd('new')
  vim.api.nvim_buf_set_lines(0, 0, -1, false, vim.split(content, '\n'))
  vim.bo.filetype = 'html'
end

-- Vim 명령어 생성
vim.api.nvim_create_user_command('FetchWebpageHankyung', function(opts)
    M.fetch_and_display(opts.args)
end, { nargs = 1, desc = 'Fetch Hankyung article and display' })

vim.api.nvim_create_user_command('FetchWebpageHankyungDebug', function(opts)
    M.debug_html(opts.args)
end, { nargs = 1, desc = 'Debug Hankyung HTML structure' })

return M
