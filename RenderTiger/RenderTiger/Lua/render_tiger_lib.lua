BUFFER = {
	VBT = {},
	IBT = {}
}
VBF = {}
VF = {
	POSITION3 = "POSITION3",
	COLOR3 = "COLOR3",
	NORMAL3 = "NORMAL3"
}
COLOR = {
	RED = "red",
	GREEN = "green",
	BLUE = "blue"
}

local dx11_vb = require("rendertiger.vertex_buffer")

local lib = {}
function lib.create_buffer()
	return {_INST = dx11_vb.new(),
			VBT = {},
			IBT = {}}
end

return lib