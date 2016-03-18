#include "myOwnOpenGLProg.h"



/***** MESH CREATION *****/

void createDiamonds(Hakurei::Mesh* mesh, Uint32 nbDiamonds, Uint32 nbFaces, float dFromCenter, float diameter)
{
    mesh->vertices.clear();
    mesh->triangles.clear();

    // VBO
    for(Uint32 index=0; index<nbDiamonds; index++) createDiamond(mesh, index, nbDiamonds, nbFaces, dFromCenter, diameter);

    // IBO
    linkDiamonds(mesh, nbDiamonds, nbFaces);

    return;
}

Vec2f computeUV(char segment, Uint32 index, Uint32 nbEm, double phi)
{
    float X = 0;
    float Y = 0;

    switch(segment)
    {
    case SEG_TOP:
        X = ( (float)(index) + 0.5 ) / ( (float)(nbEm) );
        Y = 0.5;
        break;
    case SEG_1:
        X = ( (float)(index) + 0.5 + (cos(phi) / 2.7) ) / ( (float)(nbEm) );
        Y = 0.5 + (sin(phi) / 2.7);
        break;
    case SEG_2:
        X = ( (float)(index) + 0.5 + (cos(phi) / 2.3) ) / ( (float)(nbEm) );
        Y = 0.5 + (sin(phi) / 2.3);
        break;
    case SEG_BOT:
        X = ( (float)(index) + 0.5 ) / ( (float)(nbEm) );
        Y = 0.5;
        break;
    }

    return Vec2f(X,Y);
}


void createDiamond(Hakurei::Mesh* mesh, Uint32 index, Uint32 nbDia, Uint32 nbFaces, float dFromCenter, float diameter)
{
    std::vector<Vec3f> vertices;
    std::vector<Vec2f> uvs;
    double theta, phi;
    float h = diameter / 4.0;
    float H = diameter / 1.7;
    float r = diameter / 4.0;
    float R = diameter / 2.0;
    float D = dFromCenter;
    float X,Y;

    theta = ((double)(index) / (double)(nbDia)) * 2.0 * PI;

    // Point 0 : top of emerald
    vertices.push_back(Vec3f(D * cos(theta), D * sin(theta), h * 1.2));
    uvs.push_back(computeUV(SEG_TOP,index,nbDia,0));

    // Points of first segment
    for(Uint32 i=0; i<nbFaces; i++)
    {
        phi = ((double)(i) / (double)(nbFaces)) * 2.0 * PI;
        X = D * cos(theta) + r * cos(phi);
        Y = D * sin(theta) + r * sin(phi);
        vertices.push_back(Vec3f(X,Y,h));
        uvs.push_back(computeUV(SEG_1,index,nbDia,phi));
    }

    // Points of second segment
    for(Uint32 i=0; i<nbFaces; i++)
    {
        phi = ((double)(i) / (double)(nbFaces)) * 2.0 * PI;
        X = D * cos(theta) + R * cos(phi);
        Y = D * sin(theta) + R * sin(phi);
        vertices.push_back(Vec3f(X,Y,0.0));
        uvs.push_back(computeUV(SEG_2,index,nbDia,phi));
    }

    // Last point : bottom of emerald
    vertices.push_back(Vec3f(D*cos(theta),D*sin(theta),-H));
    uvs.push_back(computeUV(SEG_BOT,index,nbDia,0));

    // vertex color
    Vec4f colors[7] = {  Vec4f(1.0,0.0,0.0,1.0),
                        Vec4f(0.0,0.0,1.0,1.0),
                        Vec4f(1.0,1.0,0.0,1.0),
                        Vec4f(0.0,1.0,0.0,1.0),
                        Vec4f(0.7,0.7,0.7,1.0),
                        Vec4f(0.0,1.0,1.0,1.0),
                        Vec4f(1.0,0.0,1.0,1.0)};

    for(Uint32 i=0; i<vertices.size(); i++)
    {
        // Hot fix //
        float xFixed = vertices[i][0];
        float yFixed = -vertices[i][2];
        float zFixed = -vertices[i][1];
        // ------- //
        mesh->vertices.push_back(Hakurei::Vertex(Vec3f(xFixed,yFixed,zFixed), Vec3f(), Vec3f(), uvs[i], colors[index]));
    }
}

