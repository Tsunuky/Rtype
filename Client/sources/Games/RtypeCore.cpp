/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** RtypeCore
*/

#include "../../includes/Games/RtypeCore.hpp"

__attribute__((constructor))
void constructor(void){}

extern "C" Igame *getLib(void)
{
    Igame *games = new RtypeSysteme();
    return games;
}

__attribute__((destructor))
void destructor(void){}

void RtypeSysteme::initGame(uint nbrPlayer)
{

    std::string str = "10";
    std::string tmp;

    packet._id = 10;
    packet._data = std::vector<char>(str.begin(), str.end());
    _NetworkClient->send(packet.serialize());
    while (_GameId->_storage.size() <= 0) {
        _NetworkClient->getContext().run_one();
    }

    _nbrPlayer = nbrPlayer;
    std::cout << "cout" <<_nbrPlayer << std::endl;
    std::cout << "nbr lazer" << _num << std::endl;
    _Projectile->push_back({_num, {0, 0, 0, 0, 0}});
    _Position->AddComponent(_num, {0, 0});
    _OldPosition->AddComponent(_num, {0, 0});
    _Dead->AddComponent(_num, false);
    _Playable->AddComponent(_num, false);
    _IsVisible->AddComponent(_num, false);
    _Path->AddComponent(_num, "../Assets/lazer.png");
    _num++;
    for (; _num < _nbrPlayer + 1; _num++) {
        _Player->push_back({_num, {0, 0, 0, 0, 0}});
        _Position->AddComponent(_num, {0, 0});
        _OldPosition->AddComponent(_num, {0, 0});
        _Dead->AddComponent(_num, false);
        _Playable->AddComponent(_num, true);
        _IsVisible->AddComponent(_num, true);
        _Path->AddComponent(_num, "../Assets/sheep.png");
        _SpeedRemaingTimeBeforeMoveAgain->AddComponent(_num, {600, std::chrono::system_clock::now(), 16});
        tmp.append("10/");
        tmp.append(std::to_string(_Player->at(0)._id));
        tmp.append("/");
        tmp.append(std::to_string(_Position->_storage.at(1).getX()));
        tmp.append("@");
        tmp.append(std::to_string(_Position->_storage.at(1).getY()));

        packet._id = _GameId->Find(0)->second;
        packet._data = std::vector<char>(tmp.begin(), tmp.end());
        _NetworkClient->send(packet.serialize());
    }
}
