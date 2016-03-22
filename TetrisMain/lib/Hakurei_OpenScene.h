#ifndef __HAKUREI_FRAMEWORK__OPENSCENE__
#define __HAKUREI_FRAMEWORK__OPENSCENE__

#include "all.h"

namespace Hakurei
{
    class OpenScene
    {
    public:
        Map<String, Mesh*> objects;
        Map<String, Material*> materials;
        // matrices
        glm::mat4 MVP;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat3 normalMatrix;
        // camera
        Hakurei::OpenCamera* camera;
        // light stuff
        Vec3f lightdir;
        Vec3f lightcolor;
        Vec3f ambient;
        Vec3f diffuse;
        Vec3f specular;
        float shininess;
        // key handler
        Hakurei::KeyHandler* kh;
        // used texture unit
        Uint32 textureUnit;

        OpenScene();
        Hakurei::Mesh* getObjectByName(String objName);
        Hakurei::Material* getMaterialByName(String matName);
        void updateCamera();
        void addMaterial(String mat_name, Hakurei::Material* material);
        void removeMaterial(String mat_name);
        void addObject(String obj_name, Hakurei::Mesh* object);
        void removeObject(String obj_name);
        void drawObjectInScene(String object, String material);
        void updateProgramUniforms(ShaderProgram *prog, Mesh *obj, Material *mat);
        void resetTransforms();
        void initDrawingScene();

    private:
        void drawObject(String objName, String matName);

    };
}

#endif




