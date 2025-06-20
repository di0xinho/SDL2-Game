#include "PlayState.hpp"

/// Konstruktor � przekazuje wska�nik do danych gry
PlayState::PlayState(std::shared_ptr<GameData> data) : _data(std::move(data)) {}

/// Inicjalizuje wszystkie zasoby, obiekty i parametry potrzebne do rozgrywki
void PlayState::Init()
{
    // T�o
    if (!_data->assetManager->hasTexture("background"))
        _data->assetManager->loadTexture("background", BACKGROUND_TEXTURE);
    _backgroundTexture = _data->assetManager->getTexture("background");

    // Powierzchnia
    if (!_data->assetManager->hasTexture("land"))
        _data->assetManager->loadTexture("land", LAND_TEXTURE);
    _landTexture = _data->assetManager->getTexture("land");

    // Trofeum
    if (!_data->assetManager->hasTexture("trophy"))
        _data->assetManager->loadTexture("trophy", TROPHY);

    // D�wi�ki
    if (!_data->assetManager->hasMusic("game_music"))
        _data->assetManager->loadMusic("game_music", GAME_MUSIC);

    // Pobranie muzyki rozgrywki z mened�era asset�w
    gameMusic = _data->assetManager->getMusic("game_music");

    // �adowanie d�wi�k�w
    if (!_data->assetManager->hasSound("coin"))
        _data->assetManager->loadSound("coin", COIN_SOUND);
    if (!_data->assetManager->hasSound("jump"))
        _data->assetManager->loadSound("jump", JUMP_SOUND);
    if (!_data->assetManager->hasSound("knife"))
        _data->assetManager->loadSound("knife", KNIFE_THROW_SOUND);
    if (!_data->assetManager->hasSound("punch"))
        _data->assetManager->loadSound("punch", PUNCH_SOUND);

    if (!_data->assetManager->hasFont("roboto"))
        _data->assetManager->loadFont("roboto", ROBOTO_FONT, 24);

    if (!_data->assetManager->hasSound("enemy_hit"))
        _data->assetManager->loadSound("enemy_hit", OUCH_SOUND);

    if (!_data->assetManager->hasTexture("knife"))
        _data->assetManager->loadTexture("knife", SWORD_TEXTURE);

    _weaponTexture = _data->assetManager->getTexture("knife");
    robotoFont = _data->assetManager->getFont("roboto");
    hud = HUD(_data->renderer, robotoFont);

    // Odtwarzanie muzyki w tle (je�li nie gra)
    if (!Mix_PlayingMusic())
        Mix_PlayMusic(gameMusic, -1);

    // Inicjalizacja gracza
    _player.init(_data);
    _player.setJumpSound(_data->assetManager->getSound("jump"));
    _player.setKnifeThrowSound(_data->assetManager->getSound("knife"));
    _player.setPosition({ 100.0f, groundY - _player.getSize().y }); // start nad ziemi�

    // Bindowanie klawiszy pod sterowanie graczem (mapowanie klawiszy na polecenia)
    _player.bindCommand(SDL_SCANCODE_LEFT, std::make_unique<MoveLeftCommand>());
    _player.bindCommand(SDL_SCANCODE_RIGHT, std::make_unique<MoveRightCommand>());
    _player.bindCommand(SDL_SCANCODE_SPACE, std::make_unique<JumpCommand>());
    _player.bindCommand(SDL_SCANCODE_RETURN, std::make_unique<AttackCommand>(_weaponTexture, _weapons));

    // Definiowanie po�o�enia i wielko�ci platform
    _platforms = {
        { 200, 400, 100, 20 },
        { 400, 300, 100, 20 },
        { 600, 200, 120, 20 },
        { 800, 150, 150, 20 },
        { 1000, 250, 150, 20 },
        { 1250, 200, 170, 20 },
        { 1400, 100, 150, 30 },
        { 1700, 100, 250, 20 },
        { 2100, 200, 250, 20 }
    };

    // Przygotowanie �cie�ek do klatek animacji monet
    std::vector<const char*> coinFrames = {
        COIN_1, COIN_2, COIN_3, COIN_4, COIN_5, COIN_6,
        COIN_7, COIN_8, COIN_9, COIN_10, COIN_11, COIN_12,
        COIN_13, COIN_14
    };

    std::vector<std::pair<float, float>> coinPositions = {
        {250.0f, 370.0f}, {450.0f, 270.0f}, {660.0f, 170.0f},
        {875.0f, 120.0f}, {1075.0f, 220.0f}, {1325.0f, 170.0f},
        {1475.0f, 70.0f}, {1825.0f, 70.0f}, {2225.0f, 170.0f}
    };

    _coins.reserve(coinPositions.size());

    for (const auto& pos : coinPositions) {
        Coin coin;
        coin.init(_data, coinFrames, { pos.first, pos.second });
        _coins.push_back(coin);
    }

    std::vector<const char*> enemyFrames = {
        ENEMY_1, ENEMY_2
    };

    std::vector<float> enemyXPositions = { 500.0f, 800.0f, 1000.0f, 1250.0f, 1500.0f };
    const float enemyY = static_cast<float>(groundY - 50);
    const float patrolRange = 100.0f;

    _enemies.reserve(enemyXPositions.size());

    for (const auto& x : enemyXPositions) {
        Enemy enemy;
        enemy.init(_data, enemyFrames, { x, enemyY }, patrolRange);
        enemy.setHitSound(_data->assetManager->getSound("enemy_hit"));
        _enemies.push_back(enemy);
    }

    _trophy.init(_data);
    _trophy.setPosition(2600, static_cast<float>(groundY - _trophy.getSize().y - 20));

    // Kamera
    _camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

/// Obs�uguje wej�cie u�ytkownika podczas rozgrywki (ruch, pauza, wyj�cie z gry)
void PlayState::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);

        _data->inputManager->update(event);

        if (_data->inputManager->isKeyPressed(SDL_SCANCODE_ESCAPE)) {
            _data->machine.AddState(std::make_unique<PauseState>(_data), false);
            Mix_PauseMusic();
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    _player.handleInput(keystates);
}

