#ifndef INNER_OPTIONS_HPP
#define INNER_OPTIONS_HPP

#include <boost/unordered_map.hpp>
#include "constants.hpp"
#include "../packet/packet.hpp"

struct RoleRate {
    int max_count;
    int chance;
};

struct RoleOptionsData : public Deserializable, Serializable {
    unordered_map<RoleTypes, RoleRate> roleRates;
    bool shapeshifter_leave_skin;
    int shapeshifter_cooldown;
    int shapeshifter_duration;
    int scientist_cooldown;
    int guardian_angel_cooldown;
    int engineer_cooldown;
    int engineer_max_vent_time;
    int scientist_battery_charge;
    int protection_duration_seconds;
    bool imposters_see_protected;

    void serialize(Buffer &buffer) override;

    bool deserialize(Buffer &buffer) override;
};

struct GameOptionsData : public Deserializable, public Serializable {
    int version;
    int max_players;
    unsigned int keywords;
    int map_identifier;
    float player_speed_modifier;
    float crewmate_light_modifier;
    float imposter_light_modifier;
    float kill_cooldown;
    int total_common_tasks;
    int total_short_tasks;
    int total_long_tasks;
    int total_emergency_meetings;
    int total_imposters;
    int kill_distance;
    int total_discussion_time;
    int total_voting_time;
    bool is_default_settings;
    int total_emergency_cooldown;
    bool expose_imposter_on_eject;
    bool show_visual_tasks;
    bool do_anonymous_voting;
    int task_bar_mode;
    RoleOptionsData* data;

    GameOptionsData(int version): version(version) {}

    void serialize(Buffer &buffer) override;

    bool deserialize(Buffer &buffer) override;
};




#endif //INNER_OPTIONS_HPP
