#include "pch.h"
#include "Framework.h"

void Framework::Init(int width, int height, const std::string& name)
{
    srand(std::time(NULL));

    windowSize.x = width;
    windowSize.y = height;

    window.create(sf::VideoMode(windowSize.x, windowSize.y), name);

    SCENE_MANAGER.Init();
    InputManager::Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = realDeltaTime = clock.restart();
        deltaTime *= timeScale;

        time += deltaTime;
        realTime += realDeltaTime;

        InputManager::Clear(); // Ű �Է� �ʱ�ȭ

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputManager::UpdateEvent(event); // Ű �Է� �̺�Ʈ ó��
        }

        //Update
        InputManager::Update(GetDeltaTime());
        SCENE_MANAGER.Update(GetDeltaTime());
        
        // Draw
        window.clear();
        SCENE_MANAGER.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MANAGER.Release();
}