#include "AssetManager.hpp"

AssetManager::AssetManager(SDL_Renderer* renderer)
    : renderer(renderer) {
}

AssetManager::~AssetManager() {
    clear();
}

SDL_Texture* AssetManager::loadTexture(const std::string& id, const std::string& path) {
    if (hasTexture(id))
        return textures[id];
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) {
        std::cerr << "Failed to load texture: " << path << " - " << IMG_GetError() << '\n';
        return nullptr;
    }
    textures[id] = tex;
    return tex;
}

TTF_Font* AssetManager::loadFont(const std::string& id, const std::string& path, int size) {
    if (hasFont(id))
        return fonts[id];
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << path << " - " << TTF_GetError() << '\n';
        return nullptr;
    }
    fonts[id] = font;
    return font;
}

Mix_Chunk* AssetManager::loadSound(const std::string& id, const std::string& path) {
    if (hasSound(id))
        return sounds[id];
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        std::cerr << "Failed to load sound: " << path << " - " << Mix_GetError() << '\n';
        return nullptr;
    }
    sounds[id] = chunk;
    return chunk;
}

Mix_Music* AssetManager::loadMusic(const std::string& id, const std::string& path) {
    if (hasMusic(id))
        return music[id];
    Mix_Music* musicTrack = Mix_LoadMUS(path.c_str());
    if (!musicTrack) {
        std::cerr << "Failed to load music: " << path << " - " << Mix_GetError() << '\n';
        return nullptr;
    }
    music[id] = musicTrack;
    return musicTrack;
}

SDL_Texture* AssetManager::getTexture(const std::string& id) const {
    auto it = textures.find(id);
    return (it != textures.end()) ? it->second : nullptr;
}

TTF_Font* AssetManager::getFont(const std::string& id) const {
    auto it = fonts.find(id);
    return (it != fonts.end()) ? it->second : nullptr;
}

Mix_Chunk* AssetManager::getSound(const std::string& id) const {
    auto it = sounds.find(id);
    return (it != sounds.end()) ? it->second : nullptr;
}

Mix_Music* AssetManager::getMusic(const std::string& id) const {
    auto it = music.find(id);
    return (it != music.end()) ? it->second : nullptr;
}

bool AssetManager::hasTexture(const std::string& id) const {
    return textures.find(id) != textures.end();
}

bool AssetManager::hasFont(const std::string& id) const {
    return fonts.find(id) != fonts.end();
}

bool AssetManager::hasSound(const std::string& id) const {
    return sounds.find(id) != sounds.end();
}

bool AssetManager::hasMusic(const std::string& id) const {
    return music.find(id) != music.end();
}

void AssetManager::clear() {
    for (auto& [_, tex] : textures)
        SDL_DestroyTexture(tex);
    for (auto& [_, font] : fonts)
        TTF_CloseFont(font);
    for (auto& [_, sound] : sounds)
        Mix_FreeChunk(sound);
    for (auto& [_, musicTrack] : music)
        Mix_FreeMusic(musicTrack);

    textures.clear();
    fonts.clear();
    sounds.clear();
    music.clear();
}