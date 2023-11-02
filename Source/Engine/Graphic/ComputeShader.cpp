#include "ComputeShader.h"

#include "glad/glad.h"

ComputeShader::ComputeShader() :Shader() {
}

void ComputeShader::compute(int groupX, int groupY, int groupZ) {
    use();

    glDispatchCompute(groupX, groupY, groupZ);
}

void ComputeShader::syncStorage() {
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}