void linkDiamonds(Hakurei::Mesh* mesh, Uint32 nbDiamonds, Uint32 nbFaces)
{
    std::vector<Hakurei::Triangle> triangles;
    GLuint v0;

    for(Uint32 k=0; k<nbDiamonds; k++)
    {
        v0 = k * (2 + 2 * nbFaces);
        triangles.clear();

        for(Uint32 i=0; i<nbFaces; i++)
        {
            triangles.push_back(Hakurei::Triangle(v0, v0 + 1 + i%nbFaces, v0 + 1 + (i+1)%nbFaces));
            triangles.push_back(Hakurei::Triangle(v0 + 1 + i%nbFaces, v0 + 1 + nbFaces + i%nbFaces, v0 + 1 + nbFaces + (i+1)%nbFaces));
            triangles.push_back(Hakurei::Triangle(v0 + 1 + i%nbFaces, v0 + 1 + nbFaces + (i+1)%nbFaces, v0 + 1 + (i+1)%nbFaces));
            triangles.push_back(Hakurei::Triangle(v0 + 1 + nbFaces + i%nbFaces, v0 + 2 * nbFaces + 1, v0 + 1 + nbFaces + (i+1)%nbFaces));
        }

        // build in
        for(Uint32 i=0; i<triangles.size(); i++)
        {
            // Hot fix //
            Uint32 indexFixed = triangles[i].i0;
            triangles[i].i0 = triangles[i].i2;
            triangles[i].i2 = indexFixed;
            // ------- //
            mesh->triangles.push_back(triangles[i]);
        }
    }
}

/***** ------------------------------------------------------------ *****/






void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    // Materials
    Hakurei::Material* mat1 = new Hakurei::Material("simple.v.glsl","simple.f.glsl");
    scene->addMaterial("mat_simple",mat1);

    Hakurei::Material* mat2 = new Hakurei::Material("texture.v.glsl","texture.f.glsl");
    Hakurei::Texture* text2 = new Hakurei::Texture("sonic_body.tga");
    mat2->addTexture(text2);
    scene->addMaterial("mat_text",mat2);

    Hakurei::Material* mat3 = new Hakurei::Material("light.v.glsl","light.f.glsl");
    scene->addMaterial("mat_light",mat3);

    Hakurei::Material* mat4 = new Hakurei::Material("light.v.glsl","light.f.glsl");
    Hakurei::Texture* text4 = new Hakurei::Texture("sonic_body.tga");
    mat4->addTexture(text4);
    scene->addMaterial("mat_light_text",mat4);


    // Meshes
    Hakurei::Mesh* obj1 = new Hakurei::Mesh();
    createDiamonds(obj1, 7, 12, 2.0, 0.9);
    obj1->computeNormals();
    scene->addObject("diamonds",obj1);

    Hakurei::Mesh* obj2 = new Hakurei::Mesh();
    if(obj2->importOBJ("sonic.obj"))
    {
        obj2->transform(TRANSFORM_ROTATION, SET_TRANSFORM, Vec3f(0,0,1), PI);
        obj2->transform(TRANSFORM_SCALE, SET_TRANSFORM, Vec3f(0.15, 0.15, 0.15));
        obj2->transform(TRANSFORM_TRANSLATION, SET_TRANSFORM, Vec3f(0,-7.0,0));
        obj2->setObjectTransformAsDefault();
        scene->addObject("sonic",obj2);
    }

    return;
}


int item = 0;
void drawScene()
{
    Hakurei::OpenScene* scene = getScene();

    scene->initDrawingScene();
    enableThings();

    // move light spot with time
    scene->lightdir = Vec3f(cos(glfwGetTime()), 1.0, sin(glfwGetTime()));


    switch(item)
    {
    case 0: scene->drawObjectInScene("diamonds","mat_simple"); break;
    case 1: scene->drawObjectInScene("sonic","mat_text"); break;
    case 2: scene->drawObjectInScene("diamonds","mat_light"); break;
    case 3: scene->drawObjectInScene("sonic","mat_light_text"); break;
    case 4: scene->drawObjectInScene("diamonds","mat_light");
            scene->drawObjectInScene("sonic","mat_light_text");
            break;
    }


    disableThings();
    return;
}


void mainLoop(void)
{
    GLFWwindow* window = glfwGetCurrentContext();
    // this just loops as long as the program runs
    do
    {
        // Rendering
        drawScene();
        swapBuffers();

        updateStuff();
        if(KEY_PRESSED(GLFW_KEY_1)) {if(item != 0) {item = 0; COUT << "Item 1 : Diamonds with simple color, no lightning." << ENDL;}}
        if(KEY_PRESSED(GLFW_KEY_2)) {if(item != 1) {item = 1; COUT << "Item 2 : Sonic OBJ with texture, no lightning." << ENDL;}}
        if(KEY_PRESSED(GLFW_KEY_3)) {if(item != 2) {item = 2; COUT << "Item 3 : Diamonds with simple color and lightning." << ENDL;}}
        if(KEY_PRESSED(GLFW_KEY_4)) {if(item != 3) {item = 3; COUT << "Item 4 : Sonic OBJ with texture and lightning." << ENDL;}}
        if(KEY_PRESSED(GLFW_KEY_5)) {if(item != 4) {item = 4; COUT << "Item 5 : Final scene." << ENDL;}}
    }
    while(!KEY_PRESSED(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window) == 0);

}


int main(int argc, char* argv[])
{
    GL_Initialization();
    make_resources();
    mainLoop();
    shutDown(0);
}
