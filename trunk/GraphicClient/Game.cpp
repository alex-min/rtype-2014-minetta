#include <QApplication>
#include "Game.h"
#include "MyCanvas.h"
#include "ITime.h"
#include "ListenServer.h"
#include <QMetaType>
#include "MonsterGenerator.h"

Game::Game()
{
    _background = 0;
    _explosion = new AnimatedImage("explosion.png");
    _explosion->setRepetition(false);
    _explosion->setSpeed(40);
    _soundsManager = new Sounds("music.wav", "missil.wav", "explosion.ogg");
    _started = false;
    _mapId = '1';
    _endGame = false;
    _stopLoop = false;

    for (UInt16 i = 0; i < 20; i++)
    {
        IPlayer *missil = SingleMonsterGenerator::getInstance()->generate(MonsterGenerator::MISSILE);
        AnimatedImage *a = new AnimatedImage(SingleMonsterGenerator::getInstance()->getImageOf(MonsterGenerator::MISSILE));

        a->parseFile();
        a->setCurrentSprite(130);

        missil->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);
        missil->setPosition(-200.0, 0.0);

        _missils[i] = missil;
    }

    backupMissil(true, &_missils);

    for (UInt16 i = 0; i < 20; i++)
    {
        IPlayer *monsterMissil = SingleMonsterGenerator::getInstance()->generate(MonsterGenerator::MISSILE);
        AnimatedImage *a = new AnimatedImage(SingleMonsterGenerator::getInstance()->getImageOf(MonsterGenerator::MISSILE));

        a->parseFile();
        a->setCurrentSprite(177);

        monsterMissil->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);
        monsterMissil->setPosition(-200.0, 0.0);

        _monsterMissils[i] = monsterMissil;
    }

    backupMonsterMissil(true, &_monsterMissils);

    AnimatedImage *a = new AnimatedImage("player1.png");

    a->parseFile();
    _explosion->parseFile();

    _humanPlayer = new HumanPlayer();
    _humanPlayer->setExplosionSprite(new AnimatedImage(*_explosion),
                                     _explosion->getCurrentSprite()->GetSize().x,
                                     _explosion->getCurrentSprite()->GetSize().y);

    _humanPlayer->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);
    _humanPlayer->setPosition(10,10);
    _humanPlayer->setSpeed(0.2);

    _old_time.setToMsTimeOfDay();
    _old_time_pos.setToMsTimeOfDay();
    _totalTime = 0;

    qRegisterMetaType<UInt16>("UInt16");

    _scroll.loadBackground("../img/background.png",
                           "../img/background.png");

    connect(ListenServerSingleton::getInstance(), SIGNAL(posChanged(UInt16,UInt16,UInt16)), this, SLOT(updatePlayerPos(UInt16,UInt16,UInt16)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(popMonster(UInt16,UInt8,UInt16,UInt16,Int32)), this, SLOT(pop(UInt16,UInt8,UInt16,UInt16,Int32)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(die(UInt16)), this, SLOT(playerDie(UInt16)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(endGame()), this, SLOT(activateEndGame()));
}

void        Game::restartEventLoop()
{
    _stopLoop = false;
    _endGame = false;
    _started = false;

    _humanPlayer->erase();
    _humanPlayer->resetSprites();
    _humanPlayer->setPosition(10, 10);

    _old_time.setToMsTimeOfDay();
    _old_time_pos.setToMsTimeOfDay();
    _mapScroll.load(_mapId);

    _totalTime = 0;

    for (std::map<UInt16, IPlayer*>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
        IPlayer *item = (*it).second;

        _players.erase(it);

        delete item;
    }

    PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();
    for (PoolFactory<IPlayer>::ListType::iterator it = map.begin(); it != map.end(); ++it)
    {
        IPlayer *item = (*it).first;

        map.erase(it);

        delete item;
    }

    for (std::map<UInt16, IPlayer*>::iterator it = _missils.begin(); it != _missils.end(); ++it)
        (*it).second->erase();

    for (std::map<UInt16, IPlayer*>::iterator it = _monsterMissils.begin(); it != _monsterMissils.end(); ++it)
        (*it).second->erase();
}

void        Game::activateEndGame()
{
    _endGame = true;
}

void        Game::setMapId(UInt8 mapId)
{
    _mapId = mapId;
}

void        Game::playerDie(UInt16 id)
{
    if (_players.find(id) != _players.end())
    {
        std::map<UInt16, IPlayer*>::iterator it = _players.find(id);

        if (!(it->second->isDead()))
        {
            it->second->switchToExplosionSprite();
            it->second->die();
        }
    }
}

void        Game::setStartGame(bool b)
{
    _started = b;

    if (b == false)
    {
        _cur_time.setToMsTimeOfDay();
        _old_time.setToMsTimeOfDay();
        _mapScroll.erase();
        _mapScroll.setStartTime(_old_time.getMs());
        _soundsManager->playSound("music");
    }
}

void        Game::pop(UInt16 id,UInt8 monsterType, UInt16 x, UInt16 y, Int32)
{
    (void)monsterType;
    (void)id;

    if (monsterType == 1)
    {
        PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();

        IPlayer *monster = 0;
        for (PoolFactory<IPlayer>::ListType::iterator it = map.begin();
             it != map.end(); ++it) {
            if (it->second == false)
            {
                monster = it->first;
                it->second = true;
                break;
            }
        }

        TinyMonster *tiny = 0;

        if (!monster)
        {
            tiny = reinterpret_cast<TinyMonster*>(SingleMonsterGenerator::getInstance()->generate(MonsterGenerator::TINYMONSTER));
            map[tiny] = true;
            monster = tiny;

            AnimatedImage *a = new AnimatedImage(SingleMonsterGenerator::getInstance()->getImageOf(MonsterGenerator::TINYMONSTER));

            a->parseFile();

            tiny->setExplosionSprite(new AnimatedImage(*_explosion),
                                     _explosion->getCurrentSprite()->GetSize().x,
                                     _explosion->getCurrentSprite()->GetSize().y);

            tiny->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);
        }
        else
        {
            tiny = dynamic_cast<TinyMonster *> (monster);
            AnimatedImage *a = reinterpret_cast<AnimatedImage *> (tiny->getSprite());
            a->erase();
            tiny->erase();
            tiny->resetSprites();
            tiny->spawn(Point<float>(0,0));
        }

        tiny->setScreenSize(_screenSize.width(), _screenSize.height());
        tiny->setAmplitude(200);
        tiny->setPosition(x, y);
        tiny->setOrigin(PointF(0, y));
        tiny->setNbOscillation(1);
        tiny->setSpeed(0.1);
    }
    else
    {
        Missile *missil = dynamic_cast<Missile*>(addMissil());

        missil->setScreenSize(_screenSize.width(), _screenSize.height());
        missil->setPosition(x, y);
        missil->setDirection(1.0, 0.0);
    }
}

void        Game::updateScreenSize()
{
    _humanPlayer->setScreenSize(_screenSize.width(), _screenSize.height());
    _mapScroll.setScreenHeight(_screenSize.height());
    _mapScroll.setScreenWidth(_screenSize.width());

    for (std::map<UInt16, IPlayer*>::iterator it = _players.begin(); it != _players.end(); ++it)
        (*it).second->setScreenSize(_screenSize.width(), _screenSize.height());

    PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();
    for (PoolFactory<IPlayer>::ListType::iterator it = map.begin(); it != map.end(); ++it)
        (*it).first->setScreenSize(_screenSize.width(), _screenSize.height());

    for (std::map<UInt16, IPlayer*>::iterator it = _missils.begin(); it != _missils.end(); ++it)
        (*it).second->setScreenSize(_screenSize.width(), _screenSize.height());
}

bool        pixelPerfectCollision(AnimatedImage *a1, AnimatedImage *a2,
                                  Object<float> *p1, Object<float> *p2) {

    if (!a1 || !a2) return (true);
    sf::Sprite *s1 = a1->getCurrentSprite();
    if (!s1)
        s1 = &(a1->getSprite());
    sf::Sprite *s2 = a2->getCurrentSprite();
    if (!s2)
        s2 = &(a2->getSprite());
    unsigned int dx = p2->getX() - p1->getX();
    unsigned int dy = p2->getY() - p1->getY();

    for (unsigned int i = 0; i < s1->GetSize().x; ++i)
        for (unsigned int j = 0; j < s1->GetSize().y; ++j) {
            sf::Color c1 = s1->GetPixel(i, j);
            if (i - dx > 0 && i - dx < s1->GetSize().x &&
                    j - dy > 0 && j - dy < s1->GetSize().y &&
                    ((int)c1.a) != 255) {
                sf::Color c2 = s2->GetPixel(i - dx, j - dy);
                LOG << ((int)c1.a) << " " << ((int)c2.a) << std::endl;
                if (((int)c2.a) != 255)
                    return (true);
            }
        }
    return (false);
}

void        Game::updateSprites(MyCanvas &app)
{
    static int call = 0;
    _scroll.scroll();
    _scroll.affBackground(&app);


    if (!_started)
    {
        _mapScroll.update(20);

        Wall *w;
        while ((w = _mapScroll.getNextWall())) {
            if (!w) continue;
            AnimatedImage *a = reinterpret_cast<AnimatedImage *> (w->getSprite());
            if (!a) continue;
            sf::Sprite &cur = a->getSprite();
            cur.SetPosition(w->getX(), w->getY());
            app.Draw(cur);
            if (!(_humanPlayer->isDead()) && w->intersectWith(*_humanPlayer) /*&&
                                                                                            pixelPerfectCollision(a, reinterpret_cast<AnimatedImage *>(_humanPlayer->getSprite()),
                                                                                                                  w, _humanPlayer)*/) {
                _humanPlayer->die();
                _humanPlayer->switchToExplosionSprite();
                _soundsManager->playSound("explosion");

                ListenServerSingleton::getInstance()->sendDead();
            }
        }
    }

    if (!_started)
    {
        call++;

        _humanPlayer->update(_cur_time.getMs() - _old_time.getMs(), _eventReceiver);
        Point<float> pos = _humanPlayer->getPosition();
        sf::Sprite *sprite = reinterpret_cast<AnimatedImage *>(_humanPlayer->getSprite())->getCurrentSprite();

        if (!_humanPlayer->isDead() && _humanPlayer->getShoot() && call % 5 == 0)
        {
            IPlayer *missil = 0;

            missil = _humanPlayer->shoot(reinterpret_cast<void*>(&addMissil));

            if (_soundsManager->getStatusOf("missil") == sf::Sound::Stopped)
                _soundsManager->playSound("missil");

            if (missil)
                ListenServerSingleton::getInstance()->sendMissilPos(missil->getX(), missil->getY());
        }
        else if (_humanPlayer->isDead() || !_humanPlayer->getShoot())
            _soundsManager->stopSound("missil");

        if (_cur_time.getMs() - _old_time_pos.getMs() > 50)
        {
            ListenServerSingleton::getInstance()->sendNewPlayerPos(_humanPlayer->getX(), _humanPlayer->getY());
            _old_time_pos.setToMsTimeOfDay();
        }

        if (sprite) {
            sprite->SetPosition(pos.getX(), pos.getY());
            app.Draw(*sprite);
        }
    }

    if (!_players.empty())
    {
        for (std::map<UInt16, IPlayer*>::iterator it = _players.begin(); it != _players.end(); ++it)
        {
            if (!it->second->isDead())
            {
                sf::Sprite *sprite = reinterpret_cast<AnimatedImage *>((*it).second->getSprite())->getCurrentSprite();

                Point<float> p = (*it).second->getPosition();
                Point<float> pOld = (*it).second->getOldPos();

                double speed = (_humanPlayer->getSpeed() * (_cur_time.getMs() - _old_time.getMs())) ;

                Point<float> vec;

                if (p == pOld)
                {
                    sprite->SetPosition(p.getX(), p.getY());
                    app.Draw(*sprite);
                    continue;
                }
                vec.setX((p.getX() - pOld.getX()));
                vec.setY((p.getY() - pOld.getY()));
                vec.normalize();


                sprite->SetPosition(vec.getX() * speed + pOld.getX(),
                                    vec.getY() * speed + pOld.getY());
                (*it).second->setOldPosition(vec.getX() * speed + pOld.getX(),
                                             vec.getY() * speed + pOld.getY());

                pOld = (*it).second->getOldPos();

                if (vec.getY() > 0) {
                    if (pOld.getY() > p.getY())
                        pOld.setY(p.getY());
                } else {
                    if (pOld.getY() < p.getY())
                        pOld.setY(p.getY());
                }
                if (vec.getX() > 0) {
                    if (pOld.getX() > p.getX())
                        pOld.setX(p.getX());
                } else {
                    if (pOld.getX() < p.getX())
                        pOld.setX(p.getX());
                }

                (*it).second->setOldPosition(pOld.getX(), pOld.getY());

                app.Draw(*sprite);
            }

        }
    }

    for (std::map<UInt16, IPlayer*>::iterator it = _missils.begin(); it != _missils.end(); ++it)
    {
        if ((*it).second && !((*it).second->isDead()) && (*it).second->getSprite())
            if ((*it).second->isAvailable() == false)
            {
                sf::Sprite *sprite = (reinterpret_cast<AnimatedImage *>((*it).second->getSprite()))->getCurrentSprite();
                Point<float> p = (*it).second->getPosition();

                (*it).second->update((Int32) _cur_time.getMs() - _old_time.getMs());
                (*it).second->setPosition(p.getX() + 10, p.getY());
                sprite->SetPosition(p.getX(), p.getY());

                app.Draw(*sprite);

                PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();

                for (PoolFactory<IPlayer>::ListType::iterator it_monster = map.begin(); it_monster != map.end();
                     ++it_monster) {
                    if (!((*it_monster).first->isDead()))
                        if ((*it_monster).first->intersectWith(*((*it).second)))
                        {
                            (*it).second->die();
                            (*it_monster).first->die();
                            (*it_monster).first->switchToExplosionSprite();
                            _soundsManager->playSound("explosion");
                        }
                }
            }
    }

    PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();

    for (PoolFactory<IPlayer>::ListType::iterator it_monster = map.begin(); it_monster != map.end();
         ++it_monster)
    {
        sf::Sprite *monsterSprite = reinterpret_cast<AnimatedImage *>((*it_monster).first->getSprite())->getCurrentSprite();

        if (monsterSprite)
        {
            (*it_monster).first->update(_cur_time.getMs() - _old_time.getMs());

            if (it_monster->first->getShoot())
                it_monster->first->shoot(reinterpret_cast<void*>(&addMonsterMissil));

            monsterSprite->SetPosition((*it_monster).first->getX(), (*it_monster).first->getY());

            if (!(_humanPlayer->isDead()) && _humanPlayer->intersectWith(*((*it_monster).first)))
            {
                (*it_monster).first->die();
                (*it_monster).first->switchToExplosionSprite();

                _humanPlayer->die();
                _humanPlayer->switchToExplosionSprite();
                _soundsManager->playSound("explosion");

                ListenServerSingleton::getInstance()->sendDead();
            }
            app.Draw(*monsterSprite);
        }
    }

    for (std::map<UInt16, IPlayer*>::iterator monsterMissil_it = _monsterMissils.begin(); monsterMissil_it != _monsterMissils.end(); ++monsterMissil_it)
    {
        if (!(monsterMissil_it->second->isOutOfScreen()) || !(monsterMissil_it->second->isDead()))
        {
            sf::Sprite *monsterMissilSprite = (reinterpret_cast<AnimatedImage *>(monsterMissil_it->second->getSprite()))->getCurrentSprite();

            monsterMissil_it->second->update(_cur_time.getMs() - _old_time.getMs());

            if (monsterMissilSprite)
            {
                if (!(_humanPlayer->isDead()) && _humanPlayer->intersectWith(*(monsterMissil_it->second)))
                {
                    monsterMissil_it->second->die();
                    _humanPlayer->die();
                    _humanPlayer->switchToExplosionSprite();
                    _soundsManager->playSound("explosion");

                    ListenServerSingleton::getInstance()->sendDead();
                }

                monsterMissilSprite->SetPosition(monsterMissil_it->second->getX(), monsterMissil_it->second->getY());
            }
            app.Draw(*monsterMissilSprite);
        }
    }

    Game::updateAnimatedSprites(app);
}

void        Game::updateAnimatedSprites(MyCanvas &app)
{
    AnimatedImage *a = reinterpret_cast<AnimatedImage *> (_humanPlayer->getSprite());
    if (a) {
        a->update(_cur_time.getMs() - _old_time.getMs());
    }

    PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();
    for (PoolFactory<IPlayer>::ListType::iterator it_monster = map.begin(); it_monster != map.end(); ++it_monster)
    {
        AnimatedImage *monsterSprite = reinterpret_cast<AnimatedImage *> ((*it_monster).first->getSprite());

        if (monsterSprite && (*it_monster).first->isDead())
            monsterSprite->update(_cur_time.getMs() - _old_time.getMs());
        if ((it_monster->first->isDead() &&
             monsterSprite && monsterSprite->isDone()) || it_monster->first->getX() < 0)
            it_monster->second = false;
    }

    for (std::map<UInt16, IPlayer*>::iterator it_player = _players.begin(); it_player != _players.end(); ++it_player)
    {
        AnimatedImage *playerSprite = reinterpret_cast<AnimatedImage *> (it_player->second->getSprite());
        sf::Sprite *playerCurrentSprite = playerSprite->getCurrentSprite();

        if (playerSprite && playerCurrentSprite && it_player->second->isDead())
        {
            playerCurrentSprite->SetPosition(it_player->second->getX(), it_player->second->getY());
            playerSprite->update(_cur_time.getMs() - _old_time.getMs());

            app.Draw(*playerCurrentSprite);
        }
    }
}

void        Game::affEndGameSprite(MyCanvas &app)
{
    sf::Image image;
    sf::Sprite sprite;

    if (image.LoadFromFile(std::string(IMAGEPATH) + "gameEnd.png") == true)
    {
        sprite.SetImage(image);

        sprite.SetPosition((_screenSize.width() / 2) - (sprite.GetSize().x / 2), (_screenSize.height() / 2) - (sprite.GetSize().y / 2));
        app.Draw(sprite);
    }
}

void        Game::eventLoop(MyCanvas &app)
{
    if (_stopLoop)
        return;

    sf::Event event;

    while (app.GetEvent(event))
        _eventReceiver.OnEvent(event);

    if (_eventReceiver.isKeyPressed(sf::Key::Escape))
    {
        std::cout << "Window Closed." << std::endl;
        ListenServerSingleton::getInstance()->closeAllSocket();
        qApp->quit();
    }

    _cur_time.setToMsTimeOfDay();

    if (!_endGame)
        Game::updateSprites(app);
    else
    {
        if (_totalTime == 0)
        {
            _soundsManager->stopSound("music");
            _soundsManager->stopSound("missil");
        }

        _totalTime += (_cur_time.getMs() - _old_time.getMs());
        if (_totalTime > 1500)
        {
            _stopLoop = true;
            _soundsManager->stopSound("music");

            emit    returnToGameList();
        }
        else
            affEndGameSprite(app);
    }

    _old_time.setToMsTimeOfDay();
}

std::map<UInt16, IPlayer *> *            backupMonsterMissil(bool save, std::map<UInt16, IPlayer *> *ptr)
{
    static std::map<UInt16, IPlayer *>  *savePtr = 0;
    if (save == true)
        savePtr = ptr;
    return (savePtr);
}

IPlayer*        addMonsterMissil()
{
    std::map<UInt16, IPlayer *> * _monsterMissils = backupMonsterMissil(false, 0);
    IPlayer *monsterMissil = 0;

    for (std::map<UInt16, IPlayer*>::iterator it = _monsterMissils->begin(); it != _monsterMissils->end(); ++it)
    {
        if ((*it).second->isOutOfScreen() || (*it).second->isDead())
        {
            (*it).second->erase();
            (*it).second->setAvailibility(true);
        }

        if ((*it).second->isAvailable())
        {
            (*it).second->setAvailibility(false);
            monsterMissil = (*it).second;
            break;
        }
    }

    if (!monsterMissil)
    {
        monsterMissil = SingleMonsterGenerator::getInstance()->generate(MonsterGenerator::MISSILE);

        AnimatedImage *a = new AnimatedImage(SingleMonsterGenerator::getInstance()->getImageOf(MonsterGenerator::MISSILE));

        a->parseFile();
        a->setCurrentSprite(177);

        monsterMissil->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);

        monsterMissil->setAvailibility(false);

        (*_monsterMissils)[_monsterMissils->size()] = monsterMissil;
    }

    return (monsterMissil);
}

