#include "GameOverState.hpp"

/// Konstruktor � przekazuje dane gry, informacj� o wygranej/przegranej oraz wynik ko�cowy
GameOverState::GameOverState(std::shared_ptr<GameData> data, bool win, int finalScore)
    : data(std::move(data)), win(win), score(finalScore)
{
}

/// Destruktor � nie zwalnia zasob�w r�cznie, assetami zarz�dza assetManager
GameOverState::~GameOverState() {}

/// Inicjalizuje stan ko�ca gry (�aduje zasoby, d�wi�k, czcionk�, t�o)
void GameOverState::Init() {
    if (initialized) return;
    loadAssets();
    initialized = true;
}

/// �aduje zasoby potrzebne do wy�wietlenia ekranu ko�ca gry (czcionka, t�o, d�wi�k)
void GameOverState::loadAssets() {
    // Czcionka
    data->assetManager->loadFont("robotoFontGameOver", ROBOTO_FONT, 48);
    font = data->assetManager->getFont("robotoFontGameOver");
    if (!font) {
        std::cerr << "B��d �adowania czcionki w GameOverState: " << TTF_GetError() << std::endl;
    }

    // T�o
    data->assetManager->loadTexture("gameover_bg", GAMEOVER_IMAGE);
    backgroundTexture = data->assetManager->getTexture("gameover_bg");

    // D�wi�k � zale�ny od wygranej/przegranej
    std::string soundKey = win ? "level_passed" : "level_failed";
    std::string soundPath = win ? LEVEL_PASSED_SOUND : LEVEL_FAILED_SOUND;
    data->assetManager->loadSound(soundKey, soundPath);
    gameOverSound = data->assetManager->getSound(soundKey);

    // Puszczamy d�wi�k ko�ca gry
    if (gameOverSound) {
        Mix_PlayChannel(-1, gameOverSound, 0);
    }
}

/// Obs�uguje wej�cie u�ytkownika (wyj�cie z gry lub restart po naci�ni�ciu R)
void GameOverState::HandleInput() {
    if (!initialized) Init();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT)
            exit(0);

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_r) {
                data->machine.AddState(std::make_unique<PlayState>(data), true); // Replace na now� gr�
                return;
            }
        }
    }
}

/// Aktualizuje stan ko�ca gry (brak logiki do aktualizacji)
void GameOverState::Update(float deltaTime) {
    if (!initialized) Init();
    // Brak logiki aktualizacji
}

/// Renderuje ekran ko�ca gry: t�o, komunikaty o wyniku, informacj� o restarcie
void GameOverState::Draw(float deltaTime) {
    if (!initialized) Init();

    SDL_Renderer* renderer = data->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Rysowanie t�a
    if (backgroundTexture) {
        int texW = 0, texH = 0;
        SDL_QueryTexture(backgroundTexture, nullptr, nullptr, &texW, &texH);
        SDL_Rect dst = { WINDOW_WIDTH / 2 - texW / 2, WINDOW_HEIGHT / 2 - texH / 2 - 60, texW, texH };
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, &dst);
    }

    // Przygotowanie tekst�w
    std::string message = win ? "WYGRALES!" : "PRZEGRALES!";
    std::string scoreText = "Wynik: " + std::to_string(score);
    std::string restartText = "Nacisnij klawisz R, aby zrestartowac gre";

    SDL_Color colorMessage = win ? SDL_Color{ 0, 255, 0 } : SDL_Color{ 255, 0, 0 };
    SDL_Color white = { 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0 };

    // Generowanie powierzchni tekstowych
    SDL_Surface* msgSurf = TTF_RenderUTF8_Blended(font, message.c_str(), colorMessage);
    SDL_Surface* scoreSurf = TTF_RenderUTF8_Blended(font, scoreText.c_str(), white);
    SDL_Surface* restartSurf = TTF_RenderUTF8_Blended(font, restartText.c_str(), yellow);

    SDL_Texture* msgTex = SDL_CreateTextureFromSurface(renderer, msgSurf);
    SDL_Texture* scoreTex = SDL_CreateTextureFromSurface(renderer, scoreSurf);
    SDL_Texture* restartTex = SDL_CreateTextureFromSurface(renderer, restartSurf);

    int msgY = WINDOW_HEIGHT / 2 + 40;
    int scoreY = msgY + 60;
    int restartY = scoreY + 50;

    SDL_Rect msgRect = { WINDOW_WIDTH / 2 - msgSurf->w / 2, msgY, msgSurf->w, msgSurf->h };
    SDL_Rect scoreRect = { WINDOW_WIDTH / 2 - scoreSurf->w / 2, scoreY, scoreSurf->w, scoreSurf->h };
    SDL_Rect restartRect = { WINDOW_WIDTH / 2 - restartSurf->w / 2, restartY, restartSurf->w, restartSurf->h };

    // Render tekst�w
    SDL_RenderCopy(renderer, msgTex, nullptr, &msgRect);
    SDL_RenderCopy(renderer, scoreTex, nullptr, &scoreRect);
    SDL_RenderCopy(renderer, restartTex, nullptr, &restartRect);

    // Sprz�tanie powierzchni i tekstur
    SDL_FreeSurface(msgSurf);
    SDL_FreeSurface(scoreSurf);
    SDL_FreeSurface(restartSurf);
    SDL_DestroyTexture(msgTex);
    SDL_DestroyTexture(scoreTex);
    SDL_DestroyTexture(restartTex);

    SDL_RenderPresent(renderer);
}