//Ludum Dare 43 - Sacrifices will be made
//Curtis Maunder 01-12-2018
//Might write a play-by-play here

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <math.h>

#include "fireWizard.hpp"
#include "frostWizard.hpp"
#include "felWizard.hpp"

//At the moment static divide between human types so I can get this finished
//In future, its up to the players to micro their population
//Health is determined by stats
#include "healthyHuman.hpp"
#include "sickHuman.hpp"

#include "prison.hpp"
#include "spawnatorium.hpp"
#include "sacrificeCircle.hpp"
#include "grinder.hpp"
#include "felLab.hpp"

#include "collector.hpp"
#include "foodGremlin.hpp"

#include "spellsFreeze.hpp"
#include "spellsFire.hpp"
#include "spellsFel.hpp"

#include "hudObject.hpp"

#include "baddy.hpp"

template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

int main(){
    #pragma region SFML_INIT
    //Window initialization
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ludum Dare");
    window.setFramerateLimit(60);

    sf::Vector2i mapSize(2560, 1440);
    // / 16 == 160, 90
    sf::Vector2i viewPosition(mapSize.x / 2, mapSize.y / 2);

    //Time init
    sf::Time deltaTime;
    sf::Clock clock;
    srand(time(NULL));

    //View initialization
    auto windowSize = window.getSize();
    float zoom = 1;
    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

    //Stuff
    sf::Vector2f oldScreenPos;
    sf::Vector2f clickPos;
    bool panning = false;
    enum Selected {sNothing,
                    sPrison, sSpawnatorium, sSacrificeCircle, sGrinder, sFelLab,
                    sCollector, sFoodGremlin,
                    sFireWizard, sFelWizard, sFrostWizard};
    Selected selected;

    //text stuff
    sf::Font font;
    font.loadFromFile("dynasty.ttf");

    sf::Text display("", font);
    display.setFillColor(sf::Color::Yellow);
    display.setCharacterSize(30);
    display.setPosition(sf::Vector2f(0,0));

    #pragma endregion
    /*-- Content initialization --*/
    //I DONT HAVE A FUCKIGN CONTENT MANAGER SO HSITS FUCKED SON

    #pragma region IMAGE_INIT
    //Image initialization
    //Hud naming conventions slightly different or something
    sf::Image map_tiles;
    map_tiles.loadFromFile("map_tiles.png");

    sf::Image wizard_sheet;
    wizard_sheet.loadFromFile("wizard_sheet.png");

    sf::Image human_sheet;
    human_sheet.loadFromFile("human_sheet.png");

    sf::Image structure_sheet;
    structure_sheet.loadFromFile("structure_sheet.png");

    sf::Image mobs_large;
    mobs_large.loadFromFile("mobs_large.png");

    sf::Image mobs_small;
    mobs_small.loadFromFile("mobs_small.png");

    sf::Image hud_background;
    hud_background.loadFromFile("hud_background.png");

    sf::Image fire_wizard_spells;
    fire_wizard_spells.loadFromFile("fire_wizard_spells.png");

    sf::Image fel_wizard_spells;
    fel_wizard_spells.loadFromFile("fel_wizard_spells.png");

    sf::Image frost_wizard_spells;
    frost_wizard_spells.loadFromFile("frost_wizard_spells.png");

    sf::Image obstacles_small;
    obstacles_small.loadFromFile("obstacles_small.png");

    sf::Image obstacles_large;
    obstacles_large.loadFromFile("obstacles_large");

    sf::Image trees;
    trees.loadFromFile("trees.png");

    #pragma endregion

    #pragma region TEXTURE_INIT
    //Texture initialization

    //CUTSCENE TEXTURES
    sf::Texture cutscene_1;
    cutscene_1.loadFromFile("cutscene1.png");

    sf::Texture cutscene_2;
    cutscene_2.loadFromFile("cutscene2.png");

    sf::Texture cutscene_3;
    cutscene_3.loadFromFile("cutscene3.png");
    
    sf::Texture cutscene_4;
    cutscene_4.loadFromFile("cutscene4.png");
    
    //GROUND TEXTURES
    sf::Texture grass_texture_1;
    grass_texture_1.loadFromFile("map_tiles.png", sf::IntRect(0, 0, 16, 16));

    sf::Texture grass_texture_2;
    grass_texture_2.loadFromFile("map_tiles.png", sf::IntRect(16, 0, 16, 16));

    sf::Texture grass_texture_3;
    grass_texture_3.loadFromFile("map_tiles.png", sf::IntRect(32, 0, 16, 16));

    //WIZARD TEXTURES

    sf::Texture frost_wizard_texture;
    frost_wizard_texture.loadFromImage(wizard_sheet, sf::IntRect(0, 0, 16, 16)); //Legit not figuring out how to not hardcode this rn (which would be a loop)

    sf::Texture fire_wizard_texture;
    fire_wizard_texture.loadFromImage(wizard_sheet, sf::IntRect(16, 0, 16, 16));

    sf::Texture fel_wizard_texture;
    fel_wizard_texture.loadFromImage(wizard_sheet, sf::IntRect(16 * 2, 0, 16, 16));


    //HUMAN TEXTURE
    sf::Texture healthy_human_texture;
    healthy_human_texture.loadFromImage(human_sheet, sf::IntRect(0, 0, 16, 16));

    sf::Texture sick_human_texture;
    sick_human_texture.loadFromImage(human_sheet, sf::IntRect(32, 0, 16, 16));

    //STRUCTURE TEXTURES

    sf::Texture prison_texture;
    prison_texture.loadFromImage(structure_sheet, sf::IntRect(0, 0, 64, 64));

    sf::Texture spawnatorium_texture;
    spawnatorium_texture.loadFromImage(structure_sheet, sf::IntRect(64, 0, 64, 64));

    sf::Texture sacrificeCircle_texture;
    sacrificeCircle_texture.loadFromImage(structure_sheet, sf::IntRect(128, 0, 64, 64));

    sf::Texture grinder_texture;
    grinder_texture.loadFromImage(structure_sheet, sf::IntRect(194, 0, 64, 64));

    sf::Texture felLab_texture;
    felLab_texture.loadFromImage(structure_sheet, sf::IntRect(256, 0, 64, 64));


    //MOB TEXTURE
    sf::Texture collector_texture;
    collector_texture.loadFromImage(mobs_large, sf::IntRect(0, 0, 32, 32));

    sf::Texture food_gremlin_texture;
    food_gremlin_texture.loadFromImage(mobs_small, sf::IntRect(0, 0, 32, 32));

    //HUD TEXTURE

    sf::Texture hud_background_texture;
    hud_background_texture.loadFromImage(hud_background);

    sf::Texture fireWizardSpell_flame_icon;
    fireWizardSpell_flame_icon.loadFromImage(fire_wizard_spells, sf::IntRect(0, 0, 32, 32));

    sf::Texture felWizardSpell_felBomb_icon;
    felWizardSpell_felBomb_icon.loadFromImage(fel_wizard_spells, sf::IntRect(0, 0, 32, 32));

    sf::Texture frostWizardspell_freeze_icon;
    frostWizardspell_freeze_icon.loadFromImage(frost_wizard_spells, sf::IntRect(0, 0, 32, 32));

    //STUf
    sf::Texture rock_small_texture;
    rock_small_texture.loadFromImage(obstacles_small, sf::IntRect(0, 0, 16, 16));

    sf::Texture rock_large_texture;
    rock_large_texture.loadFromImage(obstacles_large, sf::IntRect(0, 0, 32, 32));

    sf::Texture tree_texture;
    tree_texture.loadFromImage(obstacles_large, sf::IntRect(0, 0, 32, 64));

    //BADDIES
    sf::Texture baddy_texture;
    baddy_texture.loadFromFile("baddies_sheet.png", sf::IntRect(0, 0, 16, 16));

    sf::Texture baddy_king;
    baddy_king.loadFromFile("baddyking.png");

    #pragma endregion

    #pragma region SPRITE_INIT
    //Sprite initialization
    //CREATE VECTORS OF THESE WHEN ITS TIME TO
    //IF ITS TIME TO
    //NEED TO FOR HUMANS
    //GONNA NEED DATA STRUCTURES TOO
    std::vector<HealthyHuman> healthyHumans;
    std::vector<SickHuman> sickHumans;
    std::vector<FoodGremlin> foodGremlins;
    std::vector<Prison> prisons;
    std::list<HUDObject*> hudElements;
    std::vector<std::vector<sf::Sprite>> tiles(160, std::vector<sf::Sprite>(90));
    std::vector<SpellsFreeze> freezeSpells;
    std::vector<SpellsFire> fireSpells;
    std::vector<SpellsFel> felSpells;
    std::vector<Baddy> baddies;

    for(int i = 0; i < 160; i++){
        for(int j = 0; j < 90; j++){
            //REAL GROSS BUSINESS INBOUND
            int tileNum = rand() % 5 + 1;
            sf::Sprite sprite;
            if(tileNum == 1)
                sprite.setTexture(grass_texture_1);
            else if(tileNum == 2)
                sprite.setTexture(grass_texture_2);
            else
                sprite.setTexture(grass_texture_3);

            tiles[i][j] = sprite;
            tiles[i][j].setPosition(i * 16, j * 16);
            tiles[i][j].setOrigin(8, 8);
        }
    }

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            Baddy baddy(baddy_texture);
            baddy.sprite.move((100 + (16 * i) + 8), (500 + (16 * j)));
            baddies.push_back(baddy);
        }
    }

    for(int i = 0; i < 40; i++){
        HealthyHuman human(healthy_human_texture);
        healthyHumans.push_back(human);
        healthyHumans[i].sprite.move((500 + (16 * i)) + 8, 500);
    }

    for(int i = 0; i < 40; i++){
        SickHuman human(sick_human_texture);
        sickHumans.push_back(human);
        sickHumans[i].sprite.move((500 + (16 * i)) + 8, 600);
    }

    for(int i = 0; i < 5; i++){
        FoodGremlin foodGremlin(food_gremlin_texture);
        foodGremlins.push_back(foodGremlin);
        foodGremlins[i].sprite.move((1000 + (16 * i)) + 8, 700);
    }

    Prison prison(prison_texture);
    prison.sprite.setPosition(mapSize.x /2, mapSize.y / 2);
    prison.sprite.setOrigin(32, 32);

    Spawnatorium spawnatorium(spawnatorium_texture);
    spawnatorium.sprite.setPosition(mapSize.x / 2 + 128, mapSize.y / 2 + 128);
    spawnatorium.sprite.setOrigin(32, 32);

    SacrificeCircle sacrificeCircle(sacrificeCircle_texture);
    sacrificeCircle.sprite.setPosition(mapSize.x / 2, mapSize.y / 2 + 128);
    sacrificeCircle.sprite.setOrigin(32, 32);

    Grinder grinder(grinder_texture);
    grinder.sprite.setPosition(mapSize.x / 2 + 128, mapSize.y / 2);
    grinder.sprite.setOrigin(32, 32);

    FelLab felLab(felLab_texture);
    felLab.sprite.setPosition(mapSize.x / 2 + 194, mapSize.y / 2 + 128);
    felLab.sprite.setOrigin(32, 32);

    Collector collector(collector_texture);
    collector.sprite.setPosition(mapSize.x / 2 + 64, mapSize.y / 2);
    collector.sprite.setOrigin(16,16);

    FireWizard fireWizard(fire_wizard_texture);
    fireWizard.sprite.setPosition(mapSize.x / 2 - 64, mapSize.y / 2 - 64);
    fireWizard.sprite.setOrigin(8, 8);

    FelWizard felWizard(fel_wizard_texture);
    felWizard.sprite.setPosition(mapSize.x / 2 - 96, mapSize.y / 2 - 64);
    felWizard.sprite.setOrigin(8, 8);

    FrostWizard frostWizard(frost_wizard_texture);
    frostWizard.sprite.setPosition(mapSize.x / 2 - 128, mapSize.y / 2 - 64);
    frostWizard.sprite.setOrigin(8, 8);

    sf::Sprite cutscene1(cutscene_1);
    sf::Sprite cutscene2(cutscene_2);
    sf::Sprite cutscene3(cutscene_3);
    sf::Sprite cutscene4(cutscene_4);


    //HUD SPRITES
    HUDObject hudBackground(hud_background_texture);

    HUDObject fireWizardSpells_flame(fireWizardSpell_flame_icon);
    hudElements.push_back(&fireWizardSpells_flame);

    HUDObject felWizardSpells_felBomb(felWizardSpell_felBomb_icon);
    hudElements.push_back(&felWizardSpells_felBomb);

    HUDObject frostWizardSpells_freeze(frostWizardspell_freeze_icon);
    hudElements.push_back(&frostWizardSpells_freeze);

    sf::RectangleShape rectShape(sf::Vector2f(8,8));

    #pragma endregion

    sf::Color charred(20, 20, 20, 255);
    FoodGremlin *selectedGremlin;

    /*
    window.draw(cutscene1);
    window.display();
    sf::sleep(sf::seconds(3));
    window.draw(cutscene2);
    window.display();
    sf::sleep(sf::seconds(3));
    window.draw(cutscene3);
    window.display();
    sf::sleep(sf::seconds(3));
    window.draw(cutscene4);
    window.display();
    sf::sleep(sf::seconds(3));
    */

    view.setCenter(viewPosition.x, viewPosition.y);
    window.setView(view);

    //Game loop
    while(window.isOpen()){
        //FILTHY FUCKING HACK FOR HUD FLAGS
        hudBackground.display = false;
        for(auto& h : hudElements)
            h->display = false;

        //Time
        deltaTime = clock.restart();
        float dtAsSeconds = deltaTime.asSeconds();

        //Event handling || input handling
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                case sf::Event::EventType::KeyPressed:
                    //Keyboard input || pressed
                    break;
                case sf::Event::EventType::KeyReleased:
                    if(event.key.code == sf::Keyboard::Key::Escape)
                        window.close();
                    break;

                //MOUSE CODE IS BROKEN -- Hack fix with division
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == 2){
                        panning = true; 
                        oldScreenPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                    if(event.mouseButton.button == 0){
                        clickPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                        #pragma region SPELL_SELECTION

                        if(fireWizardSpells_flame.sprite.getGlobalBounds().contains(clickPos) && selected == sFireWizard){
                            if(!fireWizard.fireClicked){
                                fireWizardSpells_flame.sprite.setColor(sf::Color::Red);
                                fireWizard.fireClicked = !fireWizard.fireClicked;
                            }
                            else{
                                fireWizardSpells_flame.sprite.setColor(sf::Color::White);
                                fireWizard.fireClicked = !fireWizard.fireClicked;
                            }

                            selected = sFireWizard;
                            break;
                        }else if(felWizardSpells_felBomb.sprite.getGlobalBounds().contains(clickPos) && selected == sFelWizard){
                            if(!felWizard.felBombClicked){
                                felWizardSpells_felBomb.sprite.setColor(sf::Color::Red);
                                felWizard.felBombClicked = !felWizard.felBombClicked;
                            }else{
                                felWizardSpells_felBomb.sprite.setColor(sf::Color::White);
                                felWizard.felBombClicked = !felWizard.felBombClicked;
                            }

                            selected = sFelWizard;
                            break;
                        }else if(frostWizardSpells_freeze.sprite.getGlobalBounds().contains(clickPos) && selected == sFrostWizard){
                            if(!frostWizard.freezeClicked){
                                frostWizardSpells_freeze.sprite.setColor(sf::Color::Red);
                                frostWizard.freezeClicked = !frostWizard.freezeClicked;
                            }else{
                                frostWizardSpells_freeze.sprite.setColor(sf::Color::White);
                                frostWizard.freezeClicked = !frostWizard.freezeClicked;
                            }

                            selected = sFrostWizard;
                            break;
                        }

                        #pragma endregion

                        #pragma region OBJECT_SELECTION

                        //Selection in order of size and movability
                        if(fireWizard.sprite.getGlobalBounds().contains(clickPos))
                            selected = sFireWizard;
                        else if(felWizard.sprite.getGlobalBounds().contains(clickPos))
                            selected = sFelWizard;
                        else if(frostWizard.sprite.getGlobalBounds().contains(clickPos))
                            selected = sFrostWizard;
                        else if(collector.sprite.getGlobalBounds().contains(clickPos))
                            selected = sCollector;
                        else if(prison.sprite.getGlobalBounds().contains(clickPos))
                            selected = sPrison; 
                        else if(spawnatorium.sprite.getGlobalBounds().contains(clickPos))
                            selected = sSpawnatorium;
                        else if(sacrificeCircle.sprite.getGlobalBounds().contains(clickPos))
                            selected = sSacrificeCircle;
                        else if(grinder.sprite.getGlobalBounds().contains(clickPos))
                            selected = sGrinder;
                        else if(felLab.sprite.getGlobalBounds().contains(clickPos))
                            selected = sFelLab;
                        else
                            selected = sNothing;

                        for(auto& f : foodGremlins){
                            if(f.sprite.getGlobalBounds().contains(clickPos)){
                                selected = sFoodGremlin;
                                selectedGremlin = &f;
                                f.selected = true;
                                break;
                            }
                        }                            

                        #pragma endregion
                    }
                    if(event.mouseButton.button == 1){
                        clickPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                        #pragma region OBJECT_MOVEMENT

                        if(selected == sCollector){
                            float dx = clickPos.x - collector.sprite.getPosition().x;
                            float dy = clickPos.y - collector.sprite.getPosition().y;

                            collector.direction.x = dx;
                            collector.direction.y = dy;

                            float mag = sqrt((collector.direction.x * collector.direction.x) + (collector.direction.y * collector.direction.y)); 

                            collector.direction /= mag;

                            collector.destination.x = clickPos.x;
                            collector.destination.y = clickPos.y;

                            collector.moving = true;
                        }
                        else if(selected == sFoodGremlin){
                            float dx = clickPos.x - selectedGremlin->sprite.getPosition().x;
                            float dy = clickPos.y - selectedGremlin->sprite.getPosition().y;

                            selectedGremlin->direction.x = dx;
                            selectedGremlin->direction.y = dy;

                            float mag = sqrt((selectedGremlin->direction.x * selectedGremlin->direction.x) + (selectedGremlin->direction.y * selectedGremlin->direction.y)); 

                            selectedGremlin->direction /= mag;

                            selectedGremlin->destination.x = clickPos.x;
                            selectedGremlin->destination.y = clickPos.y;

                            selectedGremlin->moving = true;
                        }
                        else if(selected == sFireWizard && !fireWizard.fireCasting){
                            float dx = clickPos.x - fireWizard.sprite.getPosition().x;
                            float dy = clickPos.y - fireWizard.sprite.getPosition().y;

                            fireWizard.direction.x = dx;
                            fireWizard.direction.y = dy;

                            float mag = sqrt((fireWizard.direction.x * fireWizard.direction.x) + (fireWizard.direction.y * fireWizard.direction.y)); 

                            fireWizard.direction /= mag;
                            
                            fireWizard.destination.x = clickPos.x;
                            fireWizard.destination.y = clickPos.y;

                            fireWizard.moving = true;
                        }else if(selected == sFelWizard && !felWizard.felBombCasting){
                            float dx = clickPos.x - felWizard.sprite.getPosition().x;
                            float dy = clickPos.y - felWizard.sprite.getPosition().y;

                            felWizard.direction.x = dx;
                            felWizard.direction.y = dy;

                            float mag = sqrt((felWizard.direction.x * felWizard.direction.x) + (felWizard.direction.y * felWizard.direction.y)); 

                            felWizard.direction /= mag;
                            
                            felWizard.destination.x = clickPos.x;
                            felWizard.destination.y = clickPos.y;

                            felWizard.moving = true;
                        }else if(selected == sFrostWizard && !frostWizard.freezeCasting){
                            float dx = clickPos.x - frostWizard.sprite.getPosition().x;
                            float dy = clickPos.y - frostWizard.sprite.getPosition().y;

                            frostWizard.direction.x = dx;
                            frostWizard.direction.y = dy;

                            float mag = sqrt((frostWizard.direction.x * frostWizard.direction.x) + (frostWizard.direction.y * frostWizard.direction.y)); 

                            frostWizard.direction /= mag;
                            
                            frostWizard.destination.x = clickPos.x;
                            frostWizard.destination.y = clickPos.y;

                            frostWizard.moving = true;
                        }

                        #pragma endregion
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == 2){
                        panning = false;
                        oldScreenPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                    break;
                case sf::Event::MouseMoved:
                {
                    if(!panning)
                        break;

                    const sf::Vector2f newScreenPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    const sf::Vector2f deltaScreenPos = oldScreenPos - newScreenPos;

                    viewPosition.x += deltaScreenPos.x / 20;
                    viewPosition.y += deltaScreenPos.y / 20;
                    break;
                }
                /*
                case sf::Event::MouseWheelScrolled:
                    if(panning)
                        break;

                    if(event.mouseWheelScroll.delta <= -1)
                        zoom = std::min(2.f, zoom + .1f);
                    else if(event.mouseWheelScroll.delta >= 1)
                        zoom = std::max(.5f, zoom - .1f);

                    view.zoom(zoom);
                    viewPosition.x = sf::Mouse::getPosition().x;
                    viewPosition.y = sf::Mouse::getPosition().y;
                    window.setView(view);
                    break;
                default:
                    break;
                */
            }
        }

        //Update
        view.setCenter(viewPosition.x, viewPosition.y);
        window.setView(view);
        //Set our hud in the top and bottom corners        
        display.setPosition(viewPosition.x - (windowSize.x / 2), viewPosition.y - (windowSize.y / 2));
        hudBackground.sprite.setPosition(viewPosition.x - (windowSize.x / 2), viewPosition.y + (windowSize.y / 2) - (windowSize.y / 6));
        //SELECTED STUFF
        #pragma region SELECTED_STUFF

        switch(selected){
            case sPrison:
                display.setString("Prison\nPrisoners: " + toString<int>(prison.prisoners.size()));
                break;
            case sSpawnatorium:
                display.setString("Spawnatorium\nFood:" + toString<int>(spawnatorium.foodSupply) +
                                    "\nHumans: " + toString<int>(spawnatorium.spawned.size()));
                break;
            case sSacrificeCircle:
                display.setString("Sacrifice Circle\nMana: " + toString<int>(sacrificeCircle.mana));
                break;
            case sGrinder:
                display.setString("Grinder\nUngrinded Meat: " + toString<int>(grinder.ungrindedMeat) +
                                    "\nFood: " + toString<int>(grinder.foodSupply));
                break;
            case sFelLab:
                display.setString("Fel Lab\nBodies: " + toString<int>(felLab.bodies) +
                                    "\nFel Bombs: " + toString<int>(felLab.felBombs));
                break;
            case sCollector:
                display.setString("Collector\nHealthy Prisoners: " + toString<int>(collector.healthyPrisonerCount) +
                                    "\nSick Prisoners: " + toString<int>(collector.sickPrisonerCount));
                break;
            case sFoodGremlin:
                display.setString("Food Gremlin\nFood: " + toString<int>(selectedGremlin->food));
                break;
            case sFireWizard:
                display.setString("Fire Wizard\nMana: " + toString<int>(fireWizard.mana));
                fireWizardSpells_flame.display = true;
                fireWizardSpells_flame.sprite.setPosition(viewPosition.x - (windowSize.x / 2), viewPosition.y);
                break;
            case sFelWizard:
                display.setString("Fel Wizard\nFel Bombs: " + toString<int>(felWizard.felBombs));
                felWizardSpells_felBomb.display = true;
                felWizardSpells_felBomb.sprite.setPosition(viewPosition.x - (windowSize.x / 2), viewPosition.y);
                break;
            case sFrostWizard:
                display.setString("Frost Wizard\nMana: " + toString<int>(frostWizard.mana));
                frostWizardSpells_freeze.display = true;
                frostWizardSpells_freeze.sprite.setPosition(viewPosition.x - (windowSize.x / 2), viewPosition.y);
                break;
            case sNothing:
                display.setString("");
                break;
        }

        #pragma endregion

        //FIRE WIZARD LOGIC
        fireWizard.Walking(fireWizardSpells_flame);
        fireWizard.ReplenishMana(deltaTime, &sacrificeCircle);
        fireWizard.Casting(deltaTime, fireSpells);

        //FEL WIZARD LOGIC
        felWizard.Walking(felWizardSpells_felBomb);
        felWizard.ReplenishBombs(deltaTime, &felLab);
        felWizard.Casting(deltaTime, felSpells);    

        //FROST WIZARD LOGIC
        frostWizard.Walking(frostWizardSpells_freeze);
        frostWizard.ReplenishMana(deltaTime, &sacrificeCircle);
        frostWizard.Casting(deltaTime, freezeSpells);        

        //HUMAN LOGIC
        //CBF making it nice
        for(int i = 0; i < healthyHumans.size(); i++){
            sf::Vector2f tmpPos;
            tmpPos.x = healthyHumans[i].sprite.getPosition().x - collector.sprite.getPosition().x;
            tmpPos.y = healthyHumans[i].sprite.getPosition().y - collector.sprite.getPosition().y;
            float eDistance = sqrt((tmpPos.x * tmpPos.x) + (tmpPos.y * tmpPos.y));

            if(healthyHumans[i].frosty)
                healthyHumans[i].speed = 10.0f;
            else
                healthyHumans[i].speed = 50.0f;

            if(healthyHumans[i].running)
                healthyHumans[i].sprite.move(healthyHumans[i].direction.x * (deltaTime.asSeconds() * healthyHumans[i].speed),
                                                healthyHumans[i].direction.y * (deltaTime.asSeconds() * healthyHumans[i].speed));

            if(eDistance < 75){
                float dx = healthyHumans[i].sprite.getPosition().x - collector.sprite.getPosition().x;
                float dy = healthyHumans[i].sprite.getPosition().y - collector.sprite.getPosition().y;

                healthyHumans[i].direction.x = dx;
                healthyHumans[i].direction.y = dy;

                float mag = sqrtf((healthyHumans[i].direction.x * healthyHumans[i].direction.x) + (healthyHumans[i].direction.y * healthyHumans[i].direction.y)); 

                healthyHumans[i].direction /= mag;

                healthyHumans[i].destination.x = healthyHumans[i].sprite.getPosition().x + healthyHumans[i].direction.x;
                healthyHumans[i].destination.y = healthyHumans[i].sprite.getPosition().y + healthyHumans[i].direction.y;

                healthyHumans[i].running = true;
            }else if(eDistance > 300)
                healthyHumans[i].running = false;

            if(healthyHumans[i].sprite.getGlobalBounds().intersects(collector.sprite.getGlobalBounds()) && healthyHumans[i].interactable){
                if(collector.healthyPrisonerCount + collector.sickPrisonerCount < collector.maxPrisoners){
                    healthyHumans[i].captured = true;
                    healthyHumans[i].interactable = false;
                    collector.healthyPrisonerCount++;
                    collector.healthyPrisoners.push_front(&healthyHumans[i]);
                }
            }

            for(auto const& f : freezeSpells){
                if(healthyHumans[i].sprite.getGlobalBounds().intersects(f.area.getGlobalBounds()))
                    healthyHumans[i].frosty = true;
                else
                    healthyHumans[i].frosty = false;
            }

            for(auto const& f : felSpells){
                if(healthyHumans[i].sprite.getGlobalBounds().intersects(f.area.getGlobalBounds())){
                    SickHuman human(sick_human_texture);
                    human.sprite.setPosition(healthyHumans[i].sprite.getPosition().x, healthyHumans[i].sprite.getPosition().y);
                    sickHumans.push_back(human);
                    healthyHumans.erase(healthyHumans.begin() + i);
                    break;
                }
            }
        }

        for(auto& h : sickHumans){
            if(h.sprite.getGlobalBounds().intersects(collector.sprite.getGlobalBounds()) && h.interactable){
                if(collector.healthyPrisonerCount + collector.sickPrisonerCount < collector.maxPrisoners){
                    h.captured = true;
                    h.interactable = false;
                    collector.sickPrisonerCount++;
                    collector.sickPrisoners.push_front(&h);
                }
            }
        }


        //COLLECTOR LOGIC
        #pragma region COLLECTOR_LOGIC

        if(collector.moving){
            collector.sprite.move(collector.direction.x, collector.direction.y);
            sf::Vector2i tmpPos;
            tmpPos.x = collector.sprite.getPosition().x - collector.destination.x;
            tmpPos.y = collector.sprite.getPosition().y - collector.destination.y;
            float cDistance = sqrt((tmpPos.x * tmpPos.x) + (tmpPos.y * tmpPos.y));
            if(cDistance < .1)
                collector.moving = false;
        }

        if(collector.sprite.getGlobalBounds().intersects(prison.sprite.getGlobalBounds()) && !collector.healthyPrisoners.empty()){
            for(auto& p : collector.healthyPrisoners){
                collector.healthyPrisonerCount--;
                prison.prisonerCount++;
                prison.prisoners.push_front(p);
            }
            collector.healthyPrisoners.clear();
        }

        if(collector.sprite.getGlobalBounds().intersects(grinder.sprite.getGlobalBounds()) && !collector.sickPrisoners.empty()){
            for(auto& p : collector.sickPrisoners){
                collector.sickPrisonerCount--;
                grinder.ungrindedMeat += 10;
            }
            collector.sickPrisoners.clear();
        }

        if(collector.sprite.getGlobalBounds().intersects(felLab.sprite.getGlobalBounds()) && !collector.sickPrisoners.empty()){
            for(auto& p : collector.sickPrisoners){
                collector.sickPrisonerCount--;
                felLab.bodies++;
            }
            collector.sickPrisoners.clear();
        }

        if(collector.sprite.getGlobalBounds().intersects(sacrificeCircle.sprite.getGlobalBounds()) && !collector.sickPrisoners.empty()){
            //Change this later so its 2 for 1 mana
            for(auto& p : collector.sickPrisoners){
                collector.sickPrisonerCount--;
                sacrificeCircle.mana++;
            }
            collector.sickPrisoners.clear();
        }

        if(collector.sprite.getGlobalBounds().intersects(spawnatorium.sprite.getGlobalBounds()) && !spawnatorium.spawned.empty()){
            for(int i = 0; i < spawnatorium.spawned.size(); i++){
                if(spawnatorium.spawned.empty() || collector.healthyPrisonerCount + collector.sickPrisonerCount == collector.maxPrisoners)
                    break;
                
                collector.healthyPrisonerCount++;
                collector.healthyPrisoners.push_front(spawnatorium.spawned[i]);
                spawnatorium.spawned.erase(spawnatorium.spawned.begin() + i);
            }

            for(auto& s : spawnatorium.spawned){
                if(collector.healthyPrisonerCount == collector.maxPrisoners)
                    break;

                collector.healthyPrisonerCount++;
                collector.healthyPrisoners.push_front(s);
                spawnatorium.spawned.pop_back();
            }
        }

        #pragma endregion

        //FOOD GREMLIN LOGIC
        for(auto& f : foodGremlins){
            if(f.moving){
                f.sprite.move(f.direction.x, f.direction.y);
                sf::Vector2i tmpPos;
                tmpPos.x = f.sprite.getPosition().x - f.destination.x;
                tmpPos.y = f.sprite.getPosition().y - f.destination.y;
                float cDistance = sqrt((tmpPos.x * tmpPos.x) + (tmpPos.y * tmpPos.y));
                if(cDistance < .1)
                    f.moving = false;
            }  

            if(f.sprite.getGlobalBounds().intersects(grinder.sprite.getGlobalBounds())){
                f.lastTick += deltaTime;
                if(f.lastTick > sf::seconds(0.5)){
                    if(f.food < f.maxFood && grinder.foodSupply > 0){
                        f.food++;
                        grinder.foodSupply--;
                    }
                    f.lastTick = f.lastTick - f.lastTick;
                }
            }

            if(f.sprite.getGlobalBounds().intersects(spawnatorium.sprite.getGlobalBounds())){
                if(f.food > 0){
                    spawnatorium.foodSupply += f.food;
                    f.food = 0;
                }
            }
        }

        //Spawnatorium
        spawnatorium.lastTick += deltaTime;
        if(spawnatorium.lastTick > sf::seconds(1)){
            if(spawnatorium.foodSupply > 2){
                HealthyHuman human(healthy_human_texture);
                human.spawnatorium = true;
                human.interactable = false;
                healthyHumans.push_back(human);
                spawnatorium.spawned.push_back(&healthyHumans.back());
                spawnatorium.foodSupply -= 2;
            }
        }

        //Grinder
        grinder.lastTick += deltaTime;
        if(grinder.lastTick > sf::seconds(5)){
            if(grinder.ungrindedMeat >= 10){
                grinder.foodSupply += 10;
                grinder.lastTick = grinder.lastTick - grinder.lastTick;
                grinder.ungrindedMeat -= 10;
            }
        }
        
        //Fel labs
        felLab.lastTick += deltaTime;
        if(felLab.lastTick > sf::seconds(5)){
            if(felLab.bodies >= 3){
                felLab.felBombs++;
                felLab.lastTick = felLab.lastTick - felLab.lastTick;
                felLab.bodies -= 3;
            }
        }

        //Sacrifice circle
        sacrificeCircle.lastTick += deltaTime;
        if(sacrificeCircle.lastTick > sf::seconds(1)){
            if(prison.prisonerCount > 0){
                sacrificeCircle.mana++;
                //Literally what the fuck
                //sacrificeCircle.lastTick = 0 doesnt work, so this is it
                sacrificeCircle.lastTick = sacrificeCircle.lastTick - sacrificeCircle.lastTick;
                prison.prisonerCount--;
                prison.prisoners.pop_front();
            }
        }

        //Spells
        for(auto& f : fireSpells){
            int index = 0;
            f.life += deltaTime;

            if(f.life > sf::seconds(3) && f.life < sf::seconds(6))
                f.phase = 2;
            else if(f.life > sf::seconds(6) && f.life < sf::seconds(9))
                f.phase = 3;
            else if(f.life > sf::seconds(9)){
                fireSpells.erase(fireSpells.begin() + index);
                break;
            }

            if(f.phase == 2)
                f.area.setScale(f.phase2Scale);
            else if(f.phase == 3)
                f.area.setScale(f.phase3Scale);

            index++;
        }

        //Render
        window.clear(sf::Color::Black);

        for(int i = 0; i < 160; i++)
            for(int j = 0; j < 90; j++)
                window.draw(tiles[i][j]);

        for(auto const& f : freezeSpells)
            window.draw(f.area);

        for(auto const& f : fireSpells)
            window.draw(f.area);

        for(auto const& f : felSpells)
            window.draw(f.area);

        window.draw(prison.sprite);
        window.draw(spawnatorium.sprite);
        window.draw(sacrificeCircle.sprite);
        window.draw(grinder.sprite);
        window.draw(felLab.sprite);
        window.draw(collector.sprite);
        window.draw(fireWizard.sprite);
        window.draw(felWizard.sprite);
        window.draw(frostWizard.sprite);

        for(auto const& f : foodGremlins){
            window.draw(f.sprite);
        }

        for(auto const& b : baddies){
            window.draw(b.sprite);
        }

        for(auto const& h : healthyHumans){ 
            if(!h.prison && !h.captured && !h.spawnatorium)
                window.draw(h.sprite);
        }

        for(auto const& h : sickHumans){
            if(!h.captured)
                window.draw(h.sprite);
        }

        window.draw(display);

        //if(hudBackground.display)
        //    window.draw(hudBackground.sprite);

        for(auto& h : hudElements)
            if(h->display)
                window.draw(h->sprite);

        window.draw(rectShape);
        
        window.display();
    }
}