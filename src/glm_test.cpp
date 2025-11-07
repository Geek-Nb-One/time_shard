#include "pch.h"
#include <iostream>

// Test GLM functionality
void testGLM() {
    glm::vec3 test(1.0f, 2.0f, 3.0f);
    glm::vec3 normalized = glm::normalize(test);
    
    std::cout << "GLM Test - Original: (" 
              << test.x << ", " << test.y << ", " << test.z << ")" << std::endl;
    std::cout << "GLM Test - Normalized: (" 
              << normalized.x << ", " << normalized.y << ", " << normalized.z << ")" << std::endl;
}