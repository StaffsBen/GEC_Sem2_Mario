#include "Character.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) {

	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	if (!m_texture->LoadFromFile(imagePath))
		std::cout << "Failed to load texture! Error: " << SDL_GetError() << std::endl;

	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;

	m_current_level_map = map;

	m_collision_radius = 15;

	m_alive = true;

	m_sfx = new SoundEffect();
	m_sfx->StopSFX();
}

Character::~Character() {

	m_renderer = nullptr;
}

void Character::Render() {

	
}

void Character::Update(float deltaTime, SDL_Event e) {

	if (m_moving_left)
		MoveLeft(deltaTime);
	else if (m_moving_right)
		MoveRight(deltaTime);

	//deals with jumping first
	if (m_jumping) {

		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

	//collision position variables
	int _centralX_position = (int)(m_position.x + (m_texture->GetWidth() / CENTRAL_X_POSITION_ADJUST)) / TILE_WIDTH; //* 0.5
	int _foot_position = (int)(m_position.y + m_texture->GetHeight() / FOOT_POSITION_ADJUST) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAT(_foot_position, _centralX_position) == 0)
		AddGravity(deltaTime);
	else
		m_can_jump = true; //collided with ground, can jump again
}

void Character::SetPosition(Vector2D new_position) {

	m_position = new_position;
}

Vector2D Character::GetPosition() {

	return m_position;
}

void Character::MoveLeft(float deltaTime) {

	m_facing_direction = FACING_LEFT;

	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime) {

	m_facing_direction = FACING_RIGHT;

	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime) {

	if ((m_position.y + 64) <= SCREEN_HEIGHT)
		m_position.y += GRAVITYVALUE * deltaTime;
	else
		m_can_jump = true;
}

void Character::Jump() {

	if (!m_jumping) {

		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

float Character::GetCollisionRadius() {

	return m_collision_radius;
}

void Character::SetAlive(bool isAlive) {

	m_alive = isAlive;
}