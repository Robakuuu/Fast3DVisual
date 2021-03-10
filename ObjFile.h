#pragma once
#pragma warning(disable:4996)
#include "DrawScene.h"

class ObjFile {
public:
    ObjFile(const char* path);

    bool loadOBJ(const char* path,
        std::vector < glm::vec3 >& out_vertices,
        std::vector < glm::vec2 >& out_uvs,
        std::vector < glm::vec3 >& out_normals);

    void SetVertices(std::vector< glm::vec3 > vec3Vec) { m_vec3Vertices = vec3Vec; };
    std::vector< glm::vec3 > GetVertices() { return m_vec3Vertices; };

    void SetUvs(std::vector< glm::vec2 > vec2Uv) { m_vec2Uvs = vec2Uv; };
    std::vector< glm::vec2 > GetUvs() { return m_vec2Uvs; };

    void SetNormals(std::vector< glm::vec3 > vec3Normals) { m_vec3Normals = vec3Normals; };
    std::vector< glm::vec3 > GetNormals() { return m_vec3Normals; };

private:
    std::vector< glm::vec3 > m_vec3Vertices;
    std::vector< glm::vec2 > m_vec2Uvs;
    std::vector< glm::vec3 > m_vec3Normals;
};
