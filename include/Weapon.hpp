#pragma once
#include <SDL.h>
#include "GameData.hpp"
#include <memory>

/// Klasa reprezentuj¹ca broñ rzucan¹ przez gracza 
class Weapon {
public:
    /// Domyœlny konstruktor
    Weapon();

    /// Inicjalizuje broñ: ustawia teksturê, pozycjê startow¹ i resetuje w³aœciwoœci broni
    void init(std::shared_ptr<GameData> data, SDL_Texture* texture, SDL_FPoint startPos);

    /// Aktualizuje logikê broni (ruch, czas ¿ycia)
    void update(float deltaTime);

    /// Renderuje broñ na ekranie, uwzglêdniaj¹c przesuniêcie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok¹t kolizyjny broni (do detekcji trafieñ)
    SDL_Rect getRect() const;

    /// Sprawdza, czy broñ nadal istnieje (nie wygas³a, nie zderzy³a siê)
    bool isAlive() const;

    /// Oznacza broñ jako zniszczon¹ (oznacza j¹ jako "martw¹")
    void Kill();

    /// Sprawdza kolizjê broni z innym prostok¹tem (np. przeciwnikiem)
    bool checkCollision(const SDL_Rect& other);

private:
    SDL_FPoint position{};                  /// Aktualna pozycja broni w œwiecie gry
    SDL_FPoint velocity{ 300.0f, 0.0f };    /// Prêdkoœæ broni 
    float angle = 0.0f;                     /// K¹t obrotu (np. do animacji lotu)
    float lifetime = 5.0f;                  /// Pozosta³y czas ¿ycia broni (sekundy)
    bool alive = true;                      /// Czy broñ jest aktywna?

    SDL_Texture* texture = nullptr;         /// Tekstura broni
    SDL_FPoint size{ 32.0f, 32.0f };        /// Rozmiar broni (domyœlnie 32x32 px)
};