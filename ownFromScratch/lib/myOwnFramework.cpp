#include "myOwnFramework.h"


#ifndef USE_FRAMEWORK__HAKUREI
    #define NO_PERMISSION   exitOnError("Oops, it seems you're not allowed to use this framework. Take it easy.");
#else
    #define NO_PERMISSION
#endif



void shutDown(int return_code)
{
    glfwTerminate();
    exit(return_code);
}

void exitOnError(String error)
{
    std::cerr << "Error: " << error << ENDL;
    shutDown(-1);
}

void init_GLFW(void)
{
    /* GLFW initialization */
    const int window_width = SCREEN_W, window_height = SCREEN_H;
    if (!glfwInit())
        shutDown(1);
    // Create OpenGL 3.x Core Profile Context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(window_width, window_height, TITLE, NULL, NULL);
    if(w == NULL)
    {
        std::cerr << "Could not open a window" << ENDL;
        shutDown(1);
    }
    glfwMakeContextCurrent(w);
    return;
}

void init_GLEW(void)
{
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        std::cerr << "ERROR: " << glewGetErrorString(GlewInitResult) << ENDL;
        shutDown(1);
    }
    return;
}

void GL_Initialization(void)
{
    init_GLFW();
    init_GLEW();
    COUT << "OpenGL version: " << glGetString(GL_VERSION) << ENDL;
    COUT << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << ENDL;
    return;
}

Hakurei::OpenScene* getScene()
{
    static Hakurei::OpenScene* scene = NULL;

    if(scene == NULL) {
        scene = new Hakurei::OpenScene();
    }
    return scene;
}










///////////////// SHADER PROGRAM /////////////////////

Uint8* fileContents(const char* srcf,Uint32* length)
{
    FILE* f = NULL;
    Uint8 buffer[BUFF_SIZE];
    Uint8* ret = NULL;
    int N;

    if((f=fopen(srcf,"rb")) == NULL)
    {
        CERR << "Error occurred: File " << srcf << " not found." << ENDL;
        exit(-1);
    }

    *length = 0;
    while((N=fread(buffer,sizeof(Uint8),BUFF_SIZE,f)) > 0)
    {
        if((ret = (Uint8*)realloc(ret,*length + BUFF_SIZE)) == NULL)
        {
            fclose(f);
            CERR << "Error occurred: Cannot (re)allocate return buffer." << ENDL;
            exit(-1);
        }
        for(int i=0;i<N;i++)
        {
            ret[*length] = buffer[i];
            (*length)++;
        }
    }

    fclose(f);
    return ret;
}

Hakurei::ShaderProgram::ShaderProgram(String vShader, String fShader)
{
    NO_PERMISSION
    attributes.clear();
    uniforms.clear();

    //---- CPU side for shader program
    Uint32 vLength, fLength;
    Uint8* vSource = fileContents(vShader.c_str(), &vLength);
    Uint8* fSource = fileContents(fShader.c_str(), &fLength);

    //---- GPU side (Load and compile)
    vShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderID, 1, (const GLchar**)&vSource, (const GLint*)&vLength);
    glCompileShader(vShaderID);
    fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderID, 1, (const GLchar**)&fSource, (const GLint*)&fLength);
    glCompileShader(fShaderID);

    //---- GPU side (link)
    progID = glCreateProgram();
    glAttachShader(progID, vShaderID);
    glAttachShader(progID, fShaderID);
    glLinkProgram(progID);

    //---- Get attributes location
    getAttributes();

    return;
}

void Hakurei::ShaderProgram::getAttributes()
{
    for(String attr : {ATTRIB_POSITION, ATTRIB_NORMAL, ATTRIB_TANGENT, ATTRIB_UV, ATTRIB_COLOR})
        attributes[attr] = glGetAttribLocation(progID, attr.c_str());
}

