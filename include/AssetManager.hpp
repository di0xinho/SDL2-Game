#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <iostream>

/// Klasa zarz¹dzaj¹ca zasobami gry — teksturami, czcionkami, dŸwiêkami i muzyk¹.
/// Pozwala ³adowaæ, przechowywaæ i pobieraæ zasoby po unikalnym identyfikatorze.
/// Odpowiada równie¿ za zwalnianie pamiêci przy destrukcji.
class AssetManager {
public:
    /// Tworzy mened¿era zasobów z przekazanym rendererem SDL
    AssetManager(SDL_Renderer* renderer);

    /// Usuwa wszystkie za³adowane zasoby i zwalnia pamiêæ
    ~AssetManager();

    /// £aduje teksturê z pliku i zapisuje j¹ pod wybranym identyfikatorem
    SDL_Texture* loadTexture(const std::string& id, const std::string& path);

    /// £aduje czcionkê z pliku i zapisuje j¹ pod wybranym identyfikatorem
    TTF_Font* loadFont(const std::string& id, const std::string& path, int size);

    /// £aduje dŸwiêk (efekt) z pliku i zapisuje go pod wybranym identyfikatorem
    Mix_Chunk* loadSound(const std::string& id, const std::string& path);

    /// £aduje muzykê z pliku i zapisuje j¹ pod wybranym identyfikatorem
    Mix_Music* loadMusic(const std::string& id, const std::string& path);

    /// Pobiera teksturê o podanym identyfikatorze
    SDL_Texture* getTexture(const std::string& id) const;

    /// Pobiera czcionkê o podanym identyfikatorze
    TTF_Font* getFont(const std::string& id) const;

    /// Pobiera dŸwiêk o podanym identyfikatorze
    Mix_Chunk* getSound(const std::string& id) const;

    /// Pobiera muzykê o podanym identyfikatorze
    Mix_Music* getMusic(const std::string& id) const;

    /// Sprawdza czy istnieje tekstura o podanym identyfikatorze
    bool hasTexture(const std::string& id) const;

    /// Sprawdza czy istnieje czcionka o podanym identyfikatorze
    bool hasFont(const std::string& id) const;

    /// Sprawdza czy istnieje dŸwiêk o podanym identyfikatorze
    bool hasSound(const std::string& id) const;

    /// Sprawdza czy istnieje muzyka o podanym identyfikatorze
    bool hasMusic(const std::string& id) const;

    /// Usuwa wszystkie za³adowane zasoby i czyœci mened¿era
    void clear();

private:
    SDL_Renderer* renderer; /// WskaŸnik do renderer'a SDL

    std::unordered_map<std::string, SDL_Texture*> textures; /// Tekstury
    std::unordered_map<std::string, TTF_Font*> fonts;       /// Czcionki
    std::unordered_map<std::string, Mix_Chunk*> sounds;     /// DŸwiêki (efekty)
    std::unordered_map<std::string, Mix_Music*> music;      /// Muzyka
};