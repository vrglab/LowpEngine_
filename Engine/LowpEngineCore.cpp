#include "lppch.h"
#include "LowpEngineCore.h"

LP_Export int InitGame(GameInfo* initInfo, Game* game)
{
    game->info = initInfo;
    game->soundSystem = new SoundSystem();
    InitSoundSystem(initInfo->soundSystemInfo, game->soundSystem);

    game->createdWindow = new Windowing(game->info);
    game->createdWindow->Open();

    RenderingEngineCreateInfo* renderingEngineCreateInfo = new RenderingEngineCreateInfo();
    renderingEngineCreateInfo->window = game->createdWindow->sdl_window;
    renderingEngineCreateInfo->rendererType = GetRendererType();

    game->renderingFramework = InitializeRendering(renderingEngineCreateInfo);

    delete renderingEngineCreateInfo;

    return LowpResultCodes::Success;
}

LP_Export int StartGame(Game* game)
{
    while(!game->createdWindow->ShouldClose())
    {
        game->createdWindow->ProcessEvents();
        ClearScreen(game->renderingFramework);

        SwapBuffers(game->renderingFramework);
    }

    return LowpResultCodes::Success;
}

LP_Export int CleanupGame(Game* game)
{
    delete game->createdWindow;
    delete game->info->resolution;
    delete game->info;
    delete game->renderingFramework;
    delete game->soundSystem;
    
    return LowpResultCodes::Success;
}