bool Hakurei::ShaderProgram::hasUniform(const String uniName)
{
    return uniforms.find(uniName) != uniforms.end();
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Uint32 val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1ui(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Sint32 val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1i(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const float val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1f(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const double val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1d(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Vec2f& val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform2fv(loc, 1, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Vec3f& val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform3fv(loc, 1, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Vec4f& val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform4fv(loc, 1, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const glm::mat2& val, bool transpose)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniformMatrix2fv(loc, 1, transpose, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const glm::mat3& val, bool transpose)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniformMatrix3fv(loc, 1, transpose, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const glm::mat4& val, bool transpose)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniformMatrix4fv(loc, 1, transpose, glm::value_ptr(val));
    }
}










///////////////// TEXTURE /////////////////////

Sint16 le_short(Uint8 *bytes)
{
    return bytes[0] | ((char)bytes[1] << 8);
}

size_t freadAt(void* buffer, size_t s1, size_t s2, FILE* f, Uint8 offset)
{
    if(offset != 0xFFFFFFFF) fseek(f,offset,SEEK_SET);
    return fread(buffer,s1,s2,f);
}

Uint32 getFileSize(FILE* f)
{
    Uint64 p = ftell(f);
    fseek(f,0,SEEK_END);
    Uint64 s = ftell(f);
    fseek(f,p,SEEK_SET);
    return (Uint32)(s);
}

void Hakurei::Texture::read_TGA(const char *filename)
{
    struct tga_header {
        Sint8  id_length;
        Sint8  color_map_type;
        Sint8  data_type_code;
        Uint8  color_map_origin[2];
        Uint8  color_map_length[2];
        Sint8  color_map_depth;
        Uint8  x_origin[2];
        Uint8  y_origin[2];
        Uint8  width[2];
        Uint8  height[2];
        Sint8  bits_per_pixel;
        Sint8  image_descriptor;
    } header;
    Uint32 i, color_map_size;
    FILE *f;
    size_t read;

    f = fopen(filename, "rb");

    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return;
    }

    read = fread(&header, 1, sizeof(header), f);

    if (read != sizeof(header)) {
        fprintf(stderr, "%s has incomplete tga header\n", filename);
        fclose(f);
        return;
    }
    if (header.data_type_code != 2) {
        fprintf(stderr, "%s is not an uncompressed RGB tga file\n", filename);
        fclose(f);
        return;
    }
    if (header.bits_per_pixel != 24 and header.bits_per_pixel != 32) {
        fprintf(stderr, "%s is not a 24-bit or 32-bit uncompressed RGB tga file but %i\n", filename, header.bits_per_pixel);
        fclose(f);
        return;
    }

    for (i = 0; i < header.id_length; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete id string\n", filename);
            fclose(f);
            return;
        }

    color_map_size = le_short(header.color_map_length) * (header.color_map_depth/8);
    for (i = 0; i < color_map_size; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete color map\n", filename);
            fclose(f);
            return;
        }

    w = le_short(header.width);
    h = le_short(header.height);
    d = (header.bits_per_pixel/8);
    Uint32 pixels_size = w * h * d;
    pixels = new Uint8[pixels_size];

    read = fread(pixels, 1, pixels_size, f);

    if (read != pixels_size) {
        fprintf(stderr, "%s has incomplete image\n", filename);
        delete [] pixels;
    }

    fclose(f);
}

void Hakurei::Texture::read_BMP(const char *filename)
{
    struct bmp_header {
        Uint16 magic;
        Uint32 file_size;
        Uint16 unused1;
        Uint16 unused2;
        Uint32 data_offset;
        Uint32 width;
        Uint32 height;
    } header;

    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return;
    }

    freadAt(&(header.magic), 1, sizeof(unsigned short), f, 0x0);
    freadAt(&(header.file_size), 1, sizeof(unsigned int), f, 0x2);
    freadAt(&(header.unused1), 1, sizeof(unsigned short), f, 0x6);
    freadAt(&(header.unused2), 1, sizeof(unsigned short), f, 0x8);
    freadAt(&(header.data_offset), 1, sizeof(unsigned int), f, 0xA);
    freadAt(&(header.width), 1, sizeof(unsigned int), f, 0x12);
    freadAt(&(header.height), 1, sizeof(unsigned int), f, 0x16);

    if (header.magic != 0x4D42) { // 0x4D42 = BM
        fprintf(stderr, "%s is not a Windows Bitmap file\n", filename);
        fclose(f);
        return;
    }
    if (header.file_size != getFileSize(f)) {
        fprintf(stderr, "%s has not a valid bmp header\n", filename);
        fclose(f);
        return;
    }

    w = header.width;
    h = header.height;

    Uint8* pixels = new unsigned char[w * h * 3];
    Sint32 size_of_row = (w * 3) + (4 - (w * 3) % 4) % 4;
    Uint8 tmp;
    Uint32 row_offset;

    printf("Size of row: %u Bytes\n",size_of_row);

    for(Sint32 j = 0; j < h; j++) {
        row_offset = header.data_offset + j * size_of_row;
        freadAt(&(pixels[j*w*3]), sizeof(Uint8), w*3, f, row_offset);
        for(Sint32 i = 0; i < w; i++) {
            // Swap (B, G, R) to (R, G, B)
            tmp = pixels[(j*w+i)*3];
            pixels[(j*w+i)*3] = pixels[(j*w+i)*3+2];
            pixels[(j*w+i)*3+2] = tmp;
        }
    }

    fclose(f);
}

Hakurei::Texture::Texture(const String &imagepath, GLenum wrap_s, GLenum wrap_t, GLenum mag_filter, GLenum min_filter, bool aniso)
{
    NO_PERMISSION
    pixels = NULL;
    w = 0;
    h = 0;
    d = 0;

    // Loading in CPU
    GLenum format = 0;
    GLenum type = 0;
    String file = PATH_RESOURCES + imagepath;


    if(strstr(imagepath.c_str(),".tga") != NULL)
    {
        read_TGA(file.c_str());
        format = GL_BGR;
        type = GL_UNSIGNED_BYTE;
    }
    else if(strstr(imagepath.c_str(),".bmp") != NULL)
    {
        read_BMP(file.c_str());
        format = GL_RGB;
        type = GL_UNSIGNED_BYTE;
    }


    // Uploading to GPU
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, format, type, pixels);

    // Wrapping
    wrapS = wrap_s;
    wrapT = wrap_t;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    // Filtering
    magF = mag_filter;
    minF = min_filter;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magF);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);

    // Anisotropy
    anisotropy = aniso;
    if(anisotropy)
    {
        GLfloat maxAniso = 0.0F;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,maxAniso);
    }
    else
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0F);
}










