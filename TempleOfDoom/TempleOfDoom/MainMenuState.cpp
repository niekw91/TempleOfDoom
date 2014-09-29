#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "GameState.h"
#include "MainMenuState.h"

TOD::MainMenuState TOD::MainMenuState::m_MainMenuState;

namespace TOD {
	void MainMenuState::Init() {

	}

	void MainMenuState::Cleanup() {

	}

	void MainMenuState::HandleEvents() {

	}

	void MainMenuState::Update() {

	}

	void MainMenuState::Render() {
		//ClearScreen();
		system("CLS");
		// Create main menu banner
		const std::string textfile("MainMenuBanner.txt");
		std::ifstream input_file(textfile);

		std::string line;
		while (getline(input_file, line)) {
			std::cout << line << '\n';
		}

		// Read input
		std::cin.get();


	}

	void MainMenuState::ClearScreen() {
		std::cout << std::string(100, '\n');
	}
}