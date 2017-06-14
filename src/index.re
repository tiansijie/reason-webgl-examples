open Bs_webapi.Canvas;
open Bs_webapi.Dom;

let andThenGL (f: 'a => Bs_webapi.Canvas.WebGl.glT) => fun
| Some v => f v
| None => raise (Invalid_argument "Passed `None` to andThenGL");

let gl = document
    |> Document.getElementById "reason-webgl"
    |> andThenGL CanvasElement.getContextWebGl;

WebGl.clearColor gl 0.0 0.0 0.0 1.0;

let vertexPosBuffer = WebGl.createBuffer gl;
WebGl.bindBuffer gl WebGl._ARRAY_BUFFER vertexPosBuffer;

let vertices = Js.Typed_array.Float32Array.make [|-0.5, -0.5, 0.5, -0.5, 0.0, 0.5|];
WebGl.bufferFloatData gl WebGl._ARRAY_BUFFER vertices WebGl._STATIC_DRAW;

let vs = "\n attribute vec2 pos; \n void main() {\n gl_Position = vec4(pos, 0, 1);\n }";
let fs = "\n precision mediump float;\n void main() {\n gl_FragColor = vec4(0, 0.8, 0, 1);\n }";
let program = WebGl.createProgram gl;

let vertexShader = WebGl.createShader gl WebGl._VERTEX_SHADER;
let fragShader = WebGl.createShader gl WebGl._FRAGMENT_SHADER;

WebGl.shaderSource gl vertexShader vs;
WebGl.compileShader gl vertexShader;

WebGl.shaderSource gl fragShader fs;
WebGl.compileShader gl fragShader;

WebGl.attachShader gl program vertexShader;
WebGl.attachShader gl program fragShader;
WebGl.linkProgram gl program;
WebGl.useProgram gl program;

let vertexPos = WebGl.getAttribLocation gl program "pos";
WebGl.enableVertexAttribArray gl vertexPos;
WebGl.vertexAttribPointer gl vertexPos 2 WebGl._FLOAT (Js.Boolean.to_js_boolean false) 0 0;
WebGl.drawArrays gl WebGl._TRIANGLES 0 3;
