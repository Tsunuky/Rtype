/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** RtypeCore
*/

#ifndef RTYPECORE_HPP_
#define RTYPECORE_HPP_

#include "../Core/Core.hpp"
#include "../Core/ECS.hpp"
#include "ThreadPool.hpp"
#include "../Core/Enums.hpp"
#include "RtypeEnnemi.hpp"
#include <functional>
#include <ctime> 

class RtypeCore: public Igame {
public:
    RtypeCore() {
        _Player = std::make_shared<std::vector<Entity>>();
        _Wall = std::make_shared<std::vector<Entity>>();
        _PowerUp = std::make_shared<std::vector<Entity>>();
        _Projectile = std::make_shared<std::vector<Entity>>();

        _Position = std::make_shared<Storage<dot<float>>>();
        _OldPosition = std::make_shared<Storage<dot<float>>>();

        _Dead = std::make_shared<Storage<bool>>();
        _Destroyable = std::make_shared<Storage<bool>>();
        _Playable = std::make_shared<Storage<bool>>();
        _IsVisible = std::make_shared<Storage<bool>>();
        _Size = std::make_shared<Storage<int>>();
        _GameId = std::make_shared<Storage<int>>();
        _Path = std::make_shared<Storage<std::string>>();
        _TimeRemaing = std::make_shared<Storage<std::pair<int,int>>>();
        _SpeedRemaingTimeBeforeMoveAgain = std::make_shared<Storage<std::tuple<float ,std::chrono::time_point<std::chrono::system_clock> ,float>>>();
    };
    virtual ~RtypeCore() = default;
    virtual void getInput(std::vector<INPUT> a) {
        _Input = a;

        for (size_t i = a.size(); i < _Player->size(); i++) {
            _Input.push_back({INPUT::NO_INPUT});
        }
    };
    virtual Object_t getObjectByNumber(int a) {
	    Object_t obj;

	    for (uint i = 0; i < _Player->size(); ++i) {
	    	if ((*_Player)[i]._id == a) {
	    		obj._type = TYPE::OBJSPRTE;
	    		obj._path = _Path->_storage[(*_Player)[i]._id];
	    		obj._Position = _Position->_storage[(*_Player)[i]._id];
	    		obj._OldPosition = _OldPosition->_storage[(*_Player)[i]._id];
	    		obj.id = (*_Player)[i]._id;
	    		obj._IsVisible = _IsVisible->_storage[(*_Player)[i]._id];
	    		obj.x = std::get<2>(_SpeedRemaingTimeBeforeMoveAgain->_storage[(*_Player)[i]._id]);
	    		return obj;
	    	}
	    }
        for (uint i = 0; i < _Wall->size(); ++i) {
	    	if ((*_Wall)[i]._id == a) {
	    		obj._type = TYPE::OBJSPRTE;
	    		obj._path = _Path->_storage[(*_Wall)[i]._id];
                obj._Position = _Position->_storage[(*_Wall)[i]._id];
	    		obj._OldPosition = _OldPosition->_storage[(*_Wall)[i]._id];
	    		obj.id = (*_Wall)[i]._id;
	    		obj._IsVisible = _IsVisible->_storage[(*_Wall)[i]._id];
	    		return obj;
	    	}
	    }
        for (uint i = 0; i < _PowerUp->size(); ++i) {
	    	if ((*_PowerUp)[i]._id == a) {
	    		obj._type = TYPE::OBJSPRTE;
                obj._Position = _Position->_storage[(*_PowerUp)[i]._id];
	    		obj._OldPosition = _OldPosition->_storage[(*_PowerUp)[i]._id];
	    		obj.id = (*_PowerUp)[i]._id;
	    		obj._IsVisible = _IsVisible->_storage[(*_PowerUp)[i]._id];;
	    		return obj;
	    	}
		}
        for (uint i = 0; i < _Projectile->size(); ++i) {
	    	if ((*_Projectile)[i]._id == a) {
	    		obj._type = TYPE::OBJSPRTE;
	    		obj._path = _Path->_storage[(*_Projectile)[i]._id];
                obj._Position = _Position->_storage[(*_Projectile)[i]._id];
	    		obj._OldPosition = _OldPosition->_storage[(*_Projectile)[i]._id];
	    		obj.id = (*_Projectile)[i]._id;
	    		obj._IsVisible = _IsVisible->_storage[(*_Projectile)[i]._id];
	    		obj.x = std::get<2>(_SpeedRemaingTimeBeforeMoveAgain->_storage[(*_Projectile)[i]._id]);
                //std::cout << obj.x << std::endl;
	    		return obj;
	    	}
		}
        return _ennemy.getObject(a);
    };
    virtual std::vector<std::vector<Entity>> getEntity(void) {
		std::vector<std::vector<Entity>> v;

		v.push_back(*_Player);
		v.push_back(*_Wall);
		v.push_back(*_PowerUp);
        v.push_back(*_Projectile);
        v.push_back(*_ennemy.getEntity());
		return v;
	}
    virtual void setNetworkClient(std::shared_ptr<RType::Network::NetworkClient> &ptr) {
        _NetworkClient = ptr;
    }
    virtual void Calcul() {};
    virtual void initGame(uint nbrPlayer) = 0;
    virtual void addEntity(ENTITY_TYPE type, std::string file, dot<float> pos) = 0;
    virtual void removeEntity(uint id) = 0;
    virtual void dump() {};
    virtual void deleteGame() = 0;
    virtual uint getNum() { return _num; };
    virtual void receivePacket(const std::vector<char> &arr, boost::asio::ip::udp::endpoint end) = 0;
    virtual std::vector<INPUT> setInput() = 0;
protected:
    EntityVecSPtr _Player;
    EntityVecSPtr _Wall;
    EntityVecSPtr _PowerUp;
    EntityVecSPtr _Projectile;

