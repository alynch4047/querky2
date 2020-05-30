#pragma once

#include <QList>

#include "data.h"
#include "selection.h"

class Services
{
	public:
	QList<Data*> all_objects;
	Selection selection;
};

extern Services services;

