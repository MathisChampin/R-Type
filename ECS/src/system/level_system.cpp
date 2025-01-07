#include "score.hpp"
#include "level.hpp"
#include "Registry.hpp"
#include "system.hpp"

void check_level(
    sparse_array<component::score> &scores,
    sparse_array<component::level> &levels,
    int i
)
{
    const auto &score = scores[i];
    auto &level = levels[i];

    if (score.score >= 100)
        level._levelKey = component::level::Level1;
    if (score.score >= 200)
        level._levelKey = component::level::Level2;
    if (score.score >= 300)
        level._levelKey = component::level::Level3;
    if (score.score >= 400)
        level._levelKey = component::level::Level4;
    if (score.score >= 500)
        level._levelKey = component::level::Level5;
    if (score.score >= 700)
        level._levelKey = component::level::Level6;
    if (score.score >= 900)
        level._levelKey = component::level::Level7;
    if (score.score >= 1200)
        level._levelKey = component::level::Level8;
}

void System::level_system(registry &reg)
{
    auto &scores = reg.get_components<component::score>();
    auto &levels = reg.get_components<component::level>();

    for (size_t i = 0; i < scores.size() && i < levels.size(); ++i) {
        check_level(scores, levels, i);
    }
}
