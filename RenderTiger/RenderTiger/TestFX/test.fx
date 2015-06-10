cbuffer cb_per_obj {
	float4x4 mat_wvp; 
};

struct vs_input {
	float3 pos : POSITION;
    float4 color : COLOR;
};

struct vs_output {
	float4 pos  : SV_POSITION;
    float4 color : COLOR;
};

vs_output VS(vs_input vin) {
	vs_output vout;
	vout.pos = mul(float4(vin.pos, 1.0f), mat_wvp);
    vout.color = vin.color;    
    return vout;
}

float4 PS(vs_output pin) : SV_Target {
    return pin.color;
}

technique11 ColorTech {
    pass P0 {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
