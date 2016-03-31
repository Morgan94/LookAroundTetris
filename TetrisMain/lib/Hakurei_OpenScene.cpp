#include "Hakurei_OpenScene.h"


Hakurei::OpenScene::OpenScene(Bool Camera_DefaultCallBacks, Bool Camera_RotateAroundTarget, Vec3f Camera_Target)
{
    NO_PERMISSION
    objects.clear();
    materials.clear();
    diffuse = glm::vec3(0.9, 0.9, 0.9);
    specular = glm::vec3(0.65, 0.65, 0.65);
    lightdir = glm::vec3(0.0, 0.0, 1.0);
    lightcolor = glm::vec3(0.8, 0.8, 0.8);
    ambient = glm::vec3(0.3, 0.3, 0.3);
    shininess = 300.0f;
    camera = new Hakurei::OpenCamera(Camera_DefaultCallBacks, Camera_RotateAroundTarget, Camera_Target);
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
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Object " << objName << " does not exist." << ENDL;
#endif
        return NULL;
    }
    return objects[objName];
}

Hakurei::Material* Hakurei::OpenScene::getMaterialByName(String matName)
{
    if(materials[matName] == NULL)
    {
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Material " << matName << " does not exist." << ENDL;
#endif
        return NULL;
    }
    return materials[matName];
}

void Hakurei::OpenScene::addMaterial(String mat_name, Hakurei::Material* material)
{
    if(materials[mat_name] != NULL)
    {
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Material " << mat_name << " is already set." << ENDL;
#endif
        return;
    }
    materials[mat_name] = material;
    return;
}

void Hakurei::OpenScene::removeMaterial(String mat_name)
{
    if(materials[mat_name] == NULL)
    {
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Material " << mat_name << " does not exist." << ENDL;
#endif
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
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Object " << obj_name << " is already set." << ENDL;
#endif
        return;
    }

    object->createVBO();
    object->createIBO();
    object->createVAO();
    object->meshName = obj_name;
    objects[obj_name] = object;
    return;
}

void Hakurei::OpenScene::removeObject(String obj_name)
{
    if(objects[obj_name] == NULL)
    {
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Object " << obj_name << " does not exist." << ENDL;
#endif
        return;
    }

    Hakurei::Mesh* obj = objects[obj_name];
    delete[] obj->_P;
    delete[] obj->_N;
    delete[] obj->_T;
    delete[] obj->_U;
    delete[] obj->_C;
    delete[] obj->_I;
    delete obj;
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
#ifdef DISPLAY_WARNINGS
        if(!warnObj[objName]) CERR << "Warning : there is no object named " << objName << ENDL;
        warnObj[objName] = true;
#endif
        return;
    }
    if(mat == NULL)
    {
#ifdef DISPLAY_WARNINGS
        if(!warnMat[matName]) CERR << "Warning : there is no material named " << matName << ENDL;
        warnMat[matName] = true;
#endif
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
    if(mat->alpha < 1) glDisable(GL_CULL_FACE);
    glDrawElements(GL_TRIANGLES, obj->length_i, GL_UNSIGNED_INT, 0);
    if(mat->alpha < 1) glEnable(GL_CULL_FACE);

    // Clean state again
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void Hakurei::OpenScene::initDrawingScene()
{
    typedef Map<String, Hakurei::Mesh*>::iterator it_type;
    for(it_type iterator = objects.begin(); iterator != objects.end(); iterator++) {
        if(iterator->second != NULL)
            iterator->second->resetObjectTransform();
    }
}

void Hakurei::OpenScene::drawObjectInScene(String object, String material)
{
    Hakurei::Mesh* obj = objects[object];
    Hakurei::Material* mat = materials[material];
    if(obj == NULL)
    {
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Object " << object << " does not exist." << ENDL;
#endif
        return;
    }
    if(mat == NULL)
    {
#ifdef DISPLAY_WARNINGS
        CERR << "Warning : Object " << object << " does not exist." << ENDL;
#endif
        return;
    }

    if(mat->useTexture)
    {
        Uint32 textureId = mat->texture->textureID;
        Uint32 progId = mat->prog->progID;

        // activate the texture unit (here GL_TEXTURE_0)
        glActiveTexture(GL_TEXTURE0);

        // bind the texture
        glBindTexture(GL_TEXTURE_2D, textureId);

        // associate the chosen texture unit to the GLSL sampler
        glUseProgram(progId);
        if(mat->colorSampler.size() != 0)
            mat->prog->setUniform(mat->colorSampler,0);
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
    prog->setUniform("alpha", mat->alpha);
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
