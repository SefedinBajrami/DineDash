#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Environment {
public:
    Environment();
    ~Environment();
    
    void Draw(unsigned int shaderID);
    void DrawSkybox(unsigned int skyboxShaderID, glm::mat4 view, glm::mat4 projection);
    
private:
    unsigned int groundVAO, groundVBO;
    unsigned int roadVAO, roadVBO;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int skyboxTexture;
    
    std::vector<glm::vec3> treePositions;
    std::vector<glm::vec3> buildingPositions;
    
    void setupGround();
    void setupRoad();
    void setupSkybox();
    void setupScenery();
    void drawGround(unsigned int shaderID);
    void drawRoad(unsigned int shaderID);
    void drawTrees(unsigned int shaderID);
    void drawBuildings(unsigned int shaderID);
    unsigned int loadCubemap();
};

#endif
