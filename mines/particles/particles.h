#pragma once
#include <SFML/Graphics.hpp>

struct Particle {
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Color color;
	float lifetime = 1.0f;
};

namespace particles {
	inline std::vector<Particle> currentParticles;
	inline void spawnExplosion(sf::Vector2f position, sf::Color color) {
		for (int i = 0; i < 30; i++) {
			float angle = (std::rand() % 360) * 3.14159f / 180.0f;
			float speed = (std::rand() % 360) + 50.0f;

			currentParticles.push_back({
				position,
				{std::cos(angle) * speed, std::sin(angle) * speed},
				color
			});
		}
	}
}