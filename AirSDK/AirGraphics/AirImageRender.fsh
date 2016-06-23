precision mediump float;
varying vec2 TexCoordOut;
uniform     sampler2D s_texture;
void main()
{
    float w = TexCoordOut.x - 0.5;
    float h = TexCoordOut.y - 0.5;
    float t = w * w + h * h;
    if (t > 0.25) {
        discard;
    } else if (t > 0.20) {
        gl_FragColor = vec4(1.0,1.0,1.0,1.0);
    } else {
        gl_FragColor = texture2D(s_texture, TexCoordOut);
    }
}