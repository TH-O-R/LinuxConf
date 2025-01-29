return {
  'nvim-treesitter/nvim-treesitter',
  build = ':TSUpdate',
  main = 'nvim-treesitter.configs',
  opts = {
    ensure_installed = {
      'lua',
      'vim',
      'vimdoc',
      'toml',
      'json',
      'java',
      'gitignore',
      'make',
      'bash',
      'c',
      'cpp',
      'css',
    },
    auto_install = false,
    highlight = {
      enable = true,
      additional_vim_regex_highlighting = { 'ruby' },
    },
    indent = { enable = true, disable = { 'ruby' } },
  },
}
