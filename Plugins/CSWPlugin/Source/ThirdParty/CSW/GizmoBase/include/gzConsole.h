// *****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: gzConsole.h
// Module		: gzBase
// Description	: Class definition of console utilities
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.306
//		
// 		
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	251230	Created file										(2.12.297) 	
// AMO	251231	Added VT/ANSI API extensions + demo updates			(2.12.297)
// AMO	251231	Added English Doxygen for VT/ANSI API				(2.12.297)
// AMO	251231	Added braille drawing API							(2.12.297)
// AMO	251231	Updated braille doc (ASCII fallback)				(2.12.297)
// AMO	251231	Added force-ASCII braille API						(2.12.297)
// AMO	251231	Adjusted braille ASCII fallback scaling				(2.12.297)
// AMO	251231	Use 1 cell per subpixel in ASCII fallback			(2.12.297)
// AMO	251231	Added octant drawing API							(2.12.297)
// AMO	260101	Added per-cell color braille/octet APIs				(2.12.297)
// AMO	260126	Added progress clear API					(2.12.307)
//
// ******************************************************************************

#ifndef __GZ_CONSOLE_H__
#define __GZ_CONSOLE_H__

/*!	\file 
	\brief Console Utilities

	Platform independant output on console IO
*/

#include "gzSerialize.h"

// ------------------------ conio imp --------------------------------------------

GZ_BASE_EXPORT void gz_gotoxy(int x, int y);
GZ_BASE_EXPORT void gz_clrscr();
GZ_BASE_EXPORT void gz_putch(int c);
GZ_BASE_EXPORT int	gz_getch();
GZ_BASE_EXPORT int	gz_getche();
GZ_BASE_EXPORT int	gz_kbhit();

// ------------------ console / vt100 ---------------------------------------------------

enum gzConsoleColor
{
	GZ_CONSOLE_BLACK = 0,
	GZ_CONSOLE_RED,
	GZ_CONSOLE_GREEN,
	GZ_CONSOLE_YELLOW,
	GZ_CONSOLE_BLUE,
	GZ_CONSOLE_MAGENTA,
	GZ_CONSOLE_CYAN,
	GZ_CONSOLE_WHITE
};

enum gzConsoleAttrFlags
{
	GZ_CONSOLE_ATTR_BOLD = 1 << 0,
	GZ_CONSOLE_ATTR_DIM = 1 << 1,
	GZ_CONSOLE_ATTR_ITALIC = 1 << 2,
	GZ_CONSOLE_ATTR_UNDERLINE = 1 << 3,
	GZ_CONSOLE_ATTR_BLINK = 1 << 4,
	GZ_CONSOLE_ATTR_REVERSE = 1 << 5,
	GZ_CONSOLE_ATTR_HIDDEN = 1 << 6,
	GZ_CONSOLE_ATTR_STRIKE = 1 << 7
};

enum gzConsoleCursorShape
{
	GZ_CONSOLE_CURSOR_DEFAULT = 0,
	GZ_CONSOLE_CURSOR_BLOCK_BLINK = 1,
	GZ_CONSOLE_CURSOR_BLOCK = 2,
	GZ_CONSOLE_CURSOR_UNDERLINE_BLINK = 3,
	GZ_CONSOLE_CURSOR_UNDERLINE = 4,
	GZ_CONSOLE_CURSOR_BAR_BLINK = 5,
	GZ_CONSOLE_CURSOR_BAR = 6
};

enum gzConsoleCellColorFlags
{
	GZ_CONSOLE_CELL_COLOR_256 = 0,
	GZ_CONSOLE_CELL_COLOR_RGB = 1 << 0
};

// VT/ANSI init & capability
GZ_BASE_EXPORT gzBool gz_console_is_console();
GZ_BASE_EXPORT gzBool gz_console_is_vt_enabled();
GZ_BASE_EXPORT gzBool gz_console_enable_vt(gzBool enable = TRUE); // best-effort på Win

// Färger
//! Set 8/16 colors (ANSI). bg=-1 keeps background.
GZ_BASE_EXPORT gzVoid gz_console_set_color(gzInt32 fg, gzInt32 bg = -1, gzBool bright = FALSE);
//! Set 24-bit RGB (ANSI). br/bg/bb=-1 keeps background.
GZ_BASE_EXPORT gzVoid gz_console_set_rgb(gzInt32 fr, gzInt32 fg, gzInt32 fb,
										 gzInt32 br = -1, gzInt32 bg = -1, gzInt32 bb = -1);
