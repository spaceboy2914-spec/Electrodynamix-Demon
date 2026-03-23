#include <Geode/Geode.hpp>
#include <Geode/modify/GJDifficultySprite.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

// Electrodynamix = level ID 16
constexpr int ELECTRODYNAMIX_ID = 16;

// Store current level ID
static int g_currentLevelID = -1;

// Hook LevelInfoLayer to detect which level is open
class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelInfoLayer::init(level, p1)) return false;

        if (level) {
            g_currentLevelID = level->m_levelID;
        }

        return true;
    }
};

// Hook difficulty sprite
class $modify(MyDifficultySprite, GJDifficultySprite) {
    void updateDifficultyFrame(int difficulty, GJDifficultyName name) {
        // If it's Electrodynamix → force Demon
        if (g_currentLevelID == ELECTRODYNAMIX_ID) {
            difficulty = 5; // Demon
            name = GJDifficultyName::Demon;
        }

        GJDifficultySprite::updateDifficultyFrame(difficulty, name);
    }
};
