#include "icon.h"

#include <QMap>
#include <QIcon>
#include <QString>
#include <QDir>

constexpr char* ICONS_DIR = "C:/Users/alync/source/repos/icons";

static QMap<QString, QIcon> icons;

const QIcon& get_icon(const QString& icon_name) {
	if (!icons.contains(icon_name)) {
		QString path = QDir(QString(ICONS_DIR)).filePath(icon_name);
		icons.insert(icon_name, QIcon(path));
	}
	
	return icons[icon_name];
}