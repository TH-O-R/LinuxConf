return {
	-- {
	--   'trope/vim-sleuth',
	-- },
	-- {
	--   'trope/vim-fugitive',
	-- },
	-- {
	--   'trope/vim-rhubarb',
	-- },
	{
		"folke/which-key.nvim",
	},
	{
		"windwp/nvim-autopairs",
		event = "InsertEnter",
		config = true,
		opts = {},
	},
	{
		"folke/todo-comments.nvim",
		event = "VimEnter",
		dependencies = { "nvim-lua/plenary.nvim" },
		opts = { signs = false },
	},
	{
		"folke/snacks.nvim",
		priority = 1000,
		lazy = false,
		---@type snacks.Config
		opts = {
			-- your configuration comes here
			-- or leave it empty to use the default settings
			-- refer to the configuration section below
			bigfile = { enabled = true },
			dashboard = { enabled = true },
			indent = { enabled = true },
			input = { enabled = true },
			picker = { enabled = true },
			notifier = { enabled = true },
			quickfile = { enabled = true },
			scroll = { enabled = true },
			statuscolumn = { enabled = true },
			words = { enabled = true },
		},
	},
	{
		"norcalli/nvim-colorizer.lua",
		conifg = function()
			require("colorizer").setup()
		end,
	},
}
