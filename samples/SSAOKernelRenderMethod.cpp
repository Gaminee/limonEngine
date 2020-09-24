//
// Created by engin on 23.09.2019.
//

#include <random>
#include "SSAOKernelRenderMethod.h"


float lerp(float first , float second , float factor ) {
    return first + factor * (second - first);
}

std::vector<glm::vec3> SSAOKernelRenderMethod::generateSSAOKernels(uint32_t kernelSize) {
// generate sample kernel
// ----------------------
    std::vector<glm::vec3> ssaoKernel;
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
    std::default_random_engine generator;
    for (unsigned int i = 0; i < kernelSize; ++i){
        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample = glm::normalize(sample);
        //sample *= randomFloats(generator);
        float scale = float(i) / kernelSize;

        // scale samples s.t. they're more aligned to center of kernel
        scale = lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        ssaoKernel.push_back(sample);
        //std::cout << "sampleKernel" << glm::to_string(sample) << std::endl;
    }
    return ssaoKernel;
}


bool SSAOKernelRenderMethod::initRender(std::shared_ptr<GraphicsProgram> program, std::vector<LimonAPI::ParameterRequest> parameters [[gnu::unused]]) {

    std::vector<glm::vec3> kernels = generateSSAOKernels(9);
    if(!program->setUniform("ssaoKernel[0]", kernels)) {
        std::cerr << "uniform variable \"ssaoKernel\" couldn't be set" << std::endl;
    }
    if(!program->setUniform("ssaoSampleCount", (int32_t)kernels.size())) {
        std::cerr << "uniform variable \"ssaoSampleCount\" couldn't be set" << std::endl;
    }

    return false;
}


void registerRenderMethods(std::map<std::string, RenderMethodInterface*(*)(GraphicsInterface*)>* renderMethodMap) {
    (*renderMethodMap)["SSAOKernelRenderMethod"] = &createT<SSAOKernelRenderMethod>;
}
