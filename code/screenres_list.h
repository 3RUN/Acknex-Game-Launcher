#ifndef _SCREENRES_LIST_H_
#define _SCREENRES_LIST_H_

// max resolution list results
#define SCREEN_RESOLUTION_MAX 199

// resolution list indexes
#define SCREEN_RESOLUTION_WIDTH 0
#define SCREEN_RESOLUTION_HEIGHT 1

// define smallest resolution to clip unnecessary ones
#define SCREEN_RESOLUTION_MIN_X 700
#define SCREEN_RESOLUTION_MIN_Y 500

typedef struct _devicemode
{
    char dmDeviceName[32];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    short dmOrientation;
    short dmPaperSize;
    short dmPaperLength;
    short dmPaperWidth;
    short dmScale;
    short dmCopies;
    short dmDefaultSource;
    short dmPrintQuality;
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    BYTE dmFormName[32];
    WORD dmLogPixels;
    DWORD dmBitsPerPel;
    DWORD dmPelsWidth;
    DWORD dmPelsHeight;
    DWORD dmDisplayFlags;
    DWORD dmDisplayFrequency;
    DWORD dmICMMethod;
    DWORD dmICMIntent;
    DWORD dmMediaType;
    DWORD dmDitherType;
    DWORD dmReserved1;
    DWORD dmReserved2;
    DWORD dmPanningWidth;
    DWORD dmPanningHeight;
} SCRMODE;

SCRMODE screen_resolution_struct;

int screen_resolution_available_list[2][SCREEN_RESOLUTION_MAX]; // list of all available resolutions for currently used PC
int screen_resolutions_total = 0;                        // total amount of resolutions available for currently used PC

// desktop resolution
var desktop_size_x = 0;        // width
var desktop_size_y = 0;        // height
int desktop_resolution_id = 0; // id of the desktop resolution

// sort list of resolutions in ascending order
void screen_resolutions_sort_ascending();

// check if given resolution was already added into the list or not
int is_screen_resolution_added(int width, int height);

// add given resolution into the list
void screen_resolution_add_to_list(int width, int height);

// find all available resolutions
void screen_resolutions_find_all();

#endif