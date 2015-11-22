#include "Game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "Texture.h"
#include "Random.h"

Game* Game::sInstance = nullptr;

Game::Game()
	:mRenderer(*this)
	,mAssetCache(*this, "Assets/")
	,mShouldQuit(false)
{
//	_ASSERT(!Game::sInstance);
	Game::sInstance = this;
}

Game::~Game()
{
	mGameMode = nullptr;

	mAssetCache.Clear();
	mWorld.RemoveAllActors();
    Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	//_ASSERT(Game::sInstance);
	Game::sInstance = nullptr;
}

bool Game::Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL.");
		return false;
	}

	// Initialize Renderer
	if (!mRenderer.Init(1024, 768))
	{
		SDL_Log("Failed to initialize renderer.");
		return false;
	}
    
    // Initialize SDL audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        SDL_Log("Failed to initialize SDL audio.");
        return false;
    }

	// Initialize SDL TTF API
	if ( TTF_Init() != 0 )
	{
		SDL_Log( "Failed to initialize SDL TTF API" );
		return false;
	}

	// Initialize RNG
	Random::Init();

	// Start frame timer
	mTimer.Start();
    
    // Set up input
    AddInputMappings();

	// Run any code at game start
	StartGame();

	return true;
}

void Game::RunLoop()
{
	while (!mShouldQuit)
    {
        ProcessInput();
        Tick();
        GenerateOutput();
    }
}

void Game::Quit()
{
    mShouldQuit = true;
}

void Game::StartGame()
{
	mGameMode = GameMode::Spawn( *this );
}

void Game::ProcessInput()
{
    // Poll events from SDL
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mShouldQuit = true;
                break;
                
            case SDL_KEYDOWN:
                if (event.key.repeat == 0)
                {
                    HandleKeyPressed(event.key.keysym.sym);
                }
                break;
                
            case SDL_KEYUP:
                HandleKeyReleased(event.key.keysym.sym);
                break;
                
            default:
                // Ignore other events for now
                break;
        }
    }
}

void Game::AddInputMappings()
{
    mInput.AddActionMapping("Quit", SDLK_ESCAPE);
	mInput.AddActionMapping("Recenter", 'r');
	mInput.AddActionMapping("Regenerate", 'f');
    
    mInput.AddAxisMapping("Move", 'p', SDLK_SEMICOLON);
    mInput.AddAxisMapping("Yaw", 'd', 'a');
	mInput.AddAxisMapping("Pitch", 'w', 's');
    
    mInput.BindAction("Quit", IE_Released, this, &Game::Quit);
}

void Game::HandleKeyPressed(int key)
{
    mInput.HandleKeyPressed(key);
}

void Game::HandleKeyReleased(int key)
{
    mInput.HandleKeyReleased(key);
}

void Game::Tick()
{
    static const float FPS = 0.016666f;
    
    float deltaTime = mTimer.GetFrameTime(FPS);
    mTimerManager.Tick(deltaTime);
    mWorld.Tick(deltaTime);
    mPhysWorld.Tick(deltaTime);
}

void Game::GenerateOutput()
{
    mRenderer.RenderFrame();
}
