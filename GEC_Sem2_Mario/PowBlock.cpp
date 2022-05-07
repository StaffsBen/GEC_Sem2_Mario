#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelmap, Vector2D position) {

	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture." << std::endl;
		return;
	}

	m_level_map = levelmap;
	m_single_sprite_w = m_texture->GetWidth() / 3; //there are three images in this sprite sheet in a row
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = position; //Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260)

	m_sfx = new SoundEffect();
	m_sfx->StopSFX();
}

PowBlock::~PowBlock() {

	m_renderer = nullptr;

	delete m_texture;
	m_texture = nullptr;

	m_level_map = nullptr;
}

void PowBlock::Render() {

	if (m_num_hits_left > 0) {
		
		//get the portion of the sheet we want to draw
		int left = m_single_sprite_w * (m_num_hits_left - 1);

		//				             xPos, yPos, sprite sheet width,sprite sheet height
		SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

		//determine where to draw it
		SDL_Rect dest_rect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_w, m_single_sprite_h };

		//draw the sprite
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeHit(int _levelNo) {

	m_num_hits_left = m_num_hits_left - 1;
	m_sfx->PlaySFX("SFX/BumpSFX.wav");

	if (m_num_hits_left <= 0) {

		m_num_hits_left = 0;

		if (_levelNo == 1) {

			//down levelmap, then right
			m_level_map->ChangeTileAt(8, 7, 0);
			m_level_map->ChangeTileAt(8, 8, 0);
		}
		else if (_levelNo == 2) {

			//down levelmap, then right
			m_level_map->ChangeTileAt(5, 8, 0);
			m_level_map->ChangeTileAt(5, 9, 0);
		}
	}
}