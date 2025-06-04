#include "Player.hpp"

/// Konstruktor gracza — ustawia pozycję startową, zeruje prędkość, wyłącza mruganie i ustawia domyślne parametry mrugania.
Player::Player() {
    position = { 100.0f, 300.0f };
    velocity = { 0.0f, 0.0f };
    blinking = false;
    blinkTimer = 0.0f;
    blinkDuration = 0.0f;
    blinkFrequency = 12.0f;
}

/// Inicjalizuje animacje gracza (idle, bieg, skok), ładuje tekstury przez assetManager
void Player::init(std::shared_ptr<GameData> data) {
    idleAnim.addFrame(data->assetManager->loadTexture("idle", PLAYER_IDLE));
    runAnim.addFrame(data->assetManager->loadTexture("run1", PLAYER_RUN_1));
    runAnim.addFrame(data->assetManager->loadTexture("run2", PLAYER_RUN_2));
    runAnim.addFrame(data->assetManager->loadTexture("run3", PLAYER_RUN_3));
    jumpAnim.addFrame(data->assetManager->loadTexture("jump", PLAYER_JUMP));

    idleAnim.setFrameDuration(0.5f);
    runAnim.setFrameDuration(0.1f);
    jumpAnim.setFrameDuration(0.1f);

    currentAnim = &idleAnim;
}

/// Ustawia pozycję gracza
void Player::setPosition(const SDL_FPoint& pos) {
    position = pos;
}

/// Zwraca aktualną pozycję gracza
SDL_FPoint Player::getPosition() const {
    return position;
}

/// Przypisuje komendę (wzorzec Command) do klawisza
void Player::bindCommand(SDL_Scancode key, std::unique_ptr<Command> command) {
    commandMap[key] = std::move(command);
}

/// Obsługa wejścia — wykonuje powiązane komendy zgodnie ze stanem klawiatury
void Player::handleInput(const Uint8* keystates) {
    velocity.x = 0;
    isMoving = false;

    for (const auto& [key, command] : commandMap) {
        if (keystates[key]) {
            command->Execute(*this);
        }
    }
}

/// Aktualizuje gracza: animacja, mruganie, fizyka ruchu, kolizje z ziemią i platformami
void Player::update(float deltaTime, const std::vector<SDL_Rect>& platforms, float groundY) {
    // Wybór animacji
    if (!onGround) {
        currentAnim = &jumpAnim;
    }
    else if (isMoving) {
        currentAnim = &runAnim;
    }
    else {
        currentAnim = &idleAnim;
    }
    currentAnim->update(deltaTime);

    // Mruganie (np. po otrzymaniu obrażeń)
    if (blinking) {
        blinkTimer += deltaTime;
        if (blinkTimer >= blinkDuration) {
            blinking = false;
            blinkTimer = 0.0f;
        }
    }

    if (weaponCooldown > 0.0f) weaponCooldown -= deltaTime;

    // Fizyka ruchu: pozycja x/y, grawitacja
    position.x += velocity.x * deltaTime;
    velocity.y += gravity * deltaTime;
    float newY = position.y + velocity.y * deltaTime;
    onGround = false;

    // Detekcja podłoża (grunt)
    if (position.y + size.y <= groundY && newY + size.y >= groundY) {
        newY = groundY - size.y;
        velocity.y = 0;
        onGround = true;
    }

    // Detekcja kolizji z platformami (góra platformy, tolerancja)
    const float buffer = 3.0f;
    for (const auto& plat : platforms) {
        float platLeft = plat.x;
        float platRight = plat.x + plat.w;
        float nextBottom = newY + size.y;

        bool closeToTop = nextBottom >= plat.y && nextBottom <= plat.y + buffer;
        bool xOverlap = position.x + size.x > platLeft && position.x < platRight;

        if (velocity.y >= 0 && closeToTop && xOverlap) {
            newY = plat.y - size.y;
            velocity.y = 0;
            onGround = true;
            break;
        }
    }
    position.y = newY;
}