std::map<UInt16, IPlayer *> *            backupMissil(bool save, std::map<UInt16, IPlayer *> *ptr) {
    static std::map<UInt16, IPlayer *>  *savePtr = 0;
    if (save == true)
        savePtr = ptr;
    return (savePtr);
}

IPlayer*        addMissil()
{
    std::map<UInt16, IPlayer *> * _missils = backupMissil(false, 0);
    IPlayer *missil = 0;

    for (std::map<UInt16, IPlayer*>::iterator it = _missils->begin(); it != _missils->end(); ++it)
    {
        if ((*it).second->isOutOfScreen() || (*it).second->isDead())
        {
            (*it).second->erase();
            (*it).second->setAvailibility(true);
        }

        if ((*it).second->isAvailable())
        {
            (*it).second->setAvailibility(false);
            missil = (*it).second;
            break;
        }
    }

    if (!missil)
    {
        missil = SingleMonsterGenerator::getInstance()->generate(MonsterGenerator::MISSILE);

        AnimatedImage *a = new AnimatedImage(SingleMonsterGenerator::getInstance()->getImageOf(MonsterGenerator::MISSILE));

        a->parseFile();
        a->setCurrentSprite(130); //127

        missil->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);

        missil->setAvailibility(false);

        (*_missils)[_missils->size()] = missil;
    }

    return (missil);
}

