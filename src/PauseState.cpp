#include "PauseState.hpp"

PauseState::PauseState(std::shared_ptr<GameData> data): data(std::move(data)){}

PauseState::~PauseState() {}

void PauseState::Init() {
    if (initialized) return;
    initFont();
    initialized = true;
}

void PauseState::initFont() {
    data->assetManager->loadFont("robotoFontPause", ROBOTO_FONT, 48);
    font = data->assetManager->getFont("robotoFontPause");
    if (!font) {
        std::cerr << "Blad ladowania czcionki w PauseState: " << TTF_GetError() << std::endl;
    }
}

void PauseState::HandleInput() {
    if (!initialized) Init();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        data->inputManager->update(event);
        
        if (data->inputManager->isKeyPressed(SDL_SCANCODE_ESCAPE) || data->inputManager->isKeyPressed(SDL_SCANCODE_P)) {
            Mix_ResumeMusic();
            data->machine.RemoveState(); 
        }
    }
}

void PauseState::Update(float dt) {
    if (!initialized) Init();
}

void PauseState::Draw(float dt) {
    if (!initialized) Init();

    SDL_Renderer* renderer = data->renderer;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_Rect overlay = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderFillRect(renderer, &overlay);

    // Tytu³: "PAUZA"
    const char* title = "PAUZA";
    SDL_Surface* titleSurface = TTF_RenderUTF8_Blended(font, title, titleColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    int titleW = titleSurface->w;
    int titleH = titleSurface->h;
    SDL_Rect titleRect = { WINDOW_WIDTH / 2 - titleW / 2, 200, titleW, titleH };
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    // Instrukcja
    const char* info = "Wcisnij P lub ESC, aby kontynuowac";
    SDL_Surface* infoSurface = TTF_RenderUTF8_Blended(font, info, infoColor);
    SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(renderer, infoSurface);
    int infoW = infoSurface->w;
    int infoH = infoSurface->h;
    SDL_Rect infoRect = { WINDOW_WIDTH / 2 - infoW / 2, 300, infoW, infoH };
    SDL_RenderCopy(renderer, infoTexture, nullptr, &infoRect);
    SDL_FreeSurface(infoSurface);
    SDL_DestroyTexture(infoTexture);

    SDL_RenderPresent(renderer);
}