//! Set 256-color index (ANSI). fg/bg in [0..255], -1 keeps as-is.
GZ_BASE_EXPORT gzVoid gz_console_set_color256(gzInt32 fg, gzInt32 bg = -1); // -1 => ändra ej

// Attribut / font / cursor / screen
//! Enable/disable text attributes (bold/underline/etc).
GZ_BASE_EXPORT gzVoid gz_console_attr(gzUInt32 flags, gzBool enable = TRUE);
//! Select alternate font (terminal-dependent).
GZ_BASE_EXPORT gzVoid gz_console_set_font(gzInt32 fontIndex); // 0=default, 1..10 => SGR 11..20 (terminal-beroende)
//! Reset style (colors/attributes).
GZ_BASE_EXPORT gzVoid gz_console_reset();

//! Clear the entire screen.
GZ_BASE_EXPORT gzVoid gz_console_clear_screen();
//! Clear the current line.
GZ_BASE_EXPORT gzVoid gz_console_clear_line();
//! Move cursor (0-based).
GZ_BASE_EXPORT gzVoid gz_console_move_to(gzInt32 x, gzInt32 y); // 0-baserat
//! Show/hide cursor.
GZ_BASE_EXPORT gzVoid gz_console_show_cursor(gzBool show);
//! Toggle alternative screen buffer.
GZ_BASE_EXPORT gzVoid gz_console_use_alt_screen(gzBool enable);
//! Set terminal title (UTF-8).
GZ_BASE_EXPORT gzVoid gz_console_set_title(const char* utf8Title);
//! Save cursor position.
GZ_BASE_EXPORT gzVoid gz_console_save_cursor();
//! Restore cursor position.
GZ_BASE_EXPORT gzVoid gz_console_restore_cursor();

//! Clear from cursor to end of screen.
GZ_BASE_EXPORT gzVoid gz_console_clear_screen_to_end();
//! Clear from cursor to start of screen.
GZ_BASE_EXPORT gzVoid gz_console_clear_screen_to_start();
//! Clear from cursor to end of line.
GZ_BASE_EXPORT gzVoid gz_console_clear_line_to_end();
//! Clear from cursor to start of line.
GZ_BASE_EXPORT gzVoid gz_console_clear_line_to_start();

//! Set scroll region (0-based). Requires VT.
GZ_BASE_EXPORT gzVoid gz_console_set_scroll_region(gzInt32 top, gzInt32 bottom); // 0-baserat
//! Reset scroll region. Requires VT.
GZ_BASE_EXPORT gzVoid gz_console_reset_scroll_region();
//! Scroll up N lines (VT).
GZ_BASE_EXPORT gzVoid gz_console_scroll_up(gzInt32 lines = 1);
//! Scroll down N lines (VT).
GZ_BASE_EXPORT gzVoid gz_console_scroll_down(gzInt32 lines = 1);

//! Set cursor shape (VT).
GZ_BASE_EXPORT gzVoid gz_console_set_cursor_shape(gzConsoleCursorShape shape);
//! Write hyperlink (OSC 8) if VT is supported, otherwise write text + URL.
GZ_BASE_EXPORT gzVoid gz_console_write_link(const char* url, const char* text);

// Grafik helpers
GZ_BASE_EXPORT gzVoid gz_console_draw_box(gzInt32 x, gzInt32 y, gzInt32 w, gzInt32 h, gzBool unicode = TRUE);
//! Draw a monochrome braille image (2x4 subpixels per cell).
/*! Data is row-major, 1 byte per pixel (0=off, nonzero=on).
	Width/height are in subpixels, not cells.
	When VT is not enabled, falls back to ASCII blocks using 1 cell per subpixel. */
GZ_BASE_EXPORT gzVoid gz_console_draw_braille(const gzUByte* data, gzInt32 width, gzInt32 height,
											  gzInt32 x, gzInt32 y, gzInt32 fg, gzInt32 bg);
//! Draw a monochrome braille image with optional ASCII fallback.
/*! If forceAscii is TRUE, ASCII blocks are used even if VT is enabled. */
GZ_BASE_EXPORT gzVoid gz_console_draw_braille_ex(const gzUByte* data, gzInt32 width, gzInt32 height,
												 gzInt32 x, gzInt32 y, gzInt32 fg, gzInt32 bg, gzBool forceAscii);