///////////////// MATERIAL /////////////////////

Hakurei::Material::Material(String vShader, String fShader)
{
    NO_PERMISSION
    useTexture = false;
    texture = NULL;
    String vertexSh = PATH_RESOURCES + vShader;
    String fragmentSh = PATH_RESOURCES + fShader;
    prog = new ShaderProgram(vertexSh, fragmentSh);
}

void Hakurei::Material::addTexture(Hakurei::Texture* _texture)
{
    texture = _texture;
    if(texture == NULL)
    {
        CERR << "Warning : Texture does not exist." << ENDL;
    }
    useTexture = true;
}










///////////////// MESH /////////////////////

Hakurei::Mesh::Mesh()
{
    NO_PERMISSION
    vertices.clear();
    triangles.clear();
    vbos.clear();
    ibo = 0;
    vao = 0;
    transformMatrix = glm::mat4(1.0f);
    defaultMatrix = glm::mat4(1.0f);
    _P = NULL;
    _N = NULL;
    _T = NULL;
    _U = NULL;
    _C = NULL;
    _I = NULL;
    length_p = 0;
    length_n = 0;
    length_t = 0;
    length_u = 0;
    length_c = 0;
    length_i = 0;

    //--------- Creation and activation
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Hakurei::Mesh::computeNormals()
{
    Vector<Vec3f> triangleNormal;
    triangleNormal.clear();

    Vec3f edge1;
    Vec3f edge2;
    for(Uint32 i=0; i<triangles.size(); i++)
    {
        edge1 = vertices[triangles[i].i1].position - vertices[triangles[i].i0].position;
        edge2 = vertices[triangles[i].i2].position - vertices[triangles[i].i0].position;
        triangleNormal.push_back( glm::normalize( glm::cross(edge1, edge2) ) );
    }

    Vec3f vertexNormal;
    for(Uint32 i=0; i<vertices.size(); i++)
    {
        vertexNormal = Vec3f(0,0,0);
        for(Uint32 j=0; j<triangles.size(); j++)
        {
            if(triangles[j].i0 == i || triangles[j].i1 == i || triangles[j].i2 == i)
            {
                vertexNormal += triangleNormal[j];
            }
        }
        vertices[i].normal = glm::normalize(vertexNormal);
    }

    triangleNormal.clear();
    return;
}

void Hakurei::Mesh::getPositions()
{
    // Convert vector to array
    length_p = vertices.size() * 3;
    _P = new float[length_p];
    for(int i=0; i<vertices.size(); i++)
    {
        _P[3*i+0] = vertices[i].position[0];
        _P[3*i+1] = vertices[i].position[1];
        _P[3*i+2] = vertices[i].position[2];
    }
}

void Hakurei::Mesh::getNormals(void)
{
    // Convert vector to array
    length_n = vertices.size() * 3;
    _N = new float[length_n];
    for(int i=0; i<vertices.size(); i++)
    {
        _N[3*i+0] = vertices[i].normal[0];
        _N[3*i+1] = vertices[i].normal[1];
        _N[3*i+2] = vertices[i].normal[2];
    }
}

void Hakurei::Mesh::getTangents()
{
    // Convert vector to array
    length_t = vertices.size() * 3;
    _T = new float[length_t];
    for(int i=0; i<vertices.size(); i++)
    {
        _T[3*i+0] = vertices[i].tangent[0];
        _T[3*i+1] = vertices[i].tangent[1];
        _T[3*i+2] = vertices[i].tangent[2];
    }
}

void Hakurei::Mesh::getUVs()
{
    // Convert vector to array
    length_u = vertices.size() * 2;
    _U = new float[length_u];
    for(int i=0; i<vertices.size(); i++)
    {
        _U[2*i+0] = vertices[i].uv[0];
        _U[2*i+1] = vertices[i].uv[1];
    }
}

void Hakurei::Mesh::getColors()
{
    // Convert vector to array
    length_c = vertices.size() * 4;
    _C = new float[length_c];
    for(int i=0; i<vertices.size(); i++)
    {
        _C[4*i+0] = vertices[i].color[0];
        _C[4*i+1] = vertices[i].color[1];
        _C[4*i+2] = vertices[i].color[2];
        _C[4*i+3] = vertices[i].color[3];
    }
}

void Hakurei::Mesh::getIndexes(void)
{
    // Convert vector to array
    length_i = triangles.size() * 3;
    _I = new Uint32[length_i];
    for(int i=0; i<triangles.size(); i++)
    {
        _I[3*i+0] = triangles[i].i0;
        _I[3*i+1] = triangles[i].i1;
        _I[3*i+2] = triangles[i].i2;
    }
}

void Hakurei::Mesh::createVBO(void)
{
    if(vertices.size() == 0)
        exitOnError("Cannot create VBO, the object has no vertex.");

    Uint32 vbo[5];
    glGenBuffers(5, vbo);
    // Position
    getPositions();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length_p, _P, GL_STATIC_DRAW);
    vbos[ATTRIB_POSITION] = vbo[0];
    // Normal
    getNormals();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length_n, _N, GL_STATIC_DRAW);
    vbos[ATTRIB_NORMAL] = vbo[1];
    // Tangent
    getTangents();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length_t, _T, GL_STATIC_DRAW);
    vbos[ATTRIB_TANGENT] = vbo[2];
    // UV
    getUVs();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length_u, _U, GL_STATIC_DRAW);
    vbos[ATTRIB_UV] = vbo[3];
    // Color
    getColors();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length_c, _C, GL_STATIC_DRAW);
    vbos[ATTRIB_COLOR] = vbo[4];

    // Clean state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Hakurei::Mesh::createIBO(void)
{
    if(triangles.size() == 0)
        exitOnError("Cannot create IBO, the object has no triangle.");

    glGenBuffers(1, &ibo);
    getIndexes();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Uint32) * length_i, _I, GL_STATIC_DRAW);

    // Clean state
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Hakurei::Mesh::createVAO(void)
{
    if(vao == 0)
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    glBindVertexArray(0);
    return;
}

