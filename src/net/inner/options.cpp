#include "options.hpp"

void RoleOptionsData::serialize(Buffer &buffer) {

}

bool RoleOptionsData::deserialize(Buffer &buffer) {
    return false;
}

void GameOptionsData::serialize(Buffer &buffer) {

}

bool GameOptionsData::deserialize(Buffer &buffer) {
    max_players = buffer.read_byte();
    cout << "max players: " << max_players << endl;
    keywords = buffer.read_unsigned_int_le();
    map_identifier = buffer.read_byte();
    player_speed_modifier = buffer.read_float_le();
    crewmate_light_modifier = buffer.read_float_le();
    imposter_light_modifier = buffer.read_float_le();
    kill_cooldown = buffer.read_float_le();
    total_common_tasks = buffer.read_byte();
    total_long_tasks = buffer.read_byte();
    total_short_tasks = buffer.read_byte();
    total_emergency_meetings = buffer.read_int_le();
    total_imposters = buffer.read_byte();
    kill_distance = buffer.read_byte();
    total_discussion_time = buffer.read_int_le();
    total_voting_time = buffer.read_int_le();
    is_default_settings = buffer.read_byte();

    if (version > 1) {
        total_emergency_cooldown = buffer.read_byte();
    }
    if (version > 2) {
        expose_imposter_on_eject = buffer.read_byte();
        show_visual_tasks = buffer.read_byte();
    }
    if (version > 3) {
        do_anonymous_voting = buffer.read_byte();
        task_bar_mode = buffer.read_byte();
    }
    if (version > 4) {
        //deserialize roles
    }
    return true;
}
