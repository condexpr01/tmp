---@diagnostic disable: lowercase-global, undefined-global

print(vim.fn.expand('<sfile>:p:h'))

local testlib = require("testlib")

print(testlib.add(1.1,2.2))

return testlib
