#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <iostream>

/// Klasa zarz�dzaj�ca zasobami gry � teksturami, czcionkami, d�wi�kami i muzyk�.
/// Pozwala �adowa�, przechowywa� i pobiera� zasoby po unikalnym identyfikatorze.
/// Odpowiada r�wnie� za zwalnianie pami�ci przy destrukcji.
class AssetManager {
public:
    /// Tworzy mened�era zasob�w z przekazanym rendererem SDL
    AssetManager(SDL_Renderer* renderer);

    /// Usuwa wszystkie za�adowane zasoby i zwalnia pami��
    ~AssetManager();

    /// �aduje tekstur� z pliku i zapisuje j� pod wybranym identyfikatorem
    SDL_Texture* loadTexture(const std::string& id, const std::string& path);

    /// �aduje czcionk� z pliku i zapisuje j� pod wybranym identyfikatorem
    TTF_Font* loadFont(const std::string& id, const std::string& path, int size);

    /// �aduje d�wi�k (efekt) z pliku i zapisuje go pod wybranym identyfikatorem
    Mix_Chunk* loadSound(const std::string& id, const std::string& path);

    /// �aduje muzyk� z pliku i zapisuje j� pod wybranym identyfikatorem
    Mix_Music* loadMusic(const std::string& id, const std::string& path);

    /// Pobiera tekstur� o podanym identyfikatorze
    SDL_Texture* getTexture(const std::string& id) const;

    /// Pobiera czcionk� o podanym identyfikatorze
    TTF_Font* getFont(const std::string& id) const;

    /// Pobiera d�wi�k o podanym identyfikatorze
    Mix_Chunk* getSound(const std::string& id) const;

    /// Pobiera muzyk� o podanym identyfikatorze
    Mix_Music* getMusic(const std::string& id) const;

    /// Sprawdza czy istnieje tekstura o podanym identyfikatorze
    bool hasTexture(const std::string& id) const;

    /// Sprawdza czy istnieje czcionka o podanym identyfikatorze
    bool hasFont(const std::string& id) const;

    /// Sprawdza czy istnieje d�wi�k o podanym identyfikatorze
    bool hasSound(const std::string& id) const;

    /// Sprawdza czy istnieje muzyka o podanym identyfikatorze
    bool hasMusic(const std::string& id) const;

    /// Usuwa wszystkie za�adowane zasoby i czy�ci mened�era
    void clear();

private:
    SDL_Renderer* renderer; /// Wska�nik do renderer'a SDL

    std::unordered_map<std::string, SDL_Texture*> textures; /// Tekstury
    std::unordered_map<std::string, TTF_Font*> fonts;       /// Czcionki
    std::unordered_map<std::string, Mix_Chunk*> sounds;     /// D�wi�ki (efekty)
    std::unordered_map<std::string, Mix_Music*> music;      /// Muzyka
};