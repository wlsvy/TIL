//Source By: https://www.shadertoy.com/view/Xd3cRs
#define STEPS 128
#define SUN vec3(0,0,1)

float sphere(vec3 p, vec3 c, float r) {
    return length(p - c) - r;
}

float box(vec3 p, vec3 b) {
  	vec3 d = abs(p) - b;
  	return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}

float torus(vec3 p, vec2 t) {
  	vec2 q = vec2(length(p.xz)-t.x,p.y);
  	return length(q)-t.y;
}

float scene(vec3 p) {
    vec3 ballPos = vec3(sin(iTime) * 1.5, 0, 0);
    return min(
        max(
            sphere(p, ballPos, 1.0),
            -box(p - ballPos, vec3(.4, .4, 3.))
        ),
        torus((p - ballPos).xzy, vec2(1.5, 0.2))
	);
}

vec4 occlusion(vec2 fragCoord)
{
    vec3 pos = vec3(0,0,-2);
    vec3 dir = normalize(vec3((2. * fragCoord - iResolution.xy) / iResolution.y, 1));
    
    for(int i = 0; i < 64; i++) {
        float dist = scene(pos);
        pos += dir * dist;
    }
    
    if(pos.z > 3.0) {
        return clamp(vec4(pow(dot(dir, SUN), 4.0)), 0.0, 1.0);
    }
    
    return vec4(0.0);
}

float sunShafts(vec2 uv, vec2 fragCoord) {
    float sum = 0.0;
    vec2 stepV = (uv - vec2(.5)) / float(STEPS);
    
    for(int i = 0; i < STEPS; i++) {
        sum += occlusion(uv * iResolution.xy).w;
        uv -= stepV;
    }
    
    return sum / float(STEPS);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = fragCoord / iResolution.xy;
    float shafts = sunShafts(uv, fragCoord);
    
    fragColor = occlusion(fragCoord) + vec4(shafts);
}