void        Game::setScreenSize(QSize const &screenSize)
{
    _screenSize = screenSize;
    _mapScroll.setScreenHeight(_screenSize.height());
    _mapScroll.setScreenWidth(_screenSize.width());
    // TODO : put this line on another place

    _humanPlayer->setScreenSize(_screenSize.width(), _screenSize.height());

    for (std::map<UInt16, IPlayer*>::iterator it = _players.begin(); it != _players.end(); ++it)
        (*it).second->setScreenSize(_screenSize.width(), _screenSize.height());

    PoolFactory<IPlayer>::ListType &map = _monsterPool.getMapList();
    for (PoolFactory<IPlayer>::ListType::iterator it = map.begin(); it != map.end(); ++it)
        (*it).first->setScreenSize(_screenSize.width(), _screenSize.height());

    for (std::map<UInt16, IPlayer*>::iterator it = _missils.begin(); it != _missils.end(); ++it)
        (*it).second->setScreenSize(_screenSize.width(), _screenSize.height());
}

bool        Game::loadBackground(std::string const &filename)
{
    if (_background)
        delete _background;

    _background = new Image(filename);

    if (_background->hasImageLoaded())
        return (true);

    return (false);
}

Image const *Game::getBackground() const
{
    return (_background);
}

Image       *Game::getBackground()
{
    return (_background);
}

