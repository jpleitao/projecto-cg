#include "ObjLoader.h"

ObjLoader::ObjLoader(const char* name) {

    this->file = fopen(name, "r");
    if(file == NULL) {
        printf("Can't open file!");
    }
}

ModelArrays* ObjLoader::load() {

    int nVertex = 0, nTexture = 0, nFaces = 0, nNormals = 0;

    glm::vec3 *vertex, *normals;
    glm::vec2 *texture;

    int *vertexInd, *normalInd, *textureInd;

    //First parsing to count number positions
    while(1) {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v" ) == 0) {
            ++nVertex;
        }
        else if(strcmp(lineHeader, "vt" ) == 0) {
            ++nTexture;
        }
        else if(strcmp(lineHeader, "vn" ) == 0) {
            ++nNormals;
        }
        else if(strcmp(lineHeader, "f") == 0) {
            ++nFaces;
        }
    }

    //Initializate vectors with number of positions defined above
    vertex = new glm::vec3[nVertex];
    texture = new glm::vec2[nTexture];
    normals = new glm::vec3[nNormals];

    vertexInd = new int[3*nFaces];
    normalInd = new int[3*nFaces];
    textureInd = new int[3*nFaces];

    //Reset file pointer
    rewind(file);

    int cVertex = 0, cTexture = 0, cNormal = 0, cFace = 0;

    //Load all information from .obj file
    while(1) {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v" ) == 0) {
            glm::vec3 vert;
            fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
            vertex[cVertex++] = vert;
        }
        else if(strcmp(lineHeader, "vt" ) == 0) {
            glm::vec2 vTexture;
            fscanf(file, "%f %f\n", &vTexture.x, &vTexture.y);
            texture[cTexture++] = vTexture;
        }
        else if(strcmp(lineHeader, "vn" ) == 0) {
            glm::vec3 norm;
            fscanf(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
            normals[cNormal++] = norm;
        }
        else if(strcmp(lineHeader, "f") == 0) {
            int vertexIndex[3], normalIndex[3], textureIndex[3];
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0], &vertexIndex[1], &textureIndex[1], &normalIndex[1], &vertexIndex[2], &textureIndex[2], &normalIndex[2]);
            vertexInd[cFace] = vertexIndex[0];
            textureInd[cFace] = textureIndex[0];
            normalInd[cFace++] = normalInd[0];
            vertexInd[cFace] = vertexIndex[1];
            textureInd[cFace] = textureIndex[1];
            normalInd[cFace++] = normalInd[1];
            vertexInd[cFace] = vertexIndex[2];
            textureInd[cFace] = textureIndex[2];
            normalInd[cFace++] = normalInd[2];
        }
    }

    ModelArrays* result = new ModelArrays(vertex, texture, normals, vertexInd, normalInd, textureInd, nVertex, nTexture, nNormals);

    return result;
}



