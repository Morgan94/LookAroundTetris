#ifndef __HAKUREI_FRAMEWORK__MESH__
#define __HAKUREI_FRAMEWORK__MESH__

#include "all.h"

namespace Hakurei
{
    class Mesh
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        std::map<String, Uint32> vbos;
        Uint32 ibo;
        Uint32 vao;
        glm::mat4 transformMatrix;
        glm::mat4 defaultMatrix;

        // vertices converted to arrays
        float* _P;
        Uint32 length_p;
        float* _N;
        Uint32 length_n;
        float* _T;
        Uint32 length_t;
        float* _U;
        Uint32 length_u;
        float* _C;
        Uint32 length_c;
        Uint32* _I;
        Uint32 length_i;

        Mesh();
        void computeNormals();
        void getPositions();
        void getNormals();
        void getTangents();
        void getUVs();
        void getColors();
        void getIndexes();
        void createVBO();
        void createIBO();
        void createVAO();
        void transform(Uint8 transformType, Uint8 transformAction = NO_TRANSFORM, Vec3f v = Vec3f(), float angle = 0);
        void resetObjectTransform();
        void setObjectTransformAsDefault();
        Bool importOBJ(String OBJfile, Bool deleteFixedOBJ = true);
        //void objData(); <-- for debug purpose

        // standard mesh creation routines
        void createCube(float w, float d, float h, Vec4f color);

    private:
        String fixObjFile(String OBJfile); // fill UVs if obj has no UV

    };
}

#endif