//! Draw a monochrome braille image with per-cell colors (2x4 subpixels per cell).
/*! fgColors/bgColors are per-cell arrays (size cellsX*cellsY) when using 256-color mode.
	fgRgb/bgRgb are per-cell RGB arrays (size cellsX*cellsY*3) when using RGB mode. */
GZ_BASE_EXPORT gzVoid gz_console_draw_braille_cells(const gzUByte* data, gzInt32 width, gzInt32 height,
													gzInt32 x, gzInt32 y,
													const gzUByte* fgColors, const gzUByte* bgColors,
													const gzUByte* fgRgb, const gzUByte* bgRgb,
													gzUInt32 colorFlags, gzBool forceAscii);
//! Draw a monochrome octant image (2x4 subpixels per cell) using Unicode block elements.
/*! Data is row-major, 1 byte per pixel (0=off, nonzero=on).
	Width/height are in subpixels, not cells.
	Requires VT; no ASCII fallback. */
GZ_BASE_EXPORT gzVoid gz_console_draw_octants(const gzUByte* data, gzInt32 width, gzInt32 height,
												gzInt32 x, gzInt32 y, gzInt32 fg, gzInt32 bg);
//! Draw a monochrome octant image with per-cell colors (2x4 subpixels per cell).
/*! fgColors/bgColors are per-cell arrays (size cellsX*cellsY) when using 256-color mode.
	fgRgb/bgRgb are per-cell RGB arrays (size cellsX*cellsY*3) when using RGB mode.
	Requires VT; no ASCII fallback. */
GZ_BASE_EXPORT gzVoid gz_console_draw_octants_cells(const gzUByte* data, gzInt32 width, gzInt32 height,
													gzInt32 x, gzInt32 y,
													const gzUByte* fgColors, const gzUByte* bgColors,
													const gzUByte* fgRgb, const gzUByte* bgRgb,
													gzUInt32 colorFlags);

// Progress (0..100). Vid 100: skriver sista state och rensar raden.
GZ_BASE_EXPORT gzVoid gz_console_progress(const char* headerUtf8,
										  gzInt32 progress,				// 0..100
										  gzInt32 barFillFg = GZ_CONSOLE_GREEN,
										  gzInt32 barFillBg = -1,
										  gzBool  barFillBright = TRUE,
										  gzInt32 barEmptyFg = GZ_CONSOLE_WHITE,
										  gzInt32 barEmptyBg = -1,
										  gzBool  barEmptyBright = FALSE,
										  gzInt32 textFg = -1,			// -1 => ändra ej
										  gzInt32 textBg = -1,			// -1 => ändra ej
										  gzBool  textBright = FALSE,
										  gzInt32 width = 32);			// antal “cells” i baren

// Clear current progress line without rendering 100%
GZ_BASE_EXPORT gzVoid gz_console_clear_progress();

// Demo
GZ_BASE_EXPORT gzVoid gz_console_demo_all(gzBool waitForKey = TRUE);
GZ_BASE_EXPORT gzVoid gz_console_demo_bitmap(gzInt32 x, gzInt32 y, gzInt32 fg, gzInt32 bg);


//******************************************************************************
// Class	: gzSerializeAdapterStdIO
//									
// Purpose  : Class for Serialize data to STDIO
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class  gzSerializeAdapterStdIO : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterStdIO();

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterStdIO();

	GZ_PROPERTY_EXPORT(gzBool, LF, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool, Echo, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;
	GZ_BASE_EXPORT virtual gzBool	hasData_imp() override;
	GZ_BASE_EXPORT virtual gzUInt32 length_imp() override;
};

//! line Utilities
//! use lf=yes as we want to use \n as terminating character and use 60 sek timeout
GZ_BASE_EXPORT gzBool readLine(gzString &result,gzSerializeAdapter *adapter=gzSerializeAdapter::getURLAdapter("con:?lf=yes"),gzFloat timeOut=60);
GZ_BASE_EXPORT gzBool writeLine(const gzString& output, gzSerializeAdapter* adapter = gzSerializeAdapter::getURLAdapter("con:?lf=yes"));


#endif
