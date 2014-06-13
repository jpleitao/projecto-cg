#include "ObjLoader.h"

ObjLoader::ObjLoader(const char* name) {

    this->file = fopen(name, "r");
    if(file == NULL) {
        printf("Can't open file!");
    }
}
ObjLoader::~ObjLoader() {
    if ( this->file )
        fclose(this->file);
}

ModelArrays* ObjLoader::load() {

    std::vector<unsigned int> vertexInd, normalsInd, textureInd;

    std::vector <glm::vec3> vertex, normals;
    std::vector <glm::vec2> texture;

    std::vector <glm::vec3> outVertex, outNormals;
    std::vector <glm::vec2> outTexture;

    //First parsing to count number positions
    while(1) {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);

        if(res == EOF)
            break;

        if(strcmp(lineHeader, "v") == 0){
            glm::vec3 v;
            fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z );
            vertex.push_back(v);
        }
        else if (strcmp( lineHeader, "vt") == 0){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            texture.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            normals.push_back(normal);
        }
        else if (strcmp( lineHeader, "f") == 0 ){
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");

            }
            vertexInd.push_back(vertexIndex[0]);
            vertexInd.push_back(vertexIndex[1]);
            vertexInd.push_back(vertexIndex[2]);
            textureInd.push_back(uvIndex[0]);
            textureInd.push_back(uvIndex[1]);
            textureInd.push_back(uvIndex[2]);
            normalsInd.push_back(normalIndex[0]);
            normalsInd.push_back(normalIndex[1]);
            normalsInd.push_back(normalIndex[2]);
        }
    }

    unsigned int i, index;

    glm::vec3 v3;
    glm::vec2 v2;

    for(i=0; i<vertexInd.size(); i++) {
        index = vertexInd[i];
        v3 = vertex[index-1];
        outVertex.push_back(v3);
    }

    for(i=0; i<textureInd.size(); i++) {
        index = textureInd[i];
        v2 = texture[index-1];
        outTexture.push_back(v2);
    }

    for(i=0; i<normalsInd.size(); i++) {
        index = normalsInd[i];
        v3 = normals[index-1];
        outNormals.push_back(v3);
    }

    ModelArrays* result = new ModelArrays(outVertex, outTexture, outNormals);

    return result;
}