    StorageSPtr<dot<float>> _Position;
    StorageSPtr<dot<float>> _OldPosition;
    std::shared_ptr<RType::Network::NetworkClient> _NetworkClient;
    StorageSPtr<bool> _Dead;
    StorageSPtr<bool> _Destroyable;
    StorageSPtr<bool> _Playable;
    StorageSPtr<bool> _IsVisible;
    StorageSPtr<int> _Size;
    StorageSPtr<int> _GameId;
    // atacher au player
    StorageSPtr<std::string> _Path;
    StorageSPtr<std::pair<int,int>> _TimeRemaing;

    //temp avant de bouger
    StorageSPtr<std::tuple<float, std::chrono::time_point<std::chrono::system_clock> ,float>> _SpeedRemaingTimeBeforeMoveAgain;

    std::vector<INPUT> _Input;
	uint _num = 0;
    uint _nbrPlayer;
    Ennemy _ennemy;
};

class RtypeSysteme: public RtypeCore {
public:
    RtypeSysteme(void): _System_pool(2), chrono(std::bind(&Chrono::Run, std::ref(c))) {
		//_Sys.push_back(std::move(std::unique_ptr<Isystem> (new CollidingSystem(/* a faire */))));
        std::cout << "RtypeSysteme init" << '\n';
    };
    virtual ~RtypeSysteme () {
		chrono.detach();
	};
public:
    void receivePacket(const std::vector<char> &arr, boost::asio::ip::udp::endpoint end) {
        RType::Network::ServerPacket packet;
        if (packet.deserialize(arr)) {
            std::string tmp(packet._data.cbegin(), packet._data.cend());
            std::cout << "packet id:" << packet._id << " " << tmp << std::endl;
            if (packet._id == 20) {
                std::string str(packet._data.cbegin(), packet._data.cend());
                _GameId->AddComponent(_num, std::stoi(str));
                std::cout << _GameId->_storage.at(0) << std::endl;
            } if (packet._id == _GameId->_storage.at(0)) {
                std::string str(packet._data.cbegin(), packet._data.cend());
                std::string id = str.substr(0, 3);
                std:: cout << str << " " << id << "\n";
                if (id.compare("200") == 0) {
                    std::srand(std::time(nullptr));
                    int r = std::rand() % 4;
                    dot<float> p = {std::stof(str.substr(8, 3)), std::stof(str.substr(12, 3))};
                    if (r == 1)
                        _ennemy.addEnnemy("../Assets/ennemy_1.png", p, 1, std::stoi(str.substr(4, 3)));
                    if (r == 2)
                        _ennemy.addEnnemy("../Assets/ennemy_2.png", p, 1, std::stoi(str.substr(4, 3)));
                    if (r == 3)
                        _ennemy.addEnnemy("../Assets/ennemy_3.png", p, 1, std::stoi(str.substr(4, 3)));
                } if (id.compare("201") == 0) {
                    _ennemy.setPv(0, std::stoi(str.substr(4, 3)));
                    _ennemy.checkPv(std::stoi(str.substr(4, 3)));
                } if (id.compare("202") == 0) {
                    dot<float> p = {std::stof(str.substr(8, 3)), std::stof(str.substr(12, 3))};
                    _ennemy.getPosition(p, std::stoi(str.substr(4, 3)));
                }
            }
        }
    };
    
