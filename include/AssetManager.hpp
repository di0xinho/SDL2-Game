#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <iostream>

class AssetManager {
public:
    AssetManager(SDL_Renderer* renderer);
    ~AssetManager();

    SDL_Texture* loadTexture(const std::string& id, const std::string& path);
    TTF_Font* loadFont(const std::string& id, const std::string& path, int size);
    Mix_Chunk* loadSound(const std::string& id, const std::string& path);
    Mix_Music* loadMusic(const std::string& id, const std::string& path);

    SDL_Texture* getTexture(const std::string& id) const;
    TTF_Font* getFont(const std::string& id) const;
    Mix_Chunk* getSound(const std::string& id) const;
    Mix_Music* getMusic(const std::string& id) const;

    bool hasTexture(const std::string& id) const;
    bool hasFont(const std::string& id) const;
    bool hasSound(const std::string& id) const;
    bool hasMusic(const std::string& id) const;

    void clear();

private:
    SDL_Renderer* renderer;

    std::unordered_map<std::string, SDL_Texture*> textures;
    std::unordered_map<std::string, TTF_Font*> fonts;
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    std::unordered_map<std::string, Mix_Music*> music;
};