#include "AssetManager.hpp"

/// Konstruktor — inicjalizuje AssetManager z podanym rendererem SDL
AssetManager::AssetManager(SDL_Renderer* renderer)
    : renderer(renderer) {
}

/// Destruktor — zwalnia wszystkie zasoby
AssetManager::~AssetManager() {
    clear();
}

/// £aduje i przechowuje teksturê o danym id, jeœli nie zosta³a ju¿ za³adowana
SDL_Texture* AssetManager::loadTexture(const std::string& id, const std::string& path) {
    if (hasTexture(id))
        return textures[id];
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) {
        std::cerr << "B³¹d podczas wczytywania tekstury: " << path << " - " << IMG_GetError() << '\n';
        return nullptr;
    }
    textures[id] = tex;
    return tex;
}

/// £aduje i przechowuje czcionkê o danym id, jeœli nie zosta³a ju¿ za³adowana
TTF_Font* AssetManager::loadFont(const std::string& id, const std::string& path, int size) {
    if (hasFont(id))
        return fonts[id];
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "B³¹d podczas wczytywania czcionki: " << path << " - " << TTF_GetError() << '\n';
        return nullptr;
    }
    fonts[id] = font;
    return font;
}

/// £aduje i przechowuje dŸwiêk o danym id, jeœli nie zosta³ ju¿ za³adowany
Mix_Chunk* AssetManager::loadSound(const std::string& id, const std::string& path) {
    if (hasSound(id))
        return sounds[id];
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        std::cerr << "B³¹d podczas wczytywania dŸwiêku: " << path << " - " << Mix_GetError() << '\n';
        return nullptr;
    }
    sounds[id] = chunk;
    return chunk;
}

/// £aduje i przechowuje muzykê o danym id, jeœli nie zosta³a ju¿ za³adowana
Mix_Music* AssetManager::loadMusic(const std::string& id, const std::string& path) {
    if (hasMusic(id))
        return music[id];
    Mix_Music* musicTrack = Mix_LoadMUS(path.c_str());
    if (!musicTrack) {
        std::cerr << "B³¹d podczas wczytywania muzyki: " << path << " - " << Mix_GetError() << '\n';
        return nullptr;
    }
    music[id] = musicTrack;
    return musicTrack;
}

/// Zwraca wskaŸnik do tekstury o podanym id lub nullptr jeœli nie istnieje
SDL_Texture* AssetManager::getTexture(const std::string& id) const {
    auto it = textures.find(id);
    return (it != textures.end()) ? it->second : nullptr;
}

/// Zwraca wskaŸnik do czcionki o podanym id lub nullptr jeœli nie istnieje
TTF_Font* AssetManager::getFont(const std::string& id) const {
    auto it = fonts.find(id);
    return (it != fonts.end()) ? it->second : nullptr;
}

/// Zwraca wskaŸnik do dŸwiêku o podanym id lub nullptr jeœli nie istnieje
Mix_Chunk* AssetManager::getSound(const std::string& id) const {
    auto it = sounds.find(id);
    return (it != sounds.end()) ? it->second : nullptr;
}

/// Zwraca wskaŸnik do muzyki o podanym id lub nullptr jeœli nie istnieje
Mix_Music* AssetManager::getMusic(const std::string& id) const {
    auto it = music.find(id);
    return (it != music.end()) ? it->second : nullptr;
}

/// Sprawdza, czy tekstura o danym id jest za³adowana
bool AssetManager::hasTexture(const std::string& id) const {
    return textures.find(id) != textures.end();
}

/// Sprawdza, czy czcionka o danym id jest za³adowana
bool AssetManager::hasFont(const std::string& id) const {
    return fonts.find(id) != fonts.end();
}

/// Sprawdza, czy dŸwiêk o danym id jest za³adowany
bool AssetManager::hasSound(const std::string& id) const {
    return sounds.find(id) != sounds.end();
}

/// Sprawdza, czy muzyka o danym id jest za³adowana
bool AssetManager::hasMusic(const std::string& id) const {
    return music.find(id) != music.end();
}

/// Zwalnia wszystkie za³adowane zasoby (tekstury, czcionki, dŸwiêki, muzykê)
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