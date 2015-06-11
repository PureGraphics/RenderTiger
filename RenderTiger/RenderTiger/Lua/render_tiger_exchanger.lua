local script = ...

package.path = "Lua/?.lua;"

local error_msg = require("rendertiger.error_msg")
local em = error_msg.new()
local f, err = load(script)
if f == nil then
	error_msg.add(em, err)
	return
end

f()

--require("render_tiger_lib")
if BUFFER == nil then
	error_msg.add(em, "[ERROR] You haven't creat BUFFER object.")
	return
elseif VBF == nil then
	error_msg.add(em, "ERROR] You haven't set VBF(Vertex Buffer Format).")
	return
end

local dx11_vb = require("rendertiger.vertex_buffer")
local vbp = BUFFER._INST

for i = 1, #VBF do
	dx11_vb.add_layout_element(vbp, VBF[i])
end

for i = 1, #(BUFFER.VBT) do
	local f = BUFFER.VBT[i]
	local t = type(f)
	if t == "number" then
		dx11_vb.add_vb_element(vbp, f)
	elseif t == "string" then
		if f == COLOR.RED then
			dx11_vb.add_vb_element(vbp, 1.0)
			dx11_vb.add_vb_element(vbp, 0.0)
			dx11_vb.add_vb_element(vbp, 0.0)
		elseif f == COLOR.GREEN then
			dx11_vb.add_vb_element(vbp, 0.0)
			dx11_vb.add_vb_element(vbp, 1.0)
			dx11_vb.add_vb_element(vbp, 0.0)
		elseif f == COLOR.BLUE then
			dx11_vb.add_vb_element(vbp, 0.0)
			dx11_vb.add_vb_element(vbp, 0.0)
			dx11_vb.add_vb_element(vbp, 1.0)
		end
	end
end

for i = 1, #(BUFFER.IBT) do
	dx11_vb.add_ib_element(vbp, BUFFER.IBT[i])
end

dx11_vb.flush()