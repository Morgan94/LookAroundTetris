#include "Hakurei_Mesh.h"


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


String Hakurei::Mesh::fixObjFile(String OBJfile)
{
    String fixedOBJ = OBJfile + ".fixed";
    FILE* src = fopen(OBJfile.c_str(),"r");
    if(src == NULL)
    {
        CERR << "OBJ File " << OBJfile << " not found." << ENDL;
        return "";
    }
    FILE* dst = fopen(fixedOBJ.c_str(),"w");
    if(dst == NULL)
    {
        CERR << "Cannot create new OBJ file." << ENDL;
        fclose(src);
        return "";
    }

    char cbuffer[256];
    String buffer;
    Sint32 pos;
    while(fgets(cbuffer,256,src) != NULL)
    {
        buffer = String(cbuffer);
        while((pos = buffer.find("//")) != String::npos)
        {
            String left = buffer.substr(0,pos);
            String right = buffer.substr(pos+2);
            buffer = left + "/0/" + right;
        }
        fprintf(dst,"%s",buffer.c_str());
    }

    fclose(src);
    fclose(dst);
    return fixedOBJ;
}


Bool Hakurei::Mesh::importOBJ(String OBJfile, Bool deleteFixedOBJ)
{
    Vector<Uint32> vertexIndices, uvIndices, normalIndices;
    Vector<Vec3f> temp_vertices;
    Vector<Vec2f> temp_uvs;
    Vector<Vec3f> temp_normals;

    String fullpath = fixObjFile(PATH_RESOURCES + OBJfile);
    if(fullpath.size() == 0)
    {
        return false;
    }

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
                CERR << "Error occurred while reading OBJ file : cannot load object faces." << ENDL;
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
        CERR << "--- Positions: " << vertexIndices.size() << " | UVs: " << uvIndices.size() << " | Normals: " << normalIndices.size() << ENDL;
        return false;
    }

    vertices.clear();
    triangles.clear();

    // VBO
    Vec3f out_vertex;
    Vec2f out_uv;
    Vec3f out_normal;
    for(Uint32 i=0; i<vertexIndices.size(); i++)
    {
        if(temp_vertices.size() == 0) out_vertex = Vec3f();
        else out_vertex = temp_vertices[vertexIndices[i] - 1];
        if(temp_uvs.size() == 0) out_uv = Vec2f();
        else out_uv = temp_uvs[uvIndices[i] - 1];
        if(temp_normals.size() == 0) out_normal = Vec3f();
        else out_normal = temp_normals[normalIndices[i] - 1];

        vertices.push_back(Hakurei::Vertex(out_vertex, out_normal, Vec3f(), out_uv));
    }

    // IBO
    for(Uint32 i=0; i<vertexIndices.size(); i+=3)
    {
        triangles.push_back(Hakurei::Triangle(i, i+1, i+2));
    }

    if(deleteFixedOBJ)
        remove(fullpath.c_str());

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



void Hakurei::Mesh::createCube(float w, float d, float h, Vec4f color)
{
    if(w <= 0 || d <= 0 || h <= 0)
    {
        CERR << "Warning : dimensions must be positive." << ENDL;
        return;
    }


}

