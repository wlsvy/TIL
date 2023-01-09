//Source By: https://www.shadertoy.com/view/4dVXRV

vec2 lightPos = vec2(0., .35);

float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float circle(vec2 p, float r, vec2 uv) {
 
    return length(p-uv)-r;
    
}

float scene(vec2 uv) {
    
   	float dst = circle(vec2(-.25,-.04),.1,uv);
    dst 	  = smin(dst, circle(vec2(-.12,.14),.1,uv), .125);
    dst 	  = min(dst, circle(vec2(-.5,-.25),.1,uv));
    dst 	  = min(dst, circle(vec2(.5,-.25),.1,uv));
    
   	return dst;
              
}

vec3 shade(vec2 uv) {
 
    float scn = scene(uv);
    vec3  col = vec3(0.,.5,.5);
    
    float s = 1.;
    if(scn <= 0.) {
     
        col = vec3(1., 0., 0.);
        s += .85;
        
    }

    vec2 lv = lightPos - uv;
    vec2 ld = normalize(lv);
    float a = length(lv);    
    
    float t = 0.;
    for(int i = 0; i < 128; i++) {
        if(t > a)
            break;
    	float dst = scene(uv+ld*t);
        t += dst * .85;
        if(dst < .0001) {
        	s -= .85;
            break;   
        }
    }
    col *= s;
    //col = vec3(ld,0.);
    
    float flare = 1.-smoothstep(0.,.25,distance(uv,lightPos));
    col += flare;
    
    return col;
    
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv    = (fragCoord.xy - iResolution.xy * .5) / iResolution.y;
    lightPos.x = .75 * sin(iTime);
    lightPos.y = .35;
    if(iMouse.z > 0.) {
        lightPos = 2. * (iMouse.xy / iResolution.xy) - 1.;
    }
	fragColor  = vec4(shade(uv),1.);
}