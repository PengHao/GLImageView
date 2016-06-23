uniform vec4 a_frame;
uniform vec2 offset;
uniform mat4 u_mvpMatrix;
attribute vec2 TexCoordIn;
attribute vec4 a_position;
varying vec2 TexCoordOut;
void main()
{
    gl_Position = a_position * u_mvpMatrix;
    gl_Position.x += offset.x;
    gl_Position.y -= offset.y;
    TexCoordOut = TexCoordIn;

    
}