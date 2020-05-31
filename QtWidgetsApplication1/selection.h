#pragma once

#include <QList>
#include <QObject>

#include "data.h"


class Selection: public QObject
{
	Q_OBJECT

public:
	const IAdaptable* selected;
	QList<IAdaptable*> checked;

	void set_selection(const IAdaptable* selection) {
		selected = selection;
		emit selectionChanged(selection);
	}

signals:
	void selectionChanged(const IAdaptable* selected);
};