/// Aktualizuje ca�� logik� gry: gracza, platformy, monety, wrog�w, bro�, kamer�, HUD
void PlayState::Update(float dt)
{
    _player.update(dt, _platforms, groundY);
    _player.constrainToBounds(0.0f, 2650.0f);

    // Kamera pod��a za graczem w poziomie
    SDL_FPoint playerPos = _player.getPosition();
    _camera.x = static_cast<int>(playerPos.x) - _camera.w / 2;

    // Kolizja gracza z monetami
    for (auto& coin : _coins) {

        SDL_Rect playerRect = _player.getRect();
        SDL_Rect coinRect = coin.getRect();

        if (!coin.isCollected() && SDL_HasIntersection(&playerRect, &coinRect)) {
            coin.collect();
            _score++;
            hud.updateScore(_score);
            Mix_PlayChannel(-1, _data->assetManager->getSound("coin"), 0);
        }
        coin.update(dt);
    }

    // Kolizja gracza z wrogami
    for (auto& enemy : _enemies) {

        SDL_Rect playerRect = _player.getRect();
        SDL_Rect enemyRect = enemy.getRect();

        if (enemy.IsAlive()) {
            enemy.update(dt);

            if (!_player.isBlinking() && SDL_HasIntersection(&playerRect, &enemyRect)) {
                _player.startBlink(1.0f); // 1 sekunda nie�miertelno�ci
                Mix_PlayChannel(-1, _data->assetManager->getSound("punch"), 0);
                _lives--;
                hud.updateLives(_lives);

                float knockbackStrength = 150.0f;
                SDL_FPoint offset = { 0, -50.0f };

                if (playerRect.x < enemyRect.x)
                    offset.x = -knockbackStrength;
                else
                    offset.x = knockbackStrength;

                _player.moveBy(offset);

                // Logika przegranej (je�li mamy 0 �y� = przegrywamy)
                if (_lives <= 0) {
                    Mix_HaltMusic();
                    _data->machine.AddState(std::make_unique<GameOverState>(_data, false, _score), true);
                }
            }
        }
    }

    // Aktualizacja broni i sprawdzanie kolizji z wrogami
    for (auto& weapon : _weapons) {
        weapon.update(dt);
        for (auto& enemy : _enemies) {
            if (enemy.IsAlive() && weapon.isAlive() && weapon.checkCollision(enemy.getRect())) {
                weapon.Kill();
                enemy.Hit();
            }
        }
    }

    // Usuwanie broni, kt�ra przesta�a by� aktywna
    _weapons.erase(
        std::remove_if(_weapons.begin(), _weapons.end(),
            [](const Weapon& w) { return !w.isAlive(); }),
        _weapons.end()
    );

    // Usuwanie martwych wrog�w
    _enemies.erase(
        std::remove_if(_enemies.begin(), _enemies.end(),
            [](const Enemy& e) { return !e.IsAlive(); }),
        _enemies.end());

    _trophy.update(dt);

    SDL_Rect playerRect = _player.getRect();
    SDL_Rect trophyRect = _trophy.getRect();

    // Wygrana � dotkni�cie trofeum
    if (SDL_HasIntersection(&playerRect, &trophyRect)) {
        Mix_HaltMusic();
        _data->machine.AddState(std::make_unique<GameOverState>(_data, true, _score), true);
    }

    // Ograniczenia kamery
    if (_camera.x < 0) _camera.x = 0;
}

/// Renderuje ca�� scen� gry: t�o, ziemi�, platformy, monety, wrog�w, bro�, gracza, trofeum i HUD
void PlayState::Draw(float dt)
{
    SDL_Renderer* renderer = _data->renderer;
    SDL_RenderClear(renderer);

    // T�o
    if (_backgroundTexture)
        SDL_RenderCopy(renderer, _backgroundTexture, nullptr, nullptr);

    // Ziemia (land)
    if (_landTexture) {
        SDL_Rect groundRect = {
            0 - _camera.x,
            static_cast<int>(groundY) - _camera.y,
            WINDOW_WIDTH * 3,
            WINDOW_HEIGHT - static_cast<int>(groundY)
        };
        SDL_RenderCopy(renderer, _landTexture, nullptr, &groundRect);
    }

    // Platformy
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    for (const auto& plat : _platforms) {
        SDL_Rect drawRect = plat;
        drawRect.x -= _camera.x;
        drawRect.y -= _camera.y;
        SDL_RenderFillRect(renderer, &drawRect);
    }

    // Monety
    for (auto& coin : _coins) {
        coin.render(renderer, _camera);
    }

    // Przeciwnicy
    for (auto& enemy : _enemies) {
        if (enemy.IsAlive()) {
            enemy.render(renderer, _camera);
        }
    }

    // Bronie
    for (auto& weapon : _weapons) {
        weapon.render(renderer, _camera);
    }

    // Gracz
    _player.render(renderer, _camera);

    // Trofeum
    _trophy.render(renderer, _camera);

    // HUD
    hud.render(WINDOW_WIDTH);

    // Na koniec prezentujemy przygotowan� w rendererze zawarto��
    SDL_RenderPresent(renderer);
}