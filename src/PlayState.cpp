#include "PlayState.hpp"

PlayState::PlayState(std::shared_ptr<GameData> data): _data(std::move(data)){}

void PlayState::Init()
{
    // T³o
    if (!_data->assetManager->hasTexture("background"))
        _data->assetManager->loadTexture("background", BACKGROUND_TEXTURE);
    _backgroundTexture = _data->assetManager->getTexture("background");

    if (!_data->assetManager->hasTexture("land"))
        _data->assetManager->loadTexture("land", LAND_TEXTURE);
    _landTexture = _data->assetManager->getTexture("land");

    if (!_data->assetManager->hasTexture("trophy"))
        _data->assetManager->loadTexture("trophy", TROPHY);

    // DŸwiêki
    if (!_data->assetManager->hasMusic("game_music"))
        _data->assetManager->loadMusic("game_music", GAME_MUSIC);

    gameMusic = _data->assetManager->getMusic("game_music");

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

    // Odtwarzanie muzyki w tle (jeœli nie gra)
    if (!Mix_PlayingMusic())
        Mix_PlayMusic(gameMusic, -1);
    
    // Inicjalizacja gracza
    _player.init(_data); // adapter wymagany: wrapper nad GameData lub refaktoring
    _player.setJumpSound(_data->assetManager->getSound("jump"));
    _player.setKnifeThrowSound(_data->assetManager->getSound("knife"));
    _player.setPosition({ 100.0f, groundY - _player.getSize().y}); // start nad ziemi¹

    _player.bindCommand(SDL_SCANCODE_LEFT, std::make_unique<MoveLeftCommand>());
    _player.bindCommand(SDL_SCANCODE_RIGHT, std::make_unique<MoveRightCommand>());
    _player.bindCommand(SDL_SCANCODE_SPACE, std::make_unique<JumpCommand>());
    _player.bindCommand(SDL_SCANCODE_RETURN, std::make_unique<AttackCommand>());

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

    // Przygotowanie œcie¿ek do klatek animacji monet
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
    ENEMY_1, ENEMY_2 // np. dwie klatki animacji
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
    _trophy.setPosition(2600, static_cast<float>(groundY - _trophy.getSize().y - 20)); // dostosuj do poziomu

    // Kamera
    _camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

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

        if (_data->inputManager->isKeyPressed(SDL_SCANCODE_RETURN)) {
            _player.tryThrowWeapon(_data, _weaponTexture, _weapons);
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    _player.handleInput(keystates);
}

void PlayState::Update(float dt)
{
    _player.update(dt, _platforms, groundY);

    // Kamera pod¹¿a za graczem w poziomie
    SDL_FPoint playerPos = _player.getPosition();
    _camera.x = static_cast<int>(playerPos.x) - _camera.w / 2;

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

    for (auto& enemy : _enemies) {

        SDL_Rect playerRect = _player.getRect();
        SDL_Rect enemyRect = enemy.getRect();

        if (enemy.IsAlive()) {
            enemy.update(dt);

            if (!_player.isBlinking() && SDL_HasIntersection(&playerRect, &enemyRect)) {
                _player.startBlink(1.0f); // 1 sekunda nieœmiertelnoœci
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

                if (_lives <= 0) {
                    _data->machine.AddState(std::make_unique<GameOverState>(_data, false, _score), true);
                }
            }
        }
    }

    for (auto& weapon : _weapons) {
        weapon.update(dt);
        for (auto& enemy : _enemies) {
            if (enemy.IsAlive() && weapon.isAlive() && weapon.checkCollision(enemy.getRect())) {
                weapon.Kill();
                enemy.Hit();
            }
        }
    }

    _weapons.erase(
        std::remove_if(_weapons.begin(), _weapons.end(),
            [](const Weapon& w) { return !w.isAlive(); }),
        _weapons.end()
    );

    // Usuwanie martwych wrogów
    _enemies.erase(
        std::remove_if(_enemies.begin(), _enemies.end(),
            [](const Enemy& e) { return !e.IsAlive(); }),
        _enemies.end());

    _trophy.update(dt);

    SDL_Rect playerRect = _player.getRect();
    SDL_Rect trophyRect = _trophy.getRect();

    if (SDL_HasIntersection(&playerRect, &trophyRect)) {
        Mix_HaltMusic();
        _data->machine.AddState(std::make_unique<GameOverState>(_data, true, _score), true);
    }

    // Ograniczenia kamery
    if (_camera.x < 0) _camera.x = 0;
}

void PlayState::Draw(float dt)
{
    SDL_Renderer* renderer = _data->renderer;
    SDL_RenderClear(renderer);

    // T³o
    if (_backgroundTexture)
        SDL_RenderCopy(renderer, _backgroundTexture, nullptr, nullptr);

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

    for (auto& coin : _coins) {
        coin.render(renderer, _camera);
    }

    for (auto& enemy : _enemies) {
        if (enemy.IsAlive()) {
            enemy.render(renderer, _camera);
        }
    }

    for (auto& weapon : _weapons) {
        weapon.render(renderer, _camera);
    }

    _player.render(renderer, _camera);

    _trophy.render(renderer, _camera);

    hud.render(WINDOW_WIDTH);

    SDL_RenderPresent(renderer);
}
