//
// Created by Engin Manap on 9.04.2016.
//

#include "GUIFPSCounter.h"


void GUIFPSCounter::updateFPS() {
    currentTime = SDL_GetTicks();
    Uint32 newFrameTime = currentTime - lastRenderTime;
    lastFrameTime += newFrameTime - previousFrameTimes[framePointer];
    previousFrameTimes[framePointer] = newFrameTime;
    framePointer = (framePointer + 1) % 100;
    lastRenderTime = currentTime;

    int normalizedFrameRate = (unsigned int) (1000.0f / (lastFrameTime / 100.0f));
    text = std::__cxx11::to_string(normalizedFrameRate);
}

void GUIFPSCounter::render() {
    updateFPS();

    GUIText::render();
}