return {
	"folke/tokyonight.nvim",
	lazy = false,
	priority = 1001,
	config = function()
		vim.g.tokyonight_style = "night" -- Can be Night - Moon - Storm or Day
		vim.g.tokyonight_transparent_sidebar = false
		vim.g.tokyonight_transparent = false
		vim.g.tokyonight_italic_comments = true
		vim.g.tokyonight_italic_keywords = false
		vim.g.tokyonight_italic_functions = false
		vim.g.tokyonight_bold = true

		vim.cmd("colorscheme tokyonight-night")
	end,
}
