return {
	"goolord/alpha-nvim", -- Plugin for the dashboard UI
	lazy = false, -- Load the plugin immediately
	priority = 1000,
	config = function()
		local alpha = require("alpha")
		local dashboard = require("alpha.themes.dashboard")

		-- Set the header: this can be any ASCII art or greeting you want
		dashboard.section.header.val = {
			"          _____                    _____                     _____                    _____          ",
			"         /\\    \\                  /\\    \\                   /\\    \\                  /\\    \\         ",
			"        /::\\____\\                /::\\____\\                 /::\\    \\                /::\\____\\        ",
			"       /::::|   |               /:::/    /                 \\:::\\    \\              /::::|   |        ",
			"      /:::::|   |              /:::/    /                   \\:::\\    \\            /:::::|   |        ",
			"     /::::::|   |             /:::/    /                     \\:::\\    \\          /::::::|   |        ",
			"    /:::/|::|   |            /:::/____/                       \\:::\\    \\        /:::/|::|   |        ",
			"   /:::/ |::|   |            |::|    |                        /::::\\    \\      /:::/ |::|   |        ",
			"  /:::/  |::|   | _____      |::|    |     _____     ____    /::::::\\    \\    /:::/  |::|___|______  ",
			" /:::/   |::|   |/\\    \\     |::|    |    /\\    \\   /\\   \\  /:::/\\:::\\    \\  /:::/   |::::::::\\    \\ ",
			"/:: /    |::|   /::\\____\\    |::|    |   /::\\____\\ /::\\   \\/:::/  \\:::\\____\\/:::/    |:::::::::\\____\\",
			"\\::/    /|::|  /:::/    /    |::|    |  /:::/    / \\:::\\  /:::/    \\::/    /\\::/    / ~~~~~/:::/    /",
			" \\/____/ |::| /:::/    /     |::|    | /:::/    /   \\:::\\/:::/    / \\/____/  \\/____/      /:::/    / ",
			"         |::|/:::/    /      |::|____|/:::/    /     \\::::::/    /                       /:::/    /  ",
			"         |::::::/    /       |:::::::::::/    /       \\::::/____/                       /:::/    /   ",
			"         |:::::/    /        \\::::::::::/____/         \\:::\\    \\                      /:::/    /    ",
			"         |::::/    /          ~~~~~~~~~~                \\:::\\    \\                    /:::/    /     ",
			"         /:::/    /                                      \\:::\\    \\                  /:::/    /      ",
			"        /:::/    /                                        \\:::\\____\\                /:::/    /       ",
			"        \\::/    /                                          \\::/    /                \\::/    /        ",
			"         \\/____/                                            \\/____/                  \\/____/         ",
		}

		-- Set the buttons
		dashboard.section.buttons.val = {
			dashboard.button("e", "  New File", ":ene<CR>"),
			dashboard.button("f", "  Find File", ":Telescope find_files<CR>"),
			dashboard.button("r", "  Recent Files", ":Telescope oldfiles<CR>"),
			dashboard.button("c", "  Config", ":e /home/akuma/.config/nvim/init.lua | Neotree<CR>"),
			dashboard.button("q", "  Quit", ":qa<CR>"),
		}

		-- Configure the footer (optional)
		dashboard.section.footer.val = "<Welcome to NEOVIM>"

		-- Customize the layout and margins
		-- dashboard.config.layout = {
		--   { type = "text", val = dashboard.section.header, opts = { position = "center" } },
		--   { type = "text", val = dashboard.section.buttons, opts = { position = "center" } },
		--   { type = "text", val = dashboard.section.footer, opts = { position = "center" } },
		-- }
		-- dashboard.config.opts.noautocmd = true

		-- Set the alpha dashboard as the default start screen
		alpha.setup(dashboard.opts)

		-- Optional: Add keybindings or further customization if needed
	end,
}
