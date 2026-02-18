#include "environment.h"
#include <cmath>

Environment::Environment() {
    setupGround();
    setupRoad();
    setupSkybox();
    setupScenery();
}

Environment::~Environment() {
    glDeleteVertexArrays(1, &groundVAO);
    glDeleteBuffers(1, &groundVBO);
    glDeleteVertexArrays(1, &roadVAO);
    glDeleteBuffers(1, &roadVBO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
}

void Environment::setupGround() {
    float size = 100.0f;
    float groundVertices[] = {
        // positions            // normals          // texture coords
        -size, 0.0f, -size,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         size, 0.0f, -size,    0.0f, 1.0f, 0.0f,   10.0f, 0.0f,
         size, 0.0f,  size,    0.0f, 1.0f, 0.0f,   10.0f, 10.0f,
         size, 0.0f,  size,    0.0f, 1.0f, 0.0f,   10.0f, 10.0f,
        -size, 0.0f,  size,    0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
        -size, 0.0f, -size,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f
    };
    
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);
    
    glBindVertexArray(groundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Environment::setupRoad() {
    float width = 8.0f;
    float length = 200.0f;
    float roadVertices[] = {
        // positions                    // normals          // texture coords
        -width, 0.01f, -length,         0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         width, 0.01f, -length,         0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         width, 0.01f,  length,         0.0f, 1.0f, 0.0f,   1.0f, 20.0f,
         width, 0.01f,  length,         0.0f, 1.0f, 0.0f,   1.0f, 20.0f,
        -width, 0.01f,  length,         0.0f, 1.0f, 0.0f,   0.0f, 20.0f,
        -width, 0.01f, -length,         0.0f, 1.0f, 0.0f,   0.0f, 0.0f
    };
    
    glGenVertexArrays(1, &roadVAO);
    glGenBuffers(1, &roadVBO);
    
    glBindVertexArray(roadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, roadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roadVertices), roadVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Environment::setupSkybox() {
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Environment::setupScenery() {
    // Add some trees along the road
    for (int i = -10; i < 10; i++) {
        treePositions.push_back(glm::vec3(-15.0f, 0.0f, i * 20.0f));
        treePositions.push_back(glm::vec3(15.0f, 0.0f, i * 20.0f));
    }
    
    // Add some buildings
    for (int i = -5; i < 5; i++) {
        buildingPositions.push_back(glm::vec3(-30.0f, 0.0f, i * 40.0f));
        buildingPositions.push_back(glm::vec3(30.0f, 0.0f, i * 40.0f));
    }
}

void Environment::Draw(unsigned int shaderID) {
    drawGround(shaderID);
    drawRoad(shaderID);
    drawTrees(shaderID);
    drawBuildings(shaderID);
}

void Environment::drawGround(unsigned int shaderID) {
    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
    
    // Green grass color
    glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.2f, 0.6f, 0.2f);
    
    glBindVertexArray(groundVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Environment::drawRoad(unsigned int shaderID) {
    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
    
    // Dark gray road color
    glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.3f, 0.3f, 0.3f);
    
    glBindVertexArray(roadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Environment::drawTrees(unsigned int shaderID) {
    // Simple tree representation (cylinder trunk + cone top)
    for (const auto& pos : treePositions) {
        // Tree trunk
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 4.0f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
        
        // Brown color for trunk
        glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.4f, 0.2f, 0.1f);
        
        // Draw a simple cube as tree trunk
        float cube[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f
        };
        
        unsigned int tempVAO, tempVBO;
        glGenVertexArrays(1, &tempVAO);
        glGenBuffers(1, &tempVBO);
        glBindVertexArray(tempVAO);
        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDeleteVertexArrays(1, &tempVAO);
        glDeleteBuffers(1, &tempVBO);
        
        // Tree foliage
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 3.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
        
        // Dark green color for foliage
        glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.1f, 0.4f, 0.1f);
        
        glGenVertexArrays(1, &tempVAO);
        glGenBuffers(1, &tempVBO);
        glBindVertexArray(tempVAO);
        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDeleteVertexArrays(1, &tempVAO);
        glDeleteBuffers(1, &tempVBO);
    }
}

void Environment::drawBuildings(unsigned int shaderID) {
    // Simple building representation (tall boxes)
    for (const auto& pos : buildingPositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::translate(model, glm::vec3(0.0f, 7.5f, 0.0f));
        model = glm::scale(model, glm::vec3(5.0f, 15.0f, 5.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
        
        // Gray color for buildings
        glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.5f, 0.5f, 0.5f);
        
        float cube[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };
        
        unsigned int tempVAO, tempVBO;
        glGenVertexArrays(1, &tempVAO);
        glGenBuffers(1, &tempVBO);
        glBindVertexArray(tempVAO);
        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDeleteVertexArrays(1, &tempVAO);
        glDeleteBuffers(1, &tempVBO);
    }
}

void Environment::DrawSkybox(unsigned int skyboxShaderID, glm::mat4 view, glm::mat4 projection) {
    glDepthFunc(GL_LEQUAL);
    glUseProgram(skyboxShaderID);
    
    // Remove translation from view matrix
    view = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(glGetUniformLocation(skyboxShaderID, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(skyboxShaderID, "projection"), 1, GL_FALSE, &projection[0][0]);
    
    // Sky blue color
    glUniform3f(glGetUniformLocation(skyboxShaderID, "skyColor"), 0.5f, 0.7f, 1.0f);
    
    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}
