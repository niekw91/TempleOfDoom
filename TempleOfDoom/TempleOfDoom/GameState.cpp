#include "stdafx.h"

#include "GameState.h"

void GameState::ChangeState(Game* game, GameState* state) {
	game->StateManager()->ChangeState(state);
}