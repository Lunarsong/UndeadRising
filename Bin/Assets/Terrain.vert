attribute vec4 u_vPosition;
attribute vec2 u_vTexCoords;
attribute vec3 u_vNormal;
attribute vec4 u_vColor;

varying vec2 v_vTexCoord;
varying vec2 v_vTileTexCoord;
varying vec3 v_vNormal;
varying vec4 v_vColor;

void main()
{
    v_vColor = u_vColor;
    v_vNormal = u_vNormal;
    v_vTexCoord = u_vTexCoords;
    v_vTileTexCoord = u_vTexCoords * 512.0 * 2.0;
    
    gl_Position = mWorldViewProjection * u_vPosition;
}