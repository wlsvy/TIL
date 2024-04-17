//Source By: https://www.shadertoy.com/view/4lGGzG

#define _ParticlesAmount 10

float rnd(float x)
{
    return fract(sin(dot(vec2(x + 47.49,38.2467 / (x + 2.3)), vec2(12.9898, 78.233))) * (43758.5453));
}

float drawRect(vec2 uv, vec2 bottomLeft, vec2 topRight, float d) {
	float ret;
	ret = smoothstep(bottomLeft.x-d, bottomLeft.x+d, uv.x);
	ret *= smoothstep(bottomLeft.y-d, bottomLeft.y+d, uv.y);
	ret *= 1.0 - smoothstep(topRight.y-d, topRight.y+d, uv.y);
	ret *= 1.0 - smoothstep(topRight.x-d, topRight.x+d, uv.x);
	return ret;
}

vec4 alphaBlend(vec4 base, vec4 blend)
{
    return vec4(base.rgb * base.a * (1.0 - blend.a) + blend.rgb * blend.a, blend.a + base.a * (1.0 - blend.a));   
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = (2.0 * fragCoord.xy - iResolution.xy) / min(iResolution.x, iResolution.y);
    fragColor = vec4(0.976, 0.937, 0.835, 1.0);
    
    float j;
    float move_max = 1.0;
    vec2 spawn_center = vec2(0.0, -0.1);
    vec2 spawn_size = vec2(1.0, 1.0);
    vec2 rect_size = vec2(0.03);
    
    for (int i = 0; i < _ParticlesAmount; i++)
    {
        j = float(i);
        float rnd1 = rnd(cos(j));
        float delayedTime = (0.2 + 0.2 * rnd1) * iTime;
        float d = floor(delayedTime / move_max);
        float rnd2 = rnd(j * d);
        float rnd3 = rnd(j * j * d);
        float r = delayedTime / move_max - d;
        float x_wave = 0.03 * sin(delayedTime * 7.0 + 6.282 / j);
        vec2 spawn = vec2(rnd2, rnd3) * spawn_size - spawn_size * 0.5;
        float ease = pow(2.0, 10.0 * (r - 1.0));
        float y_move = -1.0 * move_max * ease + move_max * 0.5;
        float opacity = 1.0 - ease - pow(2.0, -30.0 * r);
        float scale = 1.0 - 0.8 * rnd1 + 0.05 * sin(1.5 * iTime + 6.282 / j);
        vec2 center = (uv + spawn_center + spawn + vec2(x_wave, y_move)) * scale;
        fragColor = alphaBlend(fragColor, vec4(vec3(0.0, 0.0, 0.0), 0.5 * opacity * drawRect(center, rect_size * -1.0, rect_size, 0.01)));
        fragColor = alphaBlend(fragColor, vec4(vec3(1, 0.647, 0), 0.1 * opacity * drawRect(center, rect_size * -2.0, rect_size * 2.0, 0.1)));
    }
}
