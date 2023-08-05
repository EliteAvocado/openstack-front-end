#pragma once


/* ------------------------------------------------------------*/
					////////////////////////
					// IMPORTANT INCLUDES //
					////////////////////////
/* ------------------------------------------------------------*/

#include "FileInputOutput.h"
#include "string2wstring.h"

/* ------------------------------------------------------------*/
					///////////////////////
					// IMPORTANT GLOBALS //
					///////////////////////
/* ------------------------------------------------------------*/

#define WNDWIDTH 300
#define WNDHEIGHT 200

#define FILE_BUTTONS		"buttons.txt"
#define FILE_LABELS			"labels.txt"
#define FILE_CUR_LANGUAGE	"ressources/curlanguage.txt"
#define FILE_COMBOBOXES		"comboboxes.txt"
#define FILE_TEXTBOXES		"textboxes.txt"
#define FILE_MODALFORMS		"modalforms.txt"
#define FILE_PASSWORD		"password.txt"
#define FILE_OTHERS			"others.txt"
#define FILE_CONFIG			"config.txt"
#define FILE_REQUESTS		"requests.txt"

#define MAINFORM_FILEPATH_BASE							"ressources/mainform/"
#define NOTABBARFORM_LANGUAGE_FILEPATH_BASE				"ressources/notabbarform_language/"
#define NOTABBARFORM_LOGIN_FILEPATH_BASE				"ressources/notabbarform_login/"
#define TABPAGE_ADDITIONALFUNCTIONS_FILEPATH_BASE		"ressources/tabpage_additionalfunctions/"
#define TABPAGE_ADDITIONALFUNCTIONSSETPWD_FILEPATH_BASE	"ressources/tabpage_additionalfunctionssetpwd/"
#define TABPAGE_LINUX_FILEPATH_BASE						"ressources/tabpage_linux/"
#define TABPAGE_LINUXEXPERT_FILEPATH_BASE				"ressources/tabpage_linuxexpert/"
#define TABPAGE_WINDOWS_FILEPATH_BASE					"ressources/tabpage_windows/"
#define TABPAGE_WINDOWSEXPERT_FILEPATH_BASE				"ressources/tabpage_windowsexpert/"
#define TABPAGE_START_FILEPATH_BASE						"ressources/tabpage_start/"
#define TABPAGE_TERMINALSIMULATOR_FILEPATH_BASE			"ressources/tabpage_terminalsimulator/"
#define TABPAGE_TERMINALSIMULATORL_FILEPATH_BASE                 "ressources/tabpage_terminalsimulatorl/"
#define CONFIG_FILEPATH									"ressources/"

/* ------------------------------------------------------------*/
					//////////////////////
					// WIDGET ALIGNMENT //
					//////////////////////
/* ------------------------------------------------------------*/

#define MY_LEFT 0
#define MY_RIGHT 1
#define MY_TOP 0
#define MY_BOTTOM 1
#define MY_CENTER 2

#define MY_IN 0
#define MY_OUT 1

#define ALIGN_IN( x,y,sx,sy,va,ha,xa,ya,sxa,sya ) rectangle( ( ha == MY_LEFT ) ? ( x + xa ) : ( ( ha == MY_RIGHT ) ? ( sxa - sx - x ) : xa / 2 ),( va == MY_TOP ) ? ( y + ya ) : ( ( va == MY_BOTTOM ) ? ( sya - sy - y ) : ya / 2 ),sx,sy )
#define ALIGN_OUT( x,y,sx,sy,va,ha,xa,ya,sxa,sya ) rectangle( ( ha == MY_LEFT ) ? ( xa - sx - x ) : ( ( ha == MY_RIGHT ) ? ( xa + sxa + x ) : xa + x ),( va == MY_TOP ) ? ( ya - sy - y ) : ( ( va == MY_BOTTOM ) ? ( ya + sya + y ) : ya + y ),sx,sy )
#define ALIGN_IN_FORM( x,y,sx,sy,va,ha ) ALIGN_IN( x,y,sx,sy,va,ha,0,0,WNDWIDTH,WNDHEIGHT )
#define ALIGN_OUT_FORM( x,y,sx,sy,va,ha ) ALIGN_OUT( x,y,sx,sy,va,ha,0,0,WNDWIDTH,WNDHEIGHT )

#define ALIGN_SET( x,y,sx,sy ) __alignX = x,__alignY = y,__alignSX = sx,__alignSY = sy
#define ALIGN_SET_REC( rec ) __alignX = rec.x,__alignY = rec.y,__alignSX = rec.width,__alignSY = rec.height;

#define ALIGN( x,y,sx,sy,va,ha,rel ) ( rel == MY_IN ) ?  ALIGN_IN( x,y,sx,sy,va,ha,__alignX,__alignY,__alignSX,__alignSY ) : ALIGN_OUT( x,y,sx,sy,va,ha,__alignX,__alignY,__alignSX,__alignSY )

/* ------------------------------------------------------------*/
					////////////////////
					// FORM ALIGNMENT //
					////////////////////
/* ------------------------------------------------------------*/

#define CENTER_FORM(X,Y) rectangle( screen::desktop_size().width / ( []() -> size_t { screen screens; return screens.count(); }() * 2 ) - X / 2,( screen::desktop_size().height - Y ) / 2,X,Y )
#define CENTER_FORM_MODAL(X,Y,PARENT) rectangle( PARENT.size().width / 2 - X / 2, PARENT.size().height / 2 - Y / 2,X,Y )

/* ------------------------------------------------------------*/
					////////////////////
					// TABPAGE MACROS //
					////////////////////
/* ------------------------------------------------------------*/

#define ADD_PAGE(NAME,CLASS) m_tabBar.push_back( ( NAME ) ); m_vTabPages.push_back( std::make_shared<CLASS>( *this,this ) ); m_vTabPageDistribution.push_back( m_tabBar.length() - 1 )
#define ADD_PAGE_POST(CLASS) m_vTabPages.push_back( std::make_shared<CLASS>( *this,this ) ); m_place.field( m_tabBarDivName ).fasten( *m_vTabPages.back() ); m_vTabPages.back()->hide()

/* ------------------------------------------------------------*/
					////////////////////
					// LAZY MACROS //
					////////////////////
/* ------------------------------------------------------------*/

#define GET_CURLANGUAGE_NUM std::stoi( FIO_ReadFromFile( FILE_CUR_LANGUAGE ) )
#define GET_CURLANGUAGE_STR FIO_ReadFromFileToVector( FILE_CUR_LANGUAGE )[ 0 ]
