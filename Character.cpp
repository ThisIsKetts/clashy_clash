#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offSet{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offSet = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offSet.x,
            getScreenPos().y + offSet.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = 35.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offSet = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offSet.x - weapon.width * scale,
            getScreenPos().y + offSet.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = - 35.f;
    }

    // draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offSet.x, getScreenPos().y + offSet.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED);
}
