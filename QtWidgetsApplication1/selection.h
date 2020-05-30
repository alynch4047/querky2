#pragma once

#include <QList>
#include <QObject>

#include "data.h"


class Selection: public QObject
{
	Q_OBJECT

public:
	const Data* selected;
	QList<Data*> checked;

	void set_selection(const Data* selection) {
		selected = selection;
		emit selectionChanged(selection);
	}

signals:
	void selectionChanged(const Data* selected);
};

