#pragma once

#include <QList>
#include <QObject>

#include "data.h"
#include "selection.h"

class Services: public QObject
{
	Q_OBJECT

	public:
	QList<IAdaptable*> all_objects;
	Selection selection;

signals:
	void data_changed();
};

extern Services services;