    virtual void initGame(uint nbrPlayer) override;
    bool isBorder(uint, uint);
    virtual void Calcul() {
        enum SYSTEM {COLLSYS};
        //std::cout << _Input.at(0) << std::endl;

        if (_Input.at(0) == 5) {
            std::thread tmp(&RtypeSysteme::projectile, this);
            tmp.detach();
            _Input.at(0) = NO_INPUT;
        }
        if (_Input.at(0) == 3) {
            std::string str;
            str.append("100/");
            str.append(std::to_string(_Player->at(0)._id));

            _Position->_storage.at(1).setX(_OldPosition->_storage.at(1).getX() + 5);
            _OldPosition->_storage.at(1).setX(_Position->_storage.at(1).getX());
            str.append("/");
            str.append(std::to_string(_Position->_storage.at(1).getX()));
            str.append("@");
            str.append(std::to_string(_Position->_storage.at(1).getY()));

            packet._id = _GameId->Find(0)->second;
            packet._data = std::vector<char>(str.begin(), str.end());
            _NetworkClient->send(packet.serialize());
            _Input.at(0) = NO_INPUT;
        } if (_Input.at(0) == 2) {
            std::string str;
            str.append("100/");
            str.append(std::to_string(_Player->at(0)._id));

            _Position->_storage.at(1).setY(_OldPosition->_storage.at(1).getY() - 5);
            _OldPosition->_storage.at(1).setY(_Position->_storage.at(1).getY());
            str.append("/");
            str.append(std::to_string(_Position->_storage.at(1).getX()));
            str.append("@");
            str.append(std::to_string(_Position->_storage.at(1).getY()));

            packet._id = _GameId->Find(0)->second;
            packet._data = std::vector<char>(str.begin(), str.end());
            _NetworkClient->send(packet.serialize());
            _Input.at(0) = NO_INPUT;
        } if (_Input.at(0) == 1) {
            //std::cout << "hey\n";
            std::string str;
            str.append("100/");
            str.append(std::to_string(_Player->at(0)._id));
            //std::cout << "hey1\n";

            //std::cout << "hey2\n";
            _Position->_storage.at(1).setY(_OldPosition->_storage.at(1).getY() + 5);
            _OldPosition->_storage.at(1).setY(_Position->_storage.at(1).getY());
            str.append("/");
            str.append(std::to_string(_Position->_storage.at(1).getX()));
            str.append("@");
            str.append(std::to_string(_Position->_storage.at(1).getY()));

            packet._id = _GameId->Find(0)->second;
            packet._data = std::vector<char>(str.begin(), str.end());
            _NetworkClient->send(packet.serialize());
            _Input.at(0) = NO_INPUT;
        } if (_Input.at(0) == 0) {
            std::string str;
            str.append("100/");
            str.append(std::to_string(_Player->at(0)._id));

            _Position->_storage.at(1).setX(_OldPosition->_storage.at(1).getX() - 5);
            _OldPosition->_storage.at(1).setX(_Position->_storage.at(1).getX());
            str.append("/");
            str.append(std::to_string(_Position->_storage.at(1).getX()));
            str.append("@");
            str.append(std::to_string(_Position->_storage.at(1).getY()));

            packet._id = _GameId->Find(0)->second;
            packet._data = std::vector<char>(str.begin(), str.end());
            _NetworkClient->send(packet.serialize());
            //_ennemy.addEnnemy("../Assets/ennemy_1.png", _Position->_storage.at(1), 1, _num);
            _Input.at(0) = NO_INPUT;
        }
        //_System_pool.enqueue(std::bind(&Isystem::update, std::ref(_Sys[COLLSYS]), _Input), _Input);
    };
    virtual void addEntity(ENTITY_TYPE type, std::string file, dot<float> pos) {
        if (type == WALL)
            _Wall->push_back({_num, {0, 0, 0, 0, 0}});
        if (type == PROJECTILE)
            _Projectile->push_back({_num, {0, 0, 0, 0, 0}});
        if (type == POWERUP)
            _PowerUp->push_back({_num, {0, 0, 0, 0, 0}});
        _Position->AddComponent(_num, pos);
        _OldPosition->AddComponent(_num, pos);
        _Dead->AddComponent(_num, false);
        _Playable->AddComponent(_num, false);
        _IsVisible->AddComponent(_num, true);
        _Path->AddComponent(_num, file);
        _SpeedRemaingTimeBeforeMoveAgain->AddComponent(_num, {600, std::chrono::system_clock::now(), 16});
        _num++;
    };
    virtual void removeEntity(uint id) {
        _Position->DeleteComponent(id);
        _OldPosition->DeleteComponent(id);
        _Dead->DeleteComponent(id);
        _Playable->DeleteComponent(id);
        _IsVisible->DeleteComponent(id);
        _Path->DeleteComponent(id);
        _SpeedRemaingTimeBeforeMoveAgain->DeleteComponent(id);
    };
    virtual std::vector<INPUT> setInput() {return _Input;};
    virtual void deleteGame() {
        RType::Network::ServerPacket packet;
        std::string str = std::to_string(_GameId->_storage.at(0));

        packet._id = 11;
        packet._data = std::vector<char>(str.begin(), str.end());
        _NetworkClient->send(packet.serialize());
    }
private:
    void projectile() {
        //addEntity(PROJECTILE, "../Assets/lazer.png", _Position->_storage.at(0));
        _IsVisible->Find(_Projectile->at(0)._id)->second = true;
        _Position->Find(_Projectile->at(0)._id)->second.setY(_Position->_storage.at(1).getY());
        _Position->Find(_Projectile->at(0)._id)->second.setX(0);
        // send data
        
        std::string str;
        str.append("101/");
        str.append(std::to_string(_Player->at(0)._id));

        packet._id = _GameId->Find(0)->second;
        packet._data = std::vector<char>(str.begin(), str.end());
        _NetworkClient->send(packet.serialize());

        c = Chrono(1);
        c.Run();
        _IsVisible->Find(_Projectile->at(0)._id)->second = false;
    }
private:
    ThreadPool<std::vector<INPUT>> _System_pool;
    Chrono c;
    std::vector<std::unique_ptr<Isystem>> _Sys;
    RType::Network::ServerPacket packet;
    std::thread chrono;
    std::vector<INPUT> v;
    bool tmp;
};

#endif /* !RTYPECORE_HPP_ */
