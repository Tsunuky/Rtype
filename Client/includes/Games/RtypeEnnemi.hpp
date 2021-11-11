/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** RtypeEnnemi
*/

#ifndef RTYPEENNEMI_HPP_
#define RTYPEENNEMI_HPP_

#include "IEnnemi.hpp"
#include "../Core/ECS.hpp"
#include "ThreadPool.hpp"
#include "../Core/Enums.hpp"
#include <functional>

class RtypeEnnemi: public IEnnemi {
    public:
        RtypeEnnemi() {
            _Ennemi = std::make_shared<std::vector<Entity>>();

            _Position = std::make_shared<Storage<dot<float>>>();
            _IsVisible = std::make_shared<Storage<bool>>();
            _Pv = std::make_shared<Storage<int>>();
            _Path = std::make_shared<Storage<std::string>>();
        };
        virtual std::shared_ptr<std::vector<Entity>> getEntity(void) {
		    return _Ennemi;
	    }
        virtual Object_t getObject(int a) {
	        Object_t obj;

            for (uint i = 0; i < _Ennemi->size(); ++i) {
	            if ((*_Ennemi)[i]._id == a) {
	        		obj._type = TYPE::OBJSPRTE;
	        		obj._path = _Path->_storage[(*_Ennemi)[i]._id];
	        		obj._Position = _Position->_storage[(*_Ennemi)[i]._id];
	        		obj.id = (*_Ennemi)[i]._id;
	        		obj._IsVisible = _IsVisible->_storage[(*_Ennemi)[i]._id];
	        		return obj;
	        	}
	        }
            return obj;
        }
        virtual void setPv(int pv, int id) = 0;
        virtual int getPv(int id) = 0;
        virtual void checkPv(int id) = 0;
        virtual void addEnnemy(std::string file, dot<float> pos, int pv, uint id) = 0;
        virtual void removeEnnemy(uint id) = 0;
        virtual void getPosition(dot<float> pos, int id) = 0;
        virtual ~RtypeEnnemi() = default;

    protected:
        EntityVecSPtr _Ennemi;
        StorageSPtr<dot<float>> _Position;
        StorageSPtr<int> _Pv;
        StorageSPtr<bool> _IsVisible;
        StorageSPtr<std::string> _Path;
};

class Ennemy: public RtypeEnnemi {
    public:
        Ennemy() = default;
        ~Ennemy() = default;
        virtual void setPv(int pv, int id) {_Pv->Find(id)->second = pv;};
        virtual int getPv(int id) {return _Pv->Find(id)->second;};
        virtual void addEnnemy(std::string file, dot<float> pos, int pv, uint id) {
            _Ennemi->push_back({id, {0, 0, 0, 0, 0}});
            _Position->AddComponent(id, pos);
            _Path->AddComponent(id, file);
            _Pv->AddComponent(id, pv);
            _IsVisible->AddComponent(id, true);
        };
        virtual void checkPv(int id) {
            if (_Pv->Find(id)->second == 0)
                _IsVisible->Find(id)->second = false;
        }
        virtual void removeEnnemy(uint id) {
            _Position->DeleteComponent(id);
            _Pv->DeleteComponent(id);
            _Path->DeleteComponent(id);
            _IsVisible->DeleteComponent(id);
        };
        virtual void getPosition(dot<float> pos, int id) {_Position->Find(id)->second = pos;};
};


#endif /* !RTYPEENNEMI_HPP_ */
