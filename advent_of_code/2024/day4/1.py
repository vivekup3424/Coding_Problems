input = open("./input", mode="r")
-- Keymap to stage, commit, and push the current file
vim.keymap.set('n', '<leader>gp', function()
  local current_file = vim.fn.expand '%:p'
  local commit_message = vim.fn.input 'Commit message: '
  if commit_message ~= '' then
    vim.fn.system(string.format("git add %s && git commit -m '%s' && git push", current_file, commit_message))
    print('Committed and pushed:', current_file)
  else
    print 'Commit message is empty. Aborting.'
  end
end, { noremap = true, silent = true },
  {desc = '[G]it [P]ush current file'})
# convert input to matrix of characters
