-- return {
-- 	"uZer/pywal16.nvim",
-- 	-- for local dev replace with:
-- 	-- dir = '~/your/path/pywal16.nvim',
-- 	config = function()
-- 		vim.cmd.colorscheme("pywal16")
-- 	end,
-- }
--
return {
	-- "EdenEast/nightfox.nvim"
	{
		"folke/tokyonight.nvim",
		lazy = false,
		priority = 1000,
		config = function()
			vim.g.tokyonight_style = "night" -- Can be Night - Moon - Storm or Day
			vim.g.tokyonight_transparent_sidebar = false
			vim.g.tokyonight_transparent = false
			vim.g.tokyonight_italic_comments = true
			vim.g.tokyonight_italic_keywords = false
			vim.g.tokyonight_italic_functions = false
			vim.g.tokyonight_bold = true

			-- Toggle background transparency
			local tokyo = false

			local toggle_color = function()
				if tokyo then
					vim.cmd("colorscheme carbonfox")
				else
					vim.cmd("colorscheme tokyonight-night")
				end
				tokyo = not tokyo
			end

			vim.keymap.set(
				"n",
				"<leader>bg",
				toggle_color,
				{ desc = "toggle colorscheme", noremap = true, silent = true }
			)
			vim.cmd("colorscheme tokyonight-night")
		end,
	},
	{
		"EdenEast/nightfox.nvim",
		lazy = false,
		priority = 1000,
		config = function()
			vim.g.nightfox_style = "carbon"
			vim.g.nightfox_transparent = false
			vim.cmd("colorscheme carbonfox")
		end,
	},
}
