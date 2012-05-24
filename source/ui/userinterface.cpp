/*
    userinterface.cpp
    Copyright (C) 2012  Michał Garapich garrappachc@gmail.com

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

#ifndef NO_DEBUG
#include "vdebug/debugwindow.h"
#endif

#include "ui/windows/airportdetailswindow.h"
#include "ui/windows/atcdetailswindow.h"
#include "ui/windows/firdetailswindow.h"
#include "ui/windows/flightdetailswindow.h"
#include "ui/windows/flightslistwindow.h"
#include "ui/windows/metarswindow.h"
#include "ui/windows/settingswindow.h"

#include "vatsimdata/vatsimdatahandler.h"

#include "vatsinatorapplication.h"

#include "userinterface.h"
#include "ui/about.h"
#include "defines.h"

UserInterface::UserInterface(QWidget* _parent) :
		QMainWindow(_parent),
#ifndef NO_DEBUG
		__debugWindow(new DebugWindow()),
#endif
		__metarsWindow(new MetarsWindow()),
		__airportDetailsWindow(new AirportDetailsWindow()),
		__firDetailsWindow(new FirDetailsWindow()),
		__atcDetailsWindow(new ATCDetailsWindow()),
		__flightDetailsWindow(new FlightDetailsWindow()),
		__flightsListWindow(new FlightsListWindow()),
		__settingsWindow(new SettingsWindow()),
		__mother(VatsinatorApplication::GetSingleton()) {
	__setupWindow();
	__setWindowPosition();
	__restoreWindowGeometry();
	
	connect(ActionExit,	SIGNAL(triggered()),
		this,		SLOT(quit()));
	connect(ActionAbout,	SIGNAL(triggered()),
		this,		SLOT(about()));
	connect(ActionMetar,	SIGNAL(triggered()),
		__metarsWindow,	SLOT(showWindow()));
	connect(ActionRefresh,	SIGNAL(triggered()),
		&__mother,	SLOT(refreshData()));
	connect(ActionPreferences,	SIGNAL(triggered()),
		__settingsWindow,	SLOT(show()));
	connect(ActionFlightsList,	SIGNAL(triggered()),
		__flightsListWindow,	SLOT(show()));
	
	statusBarUpdate();
	
	ProgressBar->reset();	
}

UserInterface::~UserInterface() {
	hideAllWindows();
	__storeWindowGeometry();
	
	delete __airportDetailsWindow;
	delete __firDetailsWindow;
	delete __flightDetailsWindow;
	delete __flightsListWindow;
	delete __atcDetailsWindow;
	delete __settingsWindow;
	delete __metarsWindow;
	
#ifndef NO_DEBUG
	delete __debugWindow;
#endif
}

void
UserInterface::statusBarUpdate(const QString& _message) {
	StatusBox->setText(" " + _message);
}

void
UserInterface::quit() {
	VatsinatorApplication::GetSingleton().quit();
}

void
UserInterface::about() {
	QMessageBox::about(this, "About Vatsinator",
			trUtf8(ABOUT_TEXT)
	);
	statusBarUpdate();
}

void
UserInterface::showMetarsWindow() {
	__metarsWindow->show();
}

void
UserInterface::hideAllWindows() {
	if (__airportDetailsWindow->isVisible())
		__airportDetailsWindow->hide();
	
	if (__firDetailsWindow->isVisible())
		__firDetailsWindow->hide();
	
	if (__flightDetailsWindow->isVisible())
		__flightDetailsWindow->hide();
	
	if (__flightsListWindow->isVisible())
		__flightsListWindow->hide();
	
	if (__atcDetailsWindow->isVisible())
		__atcDetailsWindow->hide();
	
	if (__metarsWindow->isVisible())
		__metarsWindow->hide();
	
#ifndef NO_DEBUG
	if (__debugWindow->isVisible())
		__debugWindow->hide();
#endif
}

void
UserInterface::closeEvent(QCloseEvent* _event) {
	hideAllWindows();
	_event->accept();
}

void
UserInterface::__setupWindow() {
	setupUi(this);
	
#ifndef NO_DEBUG
	MenuHelp->addSeparator();
	
	QAction* debugAction = new QAction("Debug...", this);
	
	connect(debugAction,		SIGNAL(triggered()),
		__debugWindow,		SLOT(show()));
	
	MenuHelp->addAction(debugAction);
#endif
}

void
UserInterface::__setWindowPosition() {
	QDesktopWidget* desktop = QApplication::desktop();
	
	int screenWidth, width;
	int screenHeight, height;
	
	int x, y;
	
	QSize windowSize;
	
	screenWidth = desktop -> width();
	screenHeight = desktop -> height();
	
	windowSize = size();
	width = windowSize.width();
	height = windowSize.height();
	
	x = (screenWidth - width) / 2;
	y = (screenHeight - height) / 2;
	y -= 50;
	
	move(x, y);
}

void
UserInterface::__storeWindowGeometry() {
	QSettings settings("Vatsinator", "Vatsinator");
	
	settings.beginGroup("MainWindow");
	
	settings.setValue("geometry", saveGeometry());
	settings.setValue("savestate", saveState());
	settings.setValue("maximized", isMaximized());
	if (!isMaximized()) {
		settings.setValue("position", pos());
		settings.setValue("size", size());
	}
	
	settings.endGroup();
}

void
UserInterface::__restoreWindowGeometry() {
	QSettings settings("Vatsinator", "Vatsinator");
	
	settings.beginGroup("MainWindow");
	restoreGeometry(settings.value( "geometry", saveGeometry() ).toByteArray());
	restoreState(settings.value( "savestate", saveState() ).toByteArray());
	move(settings.value( "position", pos() ).toPoint());
	resize(settings.value( "size", size() ).toSize());
	if ( settings.value( "maximized", isMaximized() ).toBool() )
		showMaximized();
	settings.endGroup();
}
