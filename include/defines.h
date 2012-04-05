/**
 * defines.h
 * 
 * This file contains some const variables.
 */

#ifndef DEFINES_H
#define DEFINES_H

#define VATSINATOR_VERSION	"0.1_beta1"

// where to get all the data from
#define VATSIM_STATUS_URL	"http://status.vatsim.net/status.txt"
#define AIRPORTS_DB			PREFIX "/share/vatsinator/WorldAirports.db"

// where icons are stored
#define AIRPORT_ICON		PREFIX "/share/vatsinator/airport.png"
#define PILOT_ICON			PREFIX "/share/vatsinator/plane.png"
#define TOWER_ICON			PREFIX "/share/vatsinator/tower.png"

// below/above these values user can't zoom the map
#define ZOOM_MINIMUM		3

// the range below which the mouse is in the object's
#define OBJECT_TO_MOUSE		0.03

// how to recognize unavailable metars
#define METAR_NO_AVAIL		"No METAR available"

// for these values the GL's context rendering size reprezents
// (-1.0; 1.0) orthogonal ranges for both x and y axes
#define BASE_SIZE_WIDTH		800
#define BASE_SIZE_HEIGHT	600

// Vatsim data refresh rate in msecs
#define REFRESH_RATE		180000

// text colors
#define COLOR_BACKGROUND	1.0, 1.0, 1.0, 1.0
#define PILOT_LABEL_COLOR	0.0, 0.0, 0.0, 1.0
#define AP_LABEL_COLOR		0.5, 0.5, 0.5, 1.0

#define LINES_COLOR			0.0, 0.192, 0.337, 0.8

#endif // DEFINES_H