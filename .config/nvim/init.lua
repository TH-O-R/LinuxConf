require 'core.options' -- Load general options
require 'core.keymaps' -- Load general keymaps
require 'core.snippets' -- Custom code snippets
require 'core.lazy' -- Lazy.nvim plugin manager


-- Set up plugins
require('lazy').setup {
  require 'plugins.neotree',
  require 'plugins.colortheme',
  require 'plugins.bufferline',
  require 'plugins.lualine',
  require 'plugins.treesitter',
  require 'plugins.telescope',
  require 'plugins.lsp',
  require 'plugins.autocompletion',
  require 'plugins.none-ls',
  require 'plugins.gitsigns',
  require 'plugins.alpha',
  require 'plugins.indent-blankline',
  require 'plugins.misc',
  require 'plugins.comment',
}

-- The line beneath this is called `modeline`. See `:help modeline`
-- vim: ts=2 sts=2 sw=2 et
