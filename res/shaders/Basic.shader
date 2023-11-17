#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main(){
	gl_Position = position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 iResolution;
uniform float iTime;
vec2 fragCoord = gl_FragCoord.xy;

void main(){
	vec2 uv = fragCoord/iResolution.xy;
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    fragColor = vec4(col,1.0);
};