void    Game::updatePlayerPos(UInt16 id, UInt16 x, UInt16 y)
{
    if (_players.find(id) == _players.end())
    {
        HumanPlayer *player = new HumanPlayer();
        std::string fileName = "";

        if (_players.size() == 0)
            fileName = "player2.png";
        if (_players.size() == 1)
            fileName = "player3.png";
        if (_players.size() == 2)
            fileName = "player4.png";

        AnimatedImage *a = new AnimatedImage(fileName);

        a->parseFile();
        player->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);
        player->setExplosionSprite(new AnimatedImage(*_explosion),
                                   _explosion->getCurrentSprite()->GetSize().x,
                                   _explosion->getCurrentSprite()->GetSize().y);

        _players[id] = player;
    }

    if (!(_players[id]->isDead()))
    {
        _players[id]->setPositionWithoutOld(static_cast<float>(x), static_cast<float>(y));
        _players[id]->setScreenSize(_screenSize.width(), _screenSize.height());
    }
}

void        Game::drawWaitingSprite(MyCanvas &app)
{
    sf::Image image;
    sf::Sprite sprite;

    if (image.LoadFromFile(std::string(IMAGEPATH) + "waitGame.png") == true)
    {
        sprite.SetImage(image);

        sprite.SetPosition((_screenSize.width() / 2) - (sprite.GetSize().x / 2), (_screenSize.height() / 2) - (sprite.GetSize().y / 2));
        app.Draw(sprite);
    }
}

Game::~Game()
{
    if (_background)
        delete _background;
}
