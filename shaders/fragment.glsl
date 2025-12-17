#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec4 FragPosLightSpace;
in vec3 ViewSpace;

out vec4 outColor;

uniform vec3 lightDir = vec3(0.0, 1.0, 0.0); 
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 objectColor = vec3(0.1, 0.4, 0.2);
uniform float time;
uniform sampler2D terrainTex;
uniform sampler2D shadowMap;
//uniform int useAlpha;


void main()
{


    vec3 norm = normalize(Normal);
    vec3 up = vec3(0.0, 1.0, 0.0);


    vec3 baseColor;

    
    if(texture(terrainTex,TexCoord).r == texture(terrainTex,TexCoord).g && texture(terrainTex,TexCoord).g == texture(terrainTex,TexCoord).b){
        baseColor = objectColor + (texture(terrainTex,TexCoord).rgb * 0.02);
    }else{
        baseColor = objectColor*0.4 + (texture(terrainTex,TexCoord).rgb);
    }
    

    float y = sin(0.05*time);  // sun never below horizon
    vec3 LD = normalize(vec3(0.0, y, cos(0.05*time)));

    //vec3 L = normalize(lightDir);
    vec3 L = LD;
    float diff = max(dot(norm, L), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 ambient = 0.4 * baseColor; 

    
    vec3 result = ambient + diffuse * baseColor;
    if(L.y < 0.0){
        ambient = 0.4 * baseColor; 
        result = ambient;

    }else{
    
        float intensity = length(diffuse);
        if(intensity > 0.9) intensity = 1.0;
        else intensity = 0.6;
        result *= intensity;
    }
    float distance = length(ViewSpace);

    float fogFactor = (distance - 100.0) / (300.0 - 100.0);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    if (fogFactor < 0.3) {
        fogFactor = 0.0;     
    } else if (fogFactor < 0.4) {
        fogFactor = 0.4;     
    } else if (fogFactor < 0.7){
        fogFactor = 0.7;      
    }else {
        fogFactor = 0.9;
    }


    vec3 finalColor = mix(result.rgb, vec3(0.14, 0.5, 0.7), fogFactor);

    outColor = vec4(finalColor, 1.0);
}
