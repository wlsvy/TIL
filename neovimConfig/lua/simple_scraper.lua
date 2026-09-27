
local M = {}

local function fetch_webpage_text(url)
  -- Validate URL
  if not url or url == "" then
    vim.notify("Please provide a valid URL", vim.log.levels.ERROR)
    return
  end

  -- Use curl to fetch the webpage
  local curl_cmd = string.format("curl -s -L '%s'", url)
  local handle = io.popen(curl_cmd)
  
  if not handle then
    vim.notify("Failed to execute curl command", vim.log.levels.ERROR)
    return
  end

  local html_content = handle:read("*a")
  handle:close()

  if not html_content or html_content == "" then
    vim.notify("Failed to fetch content from URL", vim.log.levels.ERROR)
    return
  end

  -- Simple HTML tag removal (basic text extraction)
  local text = html_content
    :gsub("<%s*[Ss][Cc][Rr][Ii][Pp][Tt].-<%s*/%s*[Ss][Cc][Rr][Ii][Pp][Tt]%s*>", "") -- Remove script tags
    :gsub("<%s*[Ss][Tt][Yy][Ll][Ee].-<%s*/%s*[Ss][Tt][Yy][Ll][Ee]%s*>", "") -- Remove style tags
    :gsub("<[^>]*>", "") -- Remove all HTML tags
    :gsub("&nbsp;", " ") -- Replace HTML entities
    :gsub("&amp;", "&")
    :gsub("&lt;", "<")
    :gsub("&gt;", ">")
    :gsub("&quot;", '"')
    :gsub("&#(%d+);", function(n) return string.char(tonumber(n)) end)

  -- Split into lines and clean up
  local lines = {}
  for line in text:gmatch("[^\r\n]+") do
    local cleaned_line = line:match("^%s*(.-)%s*$") -- Trim whitespace
    if cleaned_line and cleaned_line ~= "" then
      table.insert(lines, cleaned_line)
    end
  end

  -- Insert into current buffer at cursor position
  local current_line = vim.api.nvim_win_get_cursor(0)[1]
  vim.api.nvim_buf_set_lines(0, current_line, current_line, false, lines)
  
  vim.notify(string.format("Inserted %d lines from %s", #lines, url), vim.log.levels.INFO)
end

local function scrape_with_playwright(url)
  -- Playwright 설치 필요: npm install -g playwright

  local script = string.format([[
    const { chromium } = require('playwright');
    (async () => {
      const browser = await chromium.launch();
      const page = await browser.newPage();
      await page.goto('%s');
      await page.waitForLoadState('networkidle');
      const content = await page.textContent('body');
      console.log(content);
      await browser.close();
    })();
  ]], url)
  
  -- 임시 스크립트 파일 생성
  local temp_file = "/tmp/scrape_script.js"
  local file = io.open(temp_file, "w")
  file:write(script)
  file:close()
  
  -- Node.js로 실행
  local handle = io.popen("node " .. temp_file)
  local content = handle:read("*a")
  handle:close()
  
  -- 임시 파일 삭제
  os.remove(temp_file)
  
  return content
end

-- Create a command to use the function
vim.api.nvim_create_user_command('FetchWebpage', function(opts)
  fetch_webpage_text(opts.args)
end, { nargs = 1, desc = 'Fetch webpage text and insert into buffer' })

-- Create a command to use the function
vim.api.nvim_create_user_command('FetchWebpage2', function(opts)
  scrape_with_playwright(opts.args)
end, { nargs = 1, desc = 'Fetch webpage text and insert into buffer' })

-- Optional: Create a keybinding
vim.keymap.set('n', '<leader>fw', function()
  vim.ui.input({ prompt = 'Enter URL: ' }, function(url)
    if url then
      fetch_webpage_text(url)
    end
  end)
end, { desc = 'Fetch webpage text' })


-- Export the function for external use
M.fetch_webpage_text = fetch_webpage_text

return M


