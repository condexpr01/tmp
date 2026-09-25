---@diagnostic disable: lowercase-global, undefined-global

local M = {}
M.fn = require("nvim_audio")

local default_opts = {
	bind_when_setup = true,
	volume = 1.0
}

M.setup = function(opts)
	local options = vim.tbl_deep_extend('force', default_opts, opts or {})

	if options.bind_when_setup then
		local ok,what = M.fn.ra_bind()
		if not ok then
			vim.notify(what)
		end
	end

	M.fn.ra_volume(options.volume)

	M.fn.load_wav("audiotest", vim.fn.stdpath('config') .. '/audio.wav')
	M.fn.ra_play("audiotest")

end

return M
