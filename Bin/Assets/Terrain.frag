uniform float u_fSizeX;
uniform float u_fSizeY;
uniform vec3  u_vLightDirection;

uniform sampler2D s_Texture01;
uniform sampler2D s_Texture02;
uniform sampler2D s_Texture03;
uniform sampler2D s_Texture04;
uniform sampler2D s_Texture05;
uniform sampler2D s_Texture06;

varying vec2 v_vTexCoord;
varying vec2 v_vTileTexCoord;
varying vec3 v_vNormal;
varying vec4 v_vColor;
    
void main()
{
    vec4 texel0 = texture2D(s_Texture01, v_vTileTexCoord).rgba;
    vec4 texel1 = texture2D(s_Texture02, v_vTileTexCoord).rgba;
    vec4 texel2 = texture2D(s_Texture03, v_vTileTexCoord).rgba;
    vec4 texel3 = texture2D(s_Texture04, v_vTileTexCoord).rgba;
    vec4 texel4 = texture2D(s_Texture05, v_vTileTexCoord).rgba;

    vec4 vBlendColor = texture2D(s_Texture06, v_vTexCoord).rgba;
    float fInverse = clamp(1.0 - (vBlendColor.r + vBlendColor.g + vBlendColor.b + vBlendColor.a), 0.0, 1.0);

    vec4 vFinalColor = texel0 * vBlendColor.r + texel1 * vBlendColor.g + texel2 * vBlendColor.b + texel3 * vBlendColor.a + texel4 * fInverse;

    float fLightIntensity = dot( v_vNormal, u_vLightDirection );
    gl_FragColor = vFinalColor * max( 0.2, fLightIntensity );
    gl_FragColor.a = 1.0f;
}