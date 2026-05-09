export SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export Programa=ProyectoFinal

g++ -g "$SCRIPT_DIR/$Programa.cpp" "$SCRIPT_DIR/Camera.cpp" "$SCRIPT_DIR/DirectionalLight.cpp" "$SCRIPT_DIR/Light.cpp" "$SCRIPT_DIR/Material.cpp" "$SCRIPT_DIR/Mesh_tn.cpp" "$SCRIPT_DIR/Model.cpp" "$SCRIPT_DIR/PointLight.cpp" "$SCRIPT_DIR/Shader_light.cpp" "$SCRIPT_DIR/Skybox.cpp" "$SCRIPT_DIR/Sphere.cpp" "$SCRIPT_DIR/SpotLight.cpp" "$SCRIPT_DIR/Texture.cpp" "$SCRIPT_DIR/Window.cpp" -lGLEW -lGL -lglfw -lassimp -o "$SCRIPT_DIR/$Programa.out"