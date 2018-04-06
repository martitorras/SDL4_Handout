#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// ship
	ship.x = 0;
	ship.y = 0;
	ship.w = 550;
	ship.h = 200;

	// ship bottom
	ship_bottom.x = 0;
	ship_bottom.y = 200;
	ship_bottom.w = 550;
	ship_bottom.h = 8;

	//girl animation
	girl.PushBack({ 620, 15, 40, 58 });
	girl.PushBack({ 620, 79, 40, 58 });
	girl.PushBack({ 620, 143, 40, 58 });
	girl.PushBack({ 620, 79, 40, 58 });
	girl.speed = 0.08f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	y = -29;
	i = -1;
	up = true;
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	App->render->Blit(graphics, -8, y, &ship, 0.95f);
	App->render->Blit(graphics, -8, y + 199, &ship_bottom, 0.95f);
	App->render->Blit(graphics, 188, y + 127, &(girl.GetCurrentFrame()), 0.95f);
	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	
	App->render->Blit(graphics, 0, 170, &ground);
	++i;
	if (i == 14) {
		if (y > -33 && up == true) --y;
		else if (y == -33 && up == true) up = false;
		else if (y < -29 && up == false) ++y;
		else if (y == -29 && up == false) up = true;
		i = 0;
	}

	return UPDATE_CONTINUE;
}