void Hakurei::Mesh::transform(Uint8 transformType, Uint8 transformAction, Vec3f v, float angle)
{
    switch(transformAction)
    {
    case NO_TRANSFORM: break;
    case SET_TRANSFORM:
        switch(transformType)
        {
            case TRANSFORM_TRANSLATION: transformMatrix = glm::translate(transformMatrix, v); break;
            case TRANSFORM_ROTATION: transformMatrix = glm::rotate(transformMatrix, angle, v); break;
            case TRANSFORM_SCALE: transformMatrix = glm::scale(transformMatrix, v); break;
        }
        break;
    case SET_TRANSFORM_AS_DEFAULT: defaultMatrix = transformMatrix; break;
    case DEFAULT_TRANSFORM: transformMatrix = defaultMatrix; break;
    }
    return;
}

Bool Hakurei::Mesh::importOBJ(String OBJfile)
{
    Vector<Uint32> vertexIndices, uvIndices, normalIndices;
    Vector<Vec3f> temp_vertices;
    Vector<Vec2f> temp_uvs;
    Vector<Vec3f> temp_normals;
    String fullpath = PATH_RESOURCES + OBJfile;

    FILE* file = fopen(fullpath.c_str(),"r");
    if(file == NULL)
    {
        CERR << "OBJ File " << OBJfile << " not found." << ENDL;
        return false;
    }

    char lineHeader[256];
    while(true)
    {
        int res = fscanf(file, "%s", lineHeader);
        if(res == EOF) break;

        if(strcmp(lineHeader,"v") == 0) // vertex position
        {
            Vec3f vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if(strcmp(lineHeader,"vt") == 0) // vertex uv
        {
            Vec2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if(strcmp(lineHeader,"vn") == 0) // vertex normal
        {
            Vec3f normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if(strcmp(lineHeader,"f") == 0) // face
        {
            Uint32 vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if(matches != 9)
            {
                CERR << "Error occurred when reading OBJ file : cannot load object faces." << ENDL;
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    // fill Mesh data
    if(vertexIndices.size() != uvIndices.size() ||
       uvIndices.size() != normalIndices.size() ||
       normalIndices.size() != vertexIndices.size())
    {
        CERR << "Error : Not an valid OBJ file. There is not the same number of positions, normals and uvs indices." << ENDL;
        return false;
    }

    vertices.clear();
    triangles.clear();

    // VBO
    for(Uint32 i=0; i<vertexIndices.size(); i++)
    {
        Uint32 vertexInd = vertexIndices[i];
        Vec3f out_vertex = temp_vertices[vertexInd - 1];
        Uint32 uvInd = uvIndices[i];
        Vec2f out_uv = temp_uvs[uvInd - 1];
        Uint32 normalInd = normalIndices[i];
        Vec3f out_normal = temp_normals[normalInd - 1];

        vertices.push_back(Hakurei::Vertex(out_vertex, out_normal, Vec3f(), out_uv));
    }

    // IBO
    for(Uint32 i=0; i<vertexIndices.size(); i+=3)
    {
        triangles.push_back(Hakurei::Triangle(i, i+1, i+2));
    }

    return true;
}

void Hakurei::Mesh::resetObjectTransform()
{
    transform(TRANSFORM_ALL, DEFAULT_TRANSFORM);
}

void Hakurei::Mesh::setObjectTransformAsDefault()
{
    transform(TRANSFORM_ALL, SET_TRANSFORM_AS_DEFAULT);
}

// For debug purpose only //
/*
void Hakurei::Mesh::objData()
{
    COUT << "Object data:" << ENDL;
    COUT << "----- VBOS -----" << ENDL;
#ifdef __POSITION__
    COUT << "Position: " << vbos["position"] << ENDL;
    for(int i=0; i<length_p/3; i++)
        COUT << _P[3*i] << " " << _P[3*i+1] << " " << _P[3*i+2] << ENDL;
#endif
#ifdef __NORMAL__
    COUT << "Normal: " << vbos["normal"] << ENDL;
    for(int i=0; i<length_n/3; i++)
        COUT << _N[3*i] << " " << _N[3*i+1] << " " << _N[3*i+2] << ENDL;
#endif
#ifdef __TANGENT__
    COUT << "Tangent: " << vbos["tangent"] << ENDL;
    for(int i=0; i<length_t/3; i++)
        COUT << _T[3*i] << " " << _T[3*i+1] << " " << _T[3*i+2] << ENDL;
#endif
#ifdef __UV__
    COUT << "UV: " << vbos["uv"] << ENDL;
    for(int i=0; i<length_u/2; i++)
        COUT << _U[2*i] << " " << _U[2*i+1] << ENDL;
#endif
#ifdef __COLOR__
    COUT << "Color: " << vbos["color"] << ENDL;
    for(int i=0; i<length_c/4; i++)
        COUT << _C[4*i] << " " << _C[4*i+1] << " " << _C[4*i+2] << " " << _C[4*i+3] << ENDL;
#endif
#ifdef __INDEX__
    COUT << "----- IBO -----" << ENDL;
    COUT << "Index: " << ibo << ENDL;
    for(int i=0; i<length_i/3; i++)
        COUT << _I[3*i] << " " << _I[3*i+1] << " " << _I[3*i+2] << ENDL;
#endif
#ifdef __VAO__
    COUT << "----- VAO -----" << ENDL;
    COUT << "Vao: " << vao << ENDL;
    COUT << "----- Shader program -----" << ENDL;
    COUT << "progId: " << mat->prog->progID << ENDL;
#endif
}
*/










///////////////// KEY HANDLER /////////////////////

Hakurei::KeyHandler::KeyHandler(Bool _keyRepeat)
{
    NO_PERMISSION
    for(int i=0; i<GLFW_KEYS; i++)
        key[i] = false;
    keyRepeat = _keyRepeat;
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, GL_TRUE);
}

void Hakurei::KeyHandler::enableKeyRepeat()
{
    keyRepeat = true;
}

void Hakurei::KeyHandler::disableKeyRepeat()
{
    keyRepeat = false;
}

void Hakurei::KeyHandler::update()
{
    static Bool oldContext[GLFW_KEYS]; // used only when keyRepeat is disabled
    static Bool initialized = false;

    if(!initialized)
    {
        for(int k=0; k<GLFW_KEYS; k++)
            oldContext[k] = false;
        initialized = true;
    }

    GLFWwindow* window = glfwGetCurrentContext();
    glfwPollEvents();
    for(int k=0; k<GLFW_KEYS; k++)
    {
        if(glfwGetKey(window,k) == GLFW_PRESS) // key pressed
        {
            if(!keyRepeat && oldContext[k])
            {
                key[k] = false;
            }
            else
            {
                key[k] = true;
                oldContext[k] = true;
            }
        }
        else if(glfwGetKey(window,k) == GLFW_RELEASE) // key released
        {
            key[k] = false;
            oldContext[k] = false;
        }
    }
    return;
}

Bool Hakurei::KeyHandler::pressed(Sint32 k)
{
    return key[k];
}

void Hakurei::KeyHandler::resetKeyState()
{
    for(int i=0; i<GLFW_KEYS; i++)
        key[i] = false;
}










///////////////// OPEN CAMERA /////////////////////

Hakurei::OpenCamera::OpenCamera()
{
    NO_PERMISSION
    position = Vec3f(0,0,5);
    FoV = PI / 4.0f;
    angleV = PI;
    angleH = 0;
    camSpeed = 3.0f;
    angleSpeed = 1.5f;
    mouseX = SCREEN_W/2;
    mouseY = SCREEN_H/2;
    glfwSetCursorPos(glfwGetCurrentContext(), mouseX, mouseY);

}

void Hakurei::OpenCamera::moveCameraFromInputs()
{
    GLFWwindow* window = glfwGetCurrentContext();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);

    // Get mouse position
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Bool rotated = false;
    Vec3f oldDirection = direction;

    // Rotate up
    if(KEY_PRESSED(GLFW_KEY_UP))
    {
        angleV += deltaTime * angleSpeed;
        rotated = true;
    }

    // Rotate down
    if(KEY_PRESSED(GLFW_KEY_DOWN))
    {
        angleV -= deltaTime * angleSpeed;
        rotated = true;
    }

    // Rotate left
    if(KEY_PRESSED(GLFW_KEY_LEFT))
    {
        angleH += deltaTime * angleSpeed;
        rotated = true;
    }

    // Rotate right
    if(KEY_PRESSED(GLFW_KEY_RIGHT))
    {
        angleH -= deltaTime * angleSpeed;
        rotated = true;
    }

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = Vec3f(  cos(angleV) * sin(angleH),
                        sin(angleV),
                        cos(angleV) * cos(angleH));

    // Right vector
    rightvector = Vec3f(sin(angleH - PI/2.0f),
                        0,
                        cos(angleH - PI/2.0f));

    // Up vector
    upvector = glm::cross(rightvector, direction);

    // Move forward ^
    if(KEY_PRESSED(GLFW_KEY_W))
    {
        position += direction * deltaTime * camSpeed;
    }

    // Move backward v
    if(KEY_PRESSED(GLFW_KEY_S))
    {
        position -= direction * deltaTime * camSpeed;
    }

    // Move right >
    if(KEY_PRESSED(GLFW_KEY_D))
    {
        position += rightvector * deltaTime * camSpeed;
    }

    // Move left <
    if(KEY_PRESSED(GLFW_KEY_A))
    {
        position -= rightvector * deltaTime * camSpeed;
    }

    // Move up ^
    if(KEY_PRESSED(GLFW_KEY_Q))
    {
        position += upvector * deltaTime * camSpeed;
    }

    // Move down v
    if(KEY_PRESSED(GLFW_KEY_Z))
    {
        position -= upvector * deltaTime * camSpeed;
    }

    if(rotated) // move camera around target position
    {
        position += Vec3f(oldDirection - direction) * 5.0f;
    }
    lastTime = currentTime;
}










///////////////// OPEN SCENE /////////////////////

Hakurei::OpenScene::OpenScene()
{
    NO_PERMISSION
    objects.clear();
    materials.clear();
    diffuse = glm::vec3(0.9, 0.9, 0.9);
    specular = glm::vec3(0.6, 0.6, 0.6);
    lightdir = glm::vec3(0.0, 0.0, 0.0);
    lightcolor = glm::vec3(0.6, 0.6, 0.6);
    ambient = glm::vec3(0.4, 0.4, 0.4);
    shininess = 80.0f;
    camera = new Hakurei::OpenCamera();
    kh = new Hakurei::KeyHandler();
    kh->enableKeyRepeat();
}

void Hakurei::OpenScene::updateCamera()
{
    projectionMatrix = glm::perspective(camera->FoV, ((float) SCREEN_W) / ((float) SCREEN_H), 0.1f, 100.0f);
    viewMatrix = glm::lookAt(camera->position,
                             camera->position + camera->direction,
                             camera->upvector);
    normalMatrix = glm::inverse(glm::transpose(glm::mat3(viewMatrix)));
    MVP = projectionMatrix * viewMatrix;
}

Hakurei::Mesh* Hakurei::OpenScene::getObjectByName(String objName)
{
    if(objects[objName] == NULL)
    {
        COUT << "Warning : Object " << objName << " does not exist." << ENDL;
        return NULL;
    }
    return objects[objName];
}

Hakurei::Material* Hakurei::OpenScene::getMaterialByName(String matName)
{
    if(materials[matName] == NULL)
    {
        COUT << "Warning : Material " << matName << " does not exist." << ENDL;
        return NULL;
    }
    return materials[matName];
}

void Hakurei::OpenScene::addMaterial(String mat_name, Hakurei::Material* material)
{
    if(materials[mat_name] != NULL)
    {
        COUT << "Warning : Material " << mat_name << " is already set." << ENDL;
        return;
    }
    materials[mat_name] = material;
    return;
}

void Hakurei::OpenScene::removeMaterial(String mat_name)
{
    if(materials[mat_name] == NULL)
    {
        COUT << "Warning : Material " << mat_name << " does not exist." << ENDL;
        return;
    }

    delete materials[mat_name]->prog;
    if(materials[mat_name]->useTexture)
    {
        delete[] materials[mat_name]->texture->pixels;
        delete materials[mat_name]->texture;
    }
    delete materials[mat_name];
    materials[mat_name] = NULL;
    return;
}

void Hakurei::OpenScene::addObject(String obj_name, Hakurei::Mesh* object)
{
    if(objects[obj_name] != NULL)
    {
        COUT << "Warning : Object " << obj_name << " is already set." << ENDL;
        return;
    }

    object->createVBO();
    object->createIBO();
    object->createVAO();
    objects[obj_name] = object;
    return;
}

void Hakurei::OpenScene::removeObject(String obj_name)
{
    if(objects[obj_name] == NULL)
    {
        COUT << "Warning : Object " << obj_name << " does not exist." << ENDL;
        return;
    }

    delete[] objects[obj_name]->_P;
    delete[] objects[obj_name]->_N;
    delete[] objects[obj_name]->_T;
    delete[] objects[obj_name]->_U;
    delete[] objects[obj_name]->_C;
    delete[] objects[obj_name]->_I;
    delete objects[obj_name];
    objects[obj_name] = NULL;
    return;
}

void Hakurei::OpenScene::drawObject(String objName, String matName)
{
    static std::map<String, bool> warnObj;
    static std::map<String, bool> warnMat;

    Hakurei::Mesh *obj = objects[objName];
    Hakurei::Material *mat = materials[matName];
    if(obj == NULL)
    {
        if(!warnObj[objName]) std::cerr << "Warning : there is no object named " << objName << ENDL;
        warnObj[objName] = true;
        return;
    }
    if(mat == NULL)
    {
        if(!warnMat[matName]) std::cerr << "Warning : there is no material named " << matName << ENDL;
        warnMat[matName] = true;
        return;
    }

    // Shader program
    glUseProgram(mat->prog->progID);

    // Update uniforms
    updateProgramUniforms(mat->prog, obj, mat);

    // VAO activation
    glBindVertexArray(obj->vao);


/** Allow to use of any object with any material **/
    // VBOs
    Sint32 loc;
    Map<String, Uint32> size_attr;
    size_attr[ATTRIB_POSITION] = 3;
    size_attr[ATTRIB_NORMAL] = 3;
    size_attr[ATTRIB_TANGENT] = 3;
    size_attr[ATTRIB_UV] = 2;
    size_attr[ATTRIB_COLOR] = 4;
    for(String attr : {ATTRIB_POSITION, ATTRIB_NORMAL, ATTRIB_TANGENT, ATTRIB_UV, ATTRIB_COLOR})
    {
        loc = mat->prog->attributes[attr];
        if(loc != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, obj->vbos[attr]);
            glVertexAttribPointer(loc, size_attr[attr], GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(loc);
        }
    }
    // IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ibo);
/** It seems to work **/

    // Drawing routine
    glDrawElements(GL_TRIANGLES, obj->length_i, GL_UNSIGNED_INT, 0);

    // Clean state again
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void Hakurei::OpenScene::initDrawingScene()
{
    typedef Map<String, Hakurei::Mesh*>::iterator it_type;
    for(it_type iterator = objects.begin(); iterator != objects.end(); iterator++) {
        iterator->second->resetObjectTransform();
    }
    textureUnit = -1;
}

void Hakurei::OpenScene::drawObjectInScene(String object, String material)
{
    Hakurei::Mesh* obj = objects[object];
    Hakurei::Material* mat = materials[material];
    if(obj == NULL)
    {
        CERR << "Object " << object << " does not exist." << ENDL;
        return;
    }
    if(mat == NULL)
    {
        CERR << "Object " << object << " does not exist." << ENDL;
        return;
    }

    if(mat->useTexture)
    {
        textureUnit++;

        Uint32 textureId = mat->texture->textureID;
        Uint32 progId = mat->prog->progID;

        // activate the texture unit (here GL_TEXTURE_0)
        glActiveTexture(GL_TEXTURE0 + textureUnit);

        // bind the texture
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mat->texture->wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mat->texture->wrapT);

        // Filtering
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mat->texture->magF);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mat->texture->minF);*/
        // Mipmaps
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Anisotropy
        if(mat->texture->anisotropy)
        {
            GLfloat maxAniso = 0.0F;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,maxAniso);
        }
        else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0F);

        // associate the chosen texture unit to the GLSL sampler
        glUseProgram(progId);
        mat->prog->setUniform("colormap",textureUnit);
        glUseProgram(0);
    }

    // call the drawing routine
    drawObject(object, material);
    return;
}

void Hakurei::OpenScene::updateProgramUniforms(ShaderProgram* prog, Hakurei::Mesh* obj, Hakurei::Material* mat)
{
    // REQUIRED UNIFORMS //
    prog->setUniform("mvp", MVP);
    prog->setUniform("transformMatrix", obj->transformMatrix);
    prog->setUniform("viewMatrix", viewMatrix);
    prog->setUniform("normalMatrix", normalMatrix);
    // ----------------- //

    // light stuff //
    prog->setUniform("hasTexture", (int)(mat->useTexture));
    prog->setUniform("lightdir", lightdir);
    prog->setUniform("lightcolor", lightcolor);
    prog->setUniform("ambient", ambient);
    prog->setUniform("diffuse", diffuse);
    prog->setUniform("specular", specular);
    prog->setUniform("shininess", shininess);
    // ----------------- //
}









///// FUNCTIONS USED IN MAIN LOOP /////

void swapBuffers()
{
    GLFWwindow* w = glfwGetCurrentContext();
    glfwSwapBuffers(w);
}

void updateStuff()
{
    KEY_UPDATE;
    CAMERA_UPDATE;
}

void enableThings()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
}

void disableThings()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}
