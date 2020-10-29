//
// Created by engin on 16.07.2018.
//

#include "Sound.h"
#include "../Assets/AssetManager.h"
#include "../ALHelper.h"
#include "../Assets/SoundAsset.h"

Sound::Sound(uint32_t worldID,  std::shared_ptr<AssetManager> assetManager, const std::string &filename) : name(filename), worldID(worldID), assetManager(assetManager) {}

void Sound::setLoop(bool looped) {
    this->looped = looped;
    if(this->soundHandleID != 0) {
        assetManager->getAlHelper()->setLooped(soundHandleID, this->looped);
    }
}

void Sound::setStartPosition(float startSecond) {
    this->startSecond = startSecond;
    std::cerr << "This method [setStartPosition] is not implemented yet " << std::endl;
}

void Sound::setStopPosition(float stopPosition) {
    this->stopPosition = stopPosition;
    std::cerr << "This method [setStopPosition] is not implemented yet " << std::endl;
}

void Sound::play() {
    if(playState == State::STOP_AFTER_FINISH) {
        if(this->looped && assetManager->getAlHelper()->isPlaying(soundHandleID)) {
            assetManager->getAlHelper()->setLooped(soundHandleID, this->looped);
            this->playState = State::PLAYING;
            return;
        } else {
            this->stop();//force stop if stop after finish
        }
    } else {
        if (soundHandleID != 0) {
            if (!assetManager->getAlHelper()->isPlaying(soundHandleID)) {//don't play if already playing
                soundHandleID = assetManager->getAlHelper()->play(assetManager->loadAsset<SoundAsset>({this->name}),
                                                                  this->looped, gain);
                assetManager->getAlHelper()->setSourcePosition(soundHandleID, this->listenerRelative, this->position);
            }
        } else {
            soundHandleID = assetManager->getAlHelper()->play(assetManager->loadAsset<SoundAsset>({this->name}),
                                                              this->looped, gain);
            assetManager->getAlHelper()->setSourcePosition(soundHandleID, this->listenerRelative, this->position);

        }
        this->playState = State::PLAYING;
    }
}

void Sound::stop() {
    assetManager->getAlHelper()->stop(soundHandleID);
    this->playState = State::STOPPED;
    soundHandleID = 0;
}

void Sound::pause() {
    assetManager->getAlHelper()->pause(soundHandleID);
    this->playState = State::PAUSED;
}

void Sound::resume() {
    assetManager->getAlHelper()->resume(soundHandleID);
    this->playState = State::PLAYING;
}

void Sound::stopAfterFinish() {
    if(soundHandleID != 0 && this->playState == State::PLAYING) {
        if (!assetManager->getAlHelper()->setLooped(soundHandleID, false)) {
            std::cerr << "The stop after finish is failed for " << this->name << "with handle " << soundHandleID <<  std::endl;
        }
    }
    this->playState = State::STOP_AFTER_FINISH;

}

void Sound::setWorldPosition(glm::vec3 position, bool listenerRelative) {
    this->position = position;
    this->listenerRelative = listenerRelative;
    if(this->soundHandleID != 0) {
        assetManager->getAlHelper()->setSourcePosition(soundHandleID, this->listenerRelative, this->position);
    }
}

Sound::~Sound() {
    if(soundHandleID != 0) {//we don't create asset until play, this check verifies it.
        this->stop();
        this->assetManager->freeAsset({this->name});
    } else {
        this->stop();
    }
}

Sound::State Sound::getState() {
    if(playState == State::STOP_AFTER_FINISH) {
        //check if stopped or not
        if(!assetManager->getAlHelper()->isPlaying(soundHandleID)) {
            playState = State::STOPPED;
        }
    }
    return playState;
}

bool Sound::changeGain(float gain) {
    this->gain = gain;
    if(soundHandleID != 0) {
        return assetManager->getAlHelper()->changeGain(this->soundHandleID, gain);
    } else {
        return false;
    }

}
