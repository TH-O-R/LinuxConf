return {
	"nvim-lualine/lualine.nvim",
	config = function()
		local mode = {
			"mode",
			fmt = function(str)
				return "󰀘 " .. str
			end,
		}

		local filename = {
			"filename",
			file_status = true,
			path = 0,
		}

		local hide_in_width = function()
			return vim.fn.winwidth(0) > 100
		end

		local diagnostics = {
			"diagnostics",
			source = { "nvim_diagnostic" },
			sections = { "error", "warn" },
			symbols = { error = " ", warn = " ", info = " ", hint = "󰌶 " },
			colored = true,
			update_in_insert = false,
			always_visible = false,
			cond = hide_in_width,
		}

		local diff = {
			"diff",
			colored = false,
			symbols = { added = " ", modified = " ", removed = " " },
			cond = hide_in_width,
		}

		local branch = {
			"b:gitsigns_head",
			icon = "",
			color = { gui = "bold" },
		}

		require("lualine").setup({
			options = {
				icons_enabled = true,
				theme = "tokyonight-night",
				section_separators = { left = "", right = "" },
				component_separators = { left = "", right = "" },
				disabled_filetypes = { "alpha", "neo-tree" },
				always_divide_middle = true,
			},
			sections = {
				lualine_a = { mode },
				lualine_b = { branch },
				lualine_c = { filename },
				lualine_x = { diagnostics, diff, { "filetype", cond = hide_in_width } },
				lualine_y = { "location" },
				lualine_z = { "progress" },
			},
			inactive_sections = {
				lualine_a = {},
				lualine_b = {},
				lualine_c = { { "filename", path = 1 } },
				lualine_x = { { "location", padding = 0 } },
				lualine_y = {},
			},
			tabline = {},
			extensions = { "fugitive" },
		})
	end,
}
