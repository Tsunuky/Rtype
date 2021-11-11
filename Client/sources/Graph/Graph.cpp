/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#include "../../includes/Graph/LibSFML.hpp"

__attribute__((constructor))
void constructor(void){}

extern "C" IGraphic *getLib(void)
{
    IGraphic *lib = new LibSFML();
    return lib;
}

extern "C" LibContainer *getContainer(IGraphic *a)
{
	LibContainer *container = new LibContainerSFML(a);
	return container;
}

__attribute__((destructor))
void destructor(void){}