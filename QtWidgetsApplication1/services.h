#pragma once

#include <QList>

#include "data.h"
#include "selection.h"

class Services
{
	public:
	QList<IAdaptable*> all_objects;
	Selection selection;
};

extern Services services;

