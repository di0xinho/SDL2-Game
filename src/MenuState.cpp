#include "MenuState.hpp"

/// Konstruktor ó inicjalizuje stan menu g≥Ûwnego, zapisuje wskaünik do danych gry
MenuState::MenuState(std::shared_ptr<GameData> data) : data(std::move(data)) {}

/// Destruktor ó assetami zarzπdza assetManager, nie zwalniamy rÍcznie!
MenuState::~MenuState() {}

/// Inicjalizuje zasoby potrzebne do menu: t≥o, przycisk, czcionka, muzyka.
/// Ustawia pozycjÍ przycisku "Graj" wyúrodkowanπ na ekranie.
void MenuState::Init() {
    if (initialized) return;

    // £adowanie zasobÛw przez AssetManager
    data->assetManager->loadTexture("background_2", BACKGROUND_TEXTURE_2);
    data->assetManager->loadTexture("play_button", PLAY_BUTTON);
    data->assetManager->loadFont("robotoFont", ROBOTO_FONT, fontSize);
    data->assetManager->loadMusic("menuMusic", MENU_MUSIC);

    backgroundTexture = data->assetManager->getTexture("background_2");
    playButtonTexture = data->assetManager->getTexture("play_button");
    font = data->assetManager->getFont("robotoFont");
    menuMusic = data->assetManager->getMusic("menuMusic");

    // Odtwarzanie muzyki w tle 
    if (!Mix_PlayingMusic())
        Mix_PlayMusic(menuMusic, -1);

    // Skalowanie i pozycjonowanie przycisku
    int texW, texH;
    SDL_QueryTexture(playButtonTexture, nullptr, nullptr, &texW, &texH);

    playButtonRect.w = static_cast<int>(texW * buttonScale);
    playButtonRect.h = static_cast<int>(texH * buttonScale);
    playButtonRect.x = (WINDOW_WIDTH - playButtonRect.w) / 2;
    playButtonRect.y = (WINDOW_HEIGHT - playButtonRect.h) / 2;

    initialized = true;
}

/// Obs≥uguje wejúcie uøytkownika w menu:
/// - zamkniÍcie okna,
/// - klikniÍcie przycisku "Graj" (start gry).
void MenuState::HandleInput() {
    if (!initialized) Init();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT)
            exit(0);

        // Obs≥uga klikniÍcia na przycisk
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            if (x >= playButtonRect.x && x <= playButtonRect.x + playButtonRect.w &&
                y >= playButtonRect.y && y <= playButtonRect.y + playButtonRect.h) {
                Mix_HaltMusic();
                data->machine.AddState(std::make_unique<PlayState>(data), true);
            }
        }
    }
}

/// Aktualizuje logikÍ menu 
void MenuState::Update(float deltaTime) {
    if (!initialized) Init();
    // Brak logiki czasowej w menu
}

/// Renderuje ekran menu: t≥o, przycisk, instrukcjÍ do uruchomienia gry
void MenuState::Draw(float deltaTime) {
    if (!initialized) Init();

    SDL_Renderer* renderer = data->renderer;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // T≥o
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Przycisk
    SDL_RenderCopy(renderer, playButtonTexture, nullptr, &playButtonRect);

    // Napis informacyjny
    SDL_Color color = { 50, 50, 50 };
    const char* infoText = "Nacisnij guzik, aby wystartowac gre";
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, infoText, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_Rect textRect = {
        WINDOW_WIDTH / 2 - textWidth / 2,
        playButtonRect.y - textHeight - 20,
        textWidth,
        textHeight
    };

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}