/*
    modelmatcher.cpp
    Copyright (C) 2012  Michał Garapich michal@garapich.pl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui>

#include "ui/widgets/mapwidget.h"

#include "vatsimdata/vatsimdatahandler.h"

#include "vatsinatorapplication.h"

#include "modelmatcher.h"
#include "defines.h"

ModelMatcher::ModelMatcher() {
  __modelsFiles["ZZZZ"] = "1p"; // default

  QFile modelsFile(VatsimDataHandler::getFiles()["model"]);

  if (!modelsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    VatsinatorApplication::alert(
      static_cast< QString >("File ") +
      static_cast< QString >(MODELS_DAT) +
      static_cast< QString >(" could not be opened!"));
    return;
  }

  while (!modelsFile.atEnd()) {
    QString line(modelsFile.readLine());
    line = line.simplified();

    if (line[0] == '#' || line.isEmpty())
      continue;

    auto splitted = line.split(' ');
    __modelsFiles.insert(splitted[0], splitted[1]);
  }
}

void
ModelMatcher::init() {
  QMap< QString, GLuint > pixmapsLoaded;

  pixmapsLoaded.insert("1p", MapWidget::loadImage(PIXMAPS_DIR "/1p32.png"));
  pixmapsLoaded.insert("2p", MapWidget::loadImage(PIXMAPS_DIR "/2p32.png"));
  pixmapsLoaded.insert("4p", MapWidget::loadImage(PIXMAPS_DIR "/4p32.png"));
  pixmapsLoaded.insert("2j", MapWidget::loadImage(PIXMAPS_DIR "/2j32.png"));
  pixmapsLoaded.insert("3j", MapWidget::loadImage(PIXMAPS_DIR "/3j32.png"));
  pixmapsLoaded.insert("4j", MapWidget::loadImage(PIXMAPS_DIR "/4j32.png"));
  pixmapsLoaded.insert("conc", MapWidget::loadImage(PIXMAPS_DIR "/conc32.png"));

  for (auto it = __modelsFiles.begin(); it != __modelsFiles.end(); ++it) {
    Q_ASSERT(pixmapsLoaded.find(it.value()) != pixmapsLoaded.end());
    __modelsPixmaps.insert(it.key(), pixmapsLoaded[it.value()]);
  }
}

GLuint
ModelMatcher::matchMyModel(const QString& _acft) {
  for (auto it = __modelsPixmaps.begin(); it != __modelsPixmaps.end(); ++it)
    if (_acft.contains(it.key(), Qt::CaseInsensitive))
      return it.value();

  return __modelsPixmaps["ZZZZ"];
}



