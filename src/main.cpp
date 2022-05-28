#include "CuteEngine.h"
#include <QApplication>

int main(int argc, const char *argv[]) {
    QApplication app(argc, const_cast<char **>(argv));

    cute::Map *map1 = new cute::Map(50, 50, 32);
    cute::Map *map2 = new cute::Map(30, 30, 32);

    cute::MapGrid *map_grid = new cute::MapGrid(1, 2);
    map_grid->set_map_at_pos(map1, 0, 0);
    map_grid->set_map_at_pos(map2, 0, 1);

    cute::Game *game = new cute::Game(map_grid, 0, 0);
    game->launch();

    cute::Entity *minotaur_entity = cute::get_minotaur_entity();

    // minotaur_entity->set_pos(QPointF(64, 32), QPointF(0, 0));
    // minotaur_entity->set_pos(QPointF(64, 96), QPointF(0, 0));
    // minotaur_entity->set_pos(QPointF(0, 0));
    minotaur_entity->set_pos(QPointF(256, 256));
    minotaur_entity->set_facing_angle(0);
    minotaur_entity->set_group(1);
    minotaur_entity->set_health(50);

    minotaur_entity->add_slot(new cute::MeleeWeaponSlot(), "weapon");

    cute::AnimationAttack *animation_attack =
            new cute::AnimationAttack("attack", "qrc:/cute-engine-builtin/resources/sounds/axe.wav", 10, 60, 90);

    // map1->add_entity(animation_attack);
    // map1->add_entity(animation_attack);

    // animation_attack->set_pos(QPointF(300, 300));

    minotaur_entity->slot("weapon")->equip(animation_attack);

    QObject::connect(game, &cute::Game::key_pressed, [&](int key) {
        if (key == Qt::Key_Space) {
            minotaur_entity->slot("weapon")->use();
        }
    });

    map1->add_entity(minotaur_entity);

    // minotaur_entity->sprite()->play("stand", -1, 8, 0);

    cute::ECKeyboardMoverPerspective *keyboard_mover = new cute::ECKeyboardMoverPerspective(minotaur_entity);
    // keyboard_mover->set_step_size(8);

    new cute::ECMouseFacer(minotaur_entity);

    new cute::ECCameraFollower(minotaur_entity);

    /// the ECCameraFollower can only update camera when entity moves.
    /// you need to set the initial camera position by hand.
    game->set_center_cam_pos(minotaur_entity->pos());

    new cute::ECMapMover(minotaur_entity);
    new cute::ECCurrentMapGrabber(minotaur_entity);
    new cute::ECItemPickerUpper(minotaur_entity);

    cute::Entity *spider_entity = cute::get_spider_entity();
    spider_entity->set_pos(QPointF(512, 1024));
    spider_entity->set_group(2);
    spider_entity->set_health(25);
    spider_entity->add_sound("die", "qrc:/cute-engine-builtin/resources/sounds/spider_die.mp3");

    map1->add_entity(spider_entity);

    cute::Game::game->diplomacy_manager().set_relationship(2, 1, cute::Relationship::ENEMY);
    cute::Game::game->diplomacy_manager().set_relationship(1, 2, cute::Relationship::ENEMY);

    cute::ECBodyThruster *body_thruster = new cute::ECBodyThruster(spider_entity);
    // body_thruster->set_show_FOV(true);

    cute::CHealthShower *health_shower = new cute::CHealthShower();
    health_shower->add_entity(minotaur_entity);
    health_shower->add_entity(spider_entity);

    cute::InventoryUser *gui1 = new cute::InventoryUser(game, minotaur_entity->inventory());
    game->add_GUI(gui1);

    cute::ItemRainOfSpears *item1 = new cute::ItemRainOfSpears();
    cute::ItemShardsOfFire *item2 = new cute::ItemShardsOfFire();
    cute::ItemHealthPotion *item3 = new cute::ItemHealthPotion(20);
    cute::ItemTeleport *item4 = new cute::ItemTeleport();

    cute::RainWeather *rain_weather = new cute::RainWeather();
    cute::FogWeather *fog_weather = new cute::FogWeather();
    cute::FogWeather *fog_weather_2 = new cute::FogWeather();

    // map1->add_weather_effect(*rain_weather);
    // map1->add_weather_effect(*fog_weather);

    map2->add_weather_effect(*fog_weather_2);

    map1->add_entity(item1);
    map1->add_entity(item2);
    map1->add_entity(item3);
    map2->add_entity(item4);

    item1->set_pos(QPointF(300, 100));
    item2->set_pos(QPointF(200, 500));
    item3->set_pos(QPointF(400, 300));
    item4->set_pos(QPointF(300, 100));

    cute::add_random_trees(map1, 7, 8);
    cute::add_random_trees(map2, 2, 8);

    return app.exec();
}