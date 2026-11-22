#pragma once
#include <iostream>
#include "GameObjects.h"
#include "data.h"

int runScrollMenu(const std::string& title, const std::vector<std::string>& options);

void runMidtermAttestation(Student& student);

void runSession(Student& student);

void startGame(GameSession& session);