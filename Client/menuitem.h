#pragma once

#include <string>
#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include <hgecolor.h>


class hgeGUIMenuItem : public hgeGUIObject {
public:
    hgeGUIMenuItem(int id, hgeFont* fnt, HEFFECT snd, float x, float y, float delay, const char* title);

    void Render() override;
    void Update(float dt) override;

    void Enter() override;
    void Leave() override;
    bool IsDone() override;
    void Focus(bool bFocused) override;
    void MouseOver(bool bOver) override;

    bool MouseLButton(bool bDown) override;
    bool KeyClick(int key, int chr) override;

private:
    hgeFont* fnt;
    HEFFECT snd;
    float delay;
    std::string title;

    hgeColor scolor, dcolor, scolor2, dcolor2, sshadow, dshadow;
    hgeColor color, shadow;
    float soffset, doffset, offset;
    float timer, timer2;
};
