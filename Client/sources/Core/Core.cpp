/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Core
*/

#include "../../includes/Core/Core.hpp"

std::shared_ptr<RType::Network::NetworkClient> __NetworkClient__ = nullptr;

std::shared_ptr<RType::Network::NetworkClient> &getNetworkClient() {
    return __NetworkClient__;
};
void Core::launcher(int nbrPlayer)
{
    _gameLibrary->initGame(nbrPlayer);
    while (computeGame() != -1) {
        _GraphContainer->getLib()->draw();
    };
}

int Core::computeGame(void)
{
    std::vector<std::map<KEYS, INPUT>> _keyBoardConfig;
    _keyBoardConfig.push_back({});
    for (uint i = 0; i != 99; i++)
            _keyBoardConfig[0].insert({(KEYS)i, INPUT::NO_INPUT});
    _keyBoardConfig[0].find(KEYS::Up)->second = INPUT::UP;
    _keyBoardConfig[0].find(KEYS::Left)->second = INPUT::LEFT;
    _keyBoardConfig[0].find(KEYS::Down)->second = INPUT::DOWN;
    _keyBoardConfig[0].find(KEYS::Right)->second = INPUT::RIGHT;
    _keyBoardConfig[0].find(KEYS::Space)->second = INPUT::ATTACK;

    std::vector<INPUT> _input = _GraphContainer->getLib()->getInput(_keyBoardConfig);
    _NetworkClient->getContext().poll();
    _gameLibrary->getInput(_input);
    _gameLibrary->Calcul();
    return graphicalUpdate();
}

int Core::graphicalUpdate(void)
{
    Object_t tmp;
    std::vector<std::vector<Entity>> Entitylist = _gameLibrary->getEntity();
    std::vector<std::vector<Entity>> EnnemyList;
    std::vector<int> EntityListGraph;
    std::vector<INPUT> _input = _gameLibrary->setInput();
    

    for (auto &firstvect: Entitylist) {
        for (auto &secvect: firstvect) {
            if (!_GraphContainer->getLib()->exist(secvect._id)) {
                tmp = _gameLibrary->getObjectByNumber(secvect._id);
                _GraphContainer->getLib()->createObj(tmp);
            }
        }
    }
    for (auto &firstvect: Entitylist) {
        for (auto &secvect: firstvect) {
            _GraphContainer->getLib()->setPosition(secvect._id, _gameLibrary->getObjectByNumber(secvect._id)._Position);
            _GraphContainer->getLib()->ObjVisible(secvect._id, _gameLibrary->getObjectByNumber(secvect._id)._IsVisible);
            //_GraphContainer->getLib()->setScale(secvect._id, {2, 2});
        }
    }
    EntityListGraph = _GraphContainer->getLib()->getEntity();

    if (_GraphContainer->getLib()->eventWindow() == -1) {
        _gameLibrary->deleteGame();
        return -1;
    }
    for (auto &i: EntityListGraph) {
        if (!ExistGame(i))
            _GraphContainer->getLib()->EraseObj(i);
    }
    _GraphContainer->getLib()->displayWindow();
    return 0;
}