/// Renderuje gracza z uwzględnieniem kamery i efektu mrugania (przezroczystość)
void Player::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Texture* texture = currentAnim->getCurrentFrame();
    SDL_Rect dstRect = {
        static_cast<int>(position.x) - camera.x,
        static_cast<int>(position.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };

    if (blinking) {
        float phase = fmodf(blinkTimer * blinkFrequency, 1.0f);
        if (phase < 0.5f) {
            SDL_SetTextureAlphaMod(texture, 60);
        }
        else {
            SDL_SetTextureAlphaMod(texture, 255);
        }
    }
    else {
        SDL_SetTextureAlphaMod(texture, 255);
    }

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

/// Zwraca prostokąt kolizyjny gracza
SDL_Rect Player::getRect() const {
    return {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

/// Zwraca aktualną prędkość gracza
SDL_FPoint Player::getVelocity() const {
    return velocity;
}

/// Zwraca rozmiar gracza
SDL_FPoint Player::getSize() const {
    return size;
}

/// Zwraca, czy gracz stoi na ziemi/platformie
bool Player::isOnGround() const {
    return onGround;
}

/// Przesuwa gracza o zadany wektor
void Player::moveBy(SDL_FPoint offset) {
    position.x += offset.x;
    position.y += offset.y;
}

/// Uruchamia mruganie gracza na określony czas (np. po obrażeniach)
void Player::startBlink(float duration) {
    blinking = true;
    blinkDuration = duration;
    blinkTimer = 0.0f;
}

/// Zwraca, czy gracz aktualnie mruga
bool Player::isBlinking() const {
    return blinking;
}

// Ustawia dźwięk skoku gracza
void Player::setJumpSound(Mix_Chunk* sound) {
    jumpSound = sound;
}

// Ustawia dźwięk rzutu nożem gracza
void Player::setKnifeThrowSound(Mix_Chunk* sound) {
    knifeThrowSound = sound;
}

// Zwraca wskaźnik do dźwięku rzucania nożem 
Mix_Chunk* Player::getKnifeThrowSound() {
    return knifeThrowSound;
}

// Zwraca, czy gracz może rzucić bronią (cooldown)
bool Player::canShoot() const {
    return weaponCooldown <= 0.0f;
}

// Resetuje cooldown rzutu bronią
void Player::resetWeaponCooldown() {
    weaponCooldown = weaponCooldownDuration;
}

/// Skok gracza (jeśli stoi na ziemi/platformie, odtwarza dźwięk)
void Player::Jump() {
    if (onGround) {
        velocity.y = jumpStrength;
        onGround = false;

        if (jumpSound) {
            Mix_PlayChannel(-1, jumpSound, 0);
        }
    }
}

/// Ruch w lewo
void Player::MoveLeft() {
    velocity.x = -speed;
    isMoving = true;
}

/// Ruch w prawo
void Player::MoveRight() {
    velocity.x = speed;
    isMoving = true;
}

/// Próba rzutu bronią (tworzy instancję broni i dodaje ją do listy broni)
void Player::tryThrowWeapon(std::shared_ptr<GameData> data, SDL_Texture* weaponTexture, std::vector<Weapon>& weaponList)
{
    Weapon weapon;
    SDL_FPoint playerPos = getPosition();

    SDL_FPoint weaponStart = {
        playerPos.x + 20.0f,
        playerPos.y + 10.0f
    };

    weapon.init(data, weaponTexture, weaponStart);
    weaponList.push_back(weapon);

    resetWeaponCooldown();
}

/// Ogranicza ruch gracza do podanych granic (np. nie wypada poza mapę)
void Player::constrainToBounds(float minX, float maxX) {
    if (position.x < minX) {
        position.x = minX;
        velocity.x = 0;
    }
    if (position.x + size.x > maxX) {
        position.x = maxX - size.x;
        velocity.x = 0